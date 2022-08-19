#pragma once 

#include "../../DataStructs/String/String.hpp"

#include <netinet/in.h>
#include <cstring>

class Connection final
{
private:
	enum {PORTLEN = 4};
private:	
	int serverFD_;
	String      port_;
	sockaddr_in fullAddress_; 
public:
	Connection(String const&, String const&); // Config const& config
	~Connection();
public:
	inline int getServerFd() const noexcept;
private:
	static void setSocket(int& serverFD);
	static void setAddress(sockaddr_in&, String const&, String const&);
	static void setBind(int, sockaddr_in&);
	static void setListen(int, int);
private:
	static int Accept(int, sockaddr_in&);
};