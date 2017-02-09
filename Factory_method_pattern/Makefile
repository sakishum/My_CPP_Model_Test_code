EXEC = test
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h*)
OBJECTS = $(SOURCES:.cpp=.o)
CXX := g++-4.7
CXXFLAG := -std=c++11 -Wall -O2 -lpthread  -lboost_system -lboost_filesystem-mt -lboost_thread-mt -lboost_regex-mt

all: $(SOURCES)
	$(CXX) $(CXXFLAG) -o $(EXEC) $?

.PHONY: clean
clean: $(EXEC)
	$(RM) $?
