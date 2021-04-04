#include <stdio.h>
#include <string.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;



int main(int argc, char *argv[]) {
  bool b;

  for (int i = 1; i < argc; i++) {
    for (int j = i+1; j < argc; j++) {
      b = (0 == strcmp(argv[i],argv[j]));
      if (b) {
        argc --;
        argv[j] = argv[argc];
        j--;
      }
    }
  }

  for (int i = 1; i < argc; i++)
    printf("%s ", argv[i]);

  printf("\n");

  return 0;
}

