COMPLIER=g++
CFLAGS=-Wall --std=c++11 -fsanitize=address -g
BIN_NAME=test
INCLUDE=.
OBJ_DIR=./obj

.PHONY: all clean build test

build:
	$(COMPLIER) -Wall --std=c++11 -c printHelper.cpp -o $(OBJ_DIR)/printHelper.o
	$(COMPLIER) -I$(INCLUDE) $(CFLAGS) $(OBJ_DIR)/printHelper.o $(INPUT_FILE) -o $(OBJ_DIR)/$(BIN_NAME) 

test:
	./$(OBJ_DIR)/$(BIN_NAME)

clean:
	rm -f $(BIN_NAME)

all: clean build test
