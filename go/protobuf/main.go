package main

import (
	"fmt"

	"github.com/golang/protobuf/proto"

	tutorial "protobuf/examples/tutorial"
)

func main() {
	p1 := &tutorial.Person{
		Id:    1234,
		Name:  "John Doe",
		Email: "jdoe@example.com",
		Phones: []*tutorial.Person_PhoneNumber{
			{Number: "555-4321", Type: tutorial.Person_HOME},
		},
	}

	p2 := new(tutorial.Person)
	p2.Id = 5678
	p2.Name = "John Smith"
	p2.Email = "jsmith@example.com"
	p2.Phones = []*tutorial.Person_PhoneNumber{
		{Number: "555-8765", Type: tutorial.Person_WORK},
	}

	addr := new(tutorial.AddressBook)
	addr.People = append(addr.People, p1)
	addr.People = append(addr.People, p2)

	out, err := proto.Marshal(addr)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(out)
		book := new(tutorial.AddressBook)
		proto.Unmarshal(out, book)
		for i, _ := range book.People {
			fmt.Println(book.People[i])
		}
	}
}
