#include "Server.hpp"

Server::Server(){}

Server::~Server(){
	close(m_listenSocket);
	for (std::vector<struct pollfd>::iterator it = m_pollfds.begin(); it != m_pollfds.end(); ++it){
		close(it->fd);
	}
}

Server &Server::operator=(const ServerConfig &src){
	(void) src;
	return (*this);
}

Server::Server(const ServerConfig &config){
	this->m_config = config;
	init();
}

bool Server::init(){
	std::cout << "Webserv running " << std::endl;

	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listenSocket < 0){
		std::cerr << "Cannot create socket." << std::endl;
		close(m_listenSocket);
		return false;
	}

	if (!setNonBlocking(m_listenSocket)){
		return false;
	}

	if (!bindAndListen()){
		return false;
	}

	struct pollfd pfd = {m_listenSocket, POLLIN, 0};
	m_pollfds.push_back(pfd);
	std::cout << "Server started on port: " + m_config.server_name + ":" + NumtoStr(m_config.listen_port) << std::endl;

	return true;
}

bool Server::setNonBlocking(int socket){
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

bool Server::bindAndListen(){
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

		for (size_t i = 0; i < m_pollfds.size(); ++i){
			if (m_pollfds[i].revents & POLLIN){
				if (m_pollfds[i].fd == m_listenSocket){
					int clientSocket = accept(m_listenSocket, NULL, NULL);
					if (clientSocket > 0){
						setNonBlocking(clientSocket);
						struct pollfd pfd = { clientSocket, POLLIN, 0};
						m_pollfds.push_back(pfd);
					}
				} else {
					char buffer[1024];
					ssize_t bytesRead = recv(m_pollfds[i].fd, buffer, sizeof(buffer), 0);
					if (bytesRead <= 0){
						close(m_pollfds[i].fd);
						m_pollfds.erase(m_pollfds.begin() + i);
						--i;
					} else{
						send(m_pollfds[i].fd, buffer, bytesRead, 0);
					}
				}
			}
		}
	}
}

std::string NumtoStr(int Num){
	std::ostringstream ss;
	ss << Num;
	return ss.str();
}

void Server::stop(void){
	std::cout << "Stopping Webserver" << std::endl;
	this->m_pollfds.clear();
	std::cout << "Good Bye!!" << std::endl;
}