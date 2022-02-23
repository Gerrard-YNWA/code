package cmd

import (
	"runtime"

	"github.com/Gerrard-YNWA/code/go/downloader/download"
	"github.com/spf13/cobra"
)

var (
	url         string //download url
	filename    string //output file
	concurrency int
)

var rootCmd = &cobra.Command{
	Use:   "",
	Short: "",
	RunE:  download.Run,
}

func Execute() {
	cobra.CheckErr(rootCmd.Execute())
}

func init() {
	n := runtime.NumCPU()
	rootCmd.PersistentFlags().StringVar(&url, "url", "", "download url")
	rootCmd.MarkPersistentFlagRequired("url")
	rootCmd.PersistentFlags().StringVar(&filename, "filename", "", "output filename")
	rootCmd.PersistentFlags().IntVar(&concurrency, "concurrency", n, "concurrency, default cpu numbers")
}
