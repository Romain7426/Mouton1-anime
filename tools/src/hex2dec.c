#include <stdio.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;

static int hex2dec(const char c);


int main(int argc, char *argv[]) {
  
  for (int i = 1; i < argc; i++) {
    printf("%d\n", hex2dec(argv[i][0]));
  }

  return 0;
}

int hex2dec(const char c) {
  if (('0' <= c) && (c <= '9')) return (c - '0');
  if (('a' <= c) && (c <= 'z')) return (c - 'a') + 10;
  if (('A' <= c) && (c <= 'Z')) return (c - 'A') + 10;
  
  return c;
}
