#include "IOThread.h"

cuppa::net::IOThread::IOThread(uint8_t index):io_context(),
io_guard(boost::asio::make_work_guard(io_context)),
index(index)
{

}

cuppa::net::IOThread::~IOThread()
{
	Stop();
}

void cuppa::net::IOThread::Start()
{
	io_thread = std::thread([&]() {io_context.run(); });
}

void cuppa::net::IOThread::Join()
{
	if(io_thread.joinable()==true)
	{
		io_thread.join();
	}
}

void cuppa::net::IOThread::Stop()
{
	io_guard.reset();
	io_context.stop();
	Join();
}
