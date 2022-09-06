#include "Socket.hpp"

#include <cstring>

namespace Network
{
    // конструктор, принимает ip и порт
    Socket::Socket(String const& ip, int port, bool createSocketNow) try : fd(-1), fdIsCreated(false)
    {
        if(createSocketNow)
        {
            createSocket();
            createAddress(ip, port);
        }

        cout << "Socket()\n";
    }
    catch(exception const& e)
    {
    	throw;
    }

    // виртуальный деструктор, чтобы корректно освобождать ресурсы производных классов 
    Socket::~Socket()                 
    {
        Close();
        cout << "~Socket()\n";
    }

    // cоздание сокета и привязка к его структуре адреса
    void Socket::createSocket()
    {
        if(!isActive())
        {
            if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
            {
                throw logic_error("Не удалось создать сокет");
            }

            fdIsCreated = true;
        }
        else 
        {
            throw invalid_argument("Нельзя создать новый сокет, пока не закрыт текущий");
        }
    } 

    // инициализация структуры sockaddr_in 
    void Socket::createAddress(String const& ip, int port)
    {
        if(isActive())
        {
            memset(&address, '\0', sizeof(address));
            address.sin_family = AF_INET;
            address.sin_port = port;
            address.sin_addr.s_addr = inet_addr(ip.getPtr());

            if (!address.sin_addr.s_addr)
            {
                throw invalid_argument("Неправильный ip адрес");
            }
        }
        else 
        {
            throw invalid_argument("Нельзя задать новый адресс, пока не открыт текущий сокет");
        }
    }

    // закрыть сокет
    void Socket::Close()
    {
        if (isActive())
        {
            fdIsCreated = false;
            close(fd);
        }
    }

    // cвязывание адреса с локальным адресом протокола (для серверов)
    void Socket::Bind()    
    {
        if (isActive())
        {
        	if ( bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0 )
            {
                throw logic_error("Не удалось связать адрес с локалным адресом протокола");
            }
        }
        else 
        {
            throw invalid_argument("Нельзя использовать Bind, пока не открыт сокет");
        }
    }

    // перевод сокета в состояние LISTEN (для серверов)
    void Socket::Listen(int backlog)                 
    {
        if (isActive())
        {
        	if ( listen(fd, backlog) < 0 )
            {
                throw logic_error("Не удалось перевести сокет в состояние LISTEN");
            }
        }
        else 
        {
            throw invalid_argument("Нельзя использовать Listen, пока не открыт сокет");
        }
    }

    // принятие входящих подключений (для серверов)
    int Socket::Accept()  
    {
        if (isActive())
        {
        	int connFd;
            socklen_t addressSize = sizeof(address);

            if ( (connFd = accept(fd, (struct sockaddr*)&address, &addressSize)) < 0 )
            {
                if (errno == EINTR)
                {
                    throw logic_error("Ошибка EINTR");
                }
                else 
                {
                    throw logic_error("Не удалось получить fd следующего установленного соединения");
                }
            }
            return connFd;
        }
        else 
        {
            throw invalid_argument("Нельзя использовать Accept, пока не открыт сокет");
        }
    }	

    // подключение
    void Socket::Connect() 
    {
        if (isActive())
        {
        	if ( connect(fd, (struct sockaddr*)&address, sizeof(address)) < 0 )
            {
                throw logic_error("Не удалось установить соединение");
            }
        }
        else 
        {
            throw invalid_argument("Нельзя использовать Connect, пока не открыт сокет");
        }
    }

    // получить сообщение 
    int Socket::Recv(array<char, MESSAGESIZE>& buff)       
    {
        if (isActive())
        {
        	int length = 0;
        	if ( (length = recv(fd, buff.data(), MESSAGESIZE, 0)) && length < 0 )
            {
            	throw logic_error("Ошибка при получении сообщения");
            }
            return length;
        }
        else 
        {
            throw invalid_argument("Нельзя использовать Recv, пока не открыт сокет");
        }
    }

    // послать сообщение
    int Socket::Send(array<char, MESSAGESIZE> const& buff)   
    {
        if (isActive())
        {
        	int length = 0;
            if ( (length = send(fd, buff.data(), MESSAGESIZE, 0)) && length < 0 )
            {
            	throw logic_error("Ошибка при отправке сообщения");
            }
            return length;
        }
        else 
        {
            throw invalid_argument("Нельзя использовать Send, пока не открыт сокет");
        }
    }  

    // получить дескриптор
    int Socket::getFD()  const noexcept
    {
        if (isActive())
        {
            return fd;
        }
        else 
        {
            throw invalid_argument("Сокет закрыт");
        }
    }

    // получить структуру адреса
    sockaddr_in const& Socket::getAddress() const noexcept 
    {
        if (isActive())
        {
            return address;
        }
        else 
        {
            throw invalid_argument("Сокет закрыт");
        }
    }

    // активен ли сокет
    bool Socket::isActive() const noexcept
    {
        return fdIsCreated;
    }
}
