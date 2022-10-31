#pragma once
#include <iostream>
#include <cmath>
namespace cuppa
{
	struct Vector3
	{
	public:
		Vector3()
		{
			x = y = z = 0;
		}

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3(const Vector3& vector3)
		{
			x = vector3.x;
			y = vector3.y;
			z = vector3.z;
		}

		void SetVector(const float x, const float y, const float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		size_t GetSize() const
		{
			return sizeof(x) + sizeof(y) + sizeof(z);
		}

		inline const Vector3 operator +(const Vector3 vector3)
		{
			return Vector3(x + vector3.x, y + vector3.y, z + vector3.z);
		}

		inline const Vector3& operator =(const Vector3& vector3)
		{
			x = vector3.x;
			y = vector3.y;
			z = vector3.z;
			return *this;
		}

		inline const Vector3& operator+=(const Vector3& vector3)
		{
			x += vector3.x;
			y += vector3.y;
			z += vector3.z;

			return *this;
		}

		inline  static Vector3 Zero()
		{
			return Vector3(0, 0, 0);
		}

		inline const static float Distacne(const Vector3 front, const Vector3 back)
		{
			float new_x = pow(back.x - front.x,2);
			float new_y = pow(back.y - front.y,2);
			float new_z = pow(back.z - front.z,2);

			float result = new_x + new_y + new_z;
			return sqrt(result);
		}


	public:
		//º¯¼ö
		float x, y, z;

	};
}