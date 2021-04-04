#include <stdio.h>
#include <stdlib.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;

int main(const int argc, const char * argv[]) { 
  if (1 == argc) { 
    return 0; 
  }; 
  
  if (2 == argc) { 
    const int top = atoi(argv[1]); 
    for (int i = 1; i <= top; i++) { 
      printf("%d ", i); 
    }; 
    printf("\n"); 
    return 0; 
  };
  
  if (3 == argc) { 
    const int bottom = atoi(argv[1]); 
    const int top    = atoi(argv[2]); 
    for (int i = bottom; i <= top; i++) { 
      printf("%d ", i); 
    }; 
    printf("\n"); 
    return 0; 
  };
  
  if (4 == argc) { 
    const int bottom = atoi(argv[1]); 
    const int top    = atoi(argv[2]); 
    const int step   = atoi(argv[3]); 
    if (0 == step) { return -2; }; 
    if (0 <  step) { 
      for (int i = bottom; i <= top; i += step) { 
	printf("%d ", i); 
      }; 
      printf("\n"); 
      return 0; 
    }; 
    if (0 >  step) { 
      for (int i = bottom; i >= top; i += step) { 
	printf("%d ", i); 
      }; 
      printf("\n"); 
      return 0; 
    }; 
  }; 
  
  
  return -1;
}; 

