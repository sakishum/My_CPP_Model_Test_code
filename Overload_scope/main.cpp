/**
 * @file main.cpp
 * @Synopsis  两个DoSomething不是重载。上面的那篇文章里一开头就说“Declaring two or more
 * items with the same name in a scope is called overloading”，只有在一个scope中才算重载。
 * 只有子啊一个作用域才算是重载。
 * URL: http://accu.org/index.php/journals/268
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-10-21
 */
#include <cstdio>
#include <cstdlib>

class COverLoadBase {
public:
	int doSomething(void) {
		printf("COverLoadBase::doSomething()\n");
		return 0;
	}
};

class COverLoadSub : public COverLoadBase {
public:
	int doSomething(int var) { 
		return var + 1;
	}
};

void testOverLoadSub(void) {
	COverLoadSub sub;
	//sub.doSomething();	// 这样写会出现编译错误
	//main.cpp: In function 'void testOverLoadSub()':
	//main.cpp:20:18: error: no matching function for call to 'COverLoadSub::doSomething()'
	// 修改1：
	sub.COverLoadBase::doSomething();
	// 修改2：
	// 去除sub类中的doSomething 函数。
}

int main(void) {
	testOverLoadSub();
	return EXIT_SUCCESS;
}
