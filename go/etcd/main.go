package main

import (
	"context"
	"fmt"
	"time"

	"go.etcd.io/etcd/client/v3"
)

var (
	config clientv3.Config
	client *clientv3.Client
	err    error
)

func main() {
	config = clientv3.Config{
		Endpoints:   []string{"127.0.0.1:2379"},
		DialTimeout: 5 * time.Second,
	}

	if client, err = clientv3.New(config); err != nil {
		fmt.Println("new client error: ", err)
		return
	}
	defer client.Close()

	kv := clientv3.NewKV(client)

	ctx := context.Background()
	if resp, err := kv.Put(ctx, "/v3/t", "hello world"); err != nil {
		fmt.Println(err)
		return
	} else {
		fmt.Printf("%v \n", resp)
	}
	if resp, err := kv.Get(ctx, "/v3/t"); err != nil {
		fmt.Println(err)
		return
	} else {
		fmt.Printf("key %s, value %s \n", resp.Kvs[0].Key, resp.Kvs[0].Value)
	}
}
