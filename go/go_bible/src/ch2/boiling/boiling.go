package main

import "fmt"

const boilingF = 221.0

func main() {
	var f = boilingF
	var c = (f - 32) * 5 / 9
	fmt.Printf("boiling point = %g °F or %g °C\n", f, c)
}
