package main

import (
	log "github.com/sirupsen/logrus"
	"github.com/xeipuuv/gojsonschema"
)

var (
	compiledSchema *gojsonschema.Schema

	testSchema string = `{
	"title":"test schema",
	"type": "object",
	"properties": {
		"value":{
			"type":"integer"
		},
		"list": {
			"type":"array",
			"items":{
				"type":"string"
			},
			"maxItems":3
		},
		"key":{
			"type":"string",
			"maxLength":5,
			"minLength":1
		}

	},
	"required": ["value", "key"],
    "additionalProperties":false
}`

	testJsonString string = `{
	"value":1,
	"key":"test"
}`
	testString2 string = `{
		"list":["aaa", 1],
		"key":"list",
		"value": 1
	}`
)

type TestBody struct {
	Value int      `json:"value"`
	Key   string   `json:"key"`
	List  []string `json:"list"`
}

func checkResult(s string, result *gojsonschema.Result) {
	if !result.Valid() {
		for _, err := range result.Errors() {
			log.Errorf("validate %s : %#v", s, err.String())
		}
	} else {
		log.Infof("validate %s : %#v", s, result.Valid())
	}
}

func validate(s string, schema, document gojsonschema.JSONLoader) {
	result, err := gojsonschema.Validate(schema, document)
	if err != nil {
		log.Fatal(s, err)
	}
	checkResult(s, result)
}

func validate2(s string, document gojsonschema.JSONLoader) {
	result, err := compiledSchema.Validate(document)
	if err != nil {
		log.Fatal(s, err)
	}
	checkResult(s, result)
}

func init() {
	var err error
	//compile
	sl := gojsonschema.NewSchemaLoader()
	compiledSchema, err = sl.Compile(gojsonschema.NewStringLoader(testSchema))

	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	schema := gojsonschema.NewStringLoader(testSchema)

	document1 := gojsonschema.NewStringLoader(testJsonString)
	validate("document1", schema, document1)

	//list type error
	document2 := gojsonschema.NewGoLoader(TestBody{Key: "test", Value: 1})
	validate("document2", schema, document2)

	document3 := gojsonschema.NewGoLoader(TestBody{Key: "test", Value: 1, List: []string{"aaa", "bbb", "ccc"}})
	validate("document3", schema, document3)

	document4 := gojsonschema.NewGoLoader(TestBody{Key: "aaaa", Value: 1, List: []string{"aaa", "bbb", "ccc"}})
	validate2("document4", document4)

	document5 := gojsonschema.NewStringLoader(testString2)
	validate2("document5", document5)
}
