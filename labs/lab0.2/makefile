all:

	gcc -c str-main.c -o str-main.o 
	gcc -c strlib.c -o strlib.o
	gcc str-main.o strlib.o -o str-final.o
	./str-final.o

clean: 
	rm -rf str-final