#pragma once
#include <iostream>
#include "Buffer.h"
#include "Common.h"
#include "Serializer.h"

namespace cuppa::net
{
	enum class PacketID : uint16_t
	{
		userInfo = 10,
		login = 100,
		msg = 1000,
		position = 1001,

		serverResult = 4000
	};

	interface IPacketData
	{
		virtual ~IPacketData() = default;
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

	struct RecvPacket
	{
		uint16_t packet_ID;
		Buffer buffer;
	};

	class PacketHeaderSerializer 
	{
	public:
		PacketHeaderSerializer() = default;
		~PacketHeaderSerializer() = default;
		
		void serialize(PacketHeader& t, cuppa::Serializer& serializer) 
		{
			to_stream(serializer, t.id);
			to_stream(serializer, t.size);
		}
		void deserialize(PacketHeader& t, cuppa::Serializer & serializer)
		{
			to_read(serializer, t.id);
			to_read(serializer, t.size);
		}
	};

	class Packet
	{
	public:
		Packet() = default;
		virtual ~Packet() = default;
	protected:
		Buffer* m_buffer;
		PacketHeader m_header;

	public:
		//virtual  Buffer GetBuffer() = 0;
		Serializer serializer;
		PacketHeader GetHeader()
		{
			return m_header;
		}

		void SetHeader(PacketHeader header)
		{
			m_header = header;
		}

		//버퍼 셋팅 
		void SetBuffer(Buffer* buffer)
		{
			m_buffer = buffer;
		}


		void ToStream(Buffer* buffer)
		{
			serializer.SetBuffer(buffer);
			m_buffer = buffer;
			to_stream();
		}

		virtual void ToRead(Buffer* buffer)
		{
			serializer.SetBuffer(buffer);
			to_read();
		}
	private:
		virtual void to_stream() = 0;
		virtual void to_read() = 0;
	
	protected:
		PacketHeaderSerializer m_headerSerializer;
	};
}
