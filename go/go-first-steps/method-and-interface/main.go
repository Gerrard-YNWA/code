package main

import (
	"fmt"

	"go-first-steps/method-and-interface/store"
)

func main() {
	e := &store.Employee{
		Account: store.Account{FirstName: "Steven", LastName: "Jordan"},
		Credits: 100.0,
	}
	fmt.Println(e)

	if ok, err := e.AddCredits(100); ok {
		fmt.Println("Add Credits ok: ", e.CheckCredits())
	} else {
		fmt.Println("Add Credits error: ", err)
	}
	fmt.Println(e)

	if ok, err := e.RemoveCredits(500); ok {
		fmt.Println("Remove Credits ok: ", e.CheckCredits())
	} else {

		fmt.Println("Remove Credits error: ", err)
	}
	fmt.Println(e)

	e.ChangeName("Michael")
	fmt.Println(e)
}
