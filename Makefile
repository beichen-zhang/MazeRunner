CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread
OBJS = greedy.o maze.o

all : greedy

greedy :  $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o greedy
	
greedy.o : greedy.cpp maze.h cell.h
	$(CXX) $(CXXFLAGS) greedy.cpp
	
maze.o : maze.cpp maze.h cell.h
	$(CXX) $(CXXFLAGS) maze.cpp
	
	
clean :
	rm greedy *.o
