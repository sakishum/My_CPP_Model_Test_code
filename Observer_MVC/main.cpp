/**
 * @file main.cpp
 * @Synopsis  Example for observer pattern of pub/sub in CPP. 
 *		实现观察者模式的典型做法是引入两个概念：主题(Subject)和观察者(Observer)，
 *		也称作发布者与订阅者。一个或多个观察者注册主题中感兴趣的事件，之后主题会
 *		在自身状态发生变化时通知所有注册者。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-08-28
 */
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include "observer.h"
#include "mysubject.h"

/// An observer class that wishes to receive a notification
class MyObserver : public IObserver {
public:
	explicit MyObserver(const std::string &name) : m_name(name) {
		// Empty, Do Nothing.
	}

	void update(uint32_t message) {
		std::cout << m_name << " Receive message ";
		std::cout << message << std::endl;
	}

private:
	std::string m_name;
};  // class MyObserver

int main(void) {
	// create 4 observer classes
	MyObserver observer1("Observer1");
	MyObserver observer2("Observer2");
	MyObserver observer3("Observer3");
	MyObserver observer4("Observer4");

	// create a single subject class
	MySubject subject;

	// each observer registers interest for specific
	// messages that the subject can issue
	subject.subscribe(MySubject::ADD, &observer1);
	subject.subscribe(MySubject::ADD, &observer2);
	subject.subscribe(MySubject::REMOVE, &observer2);
	subject.subscribe(MySubject::REMOVE, &observer3);
	subject.subscribe(MySubject::REMOVE, &observer4);
	subject.subscribe(MySubject::REMOVE, &observer4);

	// make the subject issue ADD and UPDATE messages
	std::cout << "Notify Msg ADD:" << std::endl;
	subject.notify(MySubject::ADD);
	std::cout << "Notify Msg REMOVE:" << std::endl;
	subject.notify(MySubject::REMOVE);

	return EXIT_SUCCESS;
}





