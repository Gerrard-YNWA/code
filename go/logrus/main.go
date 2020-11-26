package main

import (
	"fmt"
	"log/syslog"
	"path"
	"sort"
	"strings"
	"time"

	log "github.com/sirupsen/logrus"
	lSyslog "github.com/sirupsen/logrus/hooks/syslog"
)

const (
	defaultTimeStampFormat = time.RFC3339
)

var levelLabels = []string{"PANIC", "FATAL", "ERROR", "WARN", "INFO", "DEBUG"}

//custom log format
type CustomTextFormatter struct {
	TimestampFormat string
}

func (f *CustomTextFormatter) Format(entry *log.Entry) ([]byte, error) {
	timestampFormat := f.TimestampFormat
	if timestampFormat == "" {
		timestampFormat = defaultTimeStampFormat
	}
	timestamp := fmt.Sprintf(entry.Time.Format(timestampFormat))

	customKeys := make([]string, 0, len(entry.Data))
	for k := range entry.Data {
		customKeys = append(customKeys, k)
	}
	sort.Strings(customKeys)
	customFieldsVal := ""
	for _, key := range customKeys {
		customFieldsVal = fmt.Sprintf("%s %s=%s", customFieldsVal, key, entry.Data[key])
	}

	var funcVal, fileVal string
	if entry.HasCaller() {
		s := strings.Split(entry.Caller.Function, ".")
		funcVal = fmt.Sprintf("%s()", s[len(s)-1])
		fileVal = fmt.Sprintf("%s:%d", path.Base(entry.Caller.File), entry.Caller.Line)
	}
	if customFieldsVal == "" {
		return []byte(fmt.Sprintf("%s [%s] %s: %s: %s\n", timestamp, levelLabels[entry.Level], fileVal, funcVal, entry.Message)), nil
	} else {
		return []byte(fmt.Sprintf("%s [%s] %s: %s: %s, %s\n", timestamp, levelLabels[entry.Level], fileVal, funcVal, entry.Message, customFieldsVal)), nil
	}
}

func main() {
	log.SetReportCaller(true)
	logFormatter := &CustomTextFormatter{
		TimestampFormat: "2006-01-02 15:04:05",
	}
	log.SetFormatter(logFormatter)
	//send to rsyslog
	hook, err := lSyslog.NewSyslogHook("udp", "127.0.0.1:514", syslog.LOG_LOCAL1, "rsyslog")
	if err != nil {
		log.Fatal("Failed to New SyslogHook")
	}
	log.AddHook(hook)
	log.SetLevel(log.InfoLevel)

	log.WithFields(log.Fields{
		"method": "GET",
		"path":   "/index.html",
		"cost":   "0.001s",
	}).Info("log example")
}
