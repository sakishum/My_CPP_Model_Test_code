#include "factory_extend.h"
#include <iostream>

CFactory &CFactory::getInstance(void) {
	static CFactory instance;
	return instance;
}

void CFactory::registerItem(const std::string &type, CreateCallback cb) {
	CallbackMap::iterator iter = m_itemUsed.find(type);
	if (iter != m_itemUsed.end()) {
		std::cout << "Already exist." << std::endl;
	} else {
		m_itemUsed[type] = cb;
	}
}

void CFactory::unregisterItem(const std::string &type) {
	if (!type.empty()) {
		CallbackMap::iterator iter = m_itemUsed.find(type);
		if (iter != m_itemUsed.end()) {
			m_itemUsed.erase(type);
		}
	}
}

ItemBasePtr CFactory::create(const std::string &type) {
	if (!type.empty()) {
		CallbackMap::iterator iter = m_itemUsed.find(type);

		if (iter != m_itemUsed.end()) {
			// 调用回调以构造此派生类型的对象
			return (iter->second)();
		}
	}
	return NULL;
}

CFactory::CFactory(void) {
	m_itemUsed.clear();
}

CFactory::~CFactory(void) {
	// Empty. Do Nothing.
}
