# Lab 1.2
==================

### Compilation
I added a makefile to compile and run

````
make 
````

or run the next command to clean the .o files
```
make clean
```

### Other option

problem with make file is that it will always print ** hello kevin ** so if you want personalized message then:

```
	gcc broadcaster.c -o broadcaster.o
	./broadcaster.o <Message to display>
```