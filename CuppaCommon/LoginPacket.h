#pragma once
#include <string>
#include "Packet.h"
#include "Vector3.h"

namespace cuppa::net
{
	struct LoginData: public IPacketData
	{
		//uint32_t user_id;

		std::string user_id;
		std::string user_passwd;
		std::string user_token;
		Vector3 position;
		uint16_t channel;

		uint16_t GetSize() override
		{
			return sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint16_t) +
				sizeof(channel) + user_id.size() + user_passwd.size() + user_token.size() + position.GetSize();
		}
	};

	class LoginSerializer 
	{
	public:
		void serialize(LoginData& t, cuppa::Serializer& serializer);
		void deserialize(LoginData& t, cuppa::Serializer& serializer);
	};

	class LoginPacket : public Packet
	{
	private:
		void to_stream() override;
		void to_read() override;
	private: 
		LoginSerializer m_loginSerializer;
		LoginData m_loginData;

	public:
		void ToRead(Buffer* buffer) override;

		const LoginData& GetData()
		{
			return  m_loginData;
		}

		void SetData(LoginData data)
		{
			m_loginData = data;
		}
	};
}

