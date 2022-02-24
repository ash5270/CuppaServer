#pragma once
#include "Common.h"
#include "IOThread.h"
#include "MutexQueue.h"
#include "Session.h"
#include "LogSystem.h"
#include <list>

#define CONTEXT_MAX_COUNT 2

namespace cuppa
{
	namespace net
	{	
		class Server
		{
		public:
			Server(int port);
			virtual ~Server();
		private:
			void WaitForClientConnection();
		public:
			bool Start();
			bool Stop();
			void Update();

			//
			void RecvQueuePush(BufferObject&& buffer_object);
			//connect
			virtual void OnClientConnect(boost::asio::ip::tcp::socket socket){}
			//데이터 recv 
			virtual void OnMessage(BufferObject&& buffer){}
			//현재 io_context를 반환함
			boost::asio::io_context& GetNowContext();
			//현재 io_context를 반환하고 카운트를 하나 올림
			boost::asio::io_context& GetContextAndCounting();

		protected:
			IOThread m_ioThreads[CONTEXT_MAX_COUNT];
			IOThread m_acceptThread;

			std::list<std::shared_ptr<Session>> m_sessionInfos;

		private:
			boost::asio::ip::tcp::acceptor m_acceptor;
			uint32_t n_idCounter = 10000;
			//클라이언트 접속 갯수
			uint32_t client_count;
			uint16_t n_context;
			//
			bool m_isUpdate;

			std::thread m_threadContext[CONTEXT_MAX_COUNT];
			std::thread m_queueThread;

			MutexQueue<BufferObject>* m_recvQueue;
			MutexQueue<BufferObject>* m_sendQueue;
		};
	}
}
