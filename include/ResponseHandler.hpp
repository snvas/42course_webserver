#ifndef RESPONSEHANDLER_HPP
#define RESPONSEHANDLER_HPP

#include "RequestParser.hpp"
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
		Response _res;

		ResponseHandler(const Request& req);
		std::string getResponse();

		Response generate404BadRequest();
		void MimeType();
		std::string getMimeType(const std::string& fileExtension);

	private:
		std::map<std::string, std::string> _mimeTypes;
		bool readFile(const std::string&path, std::string& outContent);
		bool is_directory(const std::string& path);
		std::string getStatusCode(int code);
};

#endif