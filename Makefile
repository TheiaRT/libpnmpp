CXX = g++
CFLAGS = -O3 -g -std=c++11 -pthread -Wall -Wpedantic -Werror

all: pnm_image.o dist/jsoncpp/jsoncpp.o 
	$(CXX) $(CFLAGS) jsoncpp.o json_util.cpp pnm_image.o\
		pnm_tests.cpp -o pnm_tests

clean:
	rm -f *.o

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
