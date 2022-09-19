#pragma once

#include <unistd.h>
#include <arpa/inet.h>
#include <array>

using std::array;

#include "../../Base/nonAssignNonCopy.hpp"
#include "../../DataStructs/String/String.hpp"

using DataStructs::String;

namespace Network
{
    enum {MESSSIZE = 257}; // размер сообщения + '\0'

    class Socket final : private NonAssignable, private NonCopyable
    {
    private:  
        int           fd_;      // дескриптор
        sockaddr_in   address_; // структура адреса
        socklen_t addressSize_; // размер структуры адреса
      
    public:
        Socket(String const& ip, int port); // конструктор, принимает ip, порт и размер сообщения
        ~Socket();                          // деструктор

    public:
        void create(String const& ip, in_port_t port);  // инициализации класса сокета (создание fd и инициализация структуры sockaddr_in)
        void close();                                   // закрыть сокет

        void bind();               // cвязывание адреса с локальным адресом протокола (для серверов)
        void listen(int backlog);  // перевод сокета в состояние LISTEN               (для серверов)
        int  accept();             // принятие входящих подключений                   (для серверов)
        void connect();            // подключение

    public:
        int fd()                     const noexcept; // получить дескриптор
        sockaddr_in const& address() const noexcept; // получить структуру адреса
        bool active() const noexcept;                // активен ли сокет
    };

    ssize_t recv(int fd, array<char, MESSSIZE>& buff); // получить сообщение 
    ssize_t send(int fd, array<char, MESSSIZE> const& buff);   // послать сообщение
}