#include "Server.h"
#include"BufferObject.h"
#include <memory>

class CuppaSession : public cuppa::net::Session
{
public:
	CuppaSession(cuppa::net::SessionType type, boost::asio::io_context& context, boost::asio::ip::tcp::socket socket):
		Session(type,context,std::move(socket))
	{
		cuppa::Log::Print("connect success...");
	}

	void OnRecv(cuppa::net::Buffer buffer, size_t recvSize) override
	{
		cuppa::Log::Print("data recv...");
		cuppa::net::Buffer send_buffer(buffer);

		cuppa::net::BufferObject buffer_object(shared_from_this(), std::move(buffer));
		m_server->RecvQueuePush(std::move(buffer_object));
		Send(std::move(send_buffer));

	}

	void OnDisconnect() override
	{
		
	}
};

class CuppaServer : public cuppa::net::Server
{
public:
	CuppaServer(int port) : cuppa::net::Server(port)
	{
			
	}

	void OnClientConnect(boost::asio::ip::tcp::socket socket) override
	{
		std::shared_ptr<cuppa::net::Session>
			new_session= std::make_shared<CuppaSession>(cuppa::net::SessionType::Server,
														GetContextAndCounting(),
														std::move(socket));

		if(new_session)
		{
			//new_session->m_server = this;
			new_session->m_server = this;
			new_session->ConnectToClient();
			m_sessionInfos.push_back(std::move(new_session));
		}
	}

	void OnMessage(cuppa::net::BufferObject&& buffer) override
	{
		printf_s("recv data\n");
	}
};

int main()
{
	CuppaServer server(3000);
	server.Start();
	while(true)
	{
		
	}

	return  0;
}