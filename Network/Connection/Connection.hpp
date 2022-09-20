#pragma once

#include "../Socket/Socket.hpp"
#include "../../Log/Log.hpp"

#include <memory>
#include <utility>

using std::shared_ptr;
using std::make_shared;
using std::pair;

namespace Network
{
	class Connection final
	{
	private:
		enum connection_t {SERVER = 0, CLIENT = 1}; // тип соединения

	private:
		shared_ptr<pair<Socket, Log>>  connection_;

	public:
		explicit Connection(Config const& config); // конструктор (Config const& config)
		~Connection();                             // деструктор

	public:
		void run();

	private:
		void create(connection_t);
		void handler();
	};
}
