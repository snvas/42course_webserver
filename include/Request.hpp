#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "CommonLibs.hpp"
#include "Webserver.hpp"

struct Request
{
	std::string method;
	std::string host;
	std::string port;
	std::string uri;
	std::string httpVersion;
	std::string body;
	std::string content_lenght;
	std::string content_type;
	std::string user_agent;
	std::string authorization;
	std::string accept;
	std::string query;
	std::string cgi_path;
	std::map<std::string, std::string> headers;

	Request();
};

class RequestParser
{
      public:
		Request parsingRequest(const std::string &rawRequest);
};

#endif