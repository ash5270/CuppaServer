#include "LoginPacket.h"


void cuppa::net::LoginSerializer::serialize(LoginData& t, cuppa::Serializer& serializer)
{
	to_stream(serializer, t.user_id);
	to_stream(serializer, t.user_passwd);
	to_stream(serializer, t.user_token);

	to_stream(serializer, t.channel);

	to_stream(serializer, t.position.x);
	to_stream(serializer, t.position.y);
	to_stream(serializer, t.position.z);

	
}

void cuppa::net::LoginSerializer::deserialize(LoginData& t, cuppa::Serializer& serializer)
{
	to_read(serializer, t.user_id);
	to_read(serializer, t.user_passwd);
	to_read(serializer, t.user_token);
	
	to_read(serializer, t.channel);

	to_read(serializer, t.position.x);
	to_read(serializer, t.position.y);
	to_read(serializer, t.position.z);

}

void cuppa::net::LoginPacket::to_stream()
{
	m_header.id = (uint16_t)PacketID::login;
	m_header.size = m_loginData.GetSize();

	m_headerSerializer.serialize(m_header, serializer);
	m_loginSerializer.serialize(m_loginData, serializer);
}

void cuppa::net::LoginPacket::to_read()
{
	//m_headerSerializer.deserialize(m_header, serializer);
	m_loginSerializer.deserialize(m_loginData, serializer);
}

void cuppa::net::LoginPacket::ToRead(Buffer* buffer)
{
	serializer.SetBuffer(buffer);
	to_read();
}

