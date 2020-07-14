package main

import "fmt"

func main() {
	messages := make(chan string)

	go func() {
		for i := 0; i < 100; i++ {
			messages <- fmt.Sprintf("ping - %d", i)
		}
		//生产完要关闭channel
		close(messages)
	}()

	for s := range messages {
		fmt.Println(s)
	}
}
