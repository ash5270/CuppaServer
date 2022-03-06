#include "PositionPacket.h"

void cuppa::net::PosSerializer::serialize(PosData& t, cuppa::net::Buffer& buffer)
{
	to_stream(t.pos.x,buffer);
	to_stream(t.pos.y,buffer);
	to_stream(t.pos.z,buffer);

	to_stream(t.rotation.x,buffer);
	to_stream(t.rotation.y,buffer);
	to_stream(t.rotation.z,buffer);

	to_stream(t.user, buffer);
}

void cuppa::net::PosSerializer::deserialize(PosData& t, cuppa::net::Buffer& buffer)
{
	float x, y, z;
	to_data(x, buffer);
	to_data(y, buffer);
	to_data(z, buffer);
	t.pos.SetVector(x, y, z);

	to_data(x, buffer);
	to_data(y, buffer);
	to_data(z, buffer);
	t.rotation.SetVector(x, y, z);

	to_data(t.user, buffer);
}

cuppa::net::Buffer cuppa::net::PositionPacket::GetBuffer()
{
	m_header.id = (uint16_t)PacketID::position;
	m_header.size = m_posData.GetSize();

	m_headerSerializer.serialize(m_header, m_buffer);
	m_posSerializer.serialize(m_posData, m_buffer);

	return m_buffer;	
}
