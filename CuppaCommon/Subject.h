#pragma once
#include "Observer.h"

namespace cuppa
{
	class Subject
	{
	public:
		virtual ~Subject() = default;
	public:
		virtual void registerObserver(Observer* observer) = 0;
		virtual void removeObserver(Observer* observer) = 0;
		virtual void notifyObserver() = 0;
	};
}
