#include <stdio.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;



int main(int argc, char *argv[]) {

  printf("%d\n", argc-1);

  return 0;
}

