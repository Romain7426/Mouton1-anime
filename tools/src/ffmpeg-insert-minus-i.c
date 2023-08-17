#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include "lib.ci"
#include "lib__llfixed.ci"

static const char * argv0; 




int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 0; 
  }; 
  argv0 = argv[0]; 
  
  //check_and_assert(); 
  goto label__body; 
  
  
  label__error__stack_overflow: { 
    assert(false); 
  }; 
  
  label__error__exit: { 
    return 1; 
  }; 
  
  label__exit: { 
    return 0; 
  }; 
  
  label__body: { 
    for (int i = 1; i < argc; i++) { 
      write_string(STDOUT_FILENO, " -i "); 
      write_string(STDOUT_FILENO, argv[i]); 
    }; 
    write_eol(STDOUT_FILENO); 
    
    goto label__exit; 
  }; 
  
}; 


