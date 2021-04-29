package store

import (
	"errors"
	"fmt"
)

var ErrInvalidCreditAmount = errors.New("Invalid Credit Amount")

type Account struct {
	FirstName string
	LastName  string
}

type Employee struct {
	Account
	Credits float64
}

func (a *Account) ChangeName(name string) {
	a.FirstName = name
}

func (e *Employee) changeCredits(amount float64) {
	e.Credits += amount
}

func (e *Employee) AddCredits(amount float64) (bool, error) {
	if amount < 0 {
		return true, ErrInvalidCreditAmount
	}
	e.changeCredits(amount)
	return true, nil
}

func (e *Employee) RemoveCredits(amount float64) (bool, error) {
	if amount < 0 || amount > e.Credits {
		return false, ErrInvalidCreditAmount
	}
	e.changeCredits(-amount)
	return true, nil
}

func (e *Employee) CheckCredits() float64 {
	return e.Credits
}

func (e *Employee) String() string {
	return fmt.Sprintf("Employee: %s %s credits: %.2f", e.FirstName, e.LastName, e.Credits)
}
