all: test 

test: test_graph.cpp graph.h graph.cpp 
		g++ -o test test_graph.cpp graph.cpp --std=c++11
		rm graph.h.gch
		rm a.out
		rm *.o

