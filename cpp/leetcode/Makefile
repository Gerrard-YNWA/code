COMPLIER=g++
CFLAGS=-Wall --std=c++11 -fsanitize=address -g
BIN_NAME=test
INCLUDE=.

.PHONY: all clean build test

build:
	$(COMPLIER) -I$(INCLUDE) $(CFLAGS) $(INPUT_FILE) -o $(BIN_NAME) 

test:
	./$(BIN_NAME)

clean:
	rm -f $(BIN_NAME)

all: clean build test
