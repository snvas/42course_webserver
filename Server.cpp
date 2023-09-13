#include "Server.hpp"

Server::Server()
{
}

Server::Server(const std::vector<ServerConfig> &config) : m_config(config)
{
	std::cout << "Webserv running " << std::endl;

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
	std::cout << "Server started on port: " + m_config[index].server_name +
	                 ":" + numberToString(m_config[index].listen_port)
	          << std::endl;

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
				processClientRequest(m_pollfds[i].fd);
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
		client.clienfd = clientfd;
		client.serverIndex = serverindex;
		m_clients.push_back(client);
	}
}

void Server::processClientRequest(int clientfd)
{
	char buffer[1024];
	memset(buffer, 0, 1024);
	std::string requestString = "";

	int index;
	for (size_t i = 0; i < m_clients.size(); i++)
	{
		if (m_clients[i].clienfd == clientfd) index = i;
	}

	ssize_t bytesRead = recv(clientfd, buffer, sizeof(buffer) - 1, 0);
	while (bytesRead > 0)
	{
		requestString.append(buffer, bytesRead);

		size_t found = requestString.find("Content-Length: ");
		if (found != std::string::npos)
		{
			std::string temp = requestString.substr(found);
			found = temp.find(" ");
			temp = temp.substr(found + 1);
			int v = atoi(temp.c_str());
			if (v != 0) sleep(1);
		}
		bytesRead = recv(clientfd, buffer, sizeof(buffer) - 1, 0);
	}

	if (!requestString.empty())
	{
		RequestParser parser;
		Request request = parser.parsingRequest(requestString);

		printRequestDetails(request);

		ResponseHandler handler(request,
		                        m_config[m_clients[index].serverIndex]);
		std::string response = handler.getResponse();

		std::cout << "\n\nresponse: \n" << response << std::endl;
		send(clientfd, response.c_str(), response.length(), 0);
		// TODO: verificar erros do send
		close(clientfd);
		// TODO: remover do pollfds também
	}
}

void Server::printRequestDetails(const Request &request)
{
	std::cout << "Method: " << request.method << std::endl;
	std::cout << "URI: " << request.uri << std::endl;
	if (!request.query.empty())
	{
		std::cout << "Query: " << request.query << std::endl;
	}
	std::cout << "HTTP Version: " << request.httpVersion << std::endl;
	std::cout << "Host: " << request.host << std::endl;
	if (!request.port.empty())
	{
		std::cout << "Port: " << request.port << std::endl;
	}
	if (!request.content_length.empty())
	{
		std::cout << "Content-Lenght: " << request.content_length
			  << std::endl;
	}
	if (!request.content_type.empty())
	{
		std::cout << "Content-Type: " << request.content_type
			  << std::endl;
	}
	if (!request.user_agent.empty())
	{
		std::cout << "User-Agent: " << request.user_agent << std::endl;
	}
	if (!request.authorization.empty())
	{
		std::cout << "Authorization: " << request.authorization
			  << std::endl;
	}
	if (!request.accept.empty())
	{
		std::cout << "Accept: " << request.accept << std::endl;
	}
	if (!request.cgi_path.empty())
	{
		std::cout << "CGI Path: " << request.cgi_path << std::endl;
	}
	if (!request.body.empty())
	{
		std::cout << "Body:\n" << request.body << std::endl;
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
	std::cout << "Stopping Webserver" << std::endl;
	this->m_pollfds.clear();
	std::cout << "Good Bye!!" << std::endl;
}
