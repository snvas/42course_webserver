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
	int clientfd;
	int serverIndex;
	size_t bytesRead;
	std::string request;
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
	void sendClientResponse(ClientSocket *clientSocket);
	void recieveClientRequest(ClientSocket *clientSocket);
	void acceptNewConnection(int serverSocket);
	void stop();

private:
	std::vector<ServerConfig> m_config;
	int m_listenSocket;
	std::vector<pollfd> m_pollfds;
	std::vector<int> m_serverSocks;
	std::vector<ClientSocket> m_clients;
	bool setSocketToNonBlocking(int socket);
	void handleIncomingRequest(pollfd *pfd);
	void handleOutgoingResponse(pollfd *pfd);
	bool bindSocketAndListen(int index);
	std::string numberToString(int number);
	void printRequestDetails(const Request &request);
	void closeClientSocket(int clientfd);
	Server(const Server &other);
};

#endif