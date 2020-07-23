COMPLIER=gcc
CFLAGS=-Wall --std=c99
BIN_NAME=test
TARGET_DIR=.

.PHONY: build

build:
	$(COMPLIER) $(CFLAGS) $(INPUT_FILE) -o $(TARGET_DIR)/$(BIN_NAME) 

clean:
	rm -fr $(TARGET_DIR)/$(BIN_NAME)

all: clean build
