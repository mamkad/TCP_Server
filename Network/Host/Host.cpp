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
	return 0;
}