package main

import "fmt"

func fizzBuzz(i int) {
	switch {
	case i%15 == 0:
		fmt.Println("FizzBuzz")
	case i%3 == 0:
		fmt.Println("Fizz")
	case i%5 == 0:
		fmt.Println("Buzz")
	default:
		fmt.Println(i)
	}
}

func sqrt(x float64) {
	sroot := 1.0
	for i := 0; i < 10; i++ {
		sroot = sroot - (sroot*sroot-x)/(2*sroot)
		if sroot*sroot == x {
			fmt.Println("Square root is: ", sroot)
			break
		}
		fmt.Println("A guess for square root is ", sroot)
	}
}

func sqrt2(x float64) {
	root := x
	for i := 0; i < 10; i++ {
		root = (x/root + root) / 2
		if root*root == x {
			fmt.Println("Square root is: ", root)
			break
		}
		fmt.Println("A guess for square root is ", root)
	}
}

func main() {
	/*
		for i := 1; i <= 100; i++ {
			fizzBuzz(i)
		}
	*/
	//sqrt(25)
	//sqrt2(25)
	val := 0
	for {
		fmt.Print("Enter number: ")
		fmt.Scanf("%d", &val)
		switch {
		case val > 0:
			fmt.Println("You entered: ", val)
		case val < 0:
			panic("invalid negative input")
		default:
			fmt.Println("0 is neither negative nor positive")
		}
	}
}
