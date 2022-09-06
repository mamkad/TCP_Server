#include "Host.hpp"

#include <iostream>
using namespace std;

Host::Host(Config const& config)
{
	cout << "Host " <<  endl;
}

Host::~Host()
{
	cout << "~Host " <<  endl;
}

int Host::run()
{
	throw logic_error("gh");
	Connection conn(ipAddress_, "8080");
	//connect_.push(Connection(ipAddress_, "8080"));
	return 0;
}
