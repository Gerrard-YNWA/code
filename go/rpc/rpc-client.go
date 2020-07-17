package main

import (
	"log"
	"net/rpc"
	"time"
)

type HelloServiceClient struct {
	*rpc.Client
}

const HelloServiceName = "/rpc/HelloService"

func DialHelloService(network, address string) (*HelloServiceClient, error) {
	c, err := rpc.Dial(network, address)
	if err != nil {
		return nil, err
	}
	return &HelloServiceClient{Client: c}, nil
}

func (p *HelloServiceClient) HelloSync(request string, reply *string) error {
	return p.Client.Call(HelloServiceName+".Hello", request, reply)
}

func (p *HelloServiceClient) HelloAsync(request string, reply *string) *rpc.Call {
	return p.Client.Go(HelloServiceName+".Hello", request, reply, nil)
}

func main() {
	client, err := DialHelloService("tcp", "localhost:1234")
	if err != nil {
		log.Fatal("dialing:", err)
	}

	var reply string
	err = client.HelloSync("sync call", &reply)
	log.Println("read reply: ", reply)

	asyncRPC := client.HelloAsync("async call", &reply)
	for {
		select {
		case <-asyncRPC.Done:
			log.Println("read reply: ", reply)
			return
		default:
			log.Println("waiting")
			time.Sleep(time.Second)
		}
	}
}
