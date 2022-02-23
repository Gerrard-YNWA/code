module github.com/Gerrard-YNWA/code/go

go 1.14

require (
	github.com/Pallinder/go-randomdata v1.2.0
	github.com/fsnotify/fsnotify v1.4.7
	github.com/golang/protobuf v1.5.0
	github.com/gomodule/redigo v1.8.4
	github.com/gorilla/websocket v1.4.2
	github.com/k0kubun/go-ansi v0.0.0-20180517002512-3bf9e2903213 // indirect
	github.com/mitchellh/go-homedir v1.1.0
	github.com/moby/moby v20.10.5+incompatible
	github.com/prometheus/client_golang v1.5.1
	github.com/schollz/progressbar/v3 v3.8.6 // indirect
	github.com/sirupsen/logrus v1.8.1
	github.com/spf13/cobra v1.1.3
	github.com/spf13/viper v1.7.1
	github.com/streadway/amqp v1.0.0
	github.com/urfave/cli/v2 v2.3.0
	github.com/xeipuuv/gojsonschema v1.2.0
	go.etcd.io/etcd/client/v3 v3.5.0-alpha.0
	golang.org/x/crypto v0.0.0-20220214200702-86341886e292 // indirect
	golang.org/x/sys v0.0.0-20220209214540-3681064d5158 // indirect
	google.golang.org/grpc v1.32.0
	google.golang.org/protobuf v1.26.0
	gopkg.in/alexcesaro/quotedprintable.v3 v3.0.0-20150716171945-2caba252f4dc // indirect
	gopkg.in/gomail.v2 v2.0.0-20160411212932-81ebce5c23df
	gorm.io/driver/mysql v1.0.5
	gorm.io/gorm v1.21.6
)

replace google.golang.org/grpc v1.32.0 => google.golang.org/grpc v1.29.1
