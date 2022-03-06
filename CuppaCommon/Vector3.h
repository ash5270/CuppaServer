#pragma once
#include <iostream>

namespace cuppa
{
	struct Vector3
	{
	public:
		Vector3()	
		{
			x = y = z = 0;
		}

		Vector3(float x,float y,float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3(Vector3& vector3)
		{
			x = vector3.x;
			y = vector3.y;
			z = vector3.z;
		}

		void SetVector(float x,float y,float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		size_t GetSize()
		{
			return sizeof(x) + sizeof(y) + sizeof(z);
		}

		Vector3 operator +(const Vector3 vector3)
		{
			return Vector3(x+vector3.x, y+vector3.y, z+vector3.z);
		}

		Vector3& operator+=(const Vector3& vector3)
		{
			x += vector3.x;
			y += vector3.y;
			z += vector3.z;

			return *this;
		}



		float x, y, z;

	};
}