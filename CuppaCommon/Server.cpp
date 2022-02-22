#include "Server.h"

cuppa::net::Server::Server(int port)
	:m_acceptor(m_acceptContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
	m_recvQueue = new MutexQueue <BufferObject>();
	m_sendQueue = new MutexQueue <BufferObject>();
	m_isUpdate = true;

	client_count = 0;
	n_context = 0;
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
	try
	{
		WaitForClientConnection();
		m_acceptThread = std::thread([this]() {m_acceptContext.run(); });

		for(int i=0; i< CONTEXT_MAX_COUNT; i++)
		{
			m_threadContext[i] = std::thread([this,i]() {m_asioContexts[i].run(); });
		}

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
	m_acceptContext.stop();
	if(m_acceptThread.joinable())
	{
		m_acceptThread.join();
	}

	for(auto & context: m_asioContexts)
	{
		context.stop();
	}

	for(auto & thread : m_threadContext)
	{
		if(thread.joinable())
		{
			thread.join();
		}
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
	return m_asioContexts[n_context];
}

boost::asio::io_context& cuppa::net::Server::GetContextAndCounting()
{
	uint16_t result = n_context;
	if(n_context >= CONTEXT_MAX_COUNT - 1)
	{
		n_context = 0;
	}else
	{
		n_context++;
	}
	return m_asioContexts[result];
}

