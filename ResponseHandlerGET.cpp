#include "ResponseHandler.hpp"
#include <dirent.h>
#include <sys/types.h>

static std::string sanitizeUri(const std::string &uri)
{
	if (uri.size() > 1 && uri.at(uri.size() - 1) == '/')
	{
		return uri.substr(0, uri.size() - 1);
	}
	return uri;
}

static int isFile(std::string path)
{
	struct stat s;
	if (stat(path.c_str(), &s) == 0)
	{
		if (s.st_mode & S_IFREG)
		{
			return true;
		}
	}
	return false;
}
static int __attribute__((unused)) isDirectory(std::string path)
{
	DIR *dir = opendir(path.c_str());
	if (dir)
	{
		closedir(dir);
		return true;
	}
	return false;
}

static std::string getFileExtension(std::string path)
{
	return path.substr(path.find_last_of(".") + 1);
}

void ResponseHandler::handlerGET(void)
{
	if (hasRedirect())
	{
		generate301RedirectResponse(_locationConf->redirect);
		return;
	}

	std::string sanitizedUri = sanitizeUri(_req.uri);

	// correcting segmentation fault at this line
	if (_locationConf != 0 && !_locationConf->default_file.empty() &&
	    (isDirectory(getPath(sanitizedUri)) || sanitizedUri == "/"))
	{
		std::string path = getPath(sanitizedUri);
		if (isFile(getPath(sanitizedUri + "/" + _locationConf->default_file)))
		{
			generateResponseFromFile(
			    getPath(sanitizedUri + "/" + _locationConf->default_file));
		}
		else
		{
			generateErrorResponse(404);
		}
		return;
	}

	if (isDirectory(_conf.root + _req.uri))
	{
		if (isFile(getPath(_req.uri)))
		{
			generateResponseFromFile(getPath(_req.uri));
		}
		else if (_locationConf != 0 && _locationConf->directory_listing == "on")
		{
			generateDirectoryListining(getPath(_req.uri));
		}
		else
		{
			generateErrorResponse(404);
		}
	}
	else if (isFile(getPath(_req.uri)))
	{
		generateResponseFromFile(getPath(_req.uri));
		_res.headers["Content-Type"] =
		    getMimeType("." + getFileExtension(getPath(_req.uri)));
	}
	else
	{
		generateErrorResponse(404);
	}
}

bool ResponseHandler::hasRedirect(void)
{
	if (!_locationConf) return false;

	if (!_locationConf->redirect.empty())
	{
		return true;
	}
	return false;
}

void ResponseHandler::generate301RedirectResponse(std::string location)
{
	_res.statusCode = 301;
	_res.headers["Content-Type"] = getMimeType(".html");
	_res.body = "<html><head><title>301 Moved "
	            "Permanently</title><script>window.location.replace('" +
	            location + "');</script></head></html>";
}


std::string readAllFile(std::istream &in)
{
    std::string ret;
    char buffer[4096];
    while (in.read(buffer, sizeof(buffer)))
        ret.append(buffer, sizeof(buffer));
    ret.append(buffer, in.gcount());
    return ret;
}

void ResponseHandler::generateResponseFromFile(std::string path)
{
	std::ifstream file(path.c_str());

	_res.statusCode = 200;
	_res.headers["Content-Type"] = getMimeType(".html");

	if (file.is_open())
	{
		_res.body = readAllFile(file);
		file.close();
	}
}

void ResponseHandler::generateDirectoryListining(std::string path)
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(path.c_str())) != NULL)
	{
		_res.statusCode = 200;
		_res.httpVersion = "HTTP/1.1 ";
		_res.headers["Content-Type"] = getMimeType(".html");
		_res.body.append("<html><head><title>Index of " + path +
		                 "</title></head>"
		                 "<body><h1>Index of " +
		                 path + "</h1>");
		while ((ent = readdir(dir)) != NULL)
		{
			std::string name = ent->d_name;
			if (name != "." && name != "..")
			{
				_res.body.append("<a href=\"" + _req.uri + "/" + name + "\">" +
				                 name + "</a><br>");
			}
		}
		_res.body.append("</body></html>");
		closedir(dir);
	}
	else
	{
		generateErrorResponse(404);
	}
}
