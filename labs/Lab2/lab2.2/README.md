Lab 2.2 - Logger Library
========================

Implement a Logger library in C that will be used for printing the following types of messages.
- `INFO` General information. 
- `WARN` Warnings.
- `ERROR` Errors.
- `PANIC` Panics. Non recoverable issues with core dump.

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