#include "ResponseHandler.hpp"

// Função auxiliar para ler o conteúdo de um arquivo e armazená-lo em uma string.
static void readFromAFile(std::string path, std::string &body)
{
	// Abre o arquivo localizado no caminho especificado
	std::ifstream file(path.c_str());
	// Verifica se o arquivo foi aberto com sucesso
	if (file.is_open())
	{
		// Variável temporária para armazenar cada linha do arquivo
		std::string line;
		while (getline(file, line))
		{
			// Anexa cada linha lida à string 'body'
			body.append(line);
		}
		file.close();
	}
	// Se o arquivo não puder ser aberto, a string 'body' permanecerá vazia
}

// Função auxiliar para verificar se um arquivo existe
static bool fileExists(const std::string& filePath){
	struct stat buffer;
	// A função stat() retorna 0 se o arquivo existir
	return (stat(filePath.c_str(), &buffer) == 0);
}

std::string ResponseHandler::getPath(std::string uri){
	std::string rootDir = _conf.root;
	std::string path = rootDir + uri;

	if (path[path.length() - 1] == '/'){
		path.append("index.html");
	}
	return path;
}

void ResponseHandler::handlerDELETE(const Request &req)
{
	// Obter o caminho absoluto do arquivo a ser excluído
	std::string filePath = getPath(req.uri);
	// Verificar se o arquivo realmente existe
	if (fileExists(filePath))
	{
		// Tenta remover o arquivo e verifica se a operação foi bem-sucedida
		if (std::remove(filePath.c_str()) == 0)
		{
			// Se bem-sucedido, definir o código de status como 204 (Sem Conteúdo)
			_res.statusCode = 204;
			_res.headers["Content-Type"] = "text/html";
		}
		else
		{
			// Se falhar, carregar a página de erro 500 (Erro Interno do Servidor)
			std::string errorPath = getPath("/500.html");
			readFromAFile(errorPath, _res.body);
			_res.statusCode = 500;
			_res.headers["Content-Type"] = "text/html";
			_res.body = "<html><body><h1>500 Internal Server Error</h1></body></html>";
		}
	} else {
		// Se o arquivo não existir, carregar a página de erro 404 (Não Encontrado)
			std::string errorPath = getPath("/404.html");
			readFromAFile(errorPath, _res.body);
			_res.statusCode = 404;
			_res.headers["Content-Type"] = "text/html";
			_res.body = "<html><body><h1>404 Not Found</h1></body></html>";
	}
}
