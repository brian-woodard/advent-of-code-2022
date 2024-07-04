#CPPFLAGS = --std=c++17 -Wall -I. -g -Wno-format -Wno-sign-compare -fsanitize=address
CPPFLAGS = --std=c++17 -Wall -I. -O2 -Wno-format -Wno-sign-compare -I../../utils

all:
	g++ $(CPPFLAGS) main.cpp -o main


clean:
	rm -f *.o
	rm -f main
