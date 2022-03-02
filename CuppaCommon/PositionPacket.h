#pragma once
#include "Packet.h"
namespace cuppa::net 
{
	struct PosData : public  IPacketData
	{
		float x;
		float y;
		float z;
	};

	class PositionPacket
	{
	public:

	};
}

