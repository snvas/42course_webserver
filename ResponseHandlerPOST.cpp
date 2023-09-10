#include "CommonLibs.hpp"
#include "ResponseHandler.hpp"

static int isFile(std::string path)
{
	std::ifstream indexFile(path.c_str());

	if (indexFile.is_open())
	{
		return true;
	}
	return false;
}

static std::string sanitizeUri(const std::string &uri)
{
	if (uri.size() > 1 && uri.at(uri.size() - 1) == '/')
	{
		return uri.substr(0, uri.size() - 1);
	}
	return uri;
}

bool isMultiPartFormData(const std::string &content_type)
{
	return content_type.find("multipart/form-data") != std::string::npos;
}

std::string getBoundary(const std::string &content_type)
{
	size_t pos = content_type.find("boundary=");
	if (pos != std::string::npos)
	{
		return content_type.substr(pos + 9);
	}
	return "";
}

void extractMultipartFormDataParts(const std::string &body,
                                   const std::string &bounday,
                                   std::vector<std::string> &parts)
{
	std::string delimiter = "--" + bounday + "\r\n";
	std::string closeDelimiter = "--" + bounday + "--";
	std::size_t pos = 0, end = 0;
	while ((pos = body.find(delimiter, pos)) != std::string::npos)
	{
		end = body.find(delimiter, pos + delimiter.size());
		if (end == std::string::npos)
		{
			end = body.find(closeDelimiter, pos + delimiter.size());
		}

		if (end == std::string::npos)
		{
			std::cerr << "Could not find the end boundary!" << std::endl;
			return;
		}
		std::string part =
		    body.substr(pos + delimiter.size(), end - pos - delimiter.size());
		parts.push_back(part);
		pos = end;
	}
}

bool createFileFromFormData(const std::string &part, const std::string &path)
{
	std::size_t headerEndPos = part.find("\r\n\r\n");
	if (headerEndPos == std::string::npos)
	{
		std::cerr << "Could not find header boundary in form data part!"
		          << std::endl;
		return false;
	}

	std::string fileContent = part.substr(headerEndPos + 4);
	std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);
	if (file.is_open())
	{
		file.write(fileContent.c_str(), fileContent.size());
		file.close();
		return true;
	}
	else
	{
		std::cerr << "Failed to open file for writing!" << std::endl;
		return false;
	}
}

void ResponseHandler::handlerPOST(void)
{
	std::cout << "Handling POST request" << std::endl;
	if (!_locationConf)
	{
		std::cerr << "Location config missing" << std::endl;
		generateErrorResponse(404);
		return;
	}

	if (hasRedirect())
	{
		std::cerr << "Redirection configured" << std::endl;
		generate301RedirectResponse(_locationConf->redirect);
		return;
	}

	std::stringstream ss;
	ss << _req.body.size();
	std::string bodySizeStr = ss.str();

	if (_req.headers["Content-Length"] != bodySizeStr)
	{
		std::cerr << "Content-Length mismatch" << std::endl;
		std::cout << "Header Content-Length: " << _req.headers["Content-Length"]
		          << std::endl;
		std::cout << "Actual Body Size: " << _req.body.size() << std::endl;
		generateErrorResponse(400);
		return;
	}

	size_t maxFileSize = _conf.client_max_body_size;

	if (_req.body.size() > maxFileSize)
	{
		generateErrorResponse(413);
		return;
	}

	std::string sanitizedPath = sanitizeUri(_req.uri);
	std::string path = getPath(sanitizedPath);

	if (isMultiPartFormData(_res.headers["Content_type"]))
	{
		std::string boundary = getBoundary(_req.headers["Content-Type"]);
		if (boundary.empty())
		{
			generateErrorResponse(400);
			return;
		}
		std::vector<std::string> parts;
		extractMultipartFormDataParts(_req.body, boundary, parts);
		for (std::vector<std::string>::const_iterator it = parts.begin();
		     it != parts.end(); ++it)
		{
			const std::string &part = *it;
			std::string filePath = "/uploads";
			if (createFileFromFormData(part, filePath))
			{
				// Handle individual file create sucess
				std::cout << "Successfully created file: " << filePath
				          << std::endl;
			}
			else
			{
				// Handle individual file create failute
				std::cerr << "Failed to create file: " << filePath << std::endl;
				generateErrorResponse(500);
				return;
			}
		}
		generateSucessResponse(201, "Created");
	}
	else
	{
		try
		{
			if (isFile(path))
			{
				// Check if appending to the file would exceed maxFilesize
				std::ofstream file(path.c_str(), std::ios::app);
				if (file.is_open())
				{
					file << _req.body;
					file.close();
					generateSucessResponse(200, "OK");
				}
				else
				{
					generateErrorResponse(500);
				}
			}
			else if (isDirectory(path))
			{
				std::string newFilePath = path + "newfile.txt";
				std::ofstream file(newFilePath.c_str());

				if (file.is_open())
				{
					file << _req.body;
					file.close();
					generateSucessResponse(201, "Created");
				}
				else
				{
					generateErrorResponse(500);
				}
			}
			else
			{
				generateErrorResponse(404);
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << "Exception occured: " + std::string(e.what())
			          << std::endl;
			generateErrorResponse(500);
		}
	}
}

void ResponseHandler::generateSucessResponse(int statusCode,
                                             const std::string &message)
{
	_res.statusCode = statusCode;
	_res.httpVersion = "HTTP/1.1";
	_res.headers["Content-Type"] = getMimeType(".html");
	std::ostringstream oss;
	oss << "<html><head><title>" << message << "</title></head><body><h1>"
	    << message << "</h1></body></html>";
	_res.body = oss.str();
}
