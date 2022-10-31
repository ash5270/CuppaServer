#pragma once
#include "MutexQueue.h"
#include <thread>
#include <unordered_map>
#include "BufferObject.h"
#include "SessionManager.h"
namespace cuppa::net
{
	class Server;
	class Channel 
	{
	public:
		Channel();
		~Channel();
	public:
		void Init(Server* server);
		void Stop();
		void RutinUpdate();
		//void AddUser(Observer* observer);

		virtual void OnData(BufferObject bufferObject);
		//서버에서 넘어온 buffer 넘어주기 
		void PushData(BufferObject buffer)
		{
			m_recvQueue.PushBack(buffer);
		}
		SessionManager* GetSessionManager();
		//채널에서 나갈경우
		void DiconnectSession(std::shared_ptr<Session> session);

	private:
		void Update();

	private:
		std::thread m_workThread;
		bool is_thread_loop;

		MutexQueue<BufferObject> m_recvQueue;
		MutexQueue<BufferObject> m_sendQueue;
		
		Server* currentServer;
	private:
		SessionManager* m_session_manager;
	};
}