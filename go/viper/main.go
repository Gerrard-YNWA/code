package main

import (
	"fmt"
	"log"
	"os"

	"github.com/fsnotify/fsnotify"
	"github.com/spf13/viper"
	_ "github.com/spf13/viper/remote"
)

const configFile = "viper.yaml"

func init() {
	os.Setenv("ENV", "aa")
	os.Setenv("POJ_ENV", "bb")
	//viper使用单例模式, 多个实例需要New
	viper.SetConfigFile(configFile)
	if err := viper.ReadInConfig(); err != nil {
		log.Fatal(err)
	}

	viper.SetEnvPrefix("POJ")
	viper.AutomaticEnv()
	os.Setenv("POJ_ENV2", "cc")

	viper.WatchConfig()
	viper.OnConfigChange(func(e fsnotify.Event) {
		viper.ReadInConfig()
	})
	viper.RegisterAlias("title", "app.name")
}

func printConfig() {
	fmt.Println(viper.GetStringMap("app"))
	fmt.Println(viper.GetString(`title`))
	fmt.Println(viper.GetStringSlice(`app.fruits`))
}

func loadFromEtcd() {
	viper.AddRemoteProvider("etcd", "http://127.0.0.1:2379", "/test/config.json")
	viper.SetConfigType("json")
	if err := viper.ReadRemoteConfig(); err != nil {
		log.Fatal(err)
	}
}

func main() {
	printConfig()
	/*
		watchConfig test
		for i := 0; i < 10; i++ {
			printConfig()
			time.Sleep(1 * time.Second)
		}
	*/

	//env automatically append prefix
	fmt.Println(viper.GetString("ENV"))
	fmt.Println(viper.GetString("ENV2"))

	//check if set
	fmt.Println(viper.IsSet("ENV2"))

	//remote config
	loadFromEtcd()
	fmt.Println(viper.GetStringMap("etcd"))
}
