#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <stdint.h>
#include <vector>
#include "platform.h"

class CFunctionSlotBase {
public:
	virtual ~CFunctionSlotBase(void) { /* Empty, Do Nothing. */ }
	virtual bool operator()(void *){ return true; }
	virtual long getThisAddr(void) { return 0; }
	virtual long getFunAddr(void) { return 0; }
	virtual void emptyThisAddr(void) { }
};  // class CFunctionSlotBase 

template<typename T , typename T2>
class CFunctionSlot : public CFunctionSlotBase {
public:
	CFunctionSlot( void (T::*f)( T2* ) , T * obj )
		:m_funPtr( f ),m_this( obj ){ }

	virtual ~CFunctionSlot(void) { }

	virtual bool operator() (void *pdata) {
		if( m_this != NULL && m_funPtr != NULL ) {
			(m_this->*m_funPtr)( reinterpret_cast<T2*>( pdata ) );
			return true;
		}
		else
			return false;
	}

	virtual long getThisAddr(void) {
		return ( *reinterpret_cast<long*>( &m_this ) );
	}

	virtual void emptyThisAddr(void) {
		m_this = NULL;
	}

	virtual long getFunAddr(void) {
		//提取类成员函数地址，&m_funPtr 取出成员函数指针地址，将其转为指向long型的指针，再用*取出地址值
		// "提领类型双关的指针将破坏强重叠规则"	-O2 时报错!!!
		// dereferencing type-punned pointer will break strict-aliasing rules
		// 它给出警告的位置一般来说是不会错的——gcc想告诉你的是当你提领了指针后，你可能会破坏重叠规则（除
		// 非你首先将它转换为原始类型）。该警告应该解释为，你的接口可能设计得很差，同时正确避免该警告的
		// 方式是重新以一种无须在相冲突的类型之间转换的方式重新设计他们。
		// reinterpret_cast<long>(somePointer)
		// It's used to convert the address of the pointer to its numeric representation and store it as a long.
		return ( *reinterpret_cast<long*>( &m_funPtr ) );
	}

private:
	typedef void (T::*f)( T2* );
	f m_funPtr;
	T * m_this;
};  // class CFunctionSlot

class CEventManager {
public:
	virtual ~CEventManager(void) {
		for (MSGMAP::iterator it = m_msgMap.begin(); it != m_msgMap.end(); ++it) {
			std::vector<CFunctionSlotBase* > * p = it->second ;
			for (std::vector<CFunctionSlotBase* >::iterator it2 = p->begin(); it2 != p->end(); ++it2) {
				delete *it2;
			}
			p->clear();
			delete p;
		}
		m_msgMap.clear();
	}
	/*
	*注册服务器回发事件处理例程的函数
	*参数一：消息类型
	*参数二：处理例程的地址 例程函数定义为 void f( char* )
	*参数三：例程对象的地址
	*/
	template<typename T , typename T2>
	bool registerMessageHandle(uint32_t  msgType, void (T::*f)( T2* ), T * obj) {
		std::vector<CFunctionSlotBase* > * vec = NULL;
		MSGMAP::iterator it = m_msgMap.find( msgType );
		if (it == m_msgMap.end()) {
			vec = new  std::vector<CFunctionSlotBase* >;
		} else {
			vec = it->second;
		}

		CFunctionSlotBase * pslot = new CFunctionSlot<T, T2>( f , obj );
		if (!pslot) { 
			return false;
		}

		vec->push_back( pslot );
		m_msgMap.insert( std::make_pair( msgType , vec ) );
		return true;
	}

	/**
	 * @Synopsis  unregisterMessageHandle 
	 *		注销册回调函数
	 * @tparam T
	 * @Param msgType	消息标识
	 * @Param obj		目标对象
	 *
	 * @Returns   
	 */
	template<typename T> 
	bool unregisterMessageHandle(uint32_t msgType , T* obj ) {
		std::vector<CFunctionSlotBase* > * vec = NULL;
		MSGMAP::iterator it = m_msgMap.find( msgType );
		if (it == m_msgMap.end() ) {
			return true ;
		} else {
			vec = it->second;
		}

		long thisAddr = *reinterpret_cast<long *>( &obj );

		for (std::vector<CFunctionSlotBase* >::iterator itor =  vec->begin(); itor != vec->end(); ++itor) {
			if ((*itor)->getThisAddr() == thisAddr) {
				//反注册并不真实删除，只是将this指针置空
				(*itor)->emptyThisAddr();
			}
		}
		return true;
	}

	template<typename T>
	bool fireMessage(uint32_t type, T * pdata) {
		//判断该类型事件是否在系统中注册
		MSGMAP::iterator typeIt = m_msgMap.find( type );
		if (typeIt == m_msgMap.end()) {
			print_log("%s, Not Found MsgID in Module.\n", __func__);
			return false;
		}

		//发送数据到对应的注册函数中
		for (std::vector<CFunctionSlotBase* >::iterator itor =  typeIt->second->begin(); itor != typeIt->second->end(); ++itor) {
			//判断该成员函数指针对应的对象是否为0，防止对象意外被删除
			if ((*itor)->getThisAddr() != 0) {
				(**itor)( pdata );
			}
		}
		return true;
	}

protected:
	//用于保存注册的函数地址
	xHashMap<uint32_t, std::vector<CFunctionSlotBase* >* > m_msgMap;
	typedef xHashMap<uint32_t, std::vector<CFunctionSlotBase* >* > MSGMAP;
};  // class CEventManager

#endif  // EVENT_MANAGER_H_

