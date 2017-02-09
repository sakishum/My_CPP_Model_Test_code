/**
 * @file main.cpp
 * @Synopsis  使用智能指针改善工厂方法。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-12-24
 */
#include <cstdlib>
#include <vector>
#include <iostream>
#include <boost/smart_ptr.hpp>

typedef boost::shared_ptr<class CObject> CObjectPtr;	
typedef std::vector<CObjectPtr> PCObjectVec;

class CObject {
public:
	~CObject(void) { 
		std::cout << "Destructor." << std::endl;
	}

	static CObjectPtr createInstance(void) {
		//return boost::make_shared<CObject>();
		return CObjectPtr(new CObject());
	}

	CObject(const CObject&);
	void operator=(const CObject&);
private:
	CObject(void) { 
		std::cout << "Constructor." << std::endl;
	}
};  // class CObject

int main(void) {
	CObjectPtr ptr = CObject::createInstance();
	CObjectPtr ptr1 = ptr;
	return EXIT_SUCCESS;
}
