#include "RequestParser.hpp"

Request::Request()
{
	method = "";
	host = "";
	port = "";
	uri = "";
	httpVersion = "";
	body = "";
	content_type = "";
	user_agent = "";
	authorization = "";
	accept = "";
	query = "";
	cgi_path = "";
}

void Request::display(){
	Request req;
	std::cout << "---------------DISPLAY REQUEST-------------------" << std::endl;
	std::cout << "Method: " + req.method << std::endl;
	std::cout << "Port: " + req.port << std::endl;
	std::cout << "Host: " + req.host << std::endl;
	std::cout << "URI: " + req.uri << std::endl;
	std::cout << "Version: " + req.httpVersion << std::endl;
	if (req.content_type != "")
		std::cout << "Content-Type: " + req.content_type << std::endl;
	if (req.user_agent != "")
		std::cout << "User-Agent: " + req.user_agent << std::endl;
	if (req.authorization != "")
		std::cout << "Authorization: " + req.authorization << std::endl;
	if (req.query != "")
		std::cout << "Query:" + req.query << std::endl;
	if (req.cgi_path != "")
		std::cout << "CGI Path:" + req.cgi_path << std::endl;
	if (req.body != "")
		std::cout << "Body:" + req.body << std::endl;
}

Request RequestParser::parsingRequest(const std::string &rawRequest)
{
	Request req;
	std::stringstream requestStream(rawRequest);
	std::string line;

	if (std::getline(requestStream, line))
	{
		std::istringstream lineStream(line);
		lineStream >> req.method >> req.uri >> req.httpVersion;

		size_t position = req.uri.find("?");
		if (position != std::string::npos)
		{
			req.query = req.uri.substr(position + 1);
			req.uri = req.uri.substr(0, position);
		}
	}

	std::ostringstream bodyStream;

	bool readingBody = false;
	while (std::getline(requestStream, line))
	{
		if (readingBody)
		{
			bodyStream << line;
			if (!requestStream.eof())
			{
				bodyStream << "\n";
			}
		}
		else if (line == "\r" || line.empty())
		{
			readingBody = true;
		}
		else
		{
			std::size_t delimiterPos = line.find(": ");
			if (delimiterPos != std::string::npos)
			{
				std::string headername = line.substr(0, delimiterPos);
				std::string headerValue = line.substr(
				    delimiterPos + 2, line.length() - delimiterPos - 2 - 1);
				// -1 para remover o '\r'

				if (headername == "Host")
				{
					size_t portPos = headerValue.find(":");
					if (portPos != std::string::npos)
					{
						req.host = headerValue.substr(0, portPos);
						req.port = headerValue.substr(portPos + 1);
					}
					else
					{
						req.host = headerValue;
						req.port = "80";
					}
				}
				else if (headername == "Content-Length")
				{
					req.content_length = headerValue;
				}
				else if (headername == "Content-Type")
				{
					req.content_type = headerValue;
				}
				else if (headername == "User-Agent")
				{
					req.user_agent = headerValue;
				}
				else if (headername == "Authorization")
				{
					req.authorization = headerValue;
				}
				else if (headername == "Accept")
				{
					req.accept = headerValue;
				}
				else if (headername == "Cgi")
				{
					req.cgi_path = headerValue;
				}
			}
		}
	}
	req.body = bodyStream.str();
	return req;
}

