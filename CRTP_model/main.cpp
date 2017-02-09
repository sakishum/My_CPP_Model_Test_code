/* Copyright(C)
 * For free
 * All right reserved
 */
/**
 * @file main.cpp
 * @Synopsis  Example for CRTP model in CPP.
 *		Object counter 问题。类计数器代码：
 *		通过父类中传入子类的类型，实现在编译器的多态(静态多态)。
 *		当然编译器的多态比运行时通过虚函数实现的多态(动态多态)
 *		效率要高，但是这并不是CRTP模式最重要的优点。
 *		CRTP 不可以替代虚函数，虚函数实现了懂太多态，也就是让基
 *		类指向子类，CRTP做不到这点。
 *
 *		CRTP 的最大用途，是在简化接口，提高类的扩展性。见boost::enable_shared_from_this。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-10-20
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>

const size_t MAX_ITEM_TAG_LEN = 100;
struct SD_PlayerBagItemData {
	char tag[MAX_ITEM_TAG_LEN];	// 100
	uint32_t propsid;	// 4
	uint32_t type;		// 4
	uint32_t num;		// 4
	uint64_t playerid;	// 8
};  // struct SD_PlayerBagItemData

struct SD_PlayerBagData {
	uint64_t count;
	uint64_t playerid;
	struct SD_PlayerBagItemData item;
};  // struct SD_PlayerBagData

template <typename T>
class CCounter {
public:
	static int object_created;
	static int object_alive;
	CCounter(void) {
		++object_created;
		++object_alive;
	}

protected:
	~CCounter(void) {
		--object_alive;
	}

};  // class CCounter

template <typename T> int CCounter<T>::object_created(0);
template <typename T> int CCounter<T>::object_alive(0);

class CFoo : public CCounter<CFoo> {
public:
	explicit CFoo(int data) : m_data(data) {
	}
	const int m_data;
};  // class CFoo

//  const int CFoo::m_data = 10;

class CBar : public CCounter<CBar> {
};  // class CBar

int main(void) {
	printf("size: 1.%zu\n", sizeof(SD_PlayerBagItemData));
	printf("size: 2.%zu\n", sizeof(SD_PlayerBagData));
	printf("size: %zu\n", 3*sizeof(uint32_t));
	printf("size: %zu\n", sizeof(uint64_t));
	CFoo *foo1 = new CFoo(2);
	printf("%zu\n", sizeof(NULL));		// 8
	printf("foo1 = %d\n", foo1->object_alive);
	CFoo foo2(3);
	printf("foo2 = %d\n", foo2.object_alive);
	CBar bar1;
	printf("bar1 = %d\n", bar1.object_alive);
	delete foo1;
	return EXIT_SUCCESS;
}
