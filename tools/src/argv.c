#include <unistd.h>

static const char eol[] = "\n"; 
 
int main(const int argc, const char * argv[]) { 

  for (int i = 1; i < argc; i++) { 
    const char * p = argv[i]; 
    while (*p != '\0') p++; 
    const int len = p - argv[i]; 
    write(1, argv[i], len); 
    write(1, eol, 1); 
  }; 
  return 0; 
}; 


