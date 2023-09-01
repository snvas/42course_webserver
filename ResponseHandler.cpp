#include "ResponseHandler.hpp"

ResponseHandler::ResponseHandler(const Request& req){
	_res.httpVersion = "HTTP/1.1 ";

	std::string content;
	if (readFile(req.uri, content)){
		_res.statusCode = 200;
		_res.statusMessage = "OK";
		_res.body = content;

		_res.headers["Content-Type"] = "text/html";
	} else {
		_res.statusCode = 404;
		_res.statusMessage = "Not Found";
		_res.body = "<html><body><h1>404 Not Found</h1></body></html>";
		_res.headers["Content-Type"] = "text/html";
	}
	std::stringstream ss;
	ss << _res.body.size();
	_res.headers["Content-Length"] = ss.str();
}

std::string ResponseHandler::getResponse() {
    std::string response;
	response.append( _res.httpVersion );
    response.append( getStatusCode(_res.statusCode) );
    response.append( "\r\n" );
    response.append( "Content-Type: " );
    response.append( _res.headers["Content-Type"] );
    response.append( "\r\n" );
    response.append( "Content-Length: " );
    response.append( _res.headers["Content-Length"] );
    response.append( "\r\n" );
    response.append( "Connection: keep-alive" );
    response.append( "\r\n\r\n" );

	return (response);
}

void ResponseHandler::MimeType()
{

	_mimeTypes[".css"] = "text/css";
	_mimeTypes[".csv"] = "text/csv";
	_mimeTypes[".doc"] = "application/msword";
	_mimeTypes[".docx"] =
	    "application/"
	    "vnd.openxmlformats-officedocument.wordprocessingml.document";
	_mimeTypes[".epub"] = "application/epub+zip";
	_mimeTypes[".gz"] = "application/gzip";
	_mimeTypes[".gif"] = "image/gif";
	_mimeTypes[".htm"] = "text/html";
	_mimeTypes[".html"] = "text/html";
	_mimeTypes[".ico"] = "image/vnd.microsoft.icon";
	_mimeTypes[".ics"] = "text/calendar";
	_mimeTypes[".jpeg"] = "image/jpeg";
	_mimeTypes[".jpg"] = "image/jpeg";
	_mimeTypes[".js"] = "text/javascript";
	_mimeTypes[".json"] = "application/json";
	_mimeTypes[".jsonld"] = "application/ld+json";
	_mimeTypes[".mp3"] = "audio/mpeg";
	_mimeTypes[".mpeg"] = "video/mpeg";
	_mimeTypes[".png"] = "image/png";
	_mimeTypes[".pdf"] = "application/pdf";
	_mimeTypes[".php"] = "application/x-httpd-php";
	_mimeTypes[".rar"] = "application/vnd.rar";
	_mimeTypes[".svg"] = "image/svg+xml";
	_mimeTypes[".txt"] = "text/plain";
}

std::string ResponseHandler::getMimeType(const std::string &fileExtension)
{
	// implementar tabela de mapeamento extensão -> MIME type
	return _mimeTypes[fileExtension];
}

bool ResponseHandler::is_directory(const std::string& path){
	struct stat s;
	if (stat(path.c_str(), &s) == 0){
		return S_ISDIR(s.st_mode);
	}
	return false;
}

bool ResponseHandler::readFile(const std::string &path, std::string &outContent)
{

	if (is_directory(path))
	{
		std::cout << path << "é um diretório!" << std::endl;
		return false;
	}
	else
	{
		std::ifstream file(path.c_str(),
				   std::ios::in | std::ios::binary);
		if (file)
		{
			outContent.assign(
			    (std::istreambuf_iterator<char>(file)),
			    std::istreambuf_iterator<char>());
			return true;
		}
		return false;
	}
}

Response ResponseHandler::generate404BadRequest(){
	Response res;

	res.httpVersion = "HHTP/1.1";
	res.statusCode = 400;
	res.statusMessage = "Bad Request";
	res.body = "<html><body><h1>400 Bad Request</h1></body></html>";
	res.headers["Content-Type"] = "text/html";
	std::stringstream ss;
	ss << res.body.size();
	res.headers["Content-Length"] = ss.str();
	return res;
}

std::string ResponseHandler::getStatusCode(int code)
{
	std::map<int, std::string> codeMap;
    codeMap[200] = "200 OK";
    codeMap[201] = "201 Created";
    codeMap[202] = "202 Accepted";
    codeMap[204] = "204 No Content";
    codeMap[300] = "300 Multiple Choice";
    codeMap[301] = "301 Moved Permanently";
    codeMap[302] = "302 Found";
    codeMap[400] = "400 Bad Request";
    codeMap[401] = "401 Unauthorized";
    codeMap[403] = "403 Forbidden";
    codeMap[404] = "404 Not Found";
    codeMap[405] = "405 Method Not Allowed";
    codeMap[409] = "409 Conflict";
    codeMap[413] = "413 Request Entity Too Large";
    codeMap[415] = "415 Unsupported Media Type";
    codeMap[500] = "500 Internal Server Error";
    codeMap[502] = "502 Bad Gateway";
    codeMap[504] = "504 Gateway Timeout";
    codeMap[505] = "505 HTTP Version Not Supported";

	return(codeMap[code]);
}
