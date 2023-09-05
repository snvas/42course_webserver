#include "ResponseHandler.hpp"

ResponseHandler::ResponseHandler(const Request req, const ServerConfig config):
	_req(req), _conf(config) {

	_res.httpVersion = "HTTP/1.1 ";
	_res.statusCode = 0;

	if(hasErrors()) {
		return;
	}

	if (_req.method == "DELETE"){
		handlerDELETE(_req);
		return;
	}

	if (isCGIRequest(_req.uri)){
		_res = handleCGI(_req, getCgiPathFromUri(_req.uri));
	}

	// TODO: lidar com "index doesnotexist hello.html"
	std::string content;
	if (readFile(req.uri, content)){
		_res.statusCode = 200;
		_res.body = content;

		_res.headers["Content-Type"] = "text/html";
	} else {
		_res.statusCode = 404;
		_res.body = "<html><body><h1>404 Not Found</h1></body></html>\n";
		_res.headers["Content-Type"] = "text/html";
		// TODO: Procurar default error page, se existir
	}
	// ??? autoindex precisa ser veririfcado de acordo com método?
}

template<typename T>
static bool vectorContains(std::vector<T> vec, T target) {
	for (size_t i = 0; i < vec.size(); i++) {
		if(vec[i] == target) {
			return true;
		}
	}
	return false;
}

bool ResponseHandler::hasErrors() {
	// check server_name
	if (_conf.server_name != _req.host) { 
		_res.statusCode = 400;
		_res.headers["Content-Type"] = "text/html";
		_res.body = "Invalid Host \n";
	}

	// check max_body_size
	else if (_conf.client_max_body_size != -1 &&
		 static_cast<int>(_req.body.size()) > _conf.client_max_body_size) {
		_res.statusCode = 413;
		_res.headers["Content-Type"] = "text/html";
		_res.body = "Request body too large \n";
	}

	// check server allowed methods
	else if (!vectorContains(_conf.allowed_method, _req.method)) {
		_res.statusCode = 405;
		_res.headers["Content-Type"] = "text/html";
		_res.body = "Method not allowed \n";
	}

	// check location configs
	else if (uriIsLocation()) {
		if (!vectorContains(_conf.locations[_req.uri].accepted_methods, _req.method)) {
			_res.statusCode = 405;
			_res.headers["Content-Type"] = "text/html";
			_res.body = "Method not allowed \n";
		}
	}

	if (_res.statusCode != 0) {
		// TODO: Procurar default error page, se existir
		return true;
	}
	return false;
}

std::string ResponseHandler::getResponse() {
    std::string response;
	response.append(_res.httpVersion);
    response.append(_statusCode.getStatusCode(_res.statusCode));
    response.append("\r\n");
    response.append("Content-Type: ");
    response.append(_res.headers["Content-Type"]);
    response.append("\r\n");
    response.append("Content-Length: ");
	std::stringstream ss;
	ss << _res.body.size();
    response.append(ss.str());
    response.append("\r\n");
    response.append("Connection: keep-alive");
    response.append("\r\n\r\n");

	response.append(_res.body);

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

bool ResponseHandler::isDirectory(const std::string& path){
	struct stat s;
	if (stat(path.c_str(), &s) == 0){
		return S_ISDIR(s.st_mode);
	}
	return false;
}

bool ResponseHandler::uriIsLocation(void) {
	if(_conf.locations.find(_req.uri) == _conf.locations.end()) {
		return false;
	}
	return true;
}

bool ResponseHandler::readFile(const std::string &path, std::string &outContent)
{

	if (isDirectory(path))
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
