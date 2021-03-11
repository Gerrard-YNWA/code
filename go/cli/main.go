package main

import (
	"fmt"
	"os"
	"strconv"
	"time"

	"github.com/urfave/cli/v2"
)

const (
	dateFormat = "2006-01-02 15:04:05"
)

func displayTime(c *cli.Context) error {
	switch c.String("type") {
	case "unix":
		fmt.Println(int64(time.Now().Unix()))
	case "unix-ms":
		fmt.Println(int64(time.Now().UnixNano() / 1000000))
	default:
		fmt.Println(time.Now().Format(dateFormat))
	}

	return nil
}

func convertTime(c *cli.Context) error {
	ts := time.Now().Unix()
	if c.NArg() > 0 {
		ts, _ = strconv.ParseInt(c.Args().Get(0), 10, 64)
	}
	fmt.Println(time.Unix(ts, 0).Format(dateFormat))
	return nil
}

func main() {
	app := cli.NewApp()
	app.Version = "1.0.0"
	app.Usage = "a cli tool for time convert"
	app.EnableBashCompletion = true
	app.Authors = []*cli.Author{
		{
			Name:  "gerrard",
			Email: "gyc.ssdut@gmail.com",
		},
	}

	app.Flags = []cli.Flag{
		&cli.StringFlag{Name: "type", Aliases: []string{"t"}, Value: "iso", Usage: "time format (iso or unix or unix-ms) "},
	}
	app.Commands = []*cli.Command{
		{
			Name:   "convert",
			Usage:  "convert timestamp to date, default now.",
			Action: convertTime,
		},
	}

	app.Action = displayTime
	app.Run(os.Args)
}
