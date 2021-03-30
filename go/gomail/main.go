package main

import (
	"crypto/tls"
	"gopkg.in/gomail.v2"
)

//https://pkg.go.dev/gopkg.in/gomail.v2
func main() {
	m := gomail.NewMessage()
	m.SetHeader("From", "sender@example.com")
	m.SetHeader("To", "someone@example.com")
	m.SetAddressHeader("Cc", "anotherone@example.com", "cc")
	m.SetHeader("Subject", "Gomail test")
	m.SetBody("text/html", "Hello, this is a test mail sent by gomail lib.")

	d := gomail.NewDialer("smtp.example.com", 465, "sender@example.com", "send's password")
	d.TLSConfig = &tls.Config{InsecureSkipVerify: true}
	if err := d.DialAndSend(m); err != nil {
		panic(err)
	}
}
