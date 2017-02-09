#pragma once

#include "observer.h"

/// A concrete subject class, based on the ISubject interface.
class MySubject : public ISubject {
public:
	enum Message {
		ADD,
		REMOVE
	};
};  // class MySubject

