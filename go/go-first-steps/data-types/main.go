package main

import "fmt"

func slice() {
	letters := []string{"A", "B", "C", "D", "E"}
	remove := 2

	fmt.Println("Before", letters)

	letters[remove] = letters[len(letters)-1]
	letters = letters[:len(letters)-1]

	fmt.Println("After", letters)
}

func fib(n int) int {
	if n == 1 || n == 2 {
		return 1
	}

	return fib(n-1) + fib(n-2)
}

func fib_slice(n int) []int {
	if n < 2 {
		return nil
	}
	result := make([]int, n)
	for i := 1; i <= n; i++ {
		result[i-1] = fib(i)
	}
	return result
}

var res = make([]int, 0)

func fib2(n int) int {
	if n < 2 {
		return 1
	}
	if len(res) >= n {
		return res[n-1]
	}
	res = append(res, fib2(n-1)+fib2(n-2))
	return res[n-1]
}

func fib_slice2(n int) []int {
	if n < 2 {
		return nil
	}
	res = append(res, 1)
	res = append(res, 1)
	fib2(n)
	return res
}

//非递归
func fib3(n int) []int {
	if n < 2 {
		return make([]int, 0)
	}

	nums := make([]int, n)
	nums[0], nums[1] = 1, 1

	for i := 2; i < n; i++ {
		nums[i] = nums[i-1] + nums[i-2]
	}
	return nums
}

func romanToInt(input string) {
	romanBasic := map[rune]int{
		'M': 1000,
		'D': 500,
		'C': 100,
		'L': 50,
		'X': 10,
		'V': 5,
		'I': 1,
	}
	sum := 0
	inputLength := len(input)
	valid := true
	if inputLength > 1 {
		var cur, next int
		var ok1, ok2 bool
		for i := 0; i < inputLength-1; i++ {
			cur, ok1 = romanBasic[rune(input[i])]
			next, ok2 = romanBasic[rune(input[i+1])]
			if !ok1 || !ok2 {
				valid = false
				break
			}
			if cur >= next {
				sum += cur
			} else {
				sum -= cur
			}
		}
		sum += next
	} else if inputLength == 1 {
		if v, ok := romanBasic[rune(input[0])]; !ok {
			valid = false
		} else {
			sum += v
		}
	}
	if !valid {
		fmt.Println(input, " is an invalid input")
	} else {
		fmt.Println(sum)
	}
}

func main() {
	//slice()
	//fmt.Println(fib_slice(1))
	//fmt.Println(fib_slice2(1))
	//fmt.Println(fib_slice(45))
	//fmt.Println(fib_slice2(45))
	//fmt.Println(fib3(45))

	romanToInt("MCLX")
	romanToInt("MCM")
	romanToInt("MCMXCIX")
	romanToInt("MCMZ")
}
