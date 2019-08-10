# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall -O2
LDFLAGS=-g

all: quickSort 

quickSort: quickSort.cpp 

clean:
	rm -f quickSort *.o core* *~

