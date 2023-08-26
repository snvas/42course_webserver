#include "Webserver.hpp"
#include "Server.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
	std::string configPath = checkArguments(argc, argv);
	std::string configContent = readConfigFile(configPath);

	std::vector<ServerConfig> configServers = parseConfig(configContent);
	printConfigs(configServers);

	if (!configServers.empty()){
		Server webServer(configServers[0]);
		webServer.run();
	}

	return 0;
}
