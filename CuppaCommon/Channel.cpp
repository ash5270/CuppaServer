#include "Channel.h"
#include "LogSystem.h"
#include"Session.h"
#include"PacketSerializer.h"
#include "Server.h"
#include"UserInfoPacket.h"

#include <thread>
cuppa::net::Channel::Channel()
{
	is_thread_loop = false;
	//m_recvQueue = new MutexQueue<BufferObject>();
}

cuppa::net::Channel::~Channel()
{

}


void cuppa::net::Channel::Init(Server* server)
{
	m_workThread = std::thread([&]() {Update(); });
	is_thread_loop = true;

	currentServer = server;
	m_session_manager = new SessionManager(0);
}

void cuppa::net::Channel::Stop()
{
	is_thread_loop = false;
	if (m_workThread.joinable())
		m_workThread.join();
}

void cuppa::net::Channel::RutinUpdate()
{

}


/*cuppa::Log::Print("user : ", data->user, " pos :", data->pos.x, ", ", data->pos.y, ", ", data->pos.z,
			", rotation : ",data->rotation.x,", ", data->rotation.y, ", ", data->rotation.z,
			", velocity :" ,data->veloctiy.x,", ",data->veloctiy.y,", ",data->animation);*/
void cuppa::net::Channel::OnData(BufferObject bufferObject)
{
	switch (bufferObject.header.id)
	{
	case (uint16_t)PacketID::position:
	{
		PositionPacket packet;
		packet.ToRead(&bufferObject.buffer);
		auto data = &packet.GetData();
		bufferObject.session->m_user_character->SetPosition(data->pos);

		Buffer buffer;
		packet.SetBuffer(&buffer);
		PosData pos_data(data->pos, data->rotation, data->veloctiy, data->animation, data->user);

		PacketHeaderSerializer header_serializer;
		header_serializer.serialize(bufferObject.header, packet.serializer);

		packet.SetData(pos_data);
		packet.ToStream(&buffer);


			//유저 
		for (auto session : m_session_manager->GetSession())
		{
			auto otherPlayer_pos = session->m_user_character->GetUserPos();

			if(Vector3::Distacne(data->pos,otherPlayer_pos)<20)
			{
				Buffer new_buffer(buffer);
				session->Send(std::move(new_buffer));
			}
		}
	}
	break;

	case (uint16_t)PacketID::userInfo:
	{
		UserInfoPacket user_packet;
		user_packet.ToRead(&bufferObject.buffer);
		auto user_data = user_packet.GetData();
		if (user_data.user_info == UserData::UserInfo::ALL)
		{
			m_session_manager->AllSessionInfoSend(bufferObject.session);
		}
	}
	break;
	}
}

cuppa::net::SessionManager* cuppa::net::Channel::GetSessionManager()
{
	return m_session_manager;
}

void cuppa::net::Channel::DiconnectSession(std::shared_ptr<Session> session)
{
	m_session_manager->UnRegisterSession(session);
}

void cuppa::net::Channel::Update()
{
	while (is_thread_loop)
	{
		if (m_recvQueue.Size() > 0) {
			auto object = m_recvQueue.PopData();
			OnData(object);
			//std::cout << "Channel::Update " << "thread id : " << std::this_thread::get_id() << std::endl;
		}

		if (m_sendQueue.Size() > 0) {
			auto object = m_sendQueue.PopData();
			//object.session->Send(std::move(object.buffer));
		}
	}
}

