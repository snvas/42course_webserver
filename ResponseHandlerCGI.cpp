#include "ResponseHandler.hpp"

void ResponseHandler::setupEnviroment(std::vector<std::string> &envVec,
                                      char **&envp)
{
	envVec.push_back("AUTH_TYPE=" + _req.authorization);
	envVec.push_back("REDIRECT_STATUS=200");
	envVec.push_back("GATEWAY_INTEFACE=CGI/1.1");
	envVec.push_back("SCRIPT_NAME=" + _req.cgi_path);
	envVec.push_back("SCRIPT_FILENAME" + _req.cgi_path);
	envVec.push_back("REQUEST_METHOD" + _req.method);
	envVec.push_back("CONTENT_LENGTH=" + _req.content_length);
	envVec.push_back("CONTENT_TYPE=" + _req.content_type);
	envVec.push_back("PATH_INFO=" + _req.cgi_path);
	envVec.push_back("PATH_TRANSLATED=" + _req.cgi_path);
	envVec.push_back("QUERY_STRING=" + _req.query);
	envVec.push_back("REMOTE_ADDR=" + _req.port);
	envVec.push_back("REMOTE_IDENT=" + _req.authorization);
	envVec.push_back("REMOTE_USER=" + _req.authorization);
	envVec.push_back("REQUEST_URI=" + _req.cgi_path + "?" + _req.query);
	envVec.push_back("SERVER_NAME=" + _req.host);
	envVec.push_back("SERVER_PROTOCOL=http/1.1");
	envVec.push_back("SERVER_SOFTWARE=Webserver/1.0");
	envVec.push_back("HTTP_USER_AGENT=" + _req.user_agent);
	envVec.push_back("HTTP_ACCEPT=" + _req.accept);

	envp = new char *[envVec.size() + 1];
	for (size_t i = 0; i < envVec.size(); ++i)
	{
		envp[i] = const_cast<char *>(envVec[i].c_str());
	}
	envp[envVec.size()] = NULL;
}

void ResponseHandler::executeCGIInChild(const std::string &cgiPath, char **envp,
                                        int pipefd[])
{
	close(pipefd[0]);               // Fechar a extremidade de leitura do pipe
	dup2(pipefd[1], STDOUT_FILENO); // Redirecionar stdout para o pipe
	close(pipefd[1]); // Fechar a extremidade de escrita original do pipe
	char *const argv[] = {const_cast<char *>(cgiPath.c_str()), NULL};
	// Executar o script CGI
	if (execve(cgiPath.c_str(), argv, envp) == -1)
	{
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
void ResponseHandler::handleCGI(const std::string &cgiPath)
{
	int pipefd[2]; // descritores de arquivo para pipe

	// Criar um pipe para comunicação entre processos
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return generateErrorResponse(500);
	}

	pid_t pid = fork(); // Criar um novo processo
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return generateErrorResponse(500);
	}

	std::vector<std::string> envVec;
	char **envp = NULL;
	setupEnviroment(envVec, envp);

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

		_res.httpVersion = "HTTP/1.1";
		_res.statusCode = 200;
		_res.headers["Content-Type"] = getMimeType(".html");
		_res.body = responseBody;
	}
	delete[] envp;
	return;
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

bool ResponseHandler::isCGIRequest(const std::string &uri)
{
	std::vector<std::string> cgiPaths = _conf.cgi_extensions;

	return std::find(cgiPaths.begin(), cgiPaths.end(), uri) != cgiPaths.end();
}

std::string ResponseHandler::getCgiPathFromUri(const std::string &uri)
{
	return "cgi-bin/" + uri;
}