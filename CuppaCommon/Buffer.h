#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <exception>

#define COPYMEMORY(target, original, size) memcpy_s(target,size,original,size)

#define CLEARMEMORY(buffer,size)memset(buffer,0,size)

namespace  cuppa
{
	namespace net
	{
		class Buffer
		{
		public:
			//생성자
			Buffer() :
				m_buffer(new uint8_t[BUFFER_SIZE]),
				m_capacity(BUFFER_SIZE),
				m_offset(0),
				m_readOffset(0)
			{
				CLEARMEMORY(m_buffer, m_capacity);
			}

			//복사 생성자 
			Buffer(const Buffer& buffer) :
				m_buffer(new uint8_t[buffer.m_capacity]),
				m_capacity(buffer.m_capacity),
				m_offset(buffer.m_offset),
				m_readOffset(buffer.m_readOffset)
			{
				COPYMEMORY(m_buffer, buffer.m_buffer, BUFFER_SIZE);
			}

			//이동 생성자 
			Buffer(Buffer&& buffer) noexcept :
				m_buffer(buffer.m_buffer),
				m_capacity(buffer.m_capacity),
				m_offset(buffer.m_offset),
				m_readOffset(buffer.m_readOffset)
			{
				buffer.m_buffer = nullptr;
				buffer.m_capacity = 0;
				buffer.m_offset = 0;
			}

			//소멸자 
			~Buffer()
			{
				try
				{
					if(m_buffer!=nullptr)
					{
						delete[] m_buffer;
						m_buffer = nullptr;
						m_capacity = 0;
						m_offset = 0;
					}
				}catch (std::exception ex)
				{
					printf_s("[Error] buffer delete msg : %s", ex.what());
				}
			}

		public:
			Buffer& operator =(cuppa::net::Buffer& buffer)
			{
				m_capacity = buffer.GetCapacity();
				m_offset = buffer.GetSize();

				COPYMEMORY(m_buffer, buffer.m_buffer, BUFFER_SIZE);

				return *this;
			}

			Buffer& operator=(cuppa::net::Buffer&&buffer)
			{
				m_capacity = buffer.GetCapacity();
				m_offset = buffer.GetSize();
				m_buffer = buffer.GetBuffer();

				/*buffer.m_capacity = 0;
				buffer.m_offset = 0;
				buffer.m_buffer = nullptr;*/
			}

		public:
			void SetSize(size_t size) { m_offset = size; }
			size_t GetSize() const { return  m_offset; }
			size_t GetCapacity() const { return  m_capacity; }
			uint8_t* GetBuffer() const { return m_buffer; }

			bool Write(const void* data,size_t size)
			{
				if (m_offset + size >= m_capacity)
					return  false;

				COPYMEMORY(m_buffer + m_offset, data, size);
				m_offset += size;
				return true; 
			}

			bool Write(const char* data,size_t size)
			{
				if(m_offset + size > m_capacity)
				{
					return  false;
				}
				COPYMEMORY(m_buffer + m_offset, data, size);
				m_offset += size;
				return true;
			}

			bool Write(const char data)
			{
				size_t char_size = sizeof(char);
				if(m_offset+ char_size > m_capacity)
				{
					return  false;
				}
				COPYMEMORY(m_buffer + m_offset, &data, char_size);
				m_offset += char_size;
				return  true;
			}

			bool Read(char* data,size_t size)
			{
				if (size < 0 || m_readOffset>m_offset)
				{
					return false;
				}

				COPYMEMORY(data, m_buffer+m_readOffset, size);
				m_readOffset += size;
				return true;
			}

			bool Read(void* data, size_t size)
			{
				if (size < 0 || m_readOffset>m_offset)
				{
					return false;
				}

				COPYMEMORY(data, m_buffer + m_readOffset, size);
				m_readOffset += size;
				return true;
			}

			void Clear()
			{
				CLEARMEMORY(m_buffer, m_capacity);
				m_readOffset = 0;
				m_offset = 0;
			}

		public:
			constexpr static uint32_t BUFFER_SIZE = 1024;

		private:
			uint8_t* m_buffer;

			size_t m_capacity;
			size_t m_offset;
			size_t m_readOffset;
		};
	}
}


