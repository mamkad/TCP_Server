#include "Connection.hpp"

//using std::thread;

namespace Network
{
    Connection::Connection(String const& ip, int prt, String const& netConfigFileName) try : port(prt), socket(ip, prt), connectionLog("ConnectionLog_")
    {
        cout << "Connection()\n";
    }
    catch(exception const& e)
    {
        throw;
    }

    Connection::~Connection()
    {
       cout << "~Connection()\n";
    }

    void Connection::run()
    {
        //while(1)
        {

        }
    }

    inline int Connection::getPort() const noexcept
    {
        return port;
    }

    // загрузить обработчик в память
    void Connection::loadHandler(String const& handlerName)
    {

    }

    // сгрузить обработчик из памяти   
    void Connection::unloadHandler(String const& handlerName)
    {

    }

    // функция потока работы соединения
    void Connection::connectionHandler()
    {

    } 
}     
          
