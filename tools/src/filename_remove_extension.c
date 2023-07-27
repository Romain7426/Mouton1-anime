#include <stdio.h>
#include <limits.h>
#include <assert.h>

static int look_for_last_dot(const char * str);

int main(int argc, char * argv[]) {
  if (0 == argc) return -2;
  
  if (1 == argc) return -3;

  if (argc > 2) return -4;
  
  assert(argv[1] != NULL);
  
  int p;
  p = look_for_last_dot(argv[1]);
  if (p < -1) return p-4;
  
  if (p > 0)
    argv[1][p]='\0';
  
  puts(argv[1]);
  
  return 0;
}


int look_for_last_dot(const char * str) {
  if (str == NULL) return -2;
  
  int p;
  p = -1;
  for (int i = 0; str[i] != '\0'; i++) {
    if (i == INT_MAX) return -3;
    if (str[i] == '.') p = i;
  }
  return p;
}



