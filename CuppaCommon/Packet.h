#pragma once
#include <iostream>
#include "Buffer.h"
namespace cuppa::net
{
	struct PacketHeader
	{
		uint16_t id;
		uint16_t size;
	};

	class Packet
	{
	public:
		
	private:
		Buffer m_buffer;
		PacketHeader m_header;
	};

	class PacketHeaderSerializer
	{
	public:
		PacketHeaderSerializer() = default;
		~PacketHeaderSerializer() = default;
	public:
		void Serialize(const PacketHeader header, Buffer& buffer)
		{
			buffer.Write(&header.id,sizeof(header.id));
			buffer.Write(&header.size,sizeof(header.size));
		}

		PacketHeader DeSerialize(const Buffer& buffer)
		{
			
		}
	};
}
