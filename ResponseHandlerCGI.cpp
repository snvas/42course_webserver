#include "ResponseHandler.hpp"

void ResponseHandler::setupEnviroment(const Request &req, std::vector<std::string> &envVec,
		     char **&envp)
{
	envVec.push_back("AUTH_TYPE=" + req.authorization);
	envVec.push_back("REDIRECT_STATUS=200");
	envVec.push_back("GATEWAY_INTEFACE=CGI/1.1");
	envVec.push_back("SCRIPT_NAME=" + req.cgi_path);
	envVec.push_back("SCRIPT_FILENAME" + req.cgi_path);
	envVec.push_back("REQUEST_METHOD" + req.method);
	envVec.push_back("CONTENT_LENGTH=" + req.content_lenght);
	envVec.push_back("CONTENT_TYPE=" + req.content_type);
	envVec.push_back("PATH_INFO=" + req.cgi_path);
	envVec.push_back("PATH_TRANSLATED=" + req.cgi_path);
	envVec.push_back("QUERY_STRING=" + req.query);
	envVec.push_back("REMOTE_ADDR=" + req.port);
	envVec.push_back("REMOTE_IDENT=" + req.authorization);
	envVec.push_back("REMOTE_USER=" + req.authorization);
	envVec.push_back("REQUEST_URI=" + req.cgi_path + "?" + req.query);
	envVec.push_back("SERVER_NAME=" + req.host);
	envVec.push_back("SERVER_PROTOCOL=http/1.1");
	envVec.push_back("SERVER_SOFTWARE=Webserver/1.0");
	envVec.push_back("HTTP_USER_AGENT=" + req.user_agent);
	envVec.push_back("HTTP_ACCEPT=" + req.accept);

	envp = new char *[envVec.size() + 1];
	for (size_t i = 0; i < envVec.size(); ++i)
	{
		envp[i] = const_cast<char *>(envVec[i].c_str());
	}
	envp[envVec.size()] = NULL;
}

void ResponseHandler::executeCGIInChild(const std::string &cgiPath, char **envp, int pipefd[])
{
	close(pipefd[0]); // Fechar a extremidade de leitura do pipe
	dup2(pipefd[1], STDOUT_FILENO); // Redirecionar stdout para o pipe
	close(pipefd[1]); // Fechar a extremidade de escrita original do pipe
	char* const argv[] = {const_cast<char*>(cgiPath.c_str()), NULL};
	// Executar o script CGI
	if (execve(cgiPath.c_str(), argv, envp) == -1){
		perror("execve");
		exit(EXIT_FAILURE); // Encerrar o processo filho com status de falha
	}
}

std::string ResponseHandler::readCGIOutput(int pipefd[])
{
	char buffer[4096];
	std::string output;
	// Ler a saída do script CGI
	ssize_t bytesRead;
	while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0)
	{
		output.append(buffer, bytesRead);
	}
	close(pipefd[0]); // Fechar a extremidade de leitura do pipe
	return output;
}

// Função para manipular solicitações de CGI (Common Gateway Interface)
Response ResponseHandler::handleCGI(const Request &req,
				    const std::string &cgiPath)
{
	Response response; // Objeto de resposta que será retornado
	int pipefd[2];	   // descritores de arquivo para pipe

	// Criar um pipe para comunicação entre processos
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return generate500InternalServerError();
	}

	pid_t pid = fork(); // Criar um novo processo
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return generate500InternalServerError();
	}

	std::vector<std::string> envVec;
	char **envp = NULL;
	setupEnviroment(req, envVec, envp);

	// Código do processo filho
	if (pid == 0)
	{
		executeCGIInChild(cgiPath, envp, pipefd);
	}
	// Código do processo pai
	else
	{
		close(pipefd[1]); // Fechar a extremidade de escrita do pipe
		std::string responseBody = readCGIOutput(pipefd);
		waitpid(pid, NULL, 0); // Aguardar o processo filho terminar

		response.httpVersion = "HTTP/1.1";
		response.statusCode = 200;
		response.headers["Content-Type"] = getMimeType(".html");
		response.body = responseBody;
	}
	delete[] envp;
	return response;
}

bool ResponseHandler::isValidCGIScript(const std::string &cgiPath)
{
	struct stat s;
	// Check if file exists
	if (stat(cgiPath.c_str(), &s) != 0)
	{
		return false;
	}
	// Check if file is regular and executable
	return S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR);
}

Response ResponseHandler::generate500InternalServerError()
{
	Response response;
	response.httpVersion = "HTTP/1.1";
	response.statusCode = 500;
	response.body =
	    "<html><body><h1>Internal Server Error</h1></body></html>\n";

	std::stringstream ss;
	ss << response.body.size();
	response.headers["Content-Leghth"] = ss.str();
	response.headers["Content_type"] = "text/html";

	return response;
}

bool ResponseHandler::isCGIRequest(const std::string& uri){
	std::vector<std::string> cgiPaths = _conf.cgi_extensions;

	return std::find(cgiPaths.begin(), cgiPaths.end(), uri) != cgiPaths.end();
}

std::string ResponseHandler::getCgiPathFromUri(const std::string& uri){
	return "cgi-bin/" + uri;
}