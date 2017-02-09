/**
 * @file main.cpp
 * @Synopsis  Example for Pimpl model in CPP.
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2014-10-20
 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <boost/smart_ptr.hpp>

class CFoo {
public:
	CFoo(void);
	virtual ~CFoo(void);
	void setbar(int var);
	void getbar(void);
private:
	class CPimpl;
	boost::scoped_ptr<CPimpl> m_pimpl;
};  // class CFoo

class CFoo::CPimpl {
public:
	void setbar(int var);
	void getbar(void);
private:
	int m_bar;
};  // class CFoo::CPimpl

// -------- CFoo
CFoo::CFoo(void) : m_pimpl(new CPimpl) {
	// Empty, Do Nothing.
}

CFoo::~CFoo(void) {
	// Empty, Do Nothing.
}

void CFoo::setbar(int var) {
	m_pimpl->setbar(var);
}

void CFoo::getbar(void) {
	m_pimpl->getbar();
}

// -------- CFoo::CPimpl
void CFoo::CPimpl::setbar(int var) {
	m_bar = var;
}

void CFoo::CPimpl::getbar(void) {
	printf("The Bar is %d.\n", m_bar);
}

int main(void) {
	CFoo foo;
	foo.setbar(3);
	foo.getbar();
	// ========== test for std::atoi((*iter).c_str())
	std::vector<std::string> ivet;
	ivet.push_back(std::string("5"));
	std::vector<std::string>::iterator iter = ivet.begin();
	if (iter != ivet.end()) {
		printf("The data is %d", std::atoi((*iter).c_str()));
	}
	return EXIT_SUCCESS;
}
