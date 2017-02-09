#include <cstdlib>
#include <iostream>
#include "event_manager.h"
#include "singleton_template.h"

class CEventPump : public CEventManager, public CSingleton<CEventPump> {
public:
	CEventPump(void) {
		std::cout << "constructor." << std::endl;
	}

	virtual ~CEventPump(void) {
		std::cout << "destructor." << std::endl;
	}
};

template<> CEventPump* Singleton<CEventPump>::m_instance = NULL;

class CEventCreator {
public:
	CEventCreator(void) {
		registerEvent();
	}
	~CEventCreator(void) {
		unregisterEvent();
	}
	void registerEvent(void);
	void unregisterEvent(void);
	void launchEvent(void);

	void eventHandle(void* aabb) {
		std::cout << "Callback function was called." << std::endl;
	}
};

void CEventCreator::registerEvent(void) {
	CEventPump::GetInstance().registerMessageHandle(1, &CEventCreator::eventHandle, this);
}

void CEventCreator::unregisterEvent(void) {
	CEventPump::GetInstance().unregisterMessageHandle(1, this);
}

void CEventCreator::launchEvent(void) {
	CEventPump::GetInstance().fireMessage(1, (void*)(0));
}

int main(void) {
	new CEventPump();
	CEventCreator eventCreator;
	eventCreator.launchEvent();
	return EXIT_SUCCESS;
}
