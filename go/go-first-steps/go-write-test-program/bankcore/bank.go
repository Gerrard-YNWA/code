package bank

import (
	"errors"
	"fmt"
)

var ErrInvalidDepositAmount = errors.New("the amount to deposit should be greater than zero")
var ErrInvalidWithdrawAmount = errors.New("the amount to withdraw should be greater than zero and less than the account's balance'")
var ErrInvalidTransferAmount = errors.New("the amount to transfer should be greater than zero and less than the account's balance'")

type Bank interface {
	Statement() string
}

type Customer struct {
	Name    string
	Address string
	Phone   string
}

type Account struct {
	Customer
	Number  int32
	Balance float64
}

func (a *Account) Deposit(amount float64) error {
	if amount <= 0 {
		return ErrInvalidDepositAmount
	}

	a.Balance += amount
	return nil
}

func (a *Account) Withdraw(amount float64) error {
	if amount <= 0 || amount > a.Balance {
		return ErrInvalidWithdrawAmount
	}

	a.Balance -= amount
	return nil
}

func (a *Account) Statement() string {
	return fmt.Sprintf("%v - %v - %v", a.Number, a.Name, a.Balance)
}

func (a *Account) Transfer(amount float64, b *Account) error {
	if amount <= 0 || amount > a.Balance {
		return ErrInvalidTransferAmount
	}

	a.Withdraw(amount)
	b.Deposit(amount)
	return nil
}

func Statement(b Bank) string {
	return b.Statement()
}
