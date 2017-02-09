/**
 * @file main.cpp
 * @Synopsis  Example for Observer Model in CPP with NVI and smart ptr.
 * 		Observer design pattern
 * 			Model the "independent" functionality with a "subject" abstraction
 * 			Model the "dependent" functionality with "observer" hierarchy
 * 			The Subject is coupled only to the Observer base class
 * 			Observers register themselves with the Subject
 * 			The Subject broadcasts events to all registered Observers
 * 			Observers "pull" the information they need from the Subject
 * 			Client configures the number and type of Observers
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-12-11
 */

#include <cstdint>
#include <cstdlib>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <vector>

class CObserver;
class CSubject;
class CDivObserver;
class CModObserver;

typedef boost::shared_ptr<CObserver> CObserverPtr;
typedef boost::shared_ptr<CSubject> CSubjectPtr;
typedef boost::shared_ptr<CDivObserver> CDivObserverPtr;
typedef boost::shared_ptr<CModObserver> CModObserverPtr;

class CObserver {
public:
	CObserver(CSubjectPtr model, int32_t div) {
		if (0 != model.use_count()) {
			m_model = model;
			m_denom = div;
		}
	}

	// NVI
	void refrash(void) {
		update();
	}

	virtual void update(void) = 0;

protected:
	CSubjectPtr getSubject(void) const {
		return m_model;
	}

	int32_t getDivisor(void) const {
		return m_denom;
	}

private:
	int32_t m_denom;
	// 2. "dependent" functionality
	CSubjectPtr m_model;
};  // class CObserver 

class CSubject {
	typedef std::vector<CObserverPtr> CObserverPtrVec;
public:
	void attach(CObserverPtr obs) {
		if (obs) {
			m_views.push_back(obs);
		}
	}

	void setValue(int32_t value) {
		m_value = value;
		notify();
	}

	int32_t getValue(void) const {
		return m_value;
	} 
	
	void notify(void) {
		// 5. Publisher broadcasts
		CObserverPtrVec::iterator iter = m_views.begin();
		for (; iter != m_views.end(); ++iter) {
			(*iter)->refrash();
		}
	}

private:
	int32_t m_value;
	// 1. "independent" functionality
	CObserverPtrVec m_views;	// 3. Coupled only to "interface"
};  // class CSubject

class CDivObserver : public CObserver {
public:
	CDivObserver(CSubjectPtr model, int32_t div) : CObserver(model, div) {
		
	}

	virtual void update(void) {
		// 6. "Pull" information of interest
		int32_t value = getSubject()->getValue();
		int32_t div = getDivisor();
		std::cout << value << " div " << div << " is " << value / div << std::endl;
	}
};  // class CDivObserver

class CModObserver : public CObserver {
public:
	CModObserver(CSubjectPtr model, int32_t div) : CObserver(model, div) {
		
	}

	virtual void update(void) {
		int32_t value = getSubject()->getValue();
		int32_t div = getDivisor();
		std::cout << value << " mod " << div << " is " << value % div << std::endl;
	}
};  // class CModObserver

int32_t main(void) {
	CSubjectPtr psubject(new CSubject());
	CObserverPtr pdivobs1(new CDivObserver(psubject, 4));
	CObserverPtr pdivobs2(new CDivObserver(psubject, 3));
	CObserverPtr pmodobs1(new CModObserver(psubject, 3));
	// 4. Observer register themselves with the Subject
	psubject->attach(pdivobs1);
	psubject->attach(pdivobs2);
	psubject->attach(pmodobs1);

	psubject->setValue(14);
	return EXIT_SUCCESS;
}
