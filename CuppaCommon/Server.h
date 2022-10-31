#pragma once
#include "Common.h"
#include "IOThread.h"
#include "MutexQueue.h"
#include "Session.h"
#include "LogSystem.h"
#include "BufferObject.h"
#include "Channel.h"
#include <list>

#define CONTEXT_MAX_COUNT 5

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
			//모든 유저에게 메시지를 보냄
			void SendAllUSer(Buffer&& buffer);
			//들어온 버퍼 저장 
			void RecvQueuePush( BufferObject&& buffer_object);
			//connect
			virtual void OnClientConnect(boost::asio::ip::tcp::socket socket){}
			//데이터 recv 
			virtual void OnMessage(BufferObject&& buffer){}
			//유저가 나갈때
			virtual void ClientDisconnet(std::shared_ptr<Session> m_session){}
			//현재 io_context를 반환함
			boost::asio::io_context& GetNowContext();
			//현재 io_context를 반환하고 카운트를 하나 올림
			boost::asio::io_context& GetContextAndCounting();
			//채널추가
			void AddChannel();
			//데이터 보내기
			void ChannelAddRecvData(int channel,const BufferObject buffer);
			//
			Channel* GetChannel(int index)
			{
				return m_channels[index];
			}
		protected:
			IOThread m_ioThreads[CONTEXT_MAX_COUNT];
			IOThread m_acceptThread;
			//user 관리
			std::list<std::shared_ptr<Session>> m_sessionInfos;
			//channel 
			std::unordered_map<int, Channel*> m_channels;
			uint32_t m_channel_count;
		private:
			boost::asio::ip::tcp::acceptor m_acceptor;
			uint32_t n_idCounter = 10000;

			//클라이언트 접속 갯수
			uint32_t client_count;
			uint16_t n_context;

			//
			bool m_isUpdate;

			//
			std::thread m_threadContext[CONTEXT_MAX_COUNT];
			std::thread m_queueThread;

			//
			MutexQueue<BufferObject>* m_recvQueue;
			MutexQueue<BufferObject>* m_sendQueue;
			
		};
	}
}
