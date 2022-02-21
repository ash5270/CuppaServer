#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "Buffer.h"

namespace cuppa::net
{
	enum class SessionType
	{
		Client,
		Server
	};

	class Server;

	class Session :public std::enable_shared_from_this<Session>
	{
	public:
		Session(SessionType type, boost::asio::io_context& context, boost::asio::ip::tcp::socket socket);
		virtual ~Session();

	public:
		bool ConnectToClient();
		bool ConnectToServer();

		void Send(Buffer&& buffer);

	private:
		void Connect();
		void Disconnect(); 
		void RecvData();
		void RecvDataCallBack(boost::system::error_code ec, size_t transferred);
		void SendData(Buffer buffer);
		void SendDataCallBack(boost::system::error_code ec, size_t transferred);

	public:
		virtual void OnRecv(Buffer buffer, size_t recvSize) {}
		virtual void OnDisconnect(){}
		virtual void OnSend(Buffer buffer, size_t recvSize){}
		//전방선언시 참조 형식으로 
		cuppa::net::Server* m_server;
	private:
		boost::asio::ip::tcp::socket m_socket;
		boost::asio::io_context& m_context;

		boost::asio::ip::tcp::endpoint m_endpoint;

		Buffer m_recvBuffer;
		Buffer m_sendBuffer;
		SessionType m_sessionType;
	};
}

