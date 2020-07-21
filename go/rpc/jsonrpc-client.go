package main

import (
	"encoding/json"
	"log"
	"net"
	"net/rpc"
	"net/rpc/jsonrpc"
)

type ClientRequest struct {
	Method string         `json:"method"`
	Params [1]interface{} `json:"params"`
	//Params [1]string `json:"params"`
	Id uint64 `json:"id"`
}

type ClientResponse struct {
	Id     uint64           `json:"id"`
	Result *json.RawMessage `json:"result""`
	Error  interface{}      `json:"error"`
}

func main() {
	conn, err := net.Dial("tcp", "localhost:1234")
	if err != nil {
		log.Fatal("net.Dial: ", err)
	}

	client := rpc.NewClientWithCodec(jsonrpc.NewClientCodec(conn))

	var reply ClientResponse
	request := ClientRequest{
		Id:     1,
		Params: [1]interface{}{"hello"},
		Method: "hello",
	}
	err = client.Call("/HelloService.Hello", request, &reply)
	if err != nil {
		log.Fatal(err)
	}
	log.Println(string(*reply.Result), reply.Id, reply.Error)
}
