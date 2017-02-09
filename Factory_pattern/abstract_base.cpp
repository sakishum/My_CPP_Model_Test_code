#include "./abstract_base.h"
#include <iostream>

// "纯虚方法不提供实现"的说法是不正确的。是可以为纯虚方法提供默认实现的。
// 前提是派生类需要显式的重写此方法。
void Abstract_base::foo(void) {
	std::cout << "Abstract_base::" << __func__ << std::endl;
}
