#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>

typedef int KeyEvent;
typedef boost::function<void (const KeyEvent &)> KeyCallback;
struct AbstractCallback {
    virtual bool equals(const KeyCallback &f) const=0;
    virtual ~AbstractCallback(){}
};

template<typename Callback>
struct ConcreteCallback : AbstractCallback {
    const Callback &callback;
    explicit ConcreteCallback(const Callback &p_callback) : callback(p_callback) {}
    virtual bool equals(const KeyCallback &f) const
    {
    	return callback == f;
    }
};

struct KeyCallbackChecker {
    boost::scoped_ptr<AbstractCallback> func;
public:
    template<typename Func>
    KeyCallbackChecker(const Func &f) : func(new ConcreteCallback<Func>(f)) {  }
    friend bool operator==(const KeyCallback &lhs,const KeyCallbackChecker &rhs) {
    	return rhs.func->equals(lhs);
    }
    friend bool operator==(const KeyCallbackChecker &lhs,const KeyCallback &rhs) {
    	return rhs==lhs;
    }
};

struct Caller {
    template<typename F> void operator()(F f) {
    	f(1);
    }
};

class Callbacks {
    std::vector<KeyCallback> v;
public:
    void register_callback(const KeyCallback &callback) {
        v.push_back(callback);
    }

    void unregister_callback(const KeyCallbackChecker &callback) {
        std::vector<KeyCallback>::iterator it=find(v.begin(),v.end(),callback);
        if(it!=v.end())
            v.erase(it);
    }

    void call_all(void) {
        std::for_each(v.begin(), v.end(), Caller());
        std::cout << std::string(16,'_') << std::endl;
    }
};





