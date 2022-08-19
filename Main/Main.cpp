#include "../Network/Host/Host.hpp"
#include "../Config/Config.hpp"

int main(int argc, char** argv)
{
	Config config;
	Host server(config);
	//Log log;
	//Server server;

	
	return server.run();
}