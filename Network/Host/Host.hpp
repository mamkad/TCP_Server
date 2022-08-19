#pragma once 

#include "../../DataStructs/List/List.hpp"
#include "../../Config/Config.hpp"
#include "Connection.hpp"

class Host final
{
private:
	enum {IPLEN = 15, MAXCONNECT = 10};
private:
	String ipAddress_;
private:
	List<Connection> connect_;
public:
	Host(Config const&);
	Host(Host const&) = delete;
	Host(Host&&)      = delete;
	~Host();
public:
	Host& operator= (Host const&) = delete;
	Host& operator= (Host&&)      = delete;
public:
	int run();
};