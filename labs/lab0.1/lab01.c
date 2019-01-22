/*
  I based myself mostly in the code by Edge Case Berg
  reference link: https://gist.github.com/EdgeCaseBerg/5938505 
 
    Some other References getChar: https://www.tutorialspoint.com/c_standard_library/c_function_putchar.htm
    Kevin Oswaldo Cabrera Navarro A0122157
 */

#include <stdio.h>

int main() {
  char previous, current, next;

// Run the getchar will scan while the file is not over 
  while ((current = getchar()) != EOF) {
    if (current == '"') {
      putchar(previous = current);
      while ((current = getchar())!= '"'|| previous == '\\') 
      {
        putchar(previous = current);
      }
      putchar(previous = current); 

    } else if (current == '/') 
      {
      next = getchar();
      if (next == '/') 
      {
        while ((current = getchar()) != '\n'){
          //Dont add white spaces if there is a string
          if(current=='"')
            putchar('\n');
          }
      } 
      else if (next == '*') 
      {
        previous = getchar();
        while ((current = getchar()) != '/' || previous != '*') 
        {
          previous = current;
        }
      } 
      else 
      {
        putchar(current);
        putchar(previous = next);
      }
    } 
    else 
    {
      putchar(previous = current);
    }
  }
}
