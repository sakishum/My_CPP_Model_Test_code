#pragma once 

#include <cstdio>
#include <cstdlib>

// 虚基类
// 有纯虚函数的类是抽象类，而抽象类是无法实例化的
class Abstract_base {
public:
	virtual ~Abstract_base(void) { }
	virtual void foo(void) = 0;		// 纯虚函数
};  // class Abstract_base
