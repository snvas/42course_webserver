#include "Server.hpp"

Server::Server()
{
}

Server::Server(const std::vector<ServerConfig> &config) : m_config(config)
{
	std::cout << GREEN << "Webserv running 🏃" << RESET << std::endl;

	for (int i = 0; i < (int) m_config.size(); i++)
	{
		initializeServer(i);
	}
}

Server::~Server()
{
	close(m_listenSocket);
	for (std::vector<struct pollfd>::iterator it = m_pollfds.begin();
	     it != m_pollfds.end(); ++it)
	{
		close(it->fd);
	}
}

Server &Server::operator=(const Server &other)
{
	if (this != &other) // Verifica auto-atribuição
	{
		// Limpa os recursos do objeto atual
		close(m_listenSocket);
		for (std::vector<struct pollfd>::iterator it = m_pollfds.begin();
		     it != m_pollfds.end(); ++it)
		{
			close(it->fd);
		}
		m_pollfds.clear();

		// Copia os recursos do objeto 'other'
		m_config = other.m_config;
		m_listenSocket = other.m_listenSocket;

		// Para o vetor m_pollfds, é melhor fazer uma cópia profunda,
		// para evitar problemas de propriedade compartilhada.
		for (std::vector<struct pollfd>::const_iterator it =
		         other.m_pollfds.begin();
		     it != other.m_pollfds.end(); ++it)
		{
			struct pollfd pfd;
			pfd.fd = it->fd;
			pfd.events = it->events;
			pfd.revents = it->revents;
			m_pollfds.push_back(pfd);
		}
	}
	return *this;
}

bool Server::initializeServer(int index)
{
	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listenSocket < 0)
	{
		std::cerr << "Cannot create socket." << std::endl;
		close(m_listenSocket);
		return false;
	}

	if (!setSocketToNonBlocking(m_listenSocket))
	{
		return false;
	}

	if (!bindSocketAndListen(index))
	{
		return false;
	}

	struct pollfd pfd = {m_listenSocket, POLLIN, 0};
	m_pollfds.push_back(pfd);
	m_serverSocks.push_back(m_listenSocket);
	std::cout << GREEN
	          << "Server started on port: " + m_config[index].server_name +
	                 ":" + numberToString(m_config[index].listen_port)
	          << RESET << std::endl;

	return true;
}

bool Server::setSocketToNonBlocking(int socket)
{
	int on = 1;
	int rc = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	if (rc < 0)
	{
		std::cerr << "bind() failed" << std::endl;
		close(socket);
		return false;
	}

	if (fcntl(socket, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Cannot set socket to non-blocking." << std::endl;
		return false;
	}
	return true;
}

bool Server::bindSocketAndListen(int index)
{
	sockaddr_in serverAddr;
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(m_config[index].listen_port);

	if (bind(m_listenSocket, (struct sockaddr *) &serverAddr,
	         sizeof(serverAddr)) < 0)
	{
		std::cerr << "Cannot bind to port." << std::endl;
		return false;
	}

	if (listen(m_listenSocket, SOMAXCONN) < 0)
	{
		std::cerr << "Cannot listen to socket." << std::endl;
		return false;
	}
	return true;
}

void Server::run()
{
	while (true)
	{
		if (poll((struct pollfd *) &(*m_pollfds.begin()), m_pollfds.size(),
		         -1) < 0)
		{
			std::cerr << "Error on poll." << std::endl;
			break;
		}
		handleIncomingRequest();
	}
}

void Server::handleIncomingRequest()
{
	for (size_t i = 0; i < m_pollfds.size(); ++i)
	{
		int serverfd = m_pollfds[i].fd;
		if (m_pollfds[i].revents & POLLIN)
		{
			std::vector<int>::iterator it =
			    std::find(m_serverSocks.begin(), m_serverSocks.end(), serverfd);
			if (it != m_serverSocks.end())
			{
				acceptNewConnection(it - m_serverSocks.begin());
			}
			else
			{
				ClientSocket *ptr = 0;
				for (std::vector<ClientSocket>::iterator it = m_clients.begin();
				     it != m_clients.end(); it++)
				{
					if (it->clientfd == m_pollfds[i].fd)
					{
						ptr = &(*it);
						break;
					}
				}
				processClientRequest(ptr);
			}
		}
	}
}

void Server::acceptNewConnection(int serverindex)
{
	struct sockaddr_in cli_addr;
	// store the size of the client adress
	socklen_t clilen = sizeof(cli_addr);
	int clientfd = accept(m_serverSocks[serverindex],
	                      (struct sockaddr *) &cli_addr, &clilen);
	if (clientfd < 0)
	{
		std::cerr << "Error accepting connection" << std::endl;
	}
	else
	{
		setSocketToNonBlocking(clientfd);
		struct pollfd pfd = {clientfd, POLLIN, 0};
		m_pollfds.push_back(pfd);
		ClientSocket client;
		client.clientfd = clientfd;
		client.serverIndex = serverindex;
		client.request = "";
		client.contentLength = -1;
		m_clients.push_back(client);
	}
}

bool hasEndsDelimiters(std::string buffer)
{
	size_t pos = 0;

	pos = buffer.rfind("\r\n\r\n");
	return (pos != 0);
}

template <typename T> static bool vectorContains(std::vector<T> vec, T target)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == target)
		{
			return true;
		}
	}
	return false;
}

void Server::processClientRequest(ClientSocket *clientSocket)
{
	char buffer[1024];
	memset(buffer, 0, 1024);

	ssize_t bytesRead =
	    recv(clientSocket->clientfd, buffer, sizeof(buffer) - 1, 0);

	while (bytesRead > 0)
	{
		clientSocket->request.append(buffer, bytesRead);
		size_t chunked = clientSocket->request.find("chunked");
		if (chunked != std::string::npos) break;
		if (hasEndsDelimiters(clientSocket->request))
		{
			size_t found = clientSocket->request.find("Content-Length: ");
			if (found != std::string::npos)
			{
				std::string temp = clientSocket->request.substr(found);
				found = temp.find(" ");
				temp = temp.substr(found + 1);
				int v = atoi(temp.c_str());
				clientSocket->contentLength = v;
			}
			else
			{
				clientSocket->contentLength = 0;
			}
		}
		bytesRead = recv(clientSocket->clientfd, buffer, sizeof(buffer) - 1, 0);
	}
	RequestParser parser;
	Request request = parser.parsingRequest(clientSocket->request);

	// verificar se não atingiu max_body_size
	bool maxBodySize = (int) request.body.size() >
	                   m_config[clientSocket->serverIndex].client_max_body_size;

	bool reachedBody = clientSocket->contentLength != -1 &&
	                   clientSocket->contentLength == (int) request.body.size();

	bool invalidMethod =
	    hasEndsDelimiters(clientSocket->request) &&
	    !vectorContains(m_config[clientSocket->serverIndex].allowed_method,
	                    request.method);
	if (bytesRead == 0 || maxBodySize || reachedBody || invalidMethod)
	{
		printRequestDetails(request);

		ResponseHandler handler(request, m_config[clientSocket->serverIndex]);
		std::string response = handler.getResponse();

		std::cout << "\n\nresponse: \n" << response << std::endl;
		if (send(clientSocket->clientfd, response.c_str(), response.length(),
		         0) == -1)
		{
			std::cerr << "error sending response" << std::endl;
		}
		closeClientSocket(clientSocket->clientfd);
	}
}

void Server::printRequestDetails(const Request &request)
{
	std::cout << PURPLE << "Method: " << request.method << RESET << std::endl;
	std::cout << PURPLE << "URI: " << request.uri << RESET << std::endl;
	if (!request.query.empty())
	{
		std::cout << PURPLE << "Query: " << request.query << RESET << std::endl;
	}
	std::cout << PURPLE << "HTTP Version: " << request.httpVersion << RESET
	          << std::endl;
	std::cout << PURPLE << "Host: " << request.host << RESET << std::endl;
	if (!request.port.empty())
	{
		std::cout << PURPLE << "Port: " << request.port << RESET << std::endl;
	}
	if (!request.content_length.empty())
	{
		std::cout << PURPLE << "Content-Lenght: " << request.content_length
		          << RESET << std::endl;
	}
	if (!request.content_type.empty())
	{
		std::cout << PURPLE << "Content-Type: " << request.content_type << RESET
		          << std::endl;
	}
	if (!request.user_agent.empty())
	{
		std::cout << PURPLE << "User-Agent: " << request.user_agent << RESET
		          << std::endl;
	}
	if (!request.authorization.empty())
	{
		std::cout << PURPLE << "Authorization: " << request.authorization
		          << RESET << std::endl;
	}
	if (!request.accept.empty())
	{
		std::cout << PURPLE << "Accept: " << request.accept << RESET
		          << std::endl;
	}
	if (!request.cgi_path.empty())
	{
		std::cout << PURPLE << "CGI Path: " << request.cgi_path << RESET
		          << std::endl;
	}
	if (!request.body.empty())
	{
		std::cout << PURPLE << "Body:\n" << request.body << RESET << std::endl;
	}
}

std::string Server::numberToString(int number)
{
	std::ostringstream ss;
	ss << number;
	return ss.str();
}

void Server::stop(void)
{
	std::cout << GREEN << "Stopping Webserver" << RESET << std::endl;
	this->m_pollfds.clear();
	std::cout << GREEN << "Good Bye!!" << RESET << std::endl;
}

void Server::closeClientSocket(int clientfd)
{
	close(clientfd);

	for (std::vector<ClientSocket>::iterator it = m_clients.begin();
	     it != m_clients.end(); it++)
	{
		if (it->clientfd == clientfd)
		{
			m_clients.erase(it);
			it--;
		}
	}
	for (std::vector<pollfd>::iterator it = m_pollfds.begin();
	     it != m_pollfds.end(); it++)
	{
		if (it->fd == clientfd)
		{
			m_pollfds.erase(it);
			it--;
		}
	}
}
