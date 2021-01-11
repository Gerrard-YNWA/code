package main

import (
	"fmt"
	"time"

	"github.com/gomodule/redigo/redis"
)

var redisPool *redis.Pool

func newRedisPool() *redis.Pool {
	return &redis.Pool{
		MaxIdle:     10, //max connections in pool
		MaxActive:   20, //max connections can open, will decrease to MaxIdle, which will cause TIME_WAIT state in `netstat`
		IdleTimeout: 60 * time.Second,
		Wait:        true, //If Wait is true and the pool is at the MaxActive limit, then Get() waits for a connection to be returned to the pool before returning.
		Dial: func() (redis.Conn, error) {
			c, err := redis.Dial("tcp", "127.0.0.1:6379")
			if err != nil {
				return nil, err
			}
			if _, err := c.Do("AUTH", "test"); err != nil {
				c.Close()
				return nil, err
			}
			if _, err := c.Do("SELECT", 1); err != nil {
				c.Close()
				return nil, err
			}
			return c, nil
		},
		TestOnBorrow: func(c redis.Conn, t time.Time) error {
			if time.Since(t) < time.Minute {
				return nil
			}
			_, err := c.Do("PING")
			return err
		},
	}
}

func init() {
	redisPool = newRedisPool()
}

func main() {
	conn := redisPool.Get()
	defer conn.Close()
	reply, err := redis.String(conn.Do("SET", "foo", "bar"))
	fmt.Println(reply, err)
	reply, err = redis.String(conn.Do("GET", "foo"))
	fmt.Println(reply, err)
	reply, err = redis.String(conn.Do("GET", "bar"))
	fmt.Println(reply, err)
}
