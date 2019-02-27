// ClockWall is client that ask the time.
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

func main() {
	channel := make(chan int)
	for _, args := range os.Args[1:]{
		params := strings.Split(args, "=")
		city := params[0]
		port := params[1]
		conn, err := net.Dial("tcp", port)
		if err != nil {
			log.Fatal(err)
		}
		go clockSet(conn, city, channel)
	}
	_ = <-channel
	close(channel)
}

func clockSet(conn net.Conn, city string, ch chan int) {
	var err error
	for true {
		time.Sleep((1 * time.Second))
		fmt.Printf(city + ": ")
		_, err = io.CopyN(os.Stdout, conn, 9)
		if err == io.EOF {
			break
		} else if err != nil {
			log.Fatal("Error", err)
		}
	}
	ch <- 2
}

