CPP=/usr/local/carlson-minot/crosscompilers/bin/arm-none-linux-gnueabi-g++ --std=c++11 -Wall

SRC_PATH = src/
HEADER_PATH = header/
BIN_PATH = bin/
NAME=main

all: $(NAME)

main: $(BIN_PATH)main.o
	$(CPP) -o $(BIN_PATH)$@ $^

main.o: $(HEADER_PATH)main.hpp

$(BIN_PATH)%.o: $(SRC_PATH)%.cpp
	$(CPP) -o $@ -c $<

clean:
	rm -rf $(BIN_PATH)*.o

mrproper: clean
	rm -rf $(BIN_PATH)$(NAME)

send:
	sh /opt/toev3.sh $(NAME)
