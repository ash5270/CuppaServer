#pragma once
#include <string>
#include "Client.h"
#include "ClientSession.h"
namespace cuppa::net::client
{
	class TestClient : public cuppa::net::Client
	{
	public:
		TestClient(std::string ip, int port);
	public:
		void OnMessage(Buffer& buffer) override;
		void OnServerConnect(boost::asio::ip::tcp::socket socket) override;
	};
}

