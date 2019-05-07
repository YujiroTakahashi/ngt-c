CXX = c++
CXXFLAGS = -pthread -std=c++14
LDFLAGS  = -lngt -lcroco_ngt
INCLUDES = -I.

CC = gcc
CFLAGS = -pthread

all: main.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) main.cc -o cc_ngt $(LDFLAGS)
	$(CC) $(INCLUDES) $(CFLAGS) main.c -o c_ngt -lstdc++ $(LDFLAGS)

clean:
	rm -rf *.o cc_ngt
