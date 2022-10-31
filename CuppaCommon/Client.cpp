#include "Client.h"

cuppa::net::Client::Client(std::string ip, const int port) :
m_endpoint(asio::ip::address::from_string(ip),port)
{
		
}

bool cuppa::net::Client::Start()
{
	try
	{
		Connect();
		m_isUpdate = true;
		m_trUpdate = std::thread([this]() {Update(); });
		m_contextTr = std::thread([this]() {m_asioContext.run(); });

	}
	catch (std::exception ex)
	{
		printf_s("client start error : %s\n", ex.what());
	}
	
	return true;
}

bool cuppa::net::Client::Stop()
{
	if(m_trUpdate.joinable())
	{
		m_trUpdate.join();
	}
	return true;
}

void cuppa::net::Client::Update()
{
	while(m_isUpdate)
	{
		if (!m_readBuffers.IsEmpty())
		{
			auto recvBuffer = m_readBuffers.FrontPopData();
			OnMessage(recvBuffer.buffer);
		}

		if (!m_sendBuffers.IsEmpty())
		{
			auto sendBuffer = m_sendBuffers.FrontPopData();
			sendBuffer.session->Send(std::move(sendBuffer.buffer));
		}
	}
}

void cuppa::net::Client::Send(Buffer buffer)
{
	//BufferObject buffer_object(m_session, std::move(buffer));
	//m_sendBuffers.PushBack(std::move(buffer_object));
}

void cuppa::net::Client::Connect()
{
	asio::ip::tcp::socket socket(m_asioContext);
	socket.connect(m_endpoint);
	OnServerConnect(std::move(socket));
}

