#pragma once
#include <boost/asio.hpp>
#include "Session.h"
#include "MutexQueue.h"
#include <thread>

using namespace boost;

namespace cuppa::net
{
	class Client
	{
	public:
		virtual ~Client() = default;
		Client(const std::string ip,const int port);
		
	public:
		bool Start();
		bool Stop();
		void Update();

		void Send(Buffer buffer);

		virtual void OnServerConnect(asio::ip::tcp::socket socket) {}
		virtual void OnMessage(Buffer& buffer){}

	private:
		void Connect();

	private:
		bool m_isUpdate;

		MutexQueue<BufferObject> m_readBuffers;
		MutexQueue<BufferObject> m_sendBuffers;
	protected:
		std::shared_ptr<Session> m_session;

		std::thread m_trUpdate;
		std::thread m_contextTr;

		asio::io_context m_asioContext;
		asio::ip::tcp::endpoint m_endpoint;
	};

}