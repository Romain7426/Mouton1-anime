#include <stdio.h>
#include <string.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;



int main(int argc, char *argv[]) {
  bool b;
  int at_index;

  {
    int i;
    
    for (i = 1; i < argc; i++)
      if ('@' == argv[i][0] && '\0' == argv[i][1])
        break;
    
    if (i == argc) {
      for (int i = 1; i < argc; i++)
        printf("%s ", argv[i]);
      
      printf("\n");
      
      return 0;
    }
  
    at_index = i;
  }


  int start = 1;

  for (int i = 1; i < at_index; i++) {
    for (int j = at_index+1; j < argc; j++) {
      b = (0 == strcmp(argv[i],argv[j]));
      if (b) {
        argv[i] = argv[start];
        start++;
        break;
      }
    }
  }

  for (int i = start; i < at_index; i++)
    printf("%s ", argv[i]);

  printf("\n");

  return 0;
}

