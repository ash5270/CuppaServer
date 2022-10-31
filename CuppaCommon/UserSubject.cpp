#include "UserSubject.h"

void cuppa::UserSubject::registerObserver(Observer* observer)
{
	m_observers.push_back(observer);
}

void cuppa::UserSubject::removeObserver(Observer* observer)
{
	m_observers.remove(observer);
}

void cuppa::UserSubject::notifyObserver()
{
	for (auto observer : m_observers)
	{
		observer->Notify();
	}
}
