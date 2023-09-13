#ifndef SERVER_HPP
#define SERVER_HPP

#include "CommonLibs.hpp"
#include "Parser.hpp"
#include "RequestParser.hpp"
#include "ResponseHandler.hpp"
#include "Server.hpp"
#include "StatusCode.hpp"

struct ClientSocket
{
	int clienfd;
	int serverIndex;
};

class Server
{
public:
	Server();
	Server(const std::vector<ServerConfig> &config);
	~Server();
	Server &operator=(const Server &other);

	bool initializeServer(int index);
	void run();
	void processClientRequest(int clientfd);
	void acceptNewConnection(int serverSocket);
	void stop();

private:
	std::vector<ServerConfig> m_config;
	int m_listenSocket;
	std::vector<pollfd> m_pollfds;
	std::vector<int> m_serverSocks;
	std::vector<ClientSocket> m_clients;

	bool setSocketToNonBlocking(int socket);
	void handleIncomingRequest();
	bool bindSocketAndListen(int index);
	std::string numberToString(int number);
	void printRequestDetails(const Request &request);
	Server(const Server &other);
};

#endif