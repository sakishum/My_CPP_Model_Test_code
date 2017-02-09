#pragma once 

#include <map>
#include <vector>
#include <cstdint>
#include <boost/utility.hpp>

// An abstract interface for an observer class.
class IObserver : public boost::noncopyable {
public:
	virtual ~IObserver(void) { }
	virtual void update(uint32_t message) = 0;
};  // class IObserver

// An interface for a subject class.    
class ISubject {
public:
	ISubject(void);
	virtual ~ISubject(void);

	/// Add a new observer to the list of observers.
	virtual void subscribe(uint32_t message, IObserver *observer);
	/// Remove an existing observer from the list of observers.
	virtual void unsubscribe(uint32_t message, IObserver *observer);
	/// Call the Update() method of all subscribed observers.
	virtual void notify(uint32_t message);

private:
	typedef std::vector<IObserver *> ObserverList;
	typedef std::map<uint32_t, ObserverList> ObserverMap;
	ObserverMap m_observers;
};  // class ISubject 

