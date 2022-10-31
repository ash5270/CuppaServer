#pragma once
#include "Packet.h"

namespace cuppa::net
{
	enum ServerResult: uint16_t
	{
		Success ,
		Faild,

	};

	struct ResultData :public IPacketData
	{
		uint16_t GetSize() override
		{
			return sizeof(result);
		}

		ServerResult result;
	};

	class ResultSerializer {
	public:
		void serialize(ResultData& t, cuppa::Serializer& serializer);
		void deserialize(ResultData& t, cuppa::Serializer& serializer);
	};

	class ResultPacket :public Packet
	{
	public:
		ResultData GetResultData();
		ResultData m_resultData;
	private:
		void to_stream() override;
		void to_read() override;
		ResultSerializer m_resultSerializer;
		
	};

}
