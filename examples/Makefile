CXX = c++
CXXFLAGS = -pthread -std=c++14
LDFLAGS  = -lngt -lcroco_ngt
INCLUDES = -I.

CC = gcc
CFLAGS = -pthread

all: main.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) main.cc -o cc_ngt $(LDFLAGS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) save.cc -o save_ngt $(LDFLAGS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) open.cc -o open_ngt $(LDFLAGS)
	$(CC) $(INCLUDES) $(CFLAGS) main.c -o c_ngt -lstdc++ $(LDFLAGS)
	$(CC) $(INCLUDES) $(CFLAGS) open.c -o c_open -lstdc++ $(LDFLAGS)

clean:
	rm -rf *.o c_ngt c_open cc_ngt open_ngt save_ngt
