/*
Copyright © 2021 NAME HERE <EMAIL ADDRESS>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
package cmd

import (
	"fmt"
	"strconv"
	"time"

	"github.com/spf13/cobra"
)

const (
	dateFormat = "2006-01-02 15:04:05"
)

// convertCmd represents the convert command
var convertCmd = &cobra.Command{
	Use:   "convert",
	Short: "convert unix timestamp to date format",
	Run: func(cmd *cobra.Command, args []string) {
		ts := time.Now().Unix()
		if len(args) > 0 {
			ts, _ = strconv.ParseInt(args[0], 10, 64)
		}
		fmt.Println(time.Unix(ts, 0).Format(dateFormat))
	},
}

func init() {
	rootCmd.AddCommand(convertCmd)
}
