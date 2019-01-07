package main

import (
	"encoding/json"
	"fmt"
	"log"
)

var JSON = `{
	"name" :"gopher",
	"title" : "programmer",
	"contact" :{
		"home":"415.333.333",
		"cell":"415.555.555"
	}
}`

func main() {
	var c map[string]interface{}
	err := json.Unmarshal([]byte(JSON), &c)
	if err != nil {
		log.Println("ERROR:", err)
		return
	}
	fmt.Println("Name:", c["name"])
	fmt.Println("Title:", c["title"])
	fmt.Println("Contact")
	fmt.Println("H:", c["contact"].(map[string]interface{})["home"])
	fmt.Println("C:", c["contact"].(map[string]interface{})["cell"])
}
