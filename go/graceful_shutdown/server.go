package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
	"strconv"
	"sync"
	"syscall"
	"time"
)

type server struct {
	listener    net.Listener
	tcpListener *net.TCPListener
	chStop      chan bool
	conns       map[net.Conn]struct{}
	muConns     sync.RWMutex
	isStop      bool
	muStop      sync.RWMutex
	wg          sync.WaitGroup
}

func (s *server) checkError(str string, err error) {
	if err != nil {
		log.Println("Error, ", str, ", ", err)
		panic(err)
	}
}

func (s *server) setEnv(env string, value string) {
	err := os.Setenv(env, value)
	s.checkError(fmt.Sprintf("Setenv %s %s", env, value), err)
}

func (s *server) hupSignal() {
	c := make(chan os.Signal, 1)
	signal.Notify(c, syscall.SIGHUP)
	go func() {
		<-c
		s.muStop.Lock()
		s.isStop = true
		s.muStop.Unlock()
		s.tcpListener.SetDeadline(time.Now()) // 停止接受客户端请求
		listenerFile, err := s.tcpListener.File()
		s.checkError("get listener file", err)
		s.setEnv("GRACEFUL_RESTART", "true")
		s.setEnv("GRACEFUL_RESTART_FILES", strconv.Itoa(4+len(s.conns)))

		execSpec := &syscall.ProcAttr{
			Env:   os.Environ(),
			Files: nil,
		}
		execSpec.Files = make([]uintptr, 4+len(s.conns))
		copy(execSpec.Files[0:5], []uintptr{
			os.Stdin.Fd(),
			os.Stdout.Fd(),
			os.Stderr.Fd(),
			listenerFile.Fd(), // 发送监听套接字到子进程
		})
		s.muConns.RLock()
		pos := 5
		for conn, _ := range s.conns { // 发送长连接套接字到子进程
			file, err := conn.(*net.TCPConn).File()
			s.checkError("get TCPConn file", err)
			execSpec.Files[pos] = file.Fd()
			pos++
		}
		s.muConns.RUnlock()

		pid, err := syscall.ForkExec(os.Args[0], os.Args, execSpec) // 启动新进程
		log.Println("pid of new process is", pid, err)
		s.chStop <- true
	}()
}

func (s *server) isRun() bool {
	s.muStop.RLock()
	isrun := (s.isStop == false)
	s.muStop.RUnlock()
	return isrun
}

func (s *server) closeDeleteConn(conn net.Conn) {
	s.muConns.Lock()
	delete(s.conns, conn)
	s.muConns.Unlock()
	conn.Close()
}

func (s *server) handle(conn net.Conn) {
	defer s.wg.Done()
	s.muConns.Lock()
	s.conns[conn] = struct{}{}
	s.muConns.Unlock()
	s.wg.Add(1)
	buf := make([]byte, 512)
	for s.isRun() {
		_, err := conn.Read(buf)
		if err != nil {
			log.Println("Error reading", err.Error())
			s.closeDeleteConn(conn)
			return
		}
		log.Printf("Received data: %v", string(buf))
	}
}

func (s *server) setTcpListener() {
	tcpListener, ok := s.listener.(*net.TCPListener)
	if !ok {
		log.Fatal("Error tcpListener")
	}
	s.tcpListener = tcpListener
}

func (s *server) startFromFork() {
	file := os.NewFile(3, "/tmp/graceful_reload")
	var err error
	s.listener, err = net.FileListener(file)
	s.checkError("get network listener", err)
	s.setTcpListener()

	uLimit, err := strconv.Atoi(os.Getenv("GRACEFUL_RESTART_FILES"))
	s.checkError("atoi GRACEFUL_RESTART_FILES", err)
	for fd := 4; fd < uLimit; fd++ {
		file := os.NewFile((uintptr)(fd), "/tmp/"+strconv.Itoa(fd))
		conn, err := net.FileConn(file)
		s.checkError("get network connection", err)
		go s.handle(conn)
	}
}

func (s *server) startFromPort() {
	var err error
	s.listener, err = net.Listen("tcp", "localhost:8080")
	s.checkError("listen", err)
	s.setTcpListener()
}

func main() {
	log.Println("Starting the server ...")
	s := &server{
		chStop: make(chan bool),
		conns:  make(map[net.Conn]struct{}, 10000),
	}
	if os.Getenv("GRACEFUL_RESTART") == "true" {
		s.startFromFork()
	} else {
		s.startFromPort()
	}

	s.hupSignal()

	for {
		conn, err := s.listener.Accept()
		if err != nil {
			if nerr, ok := err.(net.Error); ok && nerr.Timeout() {
				break
			} else {
				log.Fatal("Error accepting", err.Error())
			}
		}
		go s.handle(conn)
	}

	log.Println("not accept anymore")
	go func() {
		s.wg.Wait()
		s.chStop <- true
	}()
	select { // 等待旧服务不再处理连接
	case <-s.chStop:
		log.Println("server stop")
	case <-time.After(time.Second * 5):
		log.Println("timeout, server stop")
	}
}
