all: test 

test: test_graph.cpp graph.h graph.cpp 
		g++ -o test test_graph.cpp graph.cpp 

