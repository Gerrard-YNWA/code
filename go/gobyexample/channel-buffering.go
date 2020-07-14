package main

import (
	"fmt"
	"time"
)

func main() {
	//bufferd channel 有缓冲区， 当缓冲区满时，发送端会阻塞，当缓冲区空时，接收端会阻塞
	messages := make(chan string, 1)

	go func() {
		data := []string{"bufferd", "channel", "overflow1", "overflow2"}
		for i := range data {
			fmt.Println("produce: ", data[i])
			messages <- data[i]
		}
		close(messages)
	}()

	fmt.Println("sleep start")
	time.Sleep(time.Second)
	fmt.Println("sleep done")
	for s := range messages {
		fmt.Println("consume:", s)
	}
}
