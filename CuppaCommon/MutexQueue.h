#pragma once
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
				std::lock_guard<std::recursive_mutex > lock(m_mutex);
				m_queue.push(std::move(data));
			}

			void PushBack(const T& data) 
			{
				std::lock_guard<std::recursive_mutex > lock(m_mutex);
				m_queue.push(data);
			}

			T FrontPopData()
			{
				std::lock_guard<std::recursive_mutex > lock(m_mutex);
				auto data = std::move(m_queue.front());
				m_queue.pop();
				return data;
			}

			T PopData()
			{
				std::lock_guard<std::recursive_mutex > lock(m_mutex);
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
			std::recursive_mutex  m_mutex;
		};

	}
}
