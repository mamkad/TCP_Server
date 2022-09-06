#pragma once

#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <array>
#include <exception>
#include <algorithm>

using std::cout;
using std::array;
using std::fill;

using std::exception;
using std::logic_error;
using std::invalid_argument;

#include "../../Base/nonAssignNonCopy.hpp"
#include "../../DataStructs/String/String.hpp"

namespace Network
{
    class Socket final : private NonAssignable, private NonCopyable
    {
    protected:
        enum { MESSAGESIZE = 256 }; // максимальная длина передаваемого сообщения + символ '\0'
    private:  
        int         fd;          // дескриптор
        sockaddr_in address;     // структура адреса
        bool        fdIsCreated; // флаг того, что сокет открыт

    public:
        Socket(String const& ip, int port, bool createSocketNow = true); // конструктор, принимает ip и порт
        ~Socket();                                                       // деструктор

    public:
        void createSocket();                            // cоздание сокета
        void createAddress(String const& ip, int port); // инициализация структуры sockaddr_in (присваиваем ip, порт)
        void Close();                                   // закрыть сокет

        void Bind();               // cвязывание адреса с локальным адресом протокола (для серверов)
        void Listen(int backlog);  // перевод сокета в состояние LISTEN               (для серверов)
        int  Accept();             // принятие входящих подключений                   (для серверов)
        void Connect();            // подключение

        int Recv(array<char, MESSAGESIZE>& buff);       // получить сообщение 
        int Send(array<char, MESSAGESIZE> const& buff); // послать  сообщение

    public:
        inline int getFD()                     const noexcept; // получить дескриптор
        inline sockaddr_in const& getAddress() const noexcept; // получить структуру адреса

        inline bool isActive() const noexcept; // активен ли сокет
    };
}