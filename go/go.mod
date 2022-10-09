module github.com/Gerrard-YNWA/code/go

go 1.14

require (
	github.com/Pallinder/go-randomdata v1.2.0
	github.com/coreos/go-systemd/v22 v22.4.0 // indirect
	github.com/fsnotify/fsnotify v1.5.4
	github.com/golang/protobuf v1.5.2
	github.com/gomodule/redigo v1.8.4
	github.com/gorilla/websocket v1.4.2
	github.com/hashicorp/go-uuid v1.0.2 // indirect
	github.com/k0kubun/go-ansi v0.0.0-20180517002512-3bf9e2903213
	github.com/miekg/dns v1.1.48 // indirect
	github.com/mitchellh/go-homedir v1.1.0
	github.com/moby/moby v20.10.18+incompatible
	github.com/prometheus/client_golang v1.11.1
	github.com/schollz/progressbar/v3 v3.8.6
	github.com/sirupsen/logrus v1.8.1
	github.com/spf13/afero v1.9.2 // indirect
	github.com/spf13/cobra v1.1.3
	github.com/spf13/viper v1.13.0
	github.com/streadway/amqp v1.0.0
	github.com/urfave/cli/v2 v2.4.8
	github.com/xeipuuv/gojsonschema v1.2.0
	go.etcd.io/etcd/client/v3 v3.5.5
	go.uber.org/atomic v1.10.0 // indirect
	go.uber.org/multierr v1.8.0 // indirect
	go.uber.org/zap v1.23.0 // indirect
	golang.org/x/net v0.0.0-20221004154528-8021a29435af // indirect
	golang.org/x/sys v0.0.0-20221006211917-84dc82d7e875 // indirect
	golang.org/x/tools v0.1.10 // indirect
	google.golang.org/genproto v0.0.0-20220930163606-c98284e70a91 // indirect
	google.golang.org/grpc v1.50.0
	google.golang.org/protobuf v1.28.1
	gopkg.in/alexcesaro/quotedprintable.v3 v3.0.0-20150716171945-2caba252f4dc // indirect
	gopkg.in/check.v1 v1.0.0-20201130134442-10cb98267c6c // indirect
	gopkg.in/gomail.v2 v2.0.0-20160411212932-81ebce5c23df
	gorm.io/driver/mysql v1.0.5
	gorm.io/gorm v1.21.6
)

replace google.golang.org/grpc v1.32.0 => google.golang.org/grpc v1.29.1
