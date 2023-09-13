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
	void handlerGET();
	void handlerDELETE();	
	void handlerPOST(void);
 
private:
	// Verificar erros nas solicitações e configurações
	bool hasErrors();

	// Detalhes sobre o Request e Config
	Request _req;
	ServerConfig _conf;
	Response _res;
	StatusCode _statusCode;
	LocationConfig *_locationConf;
	std::string _binary;

	// Manipulação de tipos de arquivos e MIME
	void MimeType();
	std::string getMimeType(const std::string &fileExtension);
	std::map<std::string, std::string> _mimeTypes;

	// Manipulação de arquivos e diretórios
	bool readFile(const std::string &path, std::string &outContent);
	bool isDirectory(const std::string &path);
	std::string getPath(std::string uri);
	void getDefaultErrorPage(void);
	void useLocationConfig(void);

	// Manipulação de CGI
	void handleCGI(const std::string &cgiPath);
	bool isValidCGIScript(const std::string &cgiPath);
	void setupEnviroment(std::vector<std::string> &envVec, char **&envp);
	void executeCGIInChild(const std::string &cgiPath, char **envp,
                                        int outPipe[], int inPipe[]);
	std::string readCGIOutput(int pipefd[]);
	bool isCGIRequest(const std::string &uri);
	std::string getCgiPathFromUri(const std::string &uri);
	std::string resolveBinaryPath(void);

	// Gerar respostas de erro
	void generateErrorResponse(int code);
	void generate301RedirectResponse(std::string location);
	void generateResponseFromFile(std::string file);
	void generateDirectoryListining(std::string path);
	void generateSucessResponse(int statusCode, const std::string &message);
  
	bool hasRedirect(void);
};

#endif