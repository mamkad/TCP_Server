#pragma once 

#include <netinet/in.h>

class Port
{
private:
	enum {PORTLEN = 4};
private:
	 char port[PORTLEN];
	 sockaddr_in fullAddress; 
public:
	Port();
	~Port();
private:
	static void setAddress(sockaddr_in&, char*);
	static void setSocket();
};