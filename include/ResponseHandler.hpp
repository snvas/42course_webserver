#ifndef RESPONSEHANDLER_HPP
#define RESPONSEHANDLER_HPP

#include "CommonLibs.hpp"
#include "RequestParser.hpp"
#include "Server.hpp"
#include "StatusCode.hpp"

struct Response
{
	std::string httpVersion;
	int statusCode;
	std::map<std::string, std::string> headers;
	std::string body;
};

class ResponseHandler
{
public:
	ResponseHandler(const Request req, const ServerConfig config);
	std::string getResponse();
	void handlerDELETE(const Request &req);
	
private:
	// Verificar erros nas solicitações e configurações
	bool hasErrors();
	
	 // Detalhes sobre o Request e Config
	Request _req;
	ServerConfig _conf;
	Response _res;
	StatusCode _statusCode;

	// Manipulação de tipos de arquivos e MIME
	void MimeType();
	std::string getMimeType(const std::string &fileExtension);
	std::map<std::string, std::string> _mimeTypes;
	
	// Manipulação de arquivos e diretórios
	bool readFile(const std::string &path, std::string &outContent);
	bool isDirectory(const std::string &path);
	std::string getPath(std::string uri);
	bool uriIsLocation(void);
	void getDefaultErrorPage(void);

	// Manipulação de CGI
	Response handleCGI(const Request &req, const std::string &cgiPath);
	bool isValidCGIScript(const std::string &cgiPath);
	void setupEnviroment(const Request &req, std::vector<std::string> &envVec,
		     char **&envp);
	void executeCGIInChild(const std::string &cgiPath, char **envp, int pipefd[]);
	std::string readCGIOutput(int pipefd[]);
	bool isCGIRequest(const std::string& uri);
	std::string getCgiPathFromUri(const std::string& uri);
	
	// Gerar respostas de erro
	Response generate500InternalServerError();
};


#endif