#pragma once
#include <thread>
#include "MutexQueue.h"

namespace cuppa::net
{
	class Channel
	{
	public:


	private:
		std::thread m_workThread;
		MutexQueue<Buffer> m_bufferQueue;

	};
}

