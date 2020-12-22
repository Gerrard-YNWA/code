package main

import (
	"context"
	"fmt"
	"time"
)

func handle(ctx context.Context, duration time.Duration) {
	fmt.Println(ctx.Value("request-id"))
	select {
	case <-ctx.Done():
		fmt.Println(ctx.Err())
	case <-time.After(duration):
		fmt.Println("handle request with ", duration)
	}
}

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 1*time.Second)
	ctx = context.WithValue(ctx, "request-id", "123")
	defer cancel()
	go handle(ctx, 2000*time.Millisecond)
	select {
	case <-ctx.Done():
		fmt.Println("handle ", ctx.Err())
	}
}
