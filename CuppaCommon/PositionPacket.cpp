#include "PositionPacket.h"

void cuppa::net::PosSerializer::serialize(PosData& t, cuppa::Serializer& serializer)
{
	to_stream(serializer,t.pos.x);
	to_stream(serializer,t.pos.y);
	to_stream(serializer,t.pos.z);

	to_stream(serializer,t.rotation.x);
	to_stream(serializer,t.rotation.y);
	to_stream(serializer,t.rotation.z);

	to_stream(serializer, t.veloctiy.x);
	to_stream(serializer, t.veloctiy.y);

	to_stream(serializer, t.animation);

	to_stream(serializer,t.user);
}

void cuppa::net::PosSerializer::deserialize(PosData& t, cuppa::Serializer& serializer)
{
	to_read(serializer, t.pos.x);
	to_read(serializer, t.pos.y);
	to_read(serializer, t.pos.z);

	to_read(serializer, t.rotation.x);
	to_read(serializer, t.rotation.y);
	to_read(serializer, t.rotation.z);

	to_read(serializer, t.veloctiy.x);
	to_read(serializer, t.veloctiy.y);

	to_read(serializer, t.animation);

	to_read(serializer, t.user);
}

void cuppa::net::PositionPacket::to_stream()
{
	m_posSerializer.serialize(m_posData, serializer);
}

void cuppa::net::PositionPacket::to_read()
{
	m_posSerializer.deserialize(m_posData, serializer);
}

void cuppa::net::PositionPacket::ToRead(Buffer* buffer)
{
	serializer.SetBuffer(buffer);
	to_read();
}
