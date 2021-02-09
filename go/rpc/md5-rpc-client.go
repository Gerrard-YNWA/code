package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/rpc"
	"os"
)

const HashContentServiceName = "/rpc/pkg.HashContentService"

type HashContentServiceInterface interface {
	Md5(buffer []byte, reply *string) error
}

type HashContentServiceClient struct {
	*rpc.Client
}

var _ HashContentServiceInterface = (*HashContentServiceClient)(nil)

func DialHashContentService(network, address string) (*HashContentServiceClient, error) {
	c, err := rpc.Dial(network, address)
	if err != nil {
		return nil, err
	}

	return &HashContentServiceClient{Client: c}, nil
}

func (p *HashContentServiceClient) Md5(bytes []byte, reply *string) error {
	return p.Client.Call(HashContentServiceName+".Md5", bytes, reply)
}

func main() {
	if len(os.Args) < 2 {
		fmt.Printf("Usage %s filename\n", os.Args[0])
		os.Exit(1)
	}

	f := os.Args[1]
	bytes, err := ioutil.ReadFile(f)
	if err != nil {
		log.Fatal("ReadFile error:", err)
	}

	client, err := DialHashContentService("tcp", "127.0.0.1:1234")
	if err != nil {
		log.Fatal("Dial error:", err)
	}

	var reply string
	err = client.Md5(bytes, &reply)
	if err != nil {
		log.Fatal("rpc error:", err)
	}

	log.Println(reply)
}
