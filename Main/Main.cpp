#include "../Network/Host/Host.hpp"
#include "../Config/Config.hpp"

int main()
{
    Network::Connection c("127.0.0.1", 8000, "netconfig.txt");
    c.run();
}      

/*
int main(int argc, char** argv)
{


	try
	{
		Config config("config.json");
		Host server(config);
		server.run();
	}
	catch(exception& e)
	{
		cout << "-> " << e.what() << endl;
	}
	return 0;
}*/
