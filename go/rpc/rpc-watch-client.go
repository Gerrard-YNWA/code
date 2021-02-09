package main

import (
	"fmt"
	"log"
	"net/rpc"
	"time"
)

const KVStoreServiceName = "/rpc/pkg.KVStoreService"

type KVStoreServiceInterface interface {
	Get(key string, value *string) error
	Set(kv [2]string, reply *struct{}) error
	Watch(timeoutSecond int, keyChanged *string) error
}

type KVStoreServiceClient struct {
	*rpc.Client
}

var _ KVStoreServiceInterface = (*KVStoreServiceClient)(nil)

func DialKVStoreService(network, address string) (*KVStoreServiceClient, error) {
	c, err := rpc.Dial(network, address)
	if err != nil {
		return nil, err
	}

	return &KVStoreServiceClient{Client: c}, nil
}

func (p *KVStoreServiceClient) Get(key string, value *string) error {
	return p.Client.Call(KVStoreServiceName+".Get", key, value)
}

func (p *KVStoreServiceClient) Set(kv [2]string, reply *struct{}) error {
	return p.Client.Call(KVStoreServiceName+".Set", kv, reply)
}

func (p *KVStoreServiceClient) Watch(timeoutSecond int, keyChanged *string) error {
	return p.Client.Call(KVStoreServiceName+".Watch", timeoutSecond, keyChanged)
}

func main() {
	client, err := DialKVStoreService("tcp", "127.0.0.1:1234")
	if err != nil {
		log.Fatal("Dial error", err)
	}

	go func() {
		var keyChanged string
		for {
			fmt.Println("Start to watch:")
			err := client.Watch(30, &keyChanged)
			if err != nil {
				log.Fatal("Watch error:", err)
				break
			}
			fmt.Println("watch:", keyChanged)
		}
	}()

	time.Sleep(time.Second * 1)
	err = client.Set([2]string{"abc", "abc-value"}, new(struct{}))
	if err != nil {
		log.Fatal("Set error:", err)
	}

	var reply string
	err = client.Get("abc", &reply)
	if err != nil {
		log.Fatal("Set error:", err)
	}
	fmt.Println("Get:", reply)

	err = client.Set([2]string{"aaa", "aaa-value"}, new(struct{}))
	if err != nil {
		log.Fatal("Set error:", err)
	}

	time.Sleep(time.Second * 3)
}
