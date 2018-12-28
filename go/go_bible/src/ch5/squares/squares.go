package main

import "fmt"

func squares() func() int {
	var x int
	return func() int {
		x++ //可以使用外层函数中的变量
		return x * x
	}
}

func main() {
	f := squares()
	fmt.Println(f())
	fmt.Println(f())
	fmt.Println(f())
	fmt.Println(f())
}
