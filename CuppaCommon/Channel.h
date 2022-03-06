#pragma once
#include <thread>
#include "MutexQueue.h"
#include "Packet.h"
namespace cuppa::net
{
	class Channel
	{
	public:
		

	private:
		std::thread m_workThread;
		MutexQueue<Packet> m_recvQueue;
		MutexQueue<Packet> m_sendQueue;
	};
}