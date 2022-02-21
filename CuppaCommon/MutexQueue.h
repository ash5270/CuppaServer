#pragma once
#include "BufferObject.h"
#include <queue>
#include <mutex>
namespace cuppa
{
	namespace net
	{
		template<typename T>
		class MutexQueue
		{
		public:
			MutexQueue(){}
		public:
			void PushBack(const T&& data)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_queue.push(std::move(data));
			}

			T FrontPopData()
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				auto data = std::move(m_queue.front());
				m_queue.pop();
				return data;
			}

			size_t Size()
			{
				return m_queue.size();
			}

			bool IsEmpty()
			{
				return m_queue.empty();
			}

		private:
			std::queue<T> m_queue;
			std::mutex m_mutex;
		};

	}
}
