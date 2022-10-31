#pragma once
#include "Packet.h"
#include "Vector3.h"
#include "Vector2.h"
namespace cuppa::net
{
	struct PosData : public  IPacketData
	{
		Vector3 pos;
		Vector3 rotation;
		std::string user;
		
		Vector2 veloctiy;
		uint16_t animation;

		//size 
		uint16_t GetSize() override
		{
			return pos.GetSize() + rotation.GetSize() + sizeof(user) + veloctiy.GetSize()+ sizeof(animation);
		}
		//생성자
		PosData()
		{
			pos = Vector3::Zero();
			rotation = Vector3::Zero();
			user = "";
		}

		PosData(PosData& data)
		{
			this->pos = data.pos;
			this->rotation = data.rotation;
			this->user = data.user;
			this->veloctiy = data.veloctiy;
			this->animation = data.animation;
		}

		PosData(const Vector3 position, const Vector3 rotation,Vector2 veloctiy,uint16_t animation, const std::string user) 
		{
			this->pos = position;
			this->rotation = rotation;
			this->user = user;
			this->veloctiy =veloctiy;
			this->animation = animation;
		}
	};

	class PosSerializer
	{
	public:
		void serialize(PosData& t, cuppa::Serializer& serializer);
		void deserialize(PosData& t, cuppa::Serializer& serializer);
	};

	class PositionPacket : public Packet
	{
	public:
		void to_stream() override;
		void to_read() override;
	private:
		PosSerializer m_posSerializer;
		PosData m_posData;

	public:
		void ToRead(Buffer* buffer) override;

		void SetBuffer(Buffer* buffer)
		{
			this->serializer.SetBuffer(buffer);
			this->m_buffer = buffer;
		}

		const PosData& GetData()
		{
			return m_posData;
		}

		void SetData(PosData data)
		{
			m_posData = data;
		}
	};
}
//
