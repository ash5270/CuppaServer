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
		uint16_t send_user;
		uint16_t recv_user;
		uint16_t msg_size;
		std::string msg;
	};

	class MsgSerializer : public  PacketSerializer<MsgData>
	{
	public:
		void serialize(MsgData& t, cuppa::net::Buffer& buffer) override;
		void deserialize(MsgData& t, cuppa::net::Buffer& buffer) override;
	};

	class MsgPacket : public Packet
	{
	public:
		Buffer GetBuffer() override;
		MsgData GetData();
	private:
		MsgSerializer m_msgSerializer;
		MsgData m_msgData;
	};
}


