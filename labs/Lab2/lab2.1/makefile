compile:
	go build clock2.go
	go build clockWall.go
	TZ=US/Eastern    ./clock2 -port 8010 & TZ=Asia/Tokyo    ./clock2 -port 8020 & TZ=Europe/London ./clock2 -port 8030 &
clean:
	rm -rf clock2
	rm -rf clockWall
kill:
	killall clock2
clock:
	./clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030