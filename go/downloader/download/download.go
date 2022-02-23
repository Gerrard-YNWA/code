package download

import (
	"errors"
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"sync"

	"github.com/k0kubun/go-ansi"
	"github.com/schollz/progressbar/v3"
	"github.com/spf13/cobra"
)

var downloadBytesInconsistentError = errors.New("download error, byte is inconsistent!")
var mergeBytesInconsistentError = errors.New("merge error, byte is inconsistent!")

type Downloader struct {
	concurrency int
	wg          *sync.WaitGroup
	bar         *progressbar.ProgressBar
}

func errMsg(field string, err error) string {
	return fmt.Sprintf("failed to get %s, error: %s", field, err.Error())
}

func getPartialFileName(filename string, idx int) string {
	return fmt.Sprintf("%s.part-%d", filename, idx)
}

func Run(cmd *cobra.Command, args []string) error {
	flags := cmd.Flags()
	conn, err := flags.GetInt("concurrency")
	if err != nil {
		return err
	}
	downloader := &Downloader{
		concurrency: conn,
		wg:          &sync.WaitGroup{},
	}

	url, err := flags.GetString("url")
	if err != nil {
		return err
	}

	filename, err := flags.GetString("filename")
	if err != nil {
		return err
	}

	if filename == "" {
		filename = filepath.Base(url)
	}

	return downloader.Start(url, filename)
}

func (d *Downloader) Start(url, filename string) error {
	resp, err := http.Head(url)
	if err != nil {
		return err
	}

	fmt.Println(resp)
	if resp.StatusCode == http.StatusOK &&
		resp.Header.Get("Accept-Ranges") == "bytes" &&
		d.concurrency > 1 {
		//fmt.Printf("total size: %d\n", resp.ContentLength)
		return d.multiDownload(url, filename, int(resp.ContentLength))
	}

	return d.singleDownload(url, filename)
}

func (d *Downloader) multiDownload(url, filename string, size int) error {
	partial := size / d.concurrency
	d.wg.Add(d.concurrency)
	d.setBar(size)

	start := 0
	for i := 0; i < d.concurrency; i++ {
		end := start + partial
		if i == d.concurrency-1 {
			end = size
		}

		go func(start, end, idx int) {
			defer d.wg.Done()
			d.downloadPartial(url, filename, start, end, idx)
		}(start, end, i)
		start = end + 1
	}

	d.wg.Wait()

	return d.merge(filename)
}

func (d *Downloader) downloadPartial(url, filename string, start, end, idx int) error {
	//fmt.Printf("part: %d, start: %d, end: %d\n", idx, start, end)

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return err
	}

	req.Header.Set("Range", fmt.Sprintf("bytes=%d-%d", start, end))
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	fd, err := os.OpenFile(getPartialFileName(filename, idx), os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		return err
	}
	defer fd.Close()

	n, err := io.Copy(io.MultiWriter(fd, d.bar), resp.Body)
	if err != nil {
		return err
	}
	if int(n) != end-start {
		return downloadBytesInconsistentError
	}

	return nil
}

func (d *Downloader) merge(filename string) error {
	fd, err := os.OpenFile(filename, os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		return err
	}
	defer fd.Close()

	for i := 0; i < d.concurrency; i++ {
		filename := getPartialFileName(filename, i)
		partialFd, err := os.Open(filename)
		if err != nil {
			return err
		}

		n, err := io.Copy(fd, partialFd)
		if err != nil {
			return err
		}
		if stat, err := partialFd.Stat(); err != nil {
			partialFd.Close()
			return err
		} else if stat.Size() != n {
			partialFd.Close()
			return mergeBytesInconsistentError
		}

		partialFd.Close()

		if err := os.Remove(filename); err != nil {
			return err
		}
	}
	return nil
}

func (d *Downloader) singleDownload(url, filename string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	defer resp.Body.Close()
	d.setBar(int(resp.ContentLength))

	fd, err := os.OpenFile(filename, os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		return err
	}
	defer fd.Close()

	if _, err := io.Copy(io.MultiWriter(fd, d.bar), resp.Body); err != nil {
		return err
	}
	return nil
}

func (d *Downloader) setBar(length int) {
	d.bar = progressbar.NewOptions(
		length,
		progressbar.OptionSetWriter(ansi.NewAnsiStdout()),
		progressbar.OptionEnableColorCodes(true),
		progressbar.OptionShowBytes(true),
		progressbar.OptionSetWidth(30),
		progressbar.OptionSetDescription("downloading..."),
		progressbar.OptionSetTheme(progressbar.Theme{
			Saucer:        "[green]=[reset]",
			SaucerHead:    "[green]>[reset]",
			SaucerPadding: " ",
			BarStart:      "[",
			BarEnd:        "]",
		}),
	)
}
