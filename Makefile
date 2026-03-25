CCXFLAGS += -Wall -Weffc++ -std=c++14

pe-vector-tests: main.cpp
	g++ -o $@ $^
