#ifndef REQUESTPARSER_HPP
#define REQUESTPARSER_HPP

#include "CommonLibs.hpp"

class Request
{
public:
	std::string method;
	std::string host;
	std::string port;
	std::string uri;
	std::string httpVersion;
	std::string body;
	std::string content_length;
	std::string content_type;
	std::string user_agent;
	std::string authorization;
	std::string accept;
	std::string query;
	std::string cgi_path;
	std::string transfer_encoding;
	std::map<std::string, std::string> headers;

	Request();
	void display();
};

class RequestParser
{
public:
	Request parsingRequest(const std::string &rawRequest);
};

#endif