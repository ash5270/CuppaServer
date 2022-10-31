#pragma once
#include <list>
#include <iostream>
namespace cuppa::net
{
	class Session;
	class SessionManager 
	{
	public:
		SessionManager();
		SessionManager(const unsigned int channel);
		~SessionManager();
	public:
		void RegisterSession(std::shared_ptr<Session> session);
		void UnRegisterSession(std::shared_ptr<Session> session);
		void AllSessionInfoSend(std::shared_ptr<Session> session);

	 	std::list < std::shared_ptr<Session>> GetSession() const;
	private:
		std::list<std::shared_ptr<Session>> sessions;
		unsigned int m_channel_info;

	};
}
