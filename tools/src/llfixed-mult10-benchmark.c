#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 
#include <stdlib.h> // man 3 arc4random 
#include <time.h> // man 3 clock 

#include "lib.ci"
#include "lib__llfixed.ci"

static const char * argv0; 




int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 4; 
  }; 
  argv0 = argv[0]; 
  goto label__body; 
  
  
  label__error__exit: { 
    return 1; 
  }; 
  
  label__exit: { 
    return 0; 
  }; 
  
  label__body: { 
    long long int start_value; 
    arc4random_buf(&start_value, sizeof(start_value)); 
    
    //enum { TRIALS = 2000 }; 
    enum { TRIALS = 2000000000 }; 
    //enum { TRIALS = 1000000000 }; 
    //enum { TRIALS = 100000000 }; 
    const clock_t u1 = clock(); 
    { 
      long long int t = start_value; 
      for (int i = 0; i < TRIALS; i++) { 
	//t *= 2; 
	t *= 10; 
      }; 
    }; 
    const clock_t u2 = clock(); 
    const long long int u0 = (u2 - u1) / CLOCKS_PER_SEC; 
    
    const clock_t v1 = clock(); 
    { 
      long long int t = start_value; 
      for (int i = 0; i < TRIALS; i++) { 
	//t <<= 1; 
	t = (t << 3) + (t << 1); 
      }; 
    }; 
    const clock_t v2 = clock(); 
    const long long int v0 = (v2 - v1) / CLOCKS_PER_SEC; 
    
    
    write_string(STDOUT_FILENO, "Standard function time: "); 
    //write_long_long_int(STDOUT_FILENO, u0); 
    //write_eol(STDOUT_FILENO); 
    write_long_long_int(STDOUT_FILENO, u2 - u1); 
    write_eol(STDOUT_FILENO); 

    write_string(STDOUT_FILENO, "Sophisticated function time: "); 
    //write_long_long_int(STDOUT_FILENO, v0); 
    //write_eol(STDOUT_FILENO); 
    write_long_long_int(STDOUT_FILENO, v2 - v1); 
    write_eol(STDOUT_FILENO); 
    goto label__exit; 
  }; 
  
  
}; 


