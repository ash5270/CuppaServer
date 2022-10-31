#pragma once

namespace cuppa
{
	struct Vector2
	{
	public:
		Vector2()
		{
			x = y = 0;
		}
		//생성자
		Vector2(float x,float y)
		{
			this->x = x;
			this->y = y;
		}
		//복사 생성자
		Vector2(const Vector2& vector2)
		{
			x = vector2.x;
			y = vector2.y;
		}
	
		size_t GetSize()
		{
			return sizeof(x) + sizeof(y);
		}

		inline const Vector2 operator +(const Vector2 vector2)
		{
			return Vector2(x + vector2.x, y + vector2.y);
		}

		inline const Vector2 operator =(const Vector2 vector2)
		{
			return Vector2(vector2.x, vector2.y);
		}

		inline const Vector2 operator +=(const Vector2 vector2)
		{
			return Vector2(x+vector2.x, y+vector2.y);
		}

		static Vector2 Zero()
		{
			return Vector2(0, 0);
		}

		//변수
		float x;
		float y;

	};
}

