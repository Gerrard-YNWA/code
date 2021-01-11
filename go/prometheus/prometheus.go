package main

import (
	"net/http"
	"runtime"

	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
	//log "github.com/sirupsen/logrus"
)

var (
	httpStatusCodeCounterVec = prometheus.NewCounterVec(
		prometheus.CounterOpts{
			Name: "http_status",
			Help: "http response status",
		},
		[]string{"code"},
	)

	goroutineGauge = prometheus.NewGauge(
		prometheus.GaugeOpts{
			Name: "goroutines",
			Help: "count of goroutines",
		},
	)

	reg *prometheus.Registry

	fns []func()
)

func RegisterFn(fn func()) {
	fns = append(fns, fn)
}

func updateGoroutineNum() {
	goroutineGauge.Set(float64(runtime.NumGoroutine()))
}

func increaseStatusCode() {
	httpStatusCodeCounterVec.WithLabelValues("200").Inc()
}

type customPromHandler struct {
	handler http.Handler
}

func (h customPromHandler) ServeHTTP(rw http.ResponseWriter, r *http.Request) {
	for _, fn := range fns {
		fn()
	}
	h.handler.ServeHTTP(rw, r)
}

func handler(handler http.Handler) customPromHandler {
	return customPromHandler{handler}
}

func init() {
	reg = prometheus.NewRegistry()
	reg.MustRegister(goroutineGauge)
	reg.MustRegister(httpStatusCodeCounterVec)
	RegisterFn(updateGoroutineNum)
	RegisterFn(increaseStatusCode)
}

func main() {
	http.Handle("/prometheus", handler(promhttp.HandlerFor(reg, promhttp.HandlerOpts{})))
	http.ListenAndServe(":8080", nil)
}
