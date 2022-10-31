#pragma once
#include "Buffer.h"
#include "Common.h"
#include "Vector3.h"

namespace cuppa
{
	class Serializer
	{
	public:
		template<typename T>
		inline bool Write(const T& data)
		{
			size_t size = sizeof(data);
			buffer->Write(reinterpret_cast<const uint8_t*>(&data), size);
			return true;
		}

		inline bool Write(const uint8_t* datas, size_t size)
		{
			buffer->Write(datas, size);
			return true;
		}

		template<typename T>
		inline bool Read(__out T& data)
		{
			size_t size = sizeof(data);
			buffer->Read(reinterpret_cast<uint8_t*>(&data), size);
			return true;
		}

		inline bool Read(uint8_t* datas, size_t size)
		{
			buffer->Read(datas, size);
			return true;
		}

		void SetBuffer(net::Buffer* set_buffer)
		{
			buffer = set_buffer;
		}

		uint8_t* GetReadPos()
		{
			return buffer->GetBuffer() + buffer->m_readOffset;
		}

		void AddReadPos(uint16_t pos)
		{
			buffer->m_readOffset += pos;
		}

	private:
		net::Buffer* buffer;
	};


	//Write
	inline bool to_stream(Serializer& serializer, bool value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, int8_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, uint8_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, uint16_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, int16_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, uint32_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, int32_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, int64_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, uint64_t value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, float value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, double value)
	{
		return serializer.Write(value);
	}

	inline bool to_stream(Serializer& serializer, std::string string)
	{
		auto size = static_cast<uint16_t>(string.size());
		if(!to_stream(serializer,size))
		{
			return false;
		}
		auto msg = reinterpret_cast<const uint8_t*>(string.c_str());
		return serializer.Write(msg, size);
	}

	inline bool to_stream(Serializer& serializer, Vector3 vector3)
	{
		size_t size = vector3.GetSize();
		if (!serializer.Write(size))
		{
			return false;
		}

		bool result = serializer.Write(vector3.x);
		result = serializer.Write(vector3.y);
		result = serializer.Write(vector3.z);

		return result;
	}

	//Read
	inline bool to_read(Serializer& serializer, __out bool& value)
	{
		return  serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out int8_t& value)
	{
		return  serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out uint8_t& value)
	{
		return  serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out uint16_t& value)
	{
		return  serializer.Read(value);
	}


	inline bool to_read(Serializer& serializer, __out int16_t& value)
	{
		return  serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out uint32_t& value)
	{
		return	serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out int32_t& value)
	{
		return	serializer.Read(value);
	}


	inline bool to_read(Serializer& serializer, __out int64_t& value)
	{
		return	serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out uint64_t& value)
	{
		return	serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out float& value)
	{
		return serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer, __out double& value)
	{
		return	serializer.Read(value);
	}

	inline bool to_read(Serializer& serializer,__out std::string& value)
	{
		uint16_t size = 0;
		if(!to_read(serializer,size))
		{
			value.assign("");
			return false;
		}

		const char* begin = reinterpret_cast<const char*>(serializer.GetReadPos());
		value.assign(begin, size);
		serializer.AddReadPos(size);
		
		return true;
	}


	//template <class T, class B, class Enable = void>
	//class Serializer
	//{
	//public:
	//	static void serialize(const T& t, B& bufffer)
	//	{
	//		t.serialize(bufffer);
	//	}

	//	static void deserialize(T& t, B& buffer)
	//	{
	//		t.deserialize(buffer);
	//	}
	//};

	//template<typename T>
	//class PacketSerializer
	//{
	//public:
	//	virtual ~PacketSerializer() = default;
	//	virtual void serialize(T& t, cuppa::net::Buffer& buffer) = 0;
	//	virtual void deserialize(T& t, cuppa::net::Buffer& buffer) = 0;
	//};


	////float 
	//template<class T, class B>
	//class Serializer<T, B, typename std::enable_if<std::is_floating_point<T>::value, void>::type>
	//{
	//public:
	//	static void serialize(const T& num, B& buffer)
	//	{
	//		const char* num_ptr = reinterpret_cast<const char*>(&num);
	//		buffer.Write(num_ptr, sizeof(num));
	//	}

	//	static void deserialize(T& num, B& buffer)
	//	{
	//		float* num_ptr = reinterpret_cast<float*>(&num);
	//		buffer.Read(num_ptr, sizeof(num));
	//	}
	//};

	////uint 
	//template<class T, class B>
	//class Serializer<T, B, typename std::enable_if<std::is_unsigned<T>::value, void>::type>
	//{
	//public:
	//	static void serialize(const T& num, B& buffer)
	//	{
	//		const char* num_ptr = reinterpret_cast<const char*>(&num);
	//		buffer.Write(num_ptr,sizeof(T));
	//	}

	//	static void deserialize(T& num, B& buffer)
	//	{
	//		char* num_ptr = reinterpret_cast<char*>(&num);
	//		buffer.Read(num_ptr, sizeof(num));
	//	}
	//};

	////int
	//template<class T, class B>
	//class Serializer<T, B, typename  std::enable_if<std::is_signed<T>::value&& std::is_integral<T>::value, void>::type>
	//{
	//public:
	//	static void serialize(const T& num, B& buffer)
	//	{
	//		const char* num_ptr = reinterpret_cast<const char*>(&num);
	//		buffer.Write(num_ptr, sizeof(T));
	//	}

	//	static void deserialize(T& num, B& buffer)
	//	{
	//		char* num_ptr = reinterpret_cast<char*>(&num);
	//		buffer.Read(num_ptr, sizeof(num));
	//	}
	//};

	//template<class B>
	//class Serializer<std::string, B> {
	//public:
	//	static void serialize(const std::string& str, B& buffer)
	//	{
	//		const size_t n_bytes = str.size();
	//		Serializer<size_t, B>::serialize(n_bytes, buffer);
	//		buffer.Write(str.data(), n_bytes);
	//	}

	//	static void deserialize(std::string& str, B& buffer)
	//	{
	//		uint16_t n_bytes;
	//		Serializer<uint16_t, B>::deserialize(n_bytes, buffer);
	//		char* num_ptr = new char[n_bytes+1];
	//		buffer.Read(num_ptr, n_bytes);
	//		str = num_ptr;
	//		str.resize(n_bytes);
	//	}
	//};

	//template<typename T>
	//void to_stream(const T&t ,cuppa::net::Buffer& buffer)
	//{
	//	Serializer<T, cuppa::net::Buffer>::serialize(t, buffer);
	//}

	//template<typename  T>
	//void to_data(T& t, cuppa::net::Buffer&buffer)
	//{
	//	Serializer<T, cuppa::net::Buffer>::deserialize(t, buffer);
	//}
}
