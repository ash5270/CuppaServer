#pragma once
#include "Server.h"
#include <memory>
namespace cuppa::net::client
{
	class ClientSession :public cuppa::net::Session
	{
	public:
		ClientSession(SessionType type, boost::asio::io_context& context, boost::asio::ip::tcp::socket socket);

		void OnRecv(Buffer buffer, size_t recvSize) override;

		void OnDisconnect() override;
	};

}

