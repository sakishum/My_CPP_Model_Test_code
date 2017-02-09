#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/noncopyable.hpp>

class A : public boost::noncopyable {
public:
	A(void);
	~A(void) {
		if(m_pimple) {
			m_pimple.reset();
		}
	}
	void setA(int);
	int getA(void) const;

private:
	class Pimple;
	boost::scoped_ptr<Pimple> m_pimple;
};

class A::Pimple {
public:
	Pimple(void) : m_a(0) {}
	void setA(int val) { m_a = val; } 
	int getA(void) const { return m_a; }

private:
	int m_a;
};

A::A(void) : m_pimple(new A::Pimple()) {
	assert(m_pimple);
}

void A::setA(int val) {
	m_pimple->setA(val);
}

int A::getA(void) const {
	return m_pimple->getA();
}

int main(void) {
	A a1;
	//A a2 = a1;	// call to implicitly-deleted copy constructor of 'A'
	a1.setA(12);
	std::cout << "a.m_pimple.m_a = " << a1.getA() << std::endl;
	exit(EXIT_SUCCESS);
}
