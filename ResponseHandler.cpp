#include "ResponseHandler.hpp"

ResponseHandler::ResponseHandler(const Request req, const ServerConfig config)
    : _req(req), _conf(config)
{
	MimeType();
	_res.httpVersion = "HTTP/1.1 ";
	_res.statusCode = 0;
	useLocationConfig();

	if (hasErrors())
	{
		return;
	}

	if (isCGIRequest(_req.uri))
	{
		handleCGI(_conf.root + _req.uri);
	}
	else if (_req.method == "GET")
	{
		handlerGET();
	}
	else if (_req.method == "DELETE")
	{
		handlerDELETE();
	}
	else if (_req.method == "POST")
	{
		handlerPOST();
	}
}

template <typename T> static bool vectorContains(std::vector<T> vec, T target)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == target)
		{
			return true;
		}
	}
	return false;
}

void ResponseHandler::useLocationConfig()
{
	_locationConf = 0;
	std::string path;

	if (_req.uri == "/" || _req.uri == "")
	{
		path = "/";
	}
	else
	{
		path = _req.uri.substr(0, _req.uri.find("/", 1));
		if (_conf.locations.find(path) == _conf.locations.end() &&
		    path[0] == '/')
		{
			path = "/";
		}
	}

	if (_conf.locations.find(path) != _conf.locations.end())
	{
		_locationConf = &_conf.locations[path];
	}
}

bool ResponseHandler::hasErrors()
{
	// check server_name
	if (_conf.server_name != _req.host)
	{
		generateErrorResponse(400);
	}

	// check max_body_size
	else if (_conf.client_max_body_size != -1 &&
	         static_cast<int>(_req.body.size()) > _conf.client_max_body_size)
	{
		generateErrorResponse(413);
	}

	// check server allowed methods
	else if (!vectorContains(_conf.allowed_method, _req.method))
	{
		generateErrorResponse(405);
	}

	// check location configs
	else if (_locationConf != 0)
	{
		if (!_locationConf->accepted_methods.empty() &&
		    !vectorContains(_locationConf->accepted_methods, _req.method))
		{
			generateErrorResponse(405);
		}
	}

	if (_res.statusCode != 0)
	{
		return true;
	}
	return false;
}

void ResponseHandler::generateErrorResponse(int code)
{
	_res.statusCode = code;

	switch (code)
	{
	case 400:
		_res.headers["Content-Type"] = getMimeType(".html");
		_res.body = "Invalid Host \n";
		break;
	case 404:
		_res.body = "<html><body><h1>404 Not Found</h1></body></html>\n";
		_res.headers["Content-Type"] = getMimeType(".html");
		break;
	case 405:
		_res.headers["Content-Type"] = getMimeType(".html");
		_res.body = "Method not allowed \n";
		break;
	case 413:
		_res.headers["Content-Type"] = getMimeType(".html");
		_res.body = "Request body too large \n";
		break;
	case 500:
		_res.headers["Content-Type"] = getMimeType(".html");
		_res.body = "<html><body><h1>500 Internal Server "
		            "Error</h1></body></html>";
	default:
		break;
	}
	getDefaultErrorPage();
}

void ResponseHandler::getDefaultErrorPage(void)
{
	std::stringstream ss;
	ss << _res.statusCode;

	for (std::vector<ErrorPages>::iterator it =
	         _conf.default_error_page.begin();
	     it != _conf.default_error_page.end(); it++)
	{
		std::string content;
		if (it->code == ss.str())
		{
			if (readFile(_conf.root + it->file, content))
			{
				_res.body = content;
			}
			break;
		}
	}
}

std::string ResponseHandler::getResponse()
{
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
	_mimeTypes[".docx"] = "application/"
	                      "vnd.openxmlformats-officedocument.wordprocessingml."
	                      "document";
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

bool ResponseHandler::isDirectory(const std::string &path)
{
	struct stat s;
	if (stat(path.c_str(), &s) == 0)
	{
		return S_ISDIR(s.st_mode);
	}
	return false;
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
		std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
		if (file)
		{
			outContent.assign((std::istreambuf_iterator<char>(file)),
			                  std::istreambuf_iterator<char>());
			return true;
		}
		return false;
	}
}

std::string ResponseHandler::getPath(std::string uri)
{
	std::string rootDir = _conf.root;
	std::string path = rootDir + uri;

	if (path[path.length() - 1] == '/')
	{
		path.append("index.html");
	}
	return path;
}
