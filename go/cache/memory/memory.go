package memory

import (
	"errors"
	"sync"
	"sync/atomic"
	"time"
)

var (
	NoSpaceError = errors.New("cache: no space for new object")
)

type Object struct {
	value  interface{}
	expire int64
}

type Objects struct {
	values     map[string]*Object
	capacity   int32
	curObjects int32
	// gc interval
	gcInterval int
	// gc max items
	gcMax  int
	stopGC chan struct{}
	sync.RWMutex
}

func New() *Objects {
	o := &Objects{
		values:     map[string]*Object{},
		capacity:   10000,
		gcInterval: 60,
		gcMax:      100,
		stopGC:     make(chan struct{}),
	}

	go o.gcCircle()

	return o
}

func (o *Objects) Get(key string) interface{} {
	o.RLock()
	defer o.RUnlock()

	v, ok := o.values[key]
	if !ok || v.expired() {
		return nil
	}

	return v.value
}

func (o *Objects) Set(key string, val interface{}, ttl int64) error {
	if ttl > 0 {
		ttl = time.Now().Add(time.Duration(ttl) * time.Second).Unix()
	}

	if atomic.LoadInt32(&o.curObjects) >= o.capacity {
		o.gc(1)
		if atomic.LoadInt32(&o.curObjects) >= o.capacity {
			return NoSpaceError
		}
	}

	o.Lock()
	defer o.Unlock()
	if _, ok := o.values[key]; !ok {
		atomic.AddInt32(&o.curObjects, 1)
	}

	o.values[key] = &Object{
		value:  val,
		expire: ttl,
	}

	return nil
}

func (o *Objects) Del(key string) error {
	o.Lock()
	defer o.Unlock()

	if _, ok := o.values[key]; ok {
		delete(o.values, key)
		atomic.AddInt32(&o.curObjects, -1)
	}

	return nil
}

func (o *Objects) Flush() error {
	o.Lock()
	defer o.Unlock()

	o.values = map[string]*Object{}
	return nil
}

func (o *Objects) Destory() {
	o.stopGC <- struct{}{}
	o.Flush()
}

func (o *Objects) gc(max int) {
	o.RLock()
	l := []string{}
	for k, v := range o.values {
		if v.expired() {
			l = append(l, k)
			if len(l) >= max {
				break
			}
		}
	}
	o.RUnlock()
	o.Lock()
	nums := len(l)
	for _, k := range l {
		delete(o.values, k)
	}
	atomic.AddInt32(&o.curObjects, -int32(nums))
	o.Unlock()
}

func (o *Objects) gcCircle() {
	max := o.gcMax
	t := time.NewTicker(time.Duration(o.gcInterval) * time.Second)
	for {
		select {
		case <-o.stopGC:
			t.Stop()
			return
		case <-t.C:
			o.gc(max)
		}
	}
}

func (o *Object) expired() bool {
	if o.expire <= 0 {
		return false
	}

	return time.Now().Unix() >= o.expire
}
