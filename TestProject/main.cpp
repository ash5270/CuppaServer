#include "Server.h"
#include "BufferObject.h"
#include "MsgPacket.h"
#include "PacketSerializer.h"
#include "UserInfoPacket.h"
#include<chrono>
#include <memory>



class CuppaSession : public cuppa::net::Session
{
public:
	CuppaSession(cuppa::net::SessionType type, boost::asio::io_context& context, boost::asio::ip::tcp::socket socket):
		Session(type,context,std::move(socket))
	{
		
	}

	void OnRecv(cuppa::net::Buffer buffer, size_t recvSize) override
	{
		//처음 받았을때 패킷 해더를 확인한다.
		//packet id 디시리얼라이즈 
		cuppa::net::PacketHeader header;
		cuppa::net::PacketHeaderSerializer header_serializer;
		cuppa::Serializer serializer;
		serializer.SetBuffer(&buffer);
		header_serializer.deserialize(header, serializer);
		//std::cout << "Session::Recv " << "thread id : " << std::this_thread::get_id() << std::endl;
		//만약 로그인 패킷이라면 로그인을 하고 채널에 넣어준다
		if (header.id == (uint16_t)cuppa::net::PacketID::login) {
			cuppa::net::LoginPacket login;
			login.ToRead(&buffer);
			auto data = login.GetData();
			cuppa::net::LoginPacket login_packet;
			cuppa::net::LoginData loginData;

			loginData.user_id = "";
			loginData.user_passwd = "";
			loginData.user_token.append("token : ");
			loginData.user_token.append(data.user_id);
			loginData.channel = data.channel;
			loginData.position = data.position;

			Login(loginData.user_token, loginData.channel,loginData.position);

			cuppa::net::Buffer new_buffer;

			login_packet.SetData(loginData);
			login_packet.ToStream(&new_buffer);
			Send(std::move(new_buffer));

			m_server->GetChannel(m_channelInfo)->GetSessionManager()->RegisterSession(shared_from_this());
		
		}
		//이미 로그인 되어있다면 자신의 채널에 있는 로직 스레드에 패킷을 보낸다.
		else
		{
			cuppa::net::BufferObject recv_packet;
			recv_packet.header = header;
			uint8_t* begin = reinterpret_cast<uint8_t*>(buffer.GetBuffer() + 4);
			recv_packet.buffer = cuppa::net::Buffer(begin,header.size);
			recv_packet.session = shared_from_this();

			m_server->ChannelAddRecvData(0, std::move(recv_packet));
		}
	}
	

	void OnDisconnect() override
	{
		m_server->ClientDisconnet(shared_from_this());
	}
};

class CuppaServer : public cuppa::net::Server
{
public:
	CuppaServer(int port) : cuppa::net::Server(port)
	{
		m_count = 0;
	}

	void OnClientConnect(boost::asio::ip::tcp::socket socket) override
	{
		std::shared_ptr<cuppa::net::Session>
			new_session= std::make_shared<CuppaSession>(cuppa::net::SessionType::Server,
														GetContextAndCounting(),
														std::move(socket));

		if(new_session)
		{
			new_session->m_server = this;
			new_session->ConnectToClient();

			cuppa::Log::Print("client count : ", m_sessionInfos.size() , ", connect success...");

			m_count++;
			m_sessionInfos.push_back(std::move(new_session));
		}
	}

	void OnMessage(cuppa::net::BufferObject&& buffer) override
	{
		printf_s("recv data\n");
	}

	void ClientDisconnet(std::shared_ptr<cuppa::net::Session> m_session) override
	{
		if(m_session->IsLogin())
			m_channels[m_session->m_channelInfo]->DiconnectSession(m_session);


		m_sessionInfos.remove(m_session);
		cuppa::Log::Print("client count : ", m_sessionInfos.size(), ", disconnect success...");
	}

private:
	int m_count = 0;
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