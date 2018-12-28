package main

import (
	"fmt"
)

type Animal interface {
	Eat()
	Sleep()
}

type Cat struct {
	name string
	food string
}

func (c *Cat) Eat() {
	fmt.Printf("%s eats %s.\n", c.name, c.food)
}

func (c *Cat) Sleep() {
	fmt.Printf("%s sleep.\n", c.name)
}

type Dog struct {
	name string
	food string
}

func (d *Dog) Eat() {
	fmt.Printf("%s eats %s.\n", d.name, d.food)
}

func (d *Dog) Sleep() {
	fmt.Printf("%s sleep.\n", d.name)
}

func Eat(a Animal) {
	a.Eat()
}

func Sleep(a Animal) {
	a.Sleep()
}

func main() {
	animal1 := Cat{"cat", "fish"}
	Eat(&animal1)
	Sleep(&animal1)
	//animal1.Eat()
	//animal1.Sleep()
	animal2 := &Dog{"dog", "pork"}
	Eat(animal2)
	Sleep(animal2)
	//animal2.Eat()
	//animal2.Sleep()
}
