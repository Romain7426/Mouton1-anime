#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 
#include "lib.ci" 
int main(const int argc, const char *argv[]) { 
  for (int i = 0; i < argc; i++) { 
    const int len = cstrlen(argv[i]); 
    write_long_long_int_old(STDOUT_FILENO, len); 
    write_eol(STDOUT_FILENO); 
  }; 
  return 0; 
}; 
