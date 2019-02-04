# Lab 0.2

This laboratory is focused on the C files linking

## Some gcc flags
- **gcc -c** compiles source files without linking.
- **gcc -o** writes the build output to an output file.

* A file ending in .o is an object file, The compiler creates an object file for each source file, before linking them together, into the final executable.

## Usage

```
gcc -c str-main.c -o str-main.o
gcc -c strlib.c -o strlib.o
gcc str-main.o strlib.o -o str-final.o
./str-final "originalString" "stringToCompare"
```

or you can simply write in the terminal:
```
make
./str-final "originalString" "stringToCompare"

```