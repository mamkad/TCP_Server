#pragma once 

#include "../Config/Config.hpp"
#include "Connection.hpp"

class Host final
{
private:
	enum {IPLEN = 15};
private:
	char ipAddress[IPLEN];
	int listenFD;
public:
	Host(Config const&);
	Host(Host const&) = delete;
	Host(Host&&)      = delete;
	~Host();
public:
	Host& operator= (Host const&) = delete;
	Host& operator= (Host&&)      = delete;
private:
	void setListen();
public:
	int run();
};