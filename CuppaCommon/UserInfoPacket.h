#pragma once
#include "Serializer.h"
#include "Packet.h"
namespace cuppa::net
{
	struct UserData : public IPacketData
	{
		std::string user;
		uint16_t channel;
		uint16_t user_info;
		Vector3 position;

		uint16_t GetSize() override
		{
			return sizeof(uint16_t) + sizeof(uint16_t)+ sizeof(uint16_t) + user.size() + position.GetSize();
		}

		enum UserInfo:uint16_t
		{
			Login=1,
			LogOut=2,
			ALL=100,
		};
	};

	class UserInfoSerializer
	{
	public:
		void serialize(UserData& t, cuppa::Serializer& serializer);
		void deserialize(UserData& t, cuppa::Serializer& serializer);
	};

	class UserInfoPacket : public Packet
	{
	private:
		void to_stream() override;
		void to_read() override;
	private:
		UserInfoSerializer m_userInfoSerializer;
		UserData m_userdata;

	public:
		void ToRead(Buffer* buffer) override;

		const UserData& GetData()
		{
			return m_userdata;
		}

		void SetBeffer(Buffer* buffer)
		{
			this->serializer.SetBuffer(buffer);
			this->m_buffer = buffer;
		}

		void SetData(UserData& user_data)
		{
			m_userdata = user_data;
		}
	};
}
