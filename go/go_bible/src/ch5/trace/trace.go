package main

import (
	"log"
	"time"
)

func bigSlowOperation() {
	defer trace("bigSlowOperation")()
	time.Sleep(10 * time.Second)
}

func trace(msg string) func() {
	start := time.Now()
	log.Printf("enter %s", msg)
	return func() {
		log.Printf("exit %s (%s)", msg, time.Since(start))
	}
}

func printMsg(msg string) {
	log.Printf("msg: %s", msg)
}

func main() {
	bigSlowOperation()
	defer printMsg("111")
	defer printMsg("222")
}
