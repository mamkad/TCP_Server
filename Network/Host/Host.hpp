#pragma once

#include "../Connection/Connection.hpp"
#include "../../DataStructs/List/List.hpp"
#include "../../Config/Config.hpp"

namespace Network
{
	class Host
	{
	private:
		String ip;					  // ip
		List<Connection> connection;  // соединение
		Log hostLog; 			      // лог сервера

		bool hostIsActive;		      // запуск сервера прошёл успешно и были запущены соединения

	public:
		Host(Config const& config);	  // конструктор (принимает конфиг с парамтерами)
		void run();					  // запуск сервера

	public:
		inline String const& getIP() const noexcept; // получить ip;

	private:
		void addConnection(); // добавить соединение
	};
}
