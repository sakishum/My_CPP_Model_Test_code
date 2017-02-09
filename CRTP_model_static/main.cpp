/**
 * @file main.cpp
 * @Synopsis  Example for CRTP model in CPP.
 *		用 CRTP (静态分发) 在 C++ 中实现静态函数的多态。
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
	// 静态的 interface
	void static foo() {
		T::foo();
	}
};

template <typename T>
void bar(base<T> &obj) {
	obj.foo();	// will static dispath
}

class my_type : public base<my_type> {
public:
	void static foo(void) {
		std::cout << "Static foo from my_type" << std::endl;
	}
};

class your_type : public base<your_type> {
public:
	void static foo(void) {
		std::cout << "Static foo from your_type" << std::endl;
	}
};

int main(void) {
	my_type my_instance;
	your_type you_instance;
	bar(my_instance);
	bar(you_instance);
	return EXIT_SUCCESS;
}

