package main

import (
	"./decoder"
	"io"
	"log"
	"os"
)

func main() {
	rFile, _ := os.Open("./audio/daohang.opus")
	wFile, _ := os.OpenFile("./audio/daohang.pcm", os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)

	var dec decoder.Decoder
	log.Printf("decode start!")
	dec = decoder.New(16000)
	dec.Decode("text", []byte(`{"sampleBytes":2,"audioType":"ogg_opus","sampleRate":16000,"channel":1}`))

	var stop bool
	var data []byte
	var bufSize = 1024 * 1000
	buf := make([]byte, bufSize)
	for {
		n, err := io.ReadFull(rFile, buf)
		if err != nil {
			if err == io.ErrUnexpectedEOF {
				stop = true
			} else {
				log.Fatal("read full error:", err)
				break
			}
		}
		if n < bufSize {
			buf = buf[:n]
		}
		data = dec.Decode("binary", buf[:n])
		log.Printf("input len:%d, output len:%d", len(buf), len(data))
		_, wErr := wFile.Write(data)
		if wErr != nil {
			log.Fatal("write data error:", wErr)
		}
		if stop {
			break
		}
	}
	dec.Decode("binary", nil)
	dec.Delete()
	log.Printf("decode done!")
	defer rFile.Close()
	defer wFile.Close()
}
