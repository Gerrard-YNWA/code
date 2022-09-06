BIN_NAME=hello
BIN_DIR=bin
LIB_NAME=hello
LIB_DIR=lib

GO_SRC=hello.go
C_SRC=hello.cc

GO=go
CC=clang++

.PHONY: build

build:
	$(GO) build -o $(BIN_DIR)/$(BIN_NAME) $(GO_SRC)

shared:
	mkdir -p $(BIN_DIR)
	CGO_ENABLED=1 GOARCH=amd64 GOOS=darwin $(GO) build --buildmode=c-shared -o $(LIB_DIR)/lib$(LIB_NAME).dylib $(GO_SRC)
	$(CC) -I$(LIB_DIR) -L$(LIB_DIR) -l$(LIB_NAME) -lpthread $(C_SRC) -o $(BIN_DIR)/$(BIN_NAME)_shared

static:
	mkdir -p $(BIN_DIR)
	CGO_ENABLED=1 GOARCH=amd64 GOOS=darwin $(GO) build --buildmode=c-archive -o $(LIB_DIR)/lib$(LIB_NAME).a $(GO_SRC)
	$(CC) -I$(LIB_DIR) $(LIB_DIR)/lib$(LIB_NAME).a -lpthread $(C_SRC) -o $(BIN_DIR)/$(BIN_NAME)_static

clean:
	rm -fr $(LIB_DIR) $(BIN_DIR)
