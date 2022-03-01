#pragma once
#include "Buffer.h"
#include "Common.h"
#include <cassert>
#include <type_traits>

namespace cuppa
{
	template<typename T>
	class Serializer
	{
	public:
		virtual ~Serializer() = default;
		virtual void serialize( T& t, cuppa::net::Buffer buffer) = 0;
		virtual void deserialize( T& t, cuppa::net::Buffer buffer) = 0;
	};

	//
	template <class T, class B, class Enable = void>
	class Serializer
	{
	public:
		static void serialize(const T& t, B& bufffer)
		{
			t.serialize(bufffer);
		}

		static void deserialize(T& t, B& buffer)
		{
			t.deserialize(buffer);
		}
	};

	//float 
	template<class T, class B>
	class Serializer<T, B, typename std::enable_if<std::is_floating_point<T>::value, void>::type>
	{
	public:
		static void serialize(const T& num, B& buffer)
		{
			const char* num_ptr = reinterpret_cast<const char*>(&num);
			buffer.Write(num_ptr, sizeof(num));
		}

		static void deserialize(T& num, B& buffer)
		{
			char* num_ptr = reinterpret_cast<char*>(&num);
			buffer.Read(num_ptr, sizeof(num));
		}
	};

	//uint 
	template<class T, class B>
	class Serializer<T, B, typename std::enable_if<std::is_unsigned<T>::value, void>::type>
	{
	public:
		static void serialize(const T& num, B& buffer)
		{
			const char* num_ptr = reinterpret_cast<const char*>(&num);
			buffer.Write(num_ptr,sizeof(T));
		}

		static void deserialize(T& num, B& buffer)
		{
			char* num_ptr = reinterpret_cast<char*>(&num);
			buffer.Read(num_ptr, sizeof(num));
		}
	};

	//int
	template<class T, class B>
	class Serializer<T, B, typename  std::enable_if<std::is_signed<T>::value&& std::is_integral<T>::value, void>::type>
	{
	public:
		static void serialize(const T& num, B& buffer)
		{
			/*const size_t n_bits = sizeof(num) * 8;
			using UT = typename  std::make_unsigned<T>::type;
			UT zigzaged_num = (num << 1) ^ (num >> (n_bits - 1));
			Serializer<UT, B>::serialize(zigzaged_num, buffer);*/
			const char* num_ptr = reinterpret_cast<const char*>(&num);
			buffer.Write(num_ptr, sizeof(T));
		}

		static void deserialize(T& num, B& buffer)
		{
			/*using UT = typename std::make_unsigned<T>::type;
			UT zigzaged_num;
			Serializer<UT, B>::deserialize(zigzaged_num, buffer);
			num = (-(zigzaged_num & 1)) ^ (zigzaged_num >> 1);*/
			char* num_ptr = reinterpret_cast<char*>(&num);
			buffer.Read(num_ptr, sizeof(num));
		}
	};

	template<class B>
	class Serializer<std::string, B> {
	public:
		static void serialize(const std::string& str, B& buffer)
		{
			const size_t n_bytes = str.size();
			Serializer<size_t, B>::serialize(n_bytes, buffer);
			buffer.Write(str.data(), n_bytes);
		}

		static void deserialize(std::string& str, B& buffer)
		{
			size_t n_bytes;
			Serializer<size_t, B>::deserialize(n_bytes, buffer);
			str.resize(n_bytes);

		}
	};

	template<class T>
	void to_stream(const T&t ,cuppa::net::Buffer& buffer)
	{
		Serializer<T, cuppa::net::Buffer>::serialize(t, buffer);
	}

	template<class T>
	void to_data(T& t, cuppa::net::Buffer&buffer)
	{
		Serializer<T, cuppa::net::Buffer>::deserialize(t, buffer);
	}
	
}
