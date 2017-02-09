#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Singleton {
public:
	static Singleton *getInstance(void);
private:
	Singleton(void) {}
	Singleton(const Singleton&) {}
	~Singleton(void) {}
	Singleton &operator=(const Singleton &);
	static Singleton *instance_;
};

Singleton *Singleton::instance_ = new Singleton();
Singleton *Singleton::getInstance(void) {
	return instance_;
}

int main(int, char**) {
	Singleton *singleton1 = Singleton::getInstance();
	Singleton *singleton2 = Singleton::getInstance();
	if (singleton1 == singleton2) {
		std::cout << "Equal." << std::endl;
	}
	exit(EXIT_SUCCESS);
}
