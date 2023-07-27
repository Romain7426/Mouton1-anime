#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include <errno.h> 

// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_wait.h.html
#include <sys/wait.h> 

#include "lib.ci"

int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    _exit(4); 
    return 4; 
  }; 
  
  write_long_long_int(STDOUT_FILENO, argc - 1); 
  write_eol(STDOUT_FILENO); 
  _exit(0); 
  return 0; 
}; 


