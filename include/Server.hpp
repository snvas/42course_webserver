#ifndef SERVER_HPP
#define SERVER_HPP

#include "CommonLibs.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "RequestParser.hpp"
#include "ResponseHandler.hpp"

class Server{
	public:
		Server();
		Server(const ServerConfig &config);
		~Server();
		Server& operator=(const Server& other);

		bool initializeServer();
		void run();
		void processClientRequest(size_t i);
		void acceptNewConnection();
		void stop();
	
	private:

		ServerConfig m_config;
		int m_listenSocket;
		std::vector<pollfd> m_pollfds;

		bool setSocketToNonBlocking(int socket);
		void handleIncomingRequest();
		bool bindSocketAndListen();
		std::string numberToString(int number);

};

#endif