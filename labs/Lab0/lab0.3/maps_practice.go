package main

import (
	"strings"

	"golang.org/x/tour/wc"
)

func WordCount(s string) map[string]int {
	c := make(map[string]int)
	for _, w := range strings.Fields(s) {
		c[w]++
	}
	return c
}

func main() {
	wc.Test(WordCount)
}
