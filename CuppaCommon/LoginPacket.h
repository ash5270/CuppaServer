#pragma once
#include "Packet.h"


namespace cuppa::net
{
	struct LogData: public IPacketData
	{
		uint16_t GetSize() override
		{
			return sizeof(user_id) + sizeof(channel);
		}
		uint16_t user_id;
		uint16_t channel;
	};

	class LoginSerializer : public PacketSerializer<LogData>
	{
	public:
		void serialize(LogData& t, cuppa::net::Buffer& buffer) override;
		void deserialize(LogData& t, cuppa::net::Buffer& buffer) override;
	};

	class LoginPacket : public Packet
	{
	public:
		Buffer GetBuffer() override;
	private:
		LoginSerializer m_loginSerializer;
		LogData m_loginData;
	};
}

