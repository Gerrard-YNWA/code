COMPLIER=g++
CFLAGS=-Wall --std=c++11
BIN_NAME=test

.PHONY: all clean build test

build:
	$(COMPLIER) $(CFLAGS) $(INPUT_FILE) -o $(BIN_NAME) 

test:
	./$(BIN_NAME)

clean:
	rm -f $(BIN_NAME)

all: clean build test
