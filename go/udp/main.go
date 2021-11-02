package main

import (
	"bytes"
	"compress/gzip"
	"fmt"
	"io/ioutil"
	"net"
	"os"
)

var (
	GZIP_MAGIC = []byte("\x1F\x8B")
)

const host = "172.16.57.42:65013"

func main() {
	addr, err := net.ResolveUDPAddr("udp", host)
	if err != nil {
		fmt.Println("Can't resolve address: ", err)
		os.Exit(1)
	}
	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		fmt.Println("Failed to listen: ", err)
		os.Exit(1)
	}

	defer conn.Close()
	fmt.Println("Start udp server at ", host)

	for {
		handleClient(conn)
	}
}

// nacos server push message
func handleClient(conn *net.UDPConn) {
	data := make([]byte, 4096)
	n, _, err := conn.ReadFromUDP(data)
	if err != nil {
		fmt.Println("Failed to read udp message: ", err.Error())
		return
	}

	data = data[:n]

	if !isGzipFile(data) {
		fmt.Println("Recv data: ", string(data))
		return
	}

	reader, err := gzip.NewReader(bytes.NewReader(data))
	if err != nil {
		fmt.Println("Failed to decompress gzip data: ", err.Error())
		return
	}

	defer reader.Close()

	bs, err := ioutil.ReadAll(reader)
	if err != nil {
		fmt.Println("Failed to read data: ", err.Error())
	}

	fmt.Println("Recv gzip data: ", string(bs))
}

func isGzipFile(data []byte) bool {
	if len(data) < 2 {
		return false
	}

	return bytes.HasPrefix(data, GZIP_MAGIC)
}
