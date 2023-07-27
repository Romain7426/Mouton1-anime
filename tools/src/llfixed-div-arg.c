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
  
  long long int llfixed_outcome_value = LLFIXED_UNIT; 

  int argv_i = 1; 
  
  for (; argv_i < argc; argv_i++) { 
    int16_t prefix_bytesize; 
    const int number_huh = llfixed__token_prefix_is_number_huh(argv[argv_i], &prefix_bytesize); 
    if (!number_huh) continue; 
    const long long int llfixed_argv_value = llfixed__convert_buffer(argv[argv_i], prefix_bytesize); 
    llfixed_outcome_value = llfixed_argv_value; 
    argv_i++; 
    break; 
  }; 
  
  for (; argv_i < argc; argv_i++) { 
    int16_t prefix_bytesize; 
    const int number_huh = llfixed__token_prefix_is_number_huh(argv[argv_i], &prefix_bytesize); 
    if (!number_huh) continue; 
    const long long int llfixed_argv_value = llfixed__convert_buffer(argv[argv_i], prefix_bytesize); 
    //llfixed_outcome_value /= llfixed_argv_value; 
    llfixed_outcome_value = llfixed__div(llfixed_outcome_value, llfixed_argv_value); 
    continue; 
  }; 
  
  llfixed__print(STDOUT_FILENO, llfixed_outcome_value); 
  write_eol(STDOUT_FILENO); 
  return 0; 
}; 


