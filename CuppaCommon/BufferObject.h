#pragma once
#include "Packet.h"

namespace cuppa
{
	namespace net {

		class Session;

		struct BufferObject
		{
			std::shared_ptr<cuppa::net::Session> session;
			PacketHeader header;
			Buffer buffer;

			BufferObject() = default;

			BufferObject(const BufferObject& buffer_object) noexcept
			{
				this->session = buffer_object.session;
				this->header = buffer_object.header;
				this->buffer = buffer_object.buffer;
			}

		/*	BufferObject(BufferObject&& buffer_object) noexcept
			{
				this->session = buffer_object.session;
				this->header = buffer_object.header;
				this->buffer = buffer_object.buffer;

				buffer_object.session = nullptr;
				
			}*/
		};


	}
}

