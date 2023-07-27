#include <stdlib.h>
#include <string.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;

#define not(b) (!(b))


int main(int argc, char *argv[]) {
  if (argc <= 2) return EXIT_SUCCESS;

  char * base;
  base = argv[1];
  bool_t b;
  b = true;
  for (int i = 2; i < argc; i++) {
    b = (0 == strcmp(base, argv[i]));
    if (not(b)) return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}

