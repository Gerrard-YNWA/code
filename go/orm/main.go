package main

import (
	"fmt"

	log "github.com/sirupsen/logrus"
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
)

type MySQLConf struct {
	Host     string
	Port     int
	User     string
	Password string
	DB       string
}

type User struct { //table name => users
	Id   int
	Age  int
	Name string
}

//hook
func (u *User) AfterFind(tx *gorm.DB) (err error) {
	if u.Name == "kyle" {
		log.Infof("After find: [#%v]", u)
	}
	return
}

var conf *MySQLConf

func init() {
	conf = &MySQLConf{
		Host:     "172.16.20.45",
		Port:     3306,
		User:     "test",
		Password: "aispeech",
		DB:       "test",
	}
}

func connect() *gorm.DB {
	dsn := fmt.Sprintf("%s:%s@tcp(%s:%d)/%s", conf.User, conf.Password, conf.Host, conf.Port, conf.DB)
	db, err := gorm.Open(mysql.Open(dsn), &gorm.Config{
		Logger: logger.Default.LogMode(logger.Info),
	})
	if err != nil {
		log.Fatalf("failed to connect error [%s]", err.Error())
	}
	return db
}

func main() {
	db := connect()
	// https://gorm.io/docs/
	var users []User
	db.Where("name = ?", "sy").Find(&users)
	log.Infof("user [%#v]", users)
	db.Select("name", "age").Find(&users)
	log.Infof("user [%#v]", users)
	db.Debug().Select("name", "age").First(&users)
	log.Infof("user [%#v]", users)
}
