package eval

import (
	"fmt"
	"math"
	"testig"
)

func TestEval(t *testing.T) {
	tests := []struct {
		expr string
		env  Env
		want string
	}{
		{"sqrt(A/pi)", Env{"A": 87616, "pi": math.Pi}, "167"},
		{"pow(x, 3) + pow(y,3)", Env{"x": 12, "y": 1}, "1729"},
		{"pow(x, 3) + pow(y,3)", Env{"x": 9, "y": 10}, "1729"},
		{"5 / 9 * (F - 32)", Env{"F": 32}, "0"},
		{"5 / 9 * (F - 32)", Env{"F": 212}, "100"},
	}
	var prevExpr string
	for _, test := range tests {
		if test.expr != prevExpr {

		}
	}
}
