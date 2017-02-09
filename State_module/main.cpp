#include <cstdint>
#include <cstdlib>
#include <iostream>


class CMachine;
class COn;
class COff;

class CState {
public:
	CState(void) { }
	virtual ~CState(void) { }

	virtual void on(CMachine *machine) {
		std::cout << "already on" << std::endl;
	}

	virtual void off(CMachine *machine) {
		std::cout << "already off" << std::endl;
	}
};  // class CState

class CMachine {
public:
	CMachine(void);
	void setCurrent(CState *state) {
		m_current = state;
	}
	void on(void);
	void off(void);

private:
	CState *m_current;
};  // class CMachine

void CMachine::on(void) {
	m_current->on(this);
}

void CMachine::off(void) {
	m_current->off(this);
}

class COn : public CState {
public:
	COn(void) {
		std::cout << "	ON-ctor ";
	}

	virtual ~COn(void) {
		std::cout << "	dtor-ON" << std::endl;
	}

	void off(CMachine *machine);
};  // class COn

class COff : public CState {
public:
	COff(void) {
		std::cout << "  OFF-ctor ";
	}

	virtual ~COff(void) {
		std::cout << "  dtor-OFF" << std::endl;
	}

	void on(CMachine *machine) {
		std::cout << "	going from to ON";
		machine->setCurrent(new COn());
		delete this;
	}
};  // class COff

void COn::off(CMachine *machine) {
	std::cout << "	going from ON to OFF";
	machine->setCurrent(new COff());
	delete this;
}

CMachine::CMachine(void) {
	m_current = new COff();
	std::cout << std::endl;
}

int main(void) {
	void(CMachine:: *ptrs[])() = {
		CMachine::off, CMachine::on
	};
	CMachine fsm;
	int num = 0;
	while (1) {
		std::cout << "Enter 0/1:";
		std::cin >> num;
		(fsm, *ptrs[num])();
	}
	return EXIT_SUCCESS;
}
