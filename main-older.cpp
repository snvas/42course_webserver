#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>  // para std::exit


struct ConfigBlock {
    std::map<std::string, std::vector<std::string> > directives;
};

struct LocationConfig : public ConfigBlock {
    std::string path;
};

struct ServerConfig : public ConfigBlock {
    std::map<std::string, LocationConfig> locations;
};

enum LineType {
    SERVER_START, LOCATION_START, DIRECTIVE, UNKNOWN, END
};

std::set<std::string> initializeServerContextKeys() {
    std::set<std::string> keys;
    keys.insert("listen");
    keys.insert("server_name");
    keys.insert("client_max_body_size");
    keys.insert("index");
    keys.insert("allowed_method");
    keys.insert("autoindex");
    keys.insert("error_page");
	keys.insert("cgi");
    keys.insert("root");
	keys.insert("location");
    return keys;
}

std::set<std::string> initializeLocationContextKeys() {
    std::set<std::string> keys;
    keys.insert("allow_methods");
    keys.insert("autoindex");
    keys.insert("root");
    keys.insert("index");
    keys.insert("cgi");
    return keys;
}

std::set<std::string> serverContextKeys = initializeServerContextKeys();
std::set<std::string> locationContextKeys = initializeLocationContextKeys();


LineType determineLineType(const std::string &line) {
    if (line.find("server") != std::string::npos) 
		return SERVER_START;
    if (line.find("location") != std::string::npos) 
		return LOCATION_START;
    if (line.empty() || line[0] == '}') 
		return END;
    return DIRECTIVE;
}

std::pair<std::string, std::vector<std::string> > splitLine(const std::string &line) {
    std::stringstream ss(line);
    std::string key;
    std::string value;
    std::vector<std::string> values;

    ss >> key;
    while (ss >> value) {
        if (value[value.length() - 1] == ';')
            value = value.substr(0, value.length() - 1);
        values.push_back(value);
    }

    return std::make_pair(key, values);
}
// Função para remover espaços em branco no início e no final de uma string.
std::string trim(const std::string &s) {
    std::string::size_type start = s.find_first_not_of(" \t\n\r");
    std::string::size_type end = s.find_last_not_of(" \t\n\r");

    if (start == std::string::npos || end == std::string::npos) {
        return "";
    } else {
        return s.substr(start, end - start + 1);
    }
}

std::map<std::string, std::vector<std::string> > parseDirectives(std::stringstream &ss, const std::set<std::string> &contextKeys) {
    std::map<std::string, std::vector<std::string> > directives;
    std::string line;

    while (std::getline(ss, line)) {
        // Ignorando linhas vazias ou espaços em branco.
        std::string trimmedLine = trim(line);

        // Se a linha for de fechamento '}', encerre o parsing deste bloco.
        if (trimmedLine == "}") {
            break;
        }
        if (trimmedLine.empty()) {
            continue;
        }
        
        std::pair<std::string, std::vector<std::string> > kv = splitLine(line);

        // Verificando se a chave é válida.
        if (contextKeys.find(kv.first) == contextKeys.end()) {
            std::cerr << "Erro: Chave inválida '" << kv.first << "' na linha: " << line << std::endl;
            std::exit(1);
        }

        // Verificando múltiplas declarações da mesma chave.
        if (directives.find(kv.first) != directives.end()) {
            std::cerr << "Erro: Múltiplas declarações da chave " << kv.first << std::endl;
            std::exit(1);
        }

        // Se encontrarmos a chave 'location', precisamos lidar com ela de maneira especial
        if (kv.first == "location") {
            // Parseamos as diretivas dentro do bloco 'location'
            std::map<std::string, std::vector<std::string> > locationDirectives = parseDirectives(ss, locationContextKeys);
            for (std::map<std::string, std::vector<std::string> >::iterator it = locationDirectives.begin(); it != locationDirectives.end(); ++it) {
                directives["location " + kv.second[0] + " " + it->first] = it->second;
            }
            continue;
        }

        directives[kv.first] = kv.second;
    }
    return directives;
}
void printParsedData(const std::vector<ServerConfig>& servers) {
    for (std::vector<ServerConfig>::const_iterator serverIt = servers.begin(); serverIt != servers.end(); ++serverIt) {
        const ServerConfig& server = *serverIt;
        
        std::cout << "Server Directives:\n";
        for (std::map<std::string, std::vector<std::string> >::const_iterator directiveIt = server.directives.begin(); directiveIt != server.directives.end(); ++directiveIt) {
            std::cout << "  " << directiveIt->first << ": ";
            for (std::vector<std::string>::const_iterator valueIt = directiveIt->second.begin(); valueIt != directiveIt->second.end(); ++valueIt) {
                std::cout << *valueIt << " ";
            }
            std::cout << "\n";
        }

        std::cout << "\nLocations:\n";
        for (std::map<std::string, LocationConfig>::const_iterator locIt = server.locations.begin(); locIt != server.locations.end(); ++locIt) {
            std::cout << "  " << locIt->first << "\n";
            for (std::map<std::string, std::vector<std::string> >::const_iterator directiveIt = locIt->second.directives.begin(); directiveIt != locIt->second.directives.end(); ++directiveIt) {
                std::cout << "    " << directiveIt->first << ": ";
                for (std::vector<std::string>::const_iterator valueIt = directiveIt->second.begin(); valueIt != directiveIt->second.end(); ++valueIt) {
                    std::cout << *valueIt << " ";
                }
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
}



int main(int argc, char* argv[]) {
    // Verificando argumentos.
    if(argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <path_to_config_file>" << std::endl;
        return 1;
    }

    std::ifstream configFile(argv[1]);
    if (!configFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de configuração." << std::endl;
        return 1;
    }

    std::string configContent((std::istreambuf_iterator<char>(configFile)),
                               std::istreambuf_iterator<char>());
    std::stringstream configStream(configContent);
    std::string line;

    ServerConfig currentServer;
    LocationConfig currentLocation;
    LineType previousType = UNKNOWN;

	std::vector<ServerConfig> servers;


    while (std::getline(configStream, line)) {
        switch (determineLineType(line)) {
            case SERVER_START:
                if (previousType != UNKNOWN && previousType != END) {
                    std::cerr << "Erro de sintaxe: bloco de servidor não fechado corretamente." << std::endl;
                    configFile.close();
                    return 1;  
                }
                currentServer = ServerConfig();
                currentServer.directives = parseDirectives(configStream, serverContextKeys);
                previousType = SERVER_START;
                break;

            case LOCATION_START:
                if (previousType != SERVER_START && previousType != END) {
                    std::cerr << "Erro de sintaxe: bloco de localização não fechado corretamente." << std::endl;
                    configFile.close();
                    return 1;  
                }
                currentLocation = LocationConfig();
                currentLocation.directives = parseDirectives(configStream, locationContextKeys);
                currentServer.locations[line] = currentLocation;
                previousType = LOCATION_START;
                break;

            case END:
			 	if (previousType == SERVER_START || previousType == LOCATION_START) {
     				servers.push_back(currentServer);
        			currentServer = ServerConfig();  // Reset currentServer
    			}
                previousType = END;
                break;

            default:
                break;
        }
    }

    configFile.close();
	printParsedData(servers);
    return 0;
}
