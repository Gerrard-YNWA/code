package main

import (
	"context"
	"fmt"
	"io"
	"log"

	"google.golang.org/grpc"

	pb "github.com/Gerrard-YNWA/code/go/pubsub/pubsub"
)

func main() {
	conn, err := grpc.Dial("127.0.0.1:1234", grpc.WithInsecure())
	if err != nil {
		log.Fatal("dial error:", err)
	}

	defer conn.Close()

	client := pb.NewPubsubServiceClient(conn)

	stream, err := client.Subscribe(context.Background(), &pb.String{
		Value: "golang",
	})
	if err != nil {
		log.Fatal("subscribe error:", err)
	}

	for {
		reply, err := stream.Recv()
		if err != nil {
			if err == io.EOF {
				break
			}

			log.Fatal("Recv error:", err)
		}

		fmt.Println(reply.GetValue())
	}
}
