BUILD_LD_FLAGS="-s -w"
TARGET_DIR=bin
PRODUCER=producer
CONSUMER=consumer


.PHONY: build

buld:
	go build -ldflags ${BUILD_LD_FLAGS} -o ${TARGET_DIR}/${PRODUCER} producer/producer.go
	go build -ldflags ${BUILD_LD_FLAGS} -o ${TARGET_DIR}/${CONSUMER} consumer/consumer.go

clean:
	rm -fr ./bin

all: clean build
