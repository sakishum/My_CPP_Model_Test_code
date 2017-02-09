/**
 * @file user_item.h
 * @Synopsis	提供给扩展工厂方法的派生类，它继承了虚基类ItemBase。
 *		注意Create 方法，这是因为工厂方法的注册方法需要接收一个返回
 *		对象的回调，此回调不必是ItemBase 的一部分，它还可以是自由函
 *		数。把他添加进ItemBase 也是个好方式，因为这样就能把所有相关
 *		功能置于相同的地方。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-08-27
 */
#pragma once 
#include <iostream>
#include <boost/smart_ptr.hpp>
#include "item.h"

typedef boost::shared_ptr<class UserItem> UserItemPtr;

class UserItem : public CItemBase {
public:
	UserItem(void) { 
		// Empty, Do Nothing.
	}

	virtual ~UserItem(void) {
		// Empty, Do Nothing.
	}
	
	static UserItemPtr Create(void) {
		return UserItemPtr(new UserItem());
	}

	UserItem(const UserItem&);
	void operator=(const UserItem&);

private:
	virtual void _used(void) {
		std::cout << "user item used." << std::endl;
	}
};  // class UserItem

