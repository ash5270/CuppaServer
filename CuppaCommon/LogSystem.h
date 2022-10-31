#pragma once
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <iostream>
#include "Vector3.h"
namespace cuppa
{
	struct LogData
	{
	public:
		enum class LogType
		{
			Error,
			Info,
			Waring,

			Empty = 10000,
		};
		LogData() = default;

		LogData(const LogData& data)
		{
			m_msg = data.m_msg;
			type = data.type;
		}

		void Clear()
		{
			type = LogType::Empty;
			m_msg = "";
		}

		void Append(const std::string data)
		{
			m_msg += data;
		}

		const char* ToString()
		{
			return m_msg.c_str();
		}

		LogType type;
	private:
		std::string m_msg;
	};


	class LogSystem
	{
	public:
		static LogSystem& instance()
		{
			if (m_instnace == NULL)
			{
				m_instnace = new LogSystem();
			}

			return *m_instnace;
		}

		LogSystem();
		~LogSystem();


	public:
		void Start();
		void Disable();
		void DataEmplace(const LogData& data);
	private:
		LogData DataDequeue();
		void DataCheck(LogData data);
		void Update();

	private:
		std::thread m_logThread;
		static LogSystem* m_instnace;
		std::queue<LogData> m_logDatas;
		bool m_isQueueLoop;

		std::mutex m_mutex;
	};


	class Log
	{
	public:
		template<typename T>
		static void Print(T arg)
		{
			m_logData.type = LogData::LogType::Info;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.Clear();
		}

		template<typename T, typename ... Types>
		static void Print(T arg, Types ... args)
		{
			MakeString(arg);
			Print(args ...);
		}

		template<typename T>
		static void Error(T arg)
		{
			m_logData.type = LogData::LogType::Error;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.Clear();
		}

		template<typename T, typename ... Types>
		static void Error(T arg, Types ... args)
		{
			MakeString(arg);
			Error(args ...);
		}

		template<typename T>
		static void Waring(T arg)
		{
			m_logData.type = LogData::LogType::Waring;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.Clear();
		}

		template<typename T, typename ... Types>
		static void Waring(T arg, Types ... args)
		{
			MakeString(arg);
			Waring(args ...);
		}

	private:
		static void MakeString(const std::string data)
		{
			m_logData.Append(data);
		}

		static void MakeString(char* data)
		{
			m_logData.Append(std::string(data));
		}

		static void MakeString(float data)
		{
			m_logData.Append(std::to_string(data));
		}

		static void MakeString(Vector3 vector3)
		{
			m_logData.Append(std::to_string(vector3.x));
			m_logData.Append(",");
			m_logData.Append(std::to_string(vector3.y));
			m_logData.Append(",");
			m_logData.Append(std::to_string(vector3.z));
		}

		template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
		static void MakeString(const T data)
		{
			m_logData.Append(std::to_string(data));
		}

		template<typename T, std::enable_if_t<std::is_floating_point<T>::value, float> = 0>
		static void MakeString(const T data)
		{
			m_logData.Append(std::to_string(data));
		}



	private:
		static LogSystem& m_logSystem;
		static LogData m_logData;
	};


}

