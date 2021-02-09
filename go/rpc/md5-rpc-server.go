package main

import (
	"crypto/md5"
	"encoding/hex"
	"log"
	"net"
	"net/rpc"
)

const HashContentServiceName = "/rpc/pkg.HashContentService"

type HashContentServiceInterface interface {
	Md5(buffer []byte, reply *string) error
}

func RegisterHashContentService(svc HashContentServiceInterface) error {
	return rpc.RegisterName(HashContentServiceName, svc)
}

type HashContentService struct {
	conn net.Conn
}

func (p *HashContentService) Md5(bytes []byte, reply *string) error {
	log.Printf("from %s\n", p.conn.RemoteAddr().String())
	hash := md5.Sum(bytes)
	*reply = hex.EncodeToString(hash[:])
	return nil
}

func main() {
	//RegisterHashContentService(new(HashContentService))
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		log.Fatal("Listen tcp error:", err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Fatal("Accept error:", err)
		}

		go func() {
			defer conn.Close()

			p := rpc.NewServer()
			p.RegisterName(HashContentServiceName, &HashContentService{conn: conn})
			p.ServeConn(conn)
		}()
	}
}
