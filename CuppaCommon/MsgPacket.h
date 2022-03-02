#pragma once
#include "Packet.h"
#include "Serializer.h"

namespace cuppa::net
{
	struct MsgData : public IPacketData
	{
		uint16_t GetSize() override
		{
			return sizeof(send_user) + sizeof(recv_user) + sizeof(msg_size) + msg.length();
		}
		uint8_t send_user;
		uint8_t recv_user;
		uint8_t msg_size;
		std::string msg;
	};

	class MsgSerializer : public  Serializer<MsgData>
	{
	public:
		void serialize(MsgData& t, cuppa::net::Buffer buffer) override;
		void deserialize(MsgData& t, cuppa::net::Buffer buffer) override;
	};

	class MsgPacket : public Packet
	{
	public:
		Buffer GetBuffer() override;

	private:
		MsgSerializer m_msgSerializer;
		MsgData m_msgData;
	};
}


