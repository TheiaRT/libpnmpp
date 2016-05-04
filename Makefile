CXX = g++
CFLAGS = -O3 -g -std=c++11 -pthread -Wall -Wpedantic -Werror

all: pnm_image.o
	$(CXX) $(CFLAGS) pnm_image.o pnm_tests.cpp -o pnm_tests

clean:
	rm -f *.o

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
