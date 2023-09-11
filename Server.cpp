#include "Server.hpp"

Server::Server()
{
}

/*Server::Server(const ServerConfig &config) : m_config(config)
{
	initializeServer();
}*/

Server::Server(const std::vector<ServerConfig> &configs)
{
    for (std::vector<ServerConfig>::const_iterator it = configs.begin(); it != configs.end(); ++it)
    {
        if (!initializeServer(*it))
        {
            std::cerr << "Failed to initialize server with config: " << it->server_name << std::endl;
        }
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

bool Server::initializeServer(const ServerConfig &config)
{
	std::cout << "Webserv running " << std::endl;

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

	if (!bindSocketAndListen(config))
	{
		return false;
	}

	struct pollfd pfd = {m_listenSocket, POLLIN, 0};
	m_pollfds.push_back(pfd);
	std::cout << "Server started on port: " + config.server_name + ":" +
	                 numberToString(config.listen_port)
	          << std::endl;

	return true;
}

bool Server::setSocketToNonBlocking(int socket)
{
	int flags = fcntl(socket, F_GETFL, 0);
	if (flags == -1)
	{
		std::cerr << "Cannot get socket flags." << std::endl;
		return false;
	}

	flags |= O_NONBLOCK;
	if (fcntl(socket, F_SETFL, flags) == -1)
	{
		std::cerr << "Cannot set socket to non-blocking." << std::endl;
		return false;
	}
	return true;
}

bool Server::bindSocketAndListen(const ServerConfig &config)
{
	sockaddr_in serverAddr;
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(config.listen_port);

	if (bind(m_listenSocket, (struct sockaddr *) &serverAddr,
	         sizeof(serverAddr)) < 0)
	{
		std::cerr << "Cannot bind to port." << std::endl;
		return false;
	}

	if (listen(m_listenSocket, 10) < 0)
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
		for (size_t i = 0; i < m_pollfds.size(); ++i){
			m_pollfds[i].revents = 0; //Limpar revents
		}
		if (poll(&m_pollfds[0], m_pollfds.size(), -1) < 0)
		{
			std::cerr << "Error on poll." << std::endl;
			break;
		}
		for (size_t i = 0; i < m_pollfds.size(); ++i){
			if (m_pollfds[i].revents & (POLLERR | POLLHUP)){
				close(m_pollfds[i].fd);
				m_pollfds.erase(m_pollfds.begin() + i);
				--i;
				continue;
			}
			handleIncomingRequest(i);
		}
	}
}

void Server::handleIncomingRequest(size_t index)
{
	if (m_pollfds[index].revents & POLLIN)
		{
			if (m_pollfds[index].fd == m_listenSocket)
			{
				acceptNewConnection();
			}
			else
			{
				processClientRequest(index);
			}
		}
}

void Server::acceptNewConnection()
{
	int clientSocket = accept(m_listenSocket, NULL, NULL);
	if (clientSocket < 0){
		perror("accept");
		return;
	}
	if (!setSocketToNonBlocking(clientSocket)){
		close(clientSocket);
		return;
	}
	struct pollfd pfd = {clientSocket, POLLIN, 0};
	m_pollfds.push_back(pfd);
}

void Server::processClientRequest(size_t i)
{
	std::cout << "Processing request for client at descriptor: " << m_pollfds[i].fd << std::endl;
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));

	////erro retorna -1
	ssize_t bytesRead = recv(m_pollfds[i].fd, buffer, sizeof(buffer) -1, 0);
	if (bytesRead < 0){
		std::cerr << "Error reading from client at descriptor: " << m_pollfds[i].fd << std::endl;
		if (errno == EAGAIN || errno == EWOULDBLOCK){
			return;
		}
		else if (errno == ENOTCONN){
			std::cerr << "Socket at descriptor: " << m_pollfds[i].fd << " is not connected." << std::endl;
			close(m_pollfds[i].fd);
			m_pollfds.erase(m_pollfds.begin() + i);
			--i;
			return;
		}
		else{
			perror("recv");
			close(m_pollfds[i].fd);
			m_pollfds.erase(m_pollfds.begin() + i);
			--i;
			return;
		}
	}
	else if (bytesRead == 0)
	{
		std::cerr << "Client at descriptor " << m_pollfds[i].fd << " closed the connection." << std::endl;
		close(m_pollfds[i].fd);
		m_pollfds.erase(m_pollfds.begin() + i);
		--i;
		return;
	}
	std::cout << "Received " << bytesRead << " bytes from client at descriptor: " << m_pollfds[i].fd << std::endl;
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

		ResponseHandler handler(request, m_config);
		std::string response = handler.getResponse();

		std::cout << "\n\nresponse: \n" << response << std::endl;
		ssize_t bytesSent = send(m_pollfds[i].fd, response.c_str(), response.length(), 0);

		if (bytesSent < 0){
			std::cerr << "Error sending to client at descriptor: " << m_pollfds[i].fd << std::endl;
			if (errno == EPIPE){
				std::cerr << "broken pipe, client might have closed the connection" << std::endl;
			} else {
				std::cout << "Sent " << bytesSent << " bytes to client at descriptor: " << m_pollfds[i].fd << std::endl;
			}
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
