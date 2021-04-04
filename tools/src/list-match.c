#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;


static void strlower(char * str);



int main(int argc, char *argv[]) {
  if (0 == argc) return -3;
  if (1 == argc) return -2;

  strlower(argv[1]);

  for (int i = 2; argv[i] != NULL; i++) {
    if (i == INT_MAX) return -5;
    strlower(argv[i]);
    if (0 == strcmp(argv[1], argv[i])) {
      printf("%d\n", i-1);
      return 0;
    }
  }
  
  printf("Not found\n");
  return 0;
}


void strlower(char * str) {
  assert(str != NULL);
  
  for (int i = 0; str[i] != '\0'; i++) {
    assert(i < INT_MAX);
    str[i] = tolower(str[i]);
  }
}
