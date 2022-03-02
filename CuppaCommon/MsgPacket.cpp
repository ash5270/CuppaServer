﻿#include "MsgPacket.h"

void cuppa::net::MsgSerializer::serialize(MsgData& t, cuppa::net::Buffer buffer)
{
	to_stream(t.send_user,buffer);
	to_stream(t.recv_user,buffer);
	to_stream(t.msg,buffer);
}

void cuppa::net::MsgSerializer::deserialize(MsgData& t, cuppa::net::Buffer buffer)
{
	to_data(t.send_user, buffer);
	to_data(t.recv_user, buffer);
	to_data(t.msg, buffer);
}

cuppa::net::Buffer cuppa::net::MsgPacket::GetBuffer()
{
	m_header.id = 0;
	m_header.size = m_msgData.GetSize();

	m_headerSerializer.serialize(m_header, m_buffer);
	m_msgSerializer.serialize(m_msgData, m_buffer);

	return m_buffer;
}