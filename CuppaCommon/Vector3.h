#pragma once
#include <iostream>

namespace cuppa
{
	struct Vector3
	{
		float x, y, z;

		size_t GetSize()
		{
			return sizeof(x) + sizeof(y) + sizeof(z);
		}

		Vector3 operator + (Vector3 vector3 )
		{
			
		}
	};
}
