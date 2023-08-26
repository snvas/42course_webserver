#include "Parser.hpp"

std::string checkArguments(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Uso: " << argv[0] << " <path_to_config_file>"
			  << std::endl;
		std::exit(1); // Encerra o programa
	}
	return std::string(argv[1]); // Retorna o caminho do arquivo
}

std::string readConfigFile(const std::string &path)
{
	std::ifstream configFile(path.c_str());
	if (!configFile.is_open())
	{
		std::cerr << "Erro ao abrir o arquivo de configuração."
			  << std::endl;
		std::exit(1); // Encerra o programa
	}
	std::string config((std::istreambuf_iterator<char>(configFile)),
			   std::istreambuf_iterator<char>());
	configFile.close();
	return config; // Retorna o conteúdo do arquivo
}

ServerConfig::ServerConfig()
{
	listen_port = 0;
	server_name = "";
	client_max_body_size = -1;
	index = std::vector<std::string>();
	allowed_method = std::vector<std::string>();
	default_error_page = std::vector<std::string>();
	directory_listing = "";
	locations = std::map<std::string, LocationConfig>();
	root = "";
}

ServerConfig::~ServerConfig() {}



// Função que retira espaços em branco no início e no final da string dada
std::string trim(const std::string &str)
{
	// Definindo os caracteres de espaço em branco
	std::string whitespace = " \t";

	// Encontra a primeira posição que não é um espaço em branco
	std::string::size_type strBegin = str.find_first_not_of(whitespace);

	// Se toda a string é um espaço em branco, retorna uma string vazia
	if (strBegin == std::string::npos)
		return "";

	// Encontra a última posição que não é um espaço em branco
	std::string::size_type strEnd = str.find_last_not_of(whitespace);

	// Calcula o tamanho da substring sem espaços em branco
	std::string::size_type strRange = strEnd - strBegin + 1;

	// Retorna a substring sem espaços em branco
	return str.substr(strBegin, strRange);
}

std::vector<std::string> extractMultipleWords(std::stringstream &ss)
{
	std::vector<std::string> words;
	std::string word;
	while (ss >> word)
	{
		words.push_back(word);
	}
	return words;
}

void processServerDirective(const std::string &line,
			    ServerConfig &currentServer)
{
	std::stringstream lineStream(line);
	std::string directive;
	lineStream >> directive;

	if (directive == "listen")
	{
		int port;
		lineStream >> port;
		currentServer.listen_port = port;
	}
	else if (directive == "server_name")
	{
		std::string name;
		lineStream >> name;
		currentServer.server_name = name;
	}
	else if (directive == "client_max_body_size")
	{
		int body_size;
		lineStream >> body_size;
		currentServer.client_max_body_size = body_size;
	}
	else if (directive == "autoindex")
	{
		std::string autoindex;
		lineStream >> autoindex;
		currentServer.directory_listing = autoindex;
	}
	else if (directive == "index")
	{
		currentServer.index = extractMultipleWords(lineStream);
	}
	else if (directive == "allowed_method")
	{
		currentServer.allowed_method = extractMultipleWords(lineStream);
	}
	else if (directive == "error_page")
	{
		currentServer.default_error_page =
		    extractMultipleWords(lineStream);
	}
	else if (directive == "cgi")
	{
		currentServer.cgi_extensions = extractMultipleWords(lineStream);
	}
	else if (directive == "root")
	{
		std::string root_dir;
		lineStream >> root_dir;
		currentServer.root = root_dir;
	}
}

void processLocationDirective(const std::string &line,
			      LocationConfig &currentLocation)
{
	std::stringstream lineStream(line);
	std::string directive;
	lineStream >> directive;

	if (directive == "allow_method")
	{
		currentLocation.accepted_methods =
		    extractMultipleWords(lineStream);
	}
	else if (directive == "location")
	{
		std::string path;
		lineStream >> path;
		currentLocation.path_dir = path;
	}
	else if (directive == "root")
	{
		std::string root_dir;
		lineStream >> root_dir;
		currentLocation.root = root_dir;
	}
	else if (directive == "cgi")
	{
		currentLocation.cgi_extensions =
		    extractMultipleWords(lineStream);
	}
	else if (directive == "http_redirect")
	{
		std::string redirect;
		lineStream >> redirect;
		currentLocation.redirect = redirect;
	}
	else if (directive == "autoindex")
	{
		std::string autoindex;
		lineStream >> autoindex;
		currentLocation.directory_listing = autoindex;
	}
	else if (directive == "default_file")
	{
		std::string index_file;
		lineStream >> index_file;
		currentLocation.default_file = index_file;
	}
	else if (directive == "upload_path")
	{
		std::string upload_dir;
		lineStream >> upload_dir;
		currentLocation.upload_path = upload_dir;
	}
}

std::vector<ServerConfig> parseConfig(const std::string &config)
{
	std::stringstream ss(config);
	std::string line;
	State currentState = START;
	std::vector<ServerConfig> servers;
	ServerConfig currentServer;
	LocationConfig currentLocation;
	while (std::getline(ss, line))
	{
		// Remove os espaços em branco no início e no final da linha
		line = trim(line);

		// Ignora as linhas que contêm apenas '{'
		if (line == "{")
			continue;

		// Trata o fim de blocos de configuração (seja server ou
		// location)
		if (line == "}")
		{
			// Se estivermos em um bloco de localização, adicionamos
			// a localização atual ao servidor atual
			if (currentState == LOCATION)
			{
				currentServer
				    .locations[currentLocation.path_dir] =
				    currentLocation;
				currentLocation.directives.clear();
				currentState = SERVER;
			}
			else if (currentState == SERVER)
			{ // Se estivermos em um bloco de servidor, adicionamos
			  // o servidor à lista de servidores
				servers.push_back(currentServer);
				currentServer.directives.clear();
				currentServer.locations.clear();
				currentState = START;
			}
			continue;
		}

		// Remove o caractere ';' se estiver presente no final da linha
		if (line[line.size() - 1] == ';')
			line = line.substr(0, line.size() - 1);

		// Máquina de estados para processar a configuração
		switch (currentState)
		{
		case START:
		{
			// Se encontrarmos a palavra "server", entramos no
			// estado SERVER
			if (line.find("server") != std::string::npos)
			{
				currentState = SERVER;
			}
			break;
		}
		case SERVER:
		{
			std::stringstream lineStream(line);
			std::string directive;
			// Se encontrarmos a palavra "location", entramos no
			// estado LOCATION
			if (line.find("location") != std::string::npos)
			{
				lineStream >> directive >>
				    currentLocation.path_dir;
				currentState = LOCATION;
			}
			else
			{
				processServerDirective(line, currentServer);
			}
			break;
		}
		case LOCATION:
		{
			processLocationDirective(line, currentLocation);
			break;
		}
		}
	}
	return servers;
}

void printConfigs(const std::vector<ServerConfig> &servers)
{
	for (std::vector<ServerConfig>::const_iterator serverIt =
		 servers.begin();
	     serverIt != servers.end(); ++serverIt)
	{
		std::cout << "server {" << std::endl;
		if (serverIt->listen_port != 0)
			std::cout << "\tlisten " << serverIt->listen_port << ";"
				  << std::endl;

		if (!serverIt->server_name.empty())
			std::cout << "\tserver_name " << serverIt->server_name
				  << ";" << std::endl;

		if (serverIt->client_max_body_size != 0)
			std::cout << "\tclient_max_body_size "
				  << serverIt->client_max_body_size << ";"
				  << std::endl;

		if (!serverIt->directory_listing.empty())
			std::cout << "\tautoindex "
				  << serverIt->directory_listing << ";"
				  << std::endl;

		if (!serverIt->index.empty())
		{
			std::cout << "\tindex ";
			for (std::vector<std::string>::const_iterator indexIt =
				 serverIt->index.begin();
			     indexIt != serverIt->index.end(); ++indexIt)
				std::cout << *indexIt << " ";
			std::cout << ";" << std::endl;
		}
		if (!serverIt->allowed_method.empty())
		{
			std::cout << "\tallowed_methods ";
			for (std::vector<std::string>::const_iterator methodIt =
				 serverIt->allowed_method.begin();
			     methodIt != serverIt->allowed_method.end();
			     ++methodIt)
				std::cout << *methodIt << " ";
			std::cout << ";" << std::endl;
		}

		if (!serverIt->cgi_extensions.empty())
		{
			std::cout << "\tcgi ";
			for (std::vector<std::string>::const_iterator cgiIt =
				 serverIt->cgi_extensions.begin();
			     cgiIt != serverIt->cgi_extensions.end(); ++cgiIt)
				std::cout << *cgiIt << " ";
			std::cout << ";" << std::endl;
		}

		for (std::map<std::string, LocationConfig>::const_iterator
			 locIt = serverIt->locations.begin();
		     locIt != serverIt->locations.end(); ++locIt)
		{
			const LocationConfig &location = locIt->second;

			std::cout << "\tlocation " << location.path_dir << " {"
				  << std::endl;

			if (!location.root.empty())
				std::cout << "\t\troot " << location.root << ";"
					  << std::endl;

			if (!location.redirect.empty())
				std::cout << "\t\thttp_redirect "
					  << location.redirect << ";"
					  << std::endl;

			if (!location.directory_listing.empty())
				std::cout << "\t\tautoindex "
					  << location.directory_listing << ";"
					  << std::endl;

			if (!location.default_file.empty())
				std::cout << "\t\tdefault_file "
					  << location.default_file << ";"
					  << std::endl;

			if (!location.upload_path.empty())
				std::cout << "\t\tupload_path "
					  << location.upload_path << ";"
					  << std::endl;

			if (!location.accepted_methods.empty())
			{
				std::cout << "\t\tallow_method ";
				for (std::vector<std::string>::const_iterator
					 methodIt =
					     location.accepted_methods.begin();
				     methodIt !=
				     location.accepted_methods.end();
				     ++methodIt)
					std::cout << *methodIt << " ";
				std::cout << ";" << std::endl;
			}

			if (!location.cgi_extensions.empty())
			{
				std::cout << "\t\tcgi ";
				for (std::vector<std::string>::const_iterator
					 cgiLocIt =
					     location.cgi_extensions.begin();
				     cgiLocIt != location.cgi_extensions.end();
				     ++cgiLocIt)
					std::cout << *cgiLocIt << " ";
				std::cout << ";" << std::endl;
			}

			std::cout << "\t}"
				  << std::endl; // Encerra bloco de localização
		}
		if (!serverIt->root.empty())
			std::cout << "\troot " << serverIt->root << ";"
				  << std::endl;

		std::cout << "}" << std::endl; // Encerra bloco de servidor
	}
}
