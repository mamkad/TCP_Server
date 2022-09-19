#include "Socket.hpp"

#include <cstring>
#include <exception>
#include <algorithm>
#include <string>
#include <iostream>

using std::cout;
using std::fill;

using std::exception;
using std::logic_error;
using std::invalid_argument;
using std::string;

namespace Network
{
    // конструктор, принимает ip и порт
    Socket::Socket(String const& ip, int port) : fd_(-1), addressSize_(sizeof(address_))
    {
        cout << "Socket()\n";
        create(ip, port);
    }
  
    // виртуальный деструктор, чтобы корректно освобождать ресурсы производных классов 
    Socket::~Socket()                 
    {
        cout << "~Socket()\n";
        close();
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    void Socket::create(String const& ip, in_port_t port)
    {   
        if(!active())
        {
            if ( (fd_ = ::socket(AF_INET, SOCK_STREAM, 0)) < 0 )
            {
                throw logic_error("Не удалось создать сокет: " + string(strerror(errno)));
            }

            memset(&address_, '\0', addressSize_);
            address_.sin_family = AF_INET;
            address_.sin_port = port;
            address_.sin_addr.s_addr = inet_addr(ip.ptr());

            if (!address_.sin_addr.s_addr)
            {
               ::close(fd_);
               fd_ = -1;
               throw invalid_argument("Неправильный ip адрес: " + string(ip.ptr()));
            }
        }
        else 
        {
            throw invalid_argument("Нельзя создать новый сокет, пока не закрыт текущий");
        }
    }    
    // закрыть сокет
    void Socket::close()
    {
        if (active())
        {
            if ( ::close(fd_) < 0 )
            {
                fd_ = -1;
                throw logic_error("Ошибка при закрытии сокета: "+ string(strerror(errno)));
            }
            fd_ = -1;
            cout << "closed\n";
        }
    }

    // cвязывание адреса с локальным адресом протокола (для серверов)
    void Socket::bind()    
    {
        if (active())
        {
        	if ( ::bind(fd_, (struct sockaddr*)&address_, addressSize_) < 0 )
            {
                throw logic_error("Не удалось связать адрес с локальным адресом протокола: "+ string(strerror(errno)));
            }
        }
        else 
        {
            throw invalid_argument("Нельзя использовать bind, пока не открыт сокет");
        }
    }

    // перевод сокета в состояние LISTEN (для серверов)
    void Socket::listen(int backlog)                 
    {
        if (active())
        {
        	if ( ::listen(fd_, backlog) < 0 )
            {
                throw logic_error("Не удалось перевести сокет в состояние LISTEN: " + string(strerror(errno)));
            }
        }
        else 
        {
            throw invalid_argument("Нельзя использовать listen, пока не открыт сокет");
        }
    }

    // принятие входящих подключений (для серверов)
    int Socket::accept()  
    {
        if (active())
        {
        	int connFd;
            if ( (connFd = ::accept(fd_, (struct sockaddr*)&address_, &addressSize_)) < 0 )
            {
                throw logic_error("Не удалось получить fd следующего установленного соединения: " + string(strerror(errno)));
            }
            return connFd;
        }
        else 
        {
            throw invalid_argument("Нельзя использовать accept, пока не открыт сокет");
        }
    }	

    // подключение
    void Socket::connect() 
    {
        if (active())
        {
        	if ( ::connect(fd_, (struct sockaddr*)&address_, addressSize_) < 0 )
            {
                throw logic_error("Не удалось установить соединение : " + string(strerror(errno)));
            }
        }
        else 
        {
            throw invalid_argument("Нельзя использовать connect, пока не открыт сокет");
        }
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    // получить дескриптор
    int Socket::fd()  const noexcept
    {
        return fd_;
    }

    // получить структуру адреса
    sockaddr_in const& Socket::address() const noexcept 
    {
        return address_;
    }

    // активен ли сокет
    bool Socket::active() const noexcept
    {
        return (fd_ >= 0);
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    // получить сообщение 
    ssize_t recv(int fd, array<char, MESSSIZE>& buff)       
    {
        ssize_t len = 0;
        if ( (len = ::recv(fd, buff.data(), MESSSIZE, 0)) && len < 0 )
        {
            throw logic_error("Ошибка при получении сообщения: " + string(strerror(errno)));
        }
        return len;
    }

    // послать сообщение
    ssize_t send(int fd, array<char, MESSSIZE> const& buff)   
    {
        ssize_t len = 0;
        if ( (len = ::send(fd, buff.data(), MESSSIZE, 0)) && len < 0 )
        {
            throw logic_error("Ошибка при отправке сообщения: " + string(strerror(errno)));
        }
        return len;
    }  
}
