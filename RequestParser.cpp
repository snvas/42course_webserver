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
	std::cout << PURPLE << "---------------DISPLAY REQUEST-------------------" << RESET << std::endl;
	std::cout << PURPLE << "Method: " + req.method << RESET << std::endl;
	std::cout << PURPLE << "Port: " + req.port << RESET << std::endl;
	std::cout << PURPLE << "Host: " + req.host << RESET << std::endl;
	std::cout << PURPLE << "URI: " + req.uri << RESET << std::endl;
	std::cout << PURPLE << "Version: " + req.httpVersion << RESET << std::endl;
	if (req.content_type != "")
		std::cout << PURPLE << "Content-Type: " + req.content_type << RESET << std::endl;
	if (req.user_agent != "")
		std::cout << PURPLE << "User-Agent: " + req.user_agent << RESET << std::endl;
	if (req.authorization != "")
		std::cout << PURPLE << "Authorization: " + req.authorization << RESET << std::endl;
	if (req.query != "")
		std::cout << PURPLE << "Query:" + req.query << RESET << std::endl;
	if (req.cgi_path != "")
		std::cout << PURPLE << "CGI Path:" + req.cgi_path << RESET << std::endl;
	if (req.body != "")
		std::cout << PURPLE << "Body:" + req.body << RESET << std::endl;
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
				else if (headername == "Transfer-Encoding")
				{
					req.transfer_encoding = headerValue;
				}
			}
		}
	}
	req.body = bodyStream.str();
	return req;
}

