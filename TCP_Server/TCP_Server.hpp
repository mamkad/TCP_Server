#pragma once 

#include "../Config/Config.hpp"
#include "Port.hpp"

class Server
{
private:
	enum {IPLEN = 15};
private:
	char ipAddress[IPLEN];
	int listenFD;
public:
	Server(Config const&);
	Server(Server const&) = delete;
	Server(Server&&)      = delete;
	~Server();
public:
	Server& operator= (Server const&) = delete;
	Server& operator= (Server&&)      = delete;
private:
	void setListen();
public:
	int run();
};