#ifndef PARSER_HPP
#define PARSER_HPP

#include "CommonLibs.hpp"

// Estados para a máquina de estados.
enum State
{
	START,
	SERVER,
	LOCATION
};

// Estrutura para configuração de uma localização.
struct LocationConfig
{
	std::vector<std::string> accepted_methods;
	std::string path_dir;
	std::string root;
	std::vector<std::string> cgi_extensions; // extensão para path do CGI
	std::string redirect;
	std::string directory_listing;
	std::string default_file;
	std::string upload_path;
	LocationConfig() {}
};

// Estrutura para configuração de um servidor.
struct ServerConfig
{
	int listen_port;
	std::string server_name;
	int client_max_body_size;
	std::vector<std::string> index;
	std::vector<std::string> allowed_method;
	std::vector<std::string> default_error_page;
	std::string directory_listing;
	std::string root;
	std::vector<std::string> cgi_extensions;
	std::map<std::string, LocationConfig> locations;
	ServerConfig();
	~ServerConfig();
};

void initLocation(LocationConfig &currentLocation);
void printServerConfigurations(const std::vector<ServerConfig> &servers);
std::vector<ServerConfig> parseConfiguration(const std::string &config);
void processLocationDirective(const std::string &line, LocationConfig &currentLocation);
void processServerDirective(const std::string &line, ServerConfig &currentServer);
std::vector<std::string> extractMultipleWords(std::stringstream &ss);
std::string trim(const std::string &str);
std::string checkCommandLineArguments(int argc, char **argv);
std::string readConfigFile(const std::string &path);

#endif
