/**
 * @file main.cpp
 * @Synopsis  Example for CRTP model in CPP.
 *		Object counter 问题。类计数器代码：
 *		通过父类中传入子类的类型，实现在编译器的多态(静态多态)。
 *		当然编译器的多态比运行时通过虚函数实现的多态(动态多态)
 *		效率要高，但是这并不是CRTP模式最重要的优点。
 *		CRTP 不可以替代虚函数，虚函数实现了懂太多态，也就是让基
 *		类指向子类，CRTP做不到这点。
 *		CRTP 可以实现和虚函数一样的功能，但是内存大小会有很大优
 *		势。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-10-20
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>

template <typename T> 
class base {
public:
	void foo(void) {
		static_cast<T*>(this)->fooImpl();
	}
private:
	// no need if no need the default implementation
	void fooImpl(void) {
		std::cout << "Hi, i\'m default!" << std::endl;
	}
};

template <typename T>
void bar(base<T> &obj) {
	obj.foo();	// will static dispath
}

class my_type : public base<my_type> {
public:
	// required to compile.
	void fooImpl(void) {
		std::cout << "my_type" << std::endl;
	}
};

class your_type : public base<your_type> {
};

int main(void) {
	my_type my_instance;
	your_type you_instance;
	bar(my_instance);
	bar(you_instance);
	return EXIT_SUCCESS;
}

