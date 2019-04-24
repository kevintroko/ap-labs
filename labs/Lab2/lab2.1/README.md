Lab 2.1 - ClockWall
===================

### Requirments
- Golang, https://golang.org
- Two terminals

### Using makefiles
#### Terminal 1
In your **terminal 1** write:
````
make
````
!! Dont forget if you have servers already running in those ports then:
````
make kill
````
if it doesn't work then:
````
killall clock2
````

#### Terminal 2
In your **terminal 2** write:
````
make clock
````

Finally, clean your binaries with
````
make clean
````
if it doesn't work then:
````
rm -rf clock2
rm -rf clockWall
````

### Compile by hand
First compile the files 
````
go build clock2.go
go build clockWall.go
````

Now in your **terminal 1** write:
````
TZ=<timezone> ./clock2 -port <portNumber>

````

Example for multiple timezones
````
TZ=US/Eastern    ./clock2 -port 8010 & TZ=Asia/Tokyo    ./clock2 -port 8020 & TZ=Europe/London ./clock2 -port 8030 &
````

To run the client in your **terminal 2** write: 
````
./clockWall <city name>=<host>:<port> 
````
An example for running multiple clients:
````
./clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
````
