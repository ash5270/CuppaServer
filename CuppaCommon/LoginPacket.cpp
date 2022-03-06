#include "LoginPacket.h"

void cuppa::net::LoginSerializer::serialize(LogData& t, cuppa::net::Buffer& buffer)
{
	to_stream(t.user_id, buffer);
	to_stream(t.channel, buffer);
}

void cuppa::net::LoginSerializer::deserialize(LogData& t, cuppa::net::Buffer& buffer)
{
	to_data(t.user_id, buffer);
	to_data(t.channel, buffer);
}

cuppa::net::Buffer cuppa::net::LoginPacket::GetBuffer()
{
	m_header.id = (uint16_t)PacketID::login;
	m_header.size = m_loginData.GetSize();

	m_headerSerializer.serialize(m_header, m_buffer);
	m_loginSerializer.serialize(m_loginData, m_buffer);

	return m_buffer;
}
