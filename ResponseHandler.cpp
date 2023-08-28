#include "ResponseHandler.hpp"

Response ResponseHandler::generateResponse(const Request& req){
	Response res;
	res.httpVersion = "HHTP/1.1";

	std::string content;
	if (readFile(req.uri, content)){
		res.statusCode = 200;
		res.statusMessage = "OK";
		res.body = content;

		res.headers["Content-Type"] = "text/html";
	} else {
		res.statusCode = 404;
		res.statusMessage = "Not Found";
		res.body = "<html><body><h1>404 Not Found</h1></body></html>";
		res.headers["Content-Type"] = "text/html";
	}
	std::stringstream ss;
	ss << res.body.size();
	res.headers["Content-Length"] = ss.str();
	return res;
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

