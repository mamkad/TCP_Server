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

/*
void Host::work()
{
	while(isRunning_)
	{
		cout << "hi" << endl;
	}
}*/

int Host::run()
{
	//isRunning_ = true;
	//task_ = std::thread(&Host::work, this);
	return 0;
}

