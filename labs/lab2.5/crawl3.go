// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 241.

// Crawl2 crawls web links starting with the command-line arguments.
//
// This version uses a buffered channel as a counting semaphore
// to limit the number of concurrent calls to links.Extract.
//
// Crawl3 adds support for depth limiting.
//
package main

import (
	"fmt"
	"flag"
	"log"
	"os"
	"gopl.io/ch5/links"
)

//!+sema
// tokens is a counting semaphore used to
// enforce a limit of 20 concurrent requests.
var tokens = make(chan struct{}, 20)

func crawl(url string) []string {
	fmt.Println(url)
	tokens <- struct{}{} // acquire a token
	list, err := links.Extract(url)
	<-tokens // release the token

	if err != nil {
		log.Print(err)
	}
	return list
}
//!-sema
var vis = make(map[string]bool)

//!+
func crawl3(url string, depth int, finished chan bool) {
	if depth <= 0 {
		finished <- true
		return
	}
	if visited, ok := vis[url]; visited && ok {
		finished <- true
		return
	} else {
		vis[url] = true
	}
	linksfinished := make(chan bool)
	links := crawl(url)
	for _, link := range links {
		go crawl3(link, depth-1, linksfinished)
		<-linksfinished
	}
	finished <- true
}
func main() {
	depth := flag.Int("depth", 1, "");
	url := os.Args[2]; // !! 
	flag.Parse();
	finished := make(chan bool)
	vis[url] = false
	go crawl3(url, *depth, finished)
	<-finished
}
//!-