Lab 2.3 - Cross-referencer
==========================

Write a cross-referencer in C that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like `the`, `and`, and so on.

Test cases
----------
Your program will be tested with the following txt-based books.

- [irving-little-573.txt](./irving-little-573.txt)
- [irving-london-598.txt](./irving-london-598.txt)

Compile (Default)
----------
````
make
````
If everything fails for some reason then:
````
gcc cross-ref.c -o cross-ref 
./cross-ref <name of file>
````

Compile Irving Little
----------
````
make irving
````
If everything fails for some reason then:
````
gcc cross-ref.c -o cross-ref 
./cross-ref irving-little-573.txt
````

Compile Irving London
----------
````
make london
````
If everything fails for some reason then:
````
gcc cross-ref.c -o cross-ref 
./cross-ref irving-london-598.txt
````

Clean 
----------
Clean binaries
````
make clean
````
If everything fails for some reason then:
````
rm *.out
rm -rf cross-ref
````
