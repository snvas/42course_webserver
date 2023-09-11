#ifndef SERVER_HPP
#define SERVER_HPP

#include "CommonLibs.hpp"
#include "Parser.hpp"
#include "RequestParser.hpp"
#include "ResponseHandler.hpp"
#include "Server.hpp"
#include "StatusCode.hpp"

class Server
{
public:
	Server();
	~Server();
	Server(const std::vector<ServerConfig> &configs);
	bool initializeServer(const ServerConfig &config);
	void run();
	void processClientRequest(size_t i);
	void acceptNewConnection();
	void stop();

private:
	ServerConfig m_config;
	int m_listenSocket;
	std::vector<pollfd> m_pollfds;

	bool setSocketToNonBlocking(int socket);
	void handleIncomingRequest(size_t i);
	bool bindSocketAndListen(const ServerConfig &config);
	std::string numberToString(int number);
	Server(const Server &other);
	Server &operator=(const Server &other);
};

#endif