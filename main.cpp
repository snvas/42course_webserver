#include "Webserver.hpp"
#include <csignal>

Server webServer;

void sigint_handler(int sig){
	std::cout << '\n';
	std::cerr << "Rceived signal " << (sig + 128) << std::endl;
	//webServer.stop();
	exit(0);
}

int main(int argc, char **argv)
{
	std::string configPath = checkCommandLineArguments(argc, argv);
	std::string configContent = readConfigFile(configPath);

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = sigint_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction( SIGINT, &sigIntHandler, NULL);

	std::vector<ServerConfig> configServers = parseConfiguration(configContent);
	printServerConfigurations(configServers);

	if (!configServers.empty()){
		Server webServer(configServers[0]);
		webServer.run();
	}

	return 0;
}
