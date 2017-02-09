/**
 * @file main.cpp
 * @Synopsis  使用shared_ptr，当不再引用该对象时，会被自动删除。
 *		使用CreateInstance() 的工厂方法创建对象实例。
 *		当需要用户销毁指针时，使用智能指针返回动态申请的对象。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-08-21
 */
#include <cstdio>
#include <cstdlib>
#include <boost/shared_ptr.hpp>

namespace myobject {

typedef boost::shared_ptr<class MyObject> MyObjectPtr;

class MyObject {
public:
	static MyObjectPtr CreateInstance(const std::string &name);
	~MyObject(void) {
		printf("%s\'s destructor\n", m_name.c_str());
	}
	std::string GetName(void) const;

private:
	std::string m_name;
	explicit MyObject(const std::string &name);		// 必须使用工厂方法来创建实例
};

MyObject::MyObject(const std::string &name) : m_name(name) {
	// Empty, Do Nothing.
}

MyObjectPtr MyObject::CreateInstance(const std::string &name) {
	return MyObjectPtr(new MyObject(name));
}

std::string MyObject::GetName(void) const {
	return m_name;
}

// 全局函数
// 优先使用非成员、非友元的形式意味着此方法与类内部细节不会耦合。
// 为了更好的传达概念上的关联性，声明在同一个命名空间中。
void PrintName(MyObjectPtr obj) {
	printf("The name is \'%s\'\n", obj->GetName().c_str());
}

}  // namespqce myobject

using namespace myobject;

int main(void) {
	MyObjectPtr ptr = MyObject::CreateInstance("obj_a");	// destructor
	PrintName(ptr);
	ptr = MyObject::CreateInstance("obj_b");				// destructor
	PrintName(ptr);
	return EXIT_SUCCESS;
}

