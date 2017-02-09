/**
 * @file singleton_template.h
 * @Synopsis  Sample sinleton template, create a thread-unsafe singleton.
 *			单例对象，不支持多线程, 需要手动释放资源。
 *			饿汉模式，在单例类的构造函数里调用另一个单例类的方法可能会出现问题。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-05-13
 */

#pragma once

#include <stddef.h>    	/* NULL */
#include <assert.h>		/* assert */

template<typename T> 
class CSingleton {
public:
	CSingleton(void) {
		assert(!m_instance);
		m_instance = static_cast<T*>(this);
	}
	virtual ~CSingleton(void) {
		assert(m_instance);
		m_instance = NULL;
	}
	// 获取对象引用(兼容旧服务器接口)
	static T &GetInstance(void) {
		assert(m_instance != NULL);
		return *m_instance;
	}
	// 获取对象引用
	static T &getSingleton(void) {
		assert(m_instance != NULL);
		return *m_instance;
	}
	// 获取对象指针
	static T *GetInstancePtr(void) {
		return m_instance;
	} 
	// 获取对象指针(兼容旧服务器接口)
	static T *getSingletonPtr(void) {
		return m_instance;
	} 

protected:
	// 利用的是类的静态全局变量
	static T* m_instance;

private:
	CSingleton(const CSingleton&);
	void operator=(const CSingleton&);
};
