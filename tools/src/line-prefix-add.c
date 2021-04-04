#include <stdio.h>
#include <assert.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;

#define not(test) (!(test))


#define PUT_STRING(str_) { const char * str = (str_); if (not(str == NULL)) while (*str != '\0') { putchar(*str); str++; } }


int main(const int argc, const char * argv[]) {
  int c;
  const char * prefix;

  if (argc >= 2)
    prefix = argv[1];
  else
    prefix = "";


  do {
    c = getchar();
    if (c == EOF) return 0;
    PUT_STRING(prefix);
    putchar(c);
    
    do {
      c = getchar();
      if (c == EOF) { putchar('\n'); return 0; }
      putchar(c);
    } while (c != '\n');

  } while (true);


  assert(false);
  return -1;
}

