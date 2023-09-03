#ifndef RESPONSEHANDLER_HPP
#define RESPONSEHANDLER_HPP

#include "RequestParser.hpp"
#include "Server.hpp"
#include "StatusCode.hpp"
#include "CommonLibs.hpp"

struct Response
{
	std::string httpVersion;
	int statusCode;
	std::map<std::string, std::string> headers;
	std::string body;
};

class ResponseHandler{
	public:
		Request _req;
		ServerConfig _conf;
		Response _res;
		StatusCode _statusCode;

		ResponseHandler(const Request req, const ServerConfig config);
		void MimeType();
		std::string getResponse();
		std::string getMimeType(const std::string& fileExtension);

	private:
		std::map<std::string, std::string> _mimeTypes;
		bool readFile(const std::string&path, std::string& outContent);
		bool is_directory(const std::string& path);
		bool uri_is_location(void);
		bool hasErrors();
};

#endif