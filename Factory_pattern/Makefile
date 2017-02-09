SOURCE := main.cpp abstract_base.cpp
EXECUTE := test
CXX := g++-4.7
CXXFLAG := -std=c++11 -Wall -O2 -L/usr/local/Cellar/boost/1.54.0/lib -lpthread -lboost_system -lboost_filesystem-mt -lboost_thread-mt

all: $(SOURCE)
	$(CXX) $(CXXFLAG) -o $(EXECUTE) $?

.PHONYL: clean
clean: $(EXECUTE)
	$(RM) $?

