#pragma once
#include "Packet.h"
#include "Vector3.h"
namespace cuppa::net
{
	struct PosData : public  IPacketData
	{
		uint16_t GetSize() override
		{
			return pos.GetSize() + rotation.GetSize() + sizeof(user);
		}
		Vector3 pos;
		Vector3 rotation;
		uint16_t user;
	};

	class PosSerializer:public PacketSerializer<PosData>
	{
	public:
		void serialize(PosData& t, cuppa::net::Buffer& buffer) override;
		void deserialize(PosData& t, cuppa::net::Buffer& buffer) override;
	};

	class PositionPacket : public Packet
	{
	public:
		Buffer GetBuffer() override;
	private:
		PosSerializer m_posSerializer;
		PosData m_posData;
	};
}

