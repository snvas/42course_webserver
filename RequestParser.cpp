#include "RequestParser.hpp"

Request::Request()
{
	method = "";
	host = "";
	port = "";
	uri = "";
	httpVersion = "";
	body = "";
	content_length = "";
	content_type = "";
	user_agent = "";
	authorization = "";
	accept = "";
	query = "";
	cgi_path = "";
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
			bodyStream << line << "\n";
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
				else if (headername == "Content-type")
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
