#pragma once

#include "../Socket/Socket.hpp"
#include "../../Log/Log.hpp"

namespace Network
{
	class Connection final 
	{
	private:
		int    port;       // порт
		Socket socket;     // сокет
		// Netconfig netConf;
		Log connectionLog; // лог соединения

	public:
		Connection(String const& ip, int prt, String const& netConfigFileName); // конструктор (Config const& config)
		~Connection();                         								    // деструктор
		void run();							   									// запуск соединения на порту. 

	public:
		inline int getPort() const noexcept;   // получить порт

	private:
		void loadHandler(String const& handlerName);   // загрузить обработчик в память
		void unloadHandler(String const& handlerName); // сгрузить обработчик из памяти
		void connectionHandler(); 					   // функция потока работы соединения
	};
}
