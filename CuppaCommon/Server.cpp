#include "Server.h"

cuppa::net::Server::Server(int port)
	:m_acceptThread(3)
	,m_acceptor(m_acceptThread.GetContext(), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	,m_ioThreads{ 0,1 }
{
	m_recvQueue = new MutexQueue <BufferObject>();
	m_sendQueue = new MutexQueue <BufferObject>();
	m_isUpdate = true;

	client_count = 0;
	n_context = 0;
}

cuppa::net::Server::~Server()
{
	cuppa::LogSystem::instance().Disable();
}

void cuppa::net::Server::WaitForClientConnection()
{
	m_acceptor.async_accept([this](std::error_code ec, boost::asio::ip::tcp::socket socket)
		{
			if (!ec)
			{
				OnClientConnect(std::move(socket));
			}
			else
			{
				printf_s("[error] accept error : %s\n", ec.message());
			}
			WaitForClientConnection();
		});
}

bool cuppa::net::Server::Start()
{
	cuppa::LogSystem::instance().Start();
	try
	{
		WaitForClientConnection();
		for (auto& thread : m_ioThreads)
		{
			thread.Start();
		}	

		m_acceptThread.Start();
	}
	catch (std::exception ex)
	{
		printf_s("[error] Server start failed msg : [%s]\n", ex.what());
		return false;
	}
	printf_s("[info] Server start \n");
	return true;
}

bool cuppa::net::Server::Stop()
{
	m_acceptThread.Stop();

	for(auto& thread : m_ioThreads)
	{
		thread.Stop();
	}

	printf_s("[info] Server stop\n");
	return true;
}

void cuppa::net::Server::Update()
{
	while (m_isUpdate)
	{
		if (!m_recvQueue->IsEmpty())
		{
			OnMessage(std::move(m_recvQueue->FrontPopData()));
		}

		if (!m_sendQueue->IsEmpty())
		{
			auto data = m_sendQueue->FrontPopData();
			data.session->Send(std::move(data.buffer));
		}
	}
}

void cuppa::net::Server::RecvQueuePush(BufferObject&& buffer_object)
{
	m_recvQueue->PushBack(std::move(buffer_object));
}

boost::asio::io_context& cuppa::net::Server::GetNowContext()
{
	return m_ioThreads[n_context].GetContext();
}

boost::asio::io_context& cuppa::net::Server::GetContextAndCounting()
{
	uint16_t result = n_context;
	if (n_context >= CONTEXT_MAX_COUNT - 1)
	{
		n_context = 0;
	}
	else
	{
		n_context++;
	}
	return m_ioThreads[result].GetContext();
}