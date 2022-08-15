#include "../TCP_Server/TCP_Server.hpp"
#include "../Config/Config.hpp"

int main(int argc, char** argv)
{
	Config config;
	Log log;
	Server server;
	
	return server.run();
}