package main

import (
	"context"
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

	for i := 1; i < 10; i++ {
		_, err = client.Publish(context.Background(), &pb.String{
			Value: "golang: hello go",
		})
		if err != nil {
			log.Fatal("publish error:", err)
		}
	}

	_, err = client.Publish(context.Background(), &pb.String{
		Value: "docker: hello docker",
	})
	if err != nil {
		log.Fatal("publish error:", err)
	}
}
