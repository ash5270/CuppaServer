#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "Buffer.h"
#include "Channel.h"
#include "UserCharacter.h"

namespace cuppa::net
{
	enum class SessionType
	{
		Client,
		Server
	};

	class Server;

	class Session :public std::enable_shared_from_this<Session> 
	{
	public:
		Session(SessionType type, boost::asio::io_context& context, boost::asio::ip::tcp::socket socket);
		Session(Session&& session);
		virtual ~Session();

	public:
		bool ConnectToClient();
		bool ConnectToServer();
		//disconnect
		void DisconnectToClient();

		void Send(const Buffer& buffer);
		void Send(Buffer&& buffer);
	private:
		void Connect();
		void Disconnect(); 
		void RecvData();
		void RecvDataCallBack(boost::system::error_code ec, size_t transferred);
		void SendData(Buffer&& buffer);
		void SendData(const Buffer& buffer);
		void SendDataCallBack(boost::system::error_code ec, size_t transferred);

	public:
		virtual void OnRecv(Buffer buffer, size_t recvSize) {}
		virtual void OnDisconnect(){}
		virtual void OnSend(Buffer buffer, size_t recvSize){}
		
		//전방선언시 참조 형식으로 
		cuppa::net::Server* m_server;

		//user info
		std::string m_user_token;
		uint32_t m_channelInfo;
		//Channel* m_curretChannel;

		//player Data
		UserCharacter*  m_user_character;

	private:
		boost::asio::ip::tcp::socket m_socket;
		boost::asio::io_context& m_context;

		boost::asio::ip::tcp::endpoint m_endpoint;

		Buffer m_recvBuffer;
		Buffer m_sendBuffer;

		SessionType m_sessionType;

		bool is_login;

	public:
		bool IsLogin() const
		{
			return is_login;
		}

		void Login(std::string user_token,uint32_t channel, Vector3 pos)
		{
			m_user_character = new UserCharacter(user_token);
			m_user_character->SetPosition(pos);
			is_login = true;
			this->m_channelInfo = channel;
			this->m_user_token = user_token;
		}
		//observer 
		//void Notify() override;
	};
}

