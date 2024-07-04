CPPFLAGS = --std=c++17 -Wall -I. -g -Wno-format -Wno-sign-compare -I../../utils
#CPPFLAGS = --std=c++17 -Wall -I. -O2 -Wno-format -Wno-sign-compare -I../../utils

all:
	g++ $(CPPFLAGS) main.cpp -o main
	g++ $(CPPFLAGS) main_pt1.cpp -o main_pt1

clean:
	rm -f *.o
	rm -f main
