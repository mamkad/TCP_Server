#include "../Network/Host/Host.hpp"
#include "../Config/Config.hpp"

int main(int argc, char** argv)
{
	Config config;
	Host server(config);
	//Log log;
	//Server server;
	try {
		server.run();
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}