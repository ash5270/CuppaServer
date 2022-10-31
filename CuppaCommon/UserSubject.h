#pragma once
#include "Subject.h"
#include <list>
namespace cuppa
{
	class UserSubject: public Subject
	{
	public:
		void registerObserver(Observer* observer) override;
		void removeObserver(Observer* observer) override;
		void notifyObserver() override;

	private:
		std::list<Observer*> m_observers;
	};
}
