package main

import (
	"fmt"
)

type (
	Operator interface {
		Apply(int, int) int
	}

	Operation struct {
		Operator Operator
	}
)

func (o *Operation) Operate(leftValue, rightValue int) int {
	return o.Operator.Apply(leftValue, rightValue)
}

type Addition struct{}

func (Addition) Apply(lval, rval int) int {
	return lval + rval
}

type Multiplication struct{}

func (Multiplication) Apply(lval, rval int) int {
	return lval * rval
}

func main() {
	add := Operation{
		Addition{},
	}
	fmt.Println(add.Operate(3, 5))
	mul := Operation{
		Multiplication{},
	}
	fmt.Println(mul.Operate(3, 5))
}
