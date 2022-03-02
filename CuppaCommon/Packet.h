#pragma once
#include <iostream>
#include "Buffer.h"
#include "Common.h"
#include "Serializer.h"

namespace cuppa::net
{
	interface IPacketData
	{
		virtual uint16_t GetSize() = 0;
	};

	struct PacketHeader : public  IPacketData
	{
		uint16_t GetSize() override
		{
			return sizeof(id) + sizeof(size);
		}
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
		Packet() = default;
		virtual ~Packet() = default;
	protected:
		Buffer m_buffer;
		PacketHeader m_header;
	public:
		virtual  Buffer GetBuffer() = 0;

		PacketHeader GetHeader()
		{
			return m_header;
		}

		void SetHeader(PacketHeader header)
		{
			m_header = header;
		}

	protected:
		PacketHeaderSerializer m_headerSerializer;
	};
}
