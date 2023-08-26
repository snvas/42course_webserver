#ifndef SERVER_HPP
#define SERVER_HPP

#include "Webserver.hpp"
#include "CommonLibs.hpp"

class Server{
	public:
		Server();
		Server(const ServerConfig &config);
		~Server();
		Server &operator=(const ServerConfig &src);

		bool init();
		void run();
	
	private:

		ServerConfig m_config;
		int m_listenSocket;
		std::vector<pollfd> m_pollfds;

		bool setNonBlocking(int socket);
		bool bindAndListen();
};

std::string NumtoStr(int Num);
#endif