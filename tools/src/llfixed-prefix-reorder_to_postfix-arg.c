#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include "lib.ci"

static const char * argv0; 


int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 4; 
  }; 
  argv0 = argv[0]; 
  assert(false); 
  // This algorithm does not work: << - 1 2 >> --> << 2 1 - >> 
  for (int arg_i = 1; arg_i < argc; arg_i++) { 
    const char * argv_i = argv[argc - arg_i]; 
    write_string_ln(STDOUT_FILENO, argv_i); 
  }; 
  return 0; 
}; 


