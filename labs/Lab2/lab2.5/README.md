Lab 2.5 - Depth-limiting Web Crawler
====================================

Add depth-limiting to the concurrent web crawler from [crawl2.go](https://github.com/CodersSquad/hello-gophers/blob/master/src/crawl2.go).
That is, if the user sets `-depth=3`, then only URLs reachable by at most 3 links will be fetched.

Compile
==========
You can go by makefile just typing 
````
make
````

if everything fails you can do it manually by 
````
go run crawl3.go -depth=2 https://google.com/
````

or
````
go build crawl3.go
./crawl3 -depth=2 https://google.com/
````

Test Cases
==========

```
# Test 1
go run crawl3.go -depth=2 https://google.com/

# Test 2
go run crawl3.go -depth=3 http://www.gopl.io/

# Test 3
go run crawl3.go -depth=1  http://www.gopl.io/

```
