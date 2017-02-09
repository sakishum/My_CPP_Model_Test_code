/**
 * @file main.cpp
 * @Synopsis  Example for abstract base class in CPP.
 *		HAS-A
 *		纯虚函数的定义仅提供方法的原型. 虽然在抽象类中通常不提供纯虚函数的实现,
 *		但是抽象类中可以包含其实现, 而且可以不在声明的同时给出定义. 每个非抽象子
 *		类仍然需要重载该方法, 抽象类中实现的调用可以采用以下这种形式.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-08-26
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "./abstract_base.h"

class Bar : public Abstract_base {
public:
	virtual void foo(void) {
		Abstract_base::foo();
	}
};  // class bar

int main(void) {
	Bar bar;
	bar.foo();
	return EXIT_SUCCESS;
}
