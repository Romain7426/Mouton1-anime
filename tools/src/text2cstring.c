#include <stdio.h>
#include <assert.h>
int main(void) { 
  putchar('"'); 
  for (;;) { 
    const int c = getchar(); 
    if (EOF  == c) { putchar('"' ); putchar('\n'); return 0; }; 
    if ('\\' == c) { putchar('\\'); putchar('\\'); continue; }; 
    if ('\'' == c) { putchar('\\'); putchar('\''); continue; }; 
    if ('\"' == c) { putchar('\\'); putchar('\"'); continue; }; 
    if ('\?' == c) { putchar('\\'); putchar('\?'); continue; }; 
    if ('\n' == c) { putchar('"' ); putchar(' '); putchar('"'); putchar('\\'); putchar('n'); putchar('"'); putchar('\n'); putchar('"'); continue; }; 
    if ('\r' == c) { putchar('"' ); putchar(' '); putchar('"'); putchar('\\'); putchar('r'); putchar('"'); putchar(' '); putchar('"'); continue; }; 
    if ('\t' == c) { putchar('"' ); putchar(' '); putchar('"'); putchar('\\'); putchar('t'); putchar('"'); putchar(' '); putchar('"'); continue; }; 
    if ('\0' == c) { putchar('\\'); putchar('0'); continue; }; 
    if ('\v' == c) { putchar('\\'); putchar('v'); continue; }; 
    if ('\a' == c) { putchar('\\'); putchar('a'); continue; }; 
    if ('\b' == c) { putchar('\\'); putchar('b'); continue; }; 
    if ('\e' == c) { putchar('\\'); putchar('e'); continue; }; 
    if ('\f' == c) { putchar('\\'); putchar('f'); continue; }; 
    putchar(c); 
  }; 
  assert(0 != 0); 
  return -1; 
}; 
