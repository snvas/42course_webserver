#include "Server.hpp"

Server::Server() {}

Server::Server(const ServerConfig &config) : m_config(config){
	initializeServer();
}

Server::~Server(){
	close(m_listenSocket);
	for (std::vector<struct pollfd>::iterator it = m_pollfds.begin(); it != m_pollfds.end(); ++it){
		close(it->fd);
	}
}

Server &Server::operator=(const Server &other)
{
	if (this != &other) // Verifica auto-atribuição
	{
		// Limpa os recursos do objeto atual
		close(m_listenSocket);
		for (std::vector<struct pollfd>::iterator it =
			 m_pollfds.begin();
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

bool Server::initializeServer(){
	std::cout << "Webserv running " << std::endl;

	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listenSocket < 0){
		std::cerr << "Cannot create socket." << std::endl;
		close(m_listenSocket);
		return false;
	}

	if (!setSocketToNonBlocking(m_listenSocket)){
		return false;
	}

	if (!bindSocketAndListen()){
		return false;
	}

	struct pollfd pfd = {m_listenSocket, POLLIN, 0};
	m_pollfds.push_back(pfd);
	std::cout << "Server started on port: " + m_config.server_name + ":" + numberToString(m_config.listen_port) << std::endl;

	return true;
}

bool Server::setSocketToNonBlocking(int socket){
	int flags = fcntl(socket, F_GETFL, 0);
	if (flags == -1){
		std::cerr << "Cannot get socket flags." << std::endl;
		return false;
	}

	flags |= O_NONBLOCK;
	if (fcntl(socket, F_SETFL, flags) == -1){
		std::cerr << "Cannot set socket to non-blocking." << std::endl;
		return false;
	}
	return true;
}

bool Server::bindSocketAndListen(){
	sockaddr_in serverAddr;
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(m_config.listen_port);

	if (bind(m_listenSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
		std::cerr << "Cannot bind to port." << std::endl;
		return false;
	}

	if (listen(m_listenSocket, 10) < 0){
		std::cerr << "Cannot listen to socket." << std::endl;
		return false;
	}
	return true;
}

void Server::run(){
	while (true){
		if (poll(&m_pollfds[0], m_pollfds.size(), -1) < 0){
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
		if (m_pollfds[i].revents & POLLIN)
		{
			if (m_pollfds[i].fd == m_listenSocket)
			{
				acceptNewConnection();
			}
			else
			{
				processClientRequest(i);
			}
		}
	}
}

void Server::acceptNewConnection()
{
	int clientSocket = accept(m_listenSocket, NULL, NULL);
	if (clientSocket > 0)
	{
		setSocketToNonBlocking(clientSocket);
		struct pollfd pfd = {clientSocket, POLLIN, 0};
		m_pollfds.push_back(pfd);
	}
}

void Server::processClientRequest(size_t i)
{
	char buffer[1024];
	ssize_t bytesRead = recv(m_pollfds[i].fd, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0)
	{
		close(m_pollfds[i].fd);
		m_pollfds.erase(m_pollfds.begin() + i);
		--i;
	}
	else
	{
		std::string requestString(buffer);
		requestString = requestString.substr(0, bytesRead);
		RequestParser parser;
		Request request = parser.parsingRequest(requestString);

		std::cout << "Method: " << request.method << std::endl;
		std::cout << "URI: " << request.uri << std::endl;
		if (!request.query.empty()){
			std::cout << "Query: " << request.query << std::endl;
		}
		std::cout << "HTTP Version: " << request.httpVersion << std::endl;
		std::cout << "Host: " << request.host << std::endl;
		if (!request.port.empty()){
			std::cout << "Port: " << request.port << std::endl;
		}
		if (!request.content_lenght.empty()){
			std::cout << "Content-Lenght: " << request.content_lenght << std::endl;
		}
		if (!request.content_type.empty()){
			std::cout << "Content-Type: " << request.content_type << std::endl;
		}
		if (!request.user_agent.empty()){
			std::cout << "User-Agent: " << request.user_agent << std::endl;
		}
		if (!request.authorization.empty()){
			std::cout << "Authorization: " << request.authorization << std::endl;
		}
		if (!request.accept.empty()){
			std::cout << "Accept: " << request.accept << std::endl;
		}
		if (!request.cgi_path.empty()){
			std::cout << "CGI Path: " << request.cgi_path << std::endl;
		}
		if (!request.body.empty()){
			std::cout << "Body:\n " << request.body << std::endl;
		}

		ResponseHandler handler(request);
		std::string response = handler.getResponse();
		std::cout << "\n\nresponse: \n" << response << std::endl;
		send(m_pollfds[i].fd, response.c_str(), response.length(), 0);

		// TODO: verificar se é necessário fazer algo com poll ao fechar o fd
		// close(m_pollfds[i].fd);
	}
}

std::string Server::numberToString(int number){
	std::ostringstream ss;
	ss <<number;
	return ss.str();
}

void Server::stop(void){
	std::cout << "Stopping Webserver" << std::endl;
	this->m_pollfds.clear();
	std::cout << "Good Bye!!" << std::endl;
}
