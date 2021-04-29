package main

import (
	"fmt"
	"time"
)

var quit = make(chan bool)

func fib2(ch chan int) {
	x, y := 1, 1
	for {
		select {
		case ch <- x:
			x, y = y, x+y
		case <-quit:
			fmt.Println("Done calculating Fibonacci!")
			return
		}
	}
}

func main() {
	start := time.Now()

	input := ""
	ch := make(chan int)
	go fib2(ch)

	for {
		sum := <-ch
		fmt.Println(sum)
		fmt.Scanf("%s", &input)
		if input == "quit" {
			quit <- true
			break
		}
	}

	time.Sleep(1 * time.Second)
	elapsed := time.Since(start)
	fmt.Printf("Done! It took %v seconds!\n", elapsed.Seconds())
}
