#include "observer.h"

ISubject::ISubject(void) {
	// Empty, Do Nothing
}

ISubject::~ISubject(void) {
	// Empty, Do Nothing
}

void ISubject::subscribe(uint32_t message, IObserver *observer) {
	if (NULL != observer) {
		ObserverMap::iterator iter = m_observers.find(message);
		if (iter == m_observers.end()) {
			m_observers[message] = ObserverList();
		}
		m_observers[message].push_back(observer);
	}
}

void ISubject::unsubscribe(uint32_t message, IObserver *observer) {
	ObserverMap::iterator iter = m_observers.find(message);
	if (iter != m_observers.end()) {
		ObserverList &list = m_observers[message];
		ObserverList::iterator liter;
		for (liter = list.begin(); liter != list.end();) {
			if ((*liter) == observer) {
				list.erase(liter);
			} else {
				++liter;
			}
		}
	}
}

void ISubject::notify(uint32_t message) {
	ObserverMap::iterator iter = m_observers.find(message);
	if (iter != m_observers.end()) {
		ObserverList &list = m_observers[message];
		ObserverList::iterator liter;
		for (liter = list.begin(); liter != list.end(); ++liter) {
			(*liter)->update(message);
		}
	}
}




