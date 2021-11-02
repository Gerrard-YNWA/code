package main

import (
	"fmt"
	"reflect"
)

type order struct {
	id         int
	customerId int
}

type customer struct {
	id      int
	name    string
	address string
}

func generateSQL(o interface{}) string {
	v := reflect.ValueOf(o)
	if v.Kind() != reflect.Struct {
		panic(fmt.Sprintf("unsupported argument type: %s", v.Kind()))
	}

	t := reflect.TypeOf(o)
	tbl := t.Name()
	sql := fmt.Sprintf("INSERT INTO %s ", tbl)
	columns := "("
	values := "VALUES ("
	columnPattern := "%s"

	var valuePattern string
	for i := 0; i < v.NumField(); i++ {
		switch v.Field(i).Kind() {
		case reflect.Int:
			if i == 0 {
				valuePattern = "%d"
			} else {
				valuePattern = ", %d"
			}
			values += fmt.Sprintf(valuePattern, v.Field(i).Int())
		case reflect.String:
			if i == 0 {
				valuePattern = "%s"
			} else {
				valuePattern = ", '%s'"
			}
			values += fmt.Sprintf(valuePattern, v.Field(i).String())
		}
		columns += fmt.Sprintf(columnPattern, t.Field(i).Name)
		columnPattern = ", %s"
	}

	columns += ") "
	values += ");"

	sql = sql + columns + values

	return sql
}

func main() {
	o := order{1, 12345}
	fmt.Println(generateSQL(o))
	c := customer{12345, "gerrard", "China"}
	fmt.Println(generateSQL(c))
}
