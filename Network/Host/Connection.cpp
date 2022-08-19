#include "Connection.hpp"

#include <arpa/inet.h>

#include <iostream>
using namespace std;

Connection::Connection(String const& ipAddress, String const& port) : port_(port)
{
  setSocket(serverFD_);
  setAddress(fullAddress_, ipAddress, port);
  setBind(serverFD_, fullAddress_);
  setListen(serverFD_, 10);

  cout << "Connection " << port<<  endl;
}

Connection::~Connection()
{
    cout << "~Connection " << port_ <<  endl;
}
//------------------------------------------------------------------------------------------------------
inline int Connection::getServerFd() const noexcept
{
    return serverFD_;
}
//------------------------------------------------------------------------------------------------------
void Connection::setSocket(int& serverFD)
{
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
}

void Connection::setAddress(sockaddr_in& serverAddress, String const& ipAddress, String const& port)
{
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;         // (IPv4)
    inet_pton(AF_INET, ipAddress.getPtr(), &serverAddress.sin_addr);
    serverAddress.sin_port = htons(atoi(port.getPtr()));
}

void Connection::setBind(int serverFD, sockaddr_in& serverAddress)
{
    bind(serverFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

void Connection::setListen(int serverFD, int backLog)
{
    listen(serverFD, backLog);
}
//------------------------------------------------------------------------------------------------------
int Connection::Accept(int serverFD, sockaddr_in& clientAddress)
{
    socklen_t clilen = sizeof(clientAddress);
    return accept(serverFD, (struct sockaddr *)&clientAddress, &clilen);
}