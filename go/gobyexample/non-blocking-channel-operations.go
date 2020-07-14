package main

import "fmt"

//使用select + default实现非阻塞操作
func main() {
	messages := make(chan string)
	signals := make(chan bool)

	select {
	case msg := <-messages:
		fmt.Println("receive message ", msg)
	default:
		fmt.Println("no message received")
	}

	msg := "hi"
	select {
	//msg 无法被发送到非缓冲channel, 因为没有接收端
	case messages <- msg:
		fmt.Println("sent message ", msg)
	default:
		fmt.Println("no message sent")
	}

	select {
	case msg := <-messages:
		fmt.Println("received message ", msg)
	case sig := <-signals:
		fmt.Println("received signal", sig)
	default:
		fmt.Println("no activity")
	}
}
