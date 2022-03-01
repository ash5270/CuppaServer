#pragma once
#include <iostream>
#include "Buffer.h"
#include "Common.h"
#include "Serializer.h"

namespace cuppa::net
{
	interface IPacketData
	{
		
	};

	struct PacketHeader : public  IPacketData
	{
		uint16_t id;
		uint16_t size;
	};

	class PacketHeaderSerializer : public Serializer<PacketHeader>
	{
	public:
		PacketHeaderSerializer() = default;
		~PacketHeaderSerializer() = default;

		void serialize(PacketHeader& t, cuppa::net::Buffer buffer) override
		{
			to_stream(t.id, buffer);
			to_stream(t.size, buffer);
		}
		void deserialize(PacketHeader& t, cuppa::net::Buffer buffer) override
		{
			to_data(t.id, buffer);
			to_data(t.size, buffer);
		}
	};

	class Packet
	{
	public:
		PacketHeaderSerializer serializer;
	private:
		Buffer m_buffer;
		PacketHeader m_header;
	};
}
