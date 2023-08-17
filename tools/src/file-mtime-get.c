#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 
#include <sys/stat.h>

#include "lib.ci"
//#include "lib__llfixed.ci"

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
    if (2 != argc) goto label__exit; 

#if 0
    man 2 stat
      int stat(const char *path, struct stat *sb);
    struct timespec st_mtim;    /* time of last data modification */
    st_mtime macros are provided that expand to the tv_secs member of their respective struct timespec member.
      
      man 2 clock_gettime
      The now and res arguments are timespec structures as defined in <sys/time.h>:
      struct timespec {
	time_t  tv_sec;         /* seconds */
	long    tv_nsec;        /* and nanoseconds */
      };
    
    What is a time_t?
      /usr/include/sys/_types.h
      typedef __int64_t       __time_t;       /* epoch time */
#endif 

    struct stat sb; 
    if (0 != stat(argv[1], &sb)) goto label__exit; 
    
    const time_t mtime_sec = sb.st_mtim.tv_sec; 
    
    write_long_long_int(STDOUT_FILENO, mtime_sec); 
    write_eol(STDOUT_FILENO); 
    
    goto label__exit; 
  }; 
  
}; 


