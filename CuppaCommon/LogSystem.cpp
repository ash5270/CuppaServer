#include "LogSystem.h"

cuppa::LogSystem* cuppa::LogSystem::m_instnace = nullptr;
cuppa::LogSystem& cuppa::Log::m_logSystem = cuppa::LogSystem::instance();
cuppa::LogData cuppa::Log::m_logData;

cuppa::LogSystem::LogSystem()
{
	m_isQueueLoop = false;
}

cuppa::LogSystem::~LogSystem()
{
	Disable();
}

void cuppa::LogSystem::Start()
{
	m_isQueueLoop = true;

	Log::Print("Start log system ...");

	m_logThread = std::thread(&LogSystem::Update,this);
}

void cuppa::LogSystem::Disable()
{
	if(m_logThread.joinable())
	{
		m_logThread.join();
	}
}

void cuppa::LogSystem::DataEmplace(const LogData& data)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_logDatas.emplace(data);
}

cuppa::LogData cuppa::LogSystem::DataDequeue()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	LogData log = m_logDatas.front();
	m_logDatas.pop();
	return log;	
}

void cuppa::LogSystem::DataCheck(LogData data)
{
	switch (data.type)
	{
	case LogData::LogType::Error:
		printf_s("[ERROR] %s \n", data.ToString());
		break;

	case LogData::LogType::Info:
		printf_s("[INFO] %s \n", data.ToString());
		break;

	case LogData::LogType::Waring:
		printf_s("[WARING] %s \n", data.ToString());
		break;

	case LogData::LogType::Empty:
		printf_s("[ERROR] Log data empty\n");
		break;
	}
}

void cuppa::LogSystem::Update()
{
	while(m_isQueueLoop)
	{
		if(m_logDatas.size()>0)
		{
			auto log = DataDequeue();
			DataCheck(log);
		}else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
}
