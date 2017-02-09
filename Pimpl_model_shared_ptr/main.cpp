#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <boost/smart_ptr.hpp>

struct B {
	int m_b;
};

struct C {
	int m_c;
};

class A {
public:
	A(void) {
		m_pimple = boost::make_shared<Pimple>();
		assert(m_pimple);
	}
	~A(void) {
		if(m_pimple) {
			m_pimple.reset();
		}
	}
	void setA(int);
	int getA(void) const;
private:
	struct Pimple;
	boost::shared_ptr<Pimple> m_pimple;
};

struct A::Pimple {
	int m_a;
	B b;
	C c;
};

void A::setA(int val) {
	m_pimple->m_a = val;
}

int A::getA(void) const {
	return m_pimple->m_a;
}

int main(void) {
	A a1;
	a1.setA(12);
	A a2 = a1;
	std::cout << "a1.m_pimple.m_a = " << a1.getA() << std::endl;
	std::cout << "a2.m_pimple.m_a = " << a2.getA() << std::endl;
	exit(EXIT_SUCCESS);
}
