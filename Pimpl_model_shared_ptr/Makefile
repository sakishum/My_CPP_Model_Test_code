SRC := $(wildcard *.cpp)
HEADS := $(wildcard *.h*)
OBJ := $(SRC:.cpp=.o)
EXC := test
CXX := g++-4.7
CXXFLAG := -Wall -L/usr/local/Cellar/boost/1.54.0/lib -lpthread  -lboost_system -lboost_filesystem-mt -lboost_thread-mt 

all: $(EXC)

$(EXC): $(OBJ)
	$(CXX) $(CXXFLAG) $(OBJ) -o $@

%.o: %.cpp $(HEADS)
	$(CXX) -Wall -I/usr/local/Cellar/boost/1.54.0/include -c $< -o $@

.PHONY: clean
claen: $(EXC)
	$(RM) $? *.o
