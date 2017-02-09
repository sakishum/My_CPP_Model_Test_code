/**
 * @file item.h
 * @Synopsis  抽象基类（ABC, abstruct Base Class）,是包含一个或多个
 *			纯虚函数的类，他不是实体类，不能使用new操作进行实例化。
 *			每一个继承CItemBase的类都要定义一个工厂方法。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-08-27
 */
#pragma once 

#include <boost/smart_ptr.hpp>

typedef boost::shared_ptr<class CItemBase> ItemBasePtr;

class CItemBase {
public:
	CItemBase (void) {
		// Do Nothing.
	}

	// 对于包含一个或多个纯虚的函数的类，应该
	// 始终将抽象基类的析构函数声明为虚的。
	virtual ~CItemBase(void) {
		// Do Nothing.
	} 

	void used(void) {
		_used();		
	}

	CItemBase(const CItemBase&);
	void operator=(const CItemBase&);

private:
	virtual void _used(void) = 0;	// 纯虚函数
};  // class Item

