CPP=/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ --std=c++11 -Wall
NAME=main

all: $(NAME)

main: main.o
	$(CPP) -o $@ $^

main.o: main.cpp
	$(CPP) -c $<

clean:
	rm *.o

send:
	sh /opt/toev3.sh $(NAME)
