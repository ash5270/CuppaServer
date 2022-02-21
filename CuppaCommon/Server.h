#pragma once
#include "Common.h"
#include "MutexQueue.h"
#include "Session.h"
#include <list>

namespace  cuppa
{
	namespace net
	{	
		class Server
		{
		public:
			Server(int port);
		private:
			void WaitForClientConnection();
		public:
			bool Start();
			bool Stop();
			void Update();

			void RecvQueuePush(BufferObject&& buffer_object);


			virtual void OnClientConnect(boost::asio::ip::tcp::socket socket){}
			//virtual void OnClientConnect(std::shared_ptr<Session> session){}
			virtual void OnMessage(BufferObject&& buffer){}
		protected:
			boost::asio::io_context m_asioContext;
			std::list<std::shared_ptr<Session>> m_sessionInfos;
		private:
			boost::asio::ip::tcp::acceptor m_acceptor;

			uint32_t n_idCounter = 10000;
			bool m_isUpdate;
			std::thread m_threadContext;
			std::thread m_queueThread;

			MutexQueue<BufferObject>* m_recvQueue;
			MutexQueue<BufferObject>* m_sendQueue;
		};
	}
}
