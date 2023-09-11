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
	// int flags = fcntl(socket, F_GETFL, 0);
	// if (flags == -1)
	// {
	// 	std::cerr << "Cannot get socket flags." << std::endl;
	// 	return false;
	// }

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
		for (size_t i = 0; i < m_pollfds.size(); ++i)
		{
			if (m_pollfds[i].revents & (POLLERR | POLLHUP))
			{
				close(m_pollfds[i].fd);
				m_pollfds.erase(m_pollfds.begin() + i);
				--i;
				continue;
			}
			handleIncomingRequest();
		}
	}
}

void Server::handleIncomingRequest()
{
	for (size_t i = 0; i < m_pollfds.size(); ++i)
	{
		int server_socket = m_pollfds[i].fd;
		if (m_pollfds[i].revents & POLLIN)
		{
			struct sockaddr_in cli_addr;
			// store the size of the client adress
			socklen_t clilen = sizeof(cli_addr);

			int clientSocket =
			    accept(server_socket, (struct sockaddr *) &cli_addr, &clilen);
			if (clientSocket < 0)
			{
				std::cerr << "Error accepting connection" << std::endl;
			}
			else
			{
				processClientRequest(clientSocket, i);
			}
		}
	}
}

// void Server::acceptNewConnection()
// {

// }

void Server::processClientRequest(int clientSocket, size_t i)
{
	std::cout << "Processing request for client at descriptor: "
	          << m_pollfds[i].fd << std::endl;
	char buffer[1024];
	ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0)
	{
		close(clientSocket);
		m_pollfds.erase(m_pollfds.begin() + i);
		--i;
		return;
	}
	else
	{
		std::cout << "Received " << bytesRead
		          << " bytes from client at descriptor: " << m_pollfds[i].fd
		          << std::endl;
		std::string requestString(buffer, bytesRead);
		RequestParser parser;
		Request request = parser.parsingRequest(requestString);

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
			std::cout << "Content-Type: " << request.content_type << std::endl;
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

		ResponseHandler handler(request, m_config[i]);
		std::string response = handler.getResponse();

		std::cout << "\n\nresponse: \n" << response << std::endl;
		send(clientSocket, response.c_str(), response.length(), 0);
		// TODO: verificar erros do send
		close(clientSocket);
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
