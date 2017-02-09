/**
 * @file main.cpp
 * @Synopsis  Example for 扩展工厂 in CPP.
 * @author Saki Shum, sakishum1118@gmail.com
 *		为了将具体的派生类和工厂方法解耦并支持在运行时添加新的派生类，
 *		工厂需要需要维护一个映射，此映射将类型名与创建对象的回调关联起
 *		来。然后就可以允许派生类通过一对新的方法调用来实现注册与注销。
 * @version 0.0.1
 * @date 2014-08-26
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "factory_extend.h"
#include "user_item.h"

int main(void) {
	// 注册
	Factor.registerItem("useritem", UserItem::Create);
	Factor.registerItem("useritem", UserItem::Create);
	// 如果目标没有注册或者类型错误，会导致返回NULL，需要验证指针
	ItemBasePtr ptr = (Factor.create("useritem"));
	if (0 != ptr.use_count()) {
		ptr->used();
		ptr.reset();
	} else {
		std::cout << "ptr is null." << std::endl;
	}

	return EXIT_SUCCESS;
}

