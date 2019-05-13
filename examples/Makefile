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
	$(CXX) $(INCLUDES) $(CXXFLAGS) import.cc -o import_ngt -lmysqlcppconn $(LDFLAGS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) export.cc -o export_ngt -lmysqlcppconn $(LDFLAGS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) getmsg.cc -o getmsg_ngt -lmysqlcppconn $(LDFLAGS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) setmsg.cc -o setmsg_ngt -lmysqlcppconn $(LDFLAGS)

	$(CC) $(INCLUDES) $(CFLAGS) main.c -o c_ngt -lstdc++ $(LDFLAGS)
	$(CC) $(INCLUDES) $(CFLAGS) open.c -o c_open -lstdc++ $(LDFLAGS)

clean:
	rm -rf *.o c_ngt c_open cc_ngt open_ngt save_ngt import_ngt export_ngt
