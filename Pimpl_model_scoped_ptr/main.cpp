#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/noncopyable.hpp>

class A {
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
	// scoped_ptr 的用法与普通的指针没有什么区别；最大的区别
	// 在于不必再记得在指针上调用 delete，还有复制是不允许的。
	// 与 auto_ptr 的区别是，所有权不能转移，但是可以交换。
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
	//A a2 = a1;		// call to implicitly-deleted copy constructor of 'A'
	a1.setA(12);
	std::cout << "a.m_pimple.m_a = " << a1.getA() << std::endl;
	exit(EXIT_SUCCESS);
}
