#include "SessionManager.h"
#include "UserInfoPacket.h"
#include "Session.h"
#include"LogSystem.h"
cuppa::net::SessionManager::SessionManager()
{

}

cuppa::net::SessionManager::SessionManager(const unsigned int channel)
{
	m_channel_info = channel;
}

cuppa::net::SessionManager::~SessionManager()
{

}

void cuppa::net::SessionManager::RegisterSession(std::shared_ptr<Session> session)
{
	//여기서 모든 세션에게 지금 들어온 세션 정보 다 알려주기
	if(sessions.size()>0)
	{
		UserData data;
		data.user = session->m_user_token;
		data.channel = session->m_channelInfo;
		data.user_info = UserData::UserInfo::Login;
		data.position = session->m_user_character->GetUserPos();

		Buffer buffer;
		UserInfoPacket packet;
		packet.SetBeffer(&buffer);
		packet.SetData(data);

		PacketHeader header;
		PacketHeaderSerializer header_serializer;

		header.id = (uint16_t)PacketID::userInfo;
		header.size = data.GetSize();
		header_serializer.serialize(header, packet.serializer);

		packet.ToStream(&buffer);

		for (auto currentSession : sessions)
		{
			Buffer new_buffer(buffer);
			currentSession->Send(std::move(new_buffer));
		}
	}
	
	sessions.push_back(session);
}

void cuppa::net::SessionManager::UnRegisterSession(std::shared_ptr<Session> session)
{
	//등록을 해제한후 모든 유저에게 나갔다고 알려주기
	if (sessions.size() > 0)
	{
		sessions.remove(session);
	}
	else
		return;

	UserData data;
	data.user = session->m_user_token;
	data.channel = session->m_channelInfo;
	data.user_info = UserData::UserInfo::LogOut;

	Buffer buffer;
	UserInfoPacket packet;
	packet.SetBeffer(&buffer);
	packet.SetData(data);

	PacketHeader header;
	PacketHeaderSerializer header_serializer;

	header.id = (uint16_t)PacketID::userInfo;
	header.size = data.GetSize();
	header_serializer.serialize(header, packet.serializer);

	packet.ToStream(&buffer);

	for (auto currentSession : sessions)
	{
		Buffer new_buffer(buffer);
		currentSession->Send(std::move(new_buffer));
	}
}

void cuppa::net::SessionManager::AllSessionInfoSend(std::shared_ptr<Session> session)
{
	UserData data;

	for (auto user : sessions)
	{
		data.user.append(user->m_user_token);
		data.user.append(",");
	}

	

	data.channel = m_channel_info;
	data.user_info= UserData::UserInfo::ALL;

	Buffer buffer;
	UserInfoPacket packet;
	packet.SetBeffer(&buffer);
	packet.SetData(data);

	PacketHeader header;
	PacketHeaderSerializer header_serializer;

	header.id = (uint16_t)PacketID::userInfo;
	header.size = data.GetSize();
	header_serializer.serialize(header, packet.serializer);

	packet.ToStream(&buffer);

	session->Send(std::move(buffer));
}

std::list<std::shared_ptr<cuppa::net::Session>> cuppa::net::SessionManager::GetSession() const
{
	return  sessions;
}
