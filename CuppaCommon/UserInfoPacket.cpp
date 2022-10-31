#include "UserInfoPacket.h"

void cuppa::net::UserInfoSerializer::serialize(UserData& t, cuppa::Serializer& serializer)
{
	to_stream(serializer, t.user);
	to_stream(serializer, t.channel);
	to_stream(serializer, t.user_info);

	to_stream(serializer, t.position.x);
	to_stream(serializer, t.position.y);
	to_stream(serializer, t.position.z);
}

void cuppa::net::UserInfoSerializer::deserialize(UserData& t, cuppa::Serializer& serializer)
{
	to_read(serializer, t.user);
	to_read(serializer, t.channel);
	to_read(serializer, t.user_info);

	to_read(serializer, t.position.x);
	to_read(serializer, t.position.y);
	to_read(serializer, t.position.z);
}

void cuppa::net::UserInfoPacket::to_stream()
{
	m_userInfoSerializer.serialize(m_userdata, serializer);
}

void cuppa::net::UserInfoPacket::to_read()
{
	m_userInfoSerializer.deserialize(m_userdata, serializer);
}

void cuppa::net::UserInfoPacket::ToRead(Buffer* buffer)
{
	serializer.SetBuffer(buffer);
	to_read();
}
