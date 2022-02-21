#include "Server.h"

cuppa::net::Server::Server(int port)
	:m_acceptor(m_asioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
	m_recvQueue = new MutexQueue <BufferObject>();
	m_sendQueue = new MutexQueue <BufferObject>();
	m_isUpdate = true;
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
		m_threadContext = std::thread([this]() {m_asioContext.run(); });
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
	m_asioContext.stop();
	if (m_threadContext.joinable())
	{
		m_threadContext.join();
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

