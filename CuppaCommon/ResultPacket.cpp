#include "ResultPacket.h"

void cuppa::net::ResultSerializer::serialize(ResultData& t, cuppa::Serializer& serializer)
{
	serializer.Write(t.result);
}

void cuppa::net::ResultSerializer::deserialize(ResultData& t, cuppa::Serializer& serializer)
{
	serializer.Read(t.result);
}

cuppa::net::ResultData cuppa::net::ResultPacket::GetResultData()
{
	return m_resultData;
}

void cuppa::net::ResultPacket::to_stream()
{
	m_header.id = (uint16_t)PacketID::serverResult;
	m_header.size = m_resultData.GetSize();

	m_headerSerializer.serialize(m_header, serializer);
	m_resultSerializer.serialize(m_resultData, serializer);
}

void cuppa::net::ResultPacket::to_read()
{
	m_resultSerializer.deserialize(m_resultData, serializer);
}
