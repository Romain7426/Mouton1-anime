#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

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
  
  llfixed_stack__check_and_assert(); 
  goto label__body; 
  
  
  label__error__exit: { 
    return 1; 
  }; 
  
  label__exit: { 
    return 0; 
  }; 
  
  label__error__arg_missing: { 
    write_string2_ln(STDERR_FILENO, argv0, ": I expect one argument; got none"); 
    return 7; 
  }; 
  
  label__error__too_many_args: { 
    write_string2(STDERR_FILENO, argv0, ": Too many arguments - I expect one (1) argument; got: "); 
    write_long_long_int(STDERR_FILENO, argc - 1); 
    write_eol(STDERR_FILENO); 
    return 5;  
  }; 
  
  label__error__number_expected: { 
    write_string4_ln(STDERR_FILENO, argv0, ": I expect one number - I got something else: '", argv[1], "'"); 
    return 6;  
  }; 
  
  label__body: { 
    if (2 > argc) goto label__error__arg_missing; 
    if (2 < argc) goto label__error__too_many_args; 
    
    const char * argv1 = argv[1]; 
    int8_t roundup_huh; 
    const int16_t prefix_bytesize = llfixed__token_get_number_prefix_bytesize(argv1, &roundup_huh); 
    if (0 == prefix_bytesize) goto label__error__number_expected; 
    const long long int llfixed_argv_value = llfixed__convert_buffer(argv1, prefix_bytesize); 
    const long long int llfixed_result_value = llfixed__exp10int(llfixed_argv_value); 
    llfixed__print(STDOUT_FILENO, llfixed_result_value); 
    write_eol(STDOUT_FILENO); 
    goto label__exit; 
  }; 
  
  
}; 


