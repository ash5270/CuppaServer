#pragma once
#include "Session.h"

namespace cuppa
{
	namespace net {

		struct BufferObject
		{
			std::shared_ptr<cuppa::net::Session> session;
			Buffer buffer;
		};
	}
}

