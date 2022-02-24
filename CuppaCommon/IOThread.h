#pragma once
#include "Common.h"
#include <boost/asio.hpp>
namespace cuppa::net
{
	class IOThread final
	{
		using IO_CONTEXT = boost::asio::io_context;
		using IO_GUARD = boost::asio::executor_work_guard<IO_CONTEXT::executor_type>;
	public:
		IOThread() = delete;
		IOThread(uint8_t index);
		~IOThread();

		void Start();
		void Join();
		void Stop();

	public:
		IO_CONTEXT& GetContext() { return io_context; }

	private:
		IO_CONTEXT io_context;
		IO_GUARD io_guard;
		std::thread io_thread;
		uint8_t index;

	};
}