/**
 * @file factory_extend.h
 * @Synopsis  扩展工厂，将具体的派生类和工厂方法解耦并支持在运行时添加新的派生类的工厂模式。
 *		工厂需要需要维护一个映射，此映射将类型名与创建对象的回调关联起
 *		来。然后就可以允许派生类通过一对新的方法调用来实现注册与注销。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-08-27
 */
#pragma once 

#include <string>
#include <vector>
#include <string>
#include <map>
#include "item.h"
#include <boost/function.hpp>

#define Factor CFactory::getInstance()

// 扩展工厂（单例模式）
class CFactory {
	typedef boost::function<ItemBasePtr (void)> CreateCallback;
	typedef std::map<std::string, CreateCallback> CallbackMap;

public:
	static CFactory &getInstance(void);
	void registerItem(const std::string &type, CreateCallback cb);
	void unregisterItem(const std::string &type);
	ItemBasePtr create(const std::string &type);
	
private:
	CFactory(void);
	// 三原则
	~CFactory(void);
	CFactory(const CFactory&);
	void operator=(const CFactory&);
	// 将类型名与创建对象的回调关联起的映射
	CallbackMap m_itemUsed;
};  // class CFactory 

