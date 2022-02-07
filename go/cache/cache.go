package cache

import (
	"github.com/Gerrard-YNWA/code/go/cache/memory"
)

type CacheType int

const (
	MemoryCache = iota
)

type Cache interface {
	Get(key string) interface{}
	Set(key string, val interface{}, ttl int64) error
	Del(key string) error
	Destory()
}

func New(ct CacheType) Cache {
	switch ct {
	case MemoryCache:
		return memory.New()
	default:
		return memory.New()
	}
}
