Lab 2.4 - Add `syslog` support to your Logger
=============================================

Now it's time to add support for Linux system logging into your logger that you implemented on [lab2.2](https://github.com/CodersSquad/ap-labs/tree/master/labs/lab2.2).

A new `initLogger`function will be added in order to add support for choosing between `stdout` or `syslog` logging.

### Compile
In order to compile the file you can simply use the makefile:
````
make
````

or clean the binaries as:
````
make
````

### Manual compilation
You can also compile and run by hand, using the commands:
````
gcc logger.c testLogger.c -o lab22
./lab22
````

### Color guide
- `INFO` : GREEN. 
- `WARN` : YELLOW.
- `ERROR`: RED.
- `PANIC`: MAGENTA.