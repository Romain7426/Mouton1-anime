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
  
  long long int llfixed_sum_value = 0; 
  
  for (int i = 1; i < argc; i++) { 
#if 0       
    int int_bytesize; 
    const int number_type = char_array0__number_type(argv[i], &int_bytesize); 
    switch (number_type) {
    default: assert(false); 
    case 1: case 2: case 5: continue; 
    case 3: case 4: case 6: case 7: break; 
    }; 
    const long long int llfixed_argv_value = convert_buffer_to_llfixed(argv[i], int_bytesize); 
#else 
    int16_t prefix_bytesize; 
    const int number_huh = llfixed__token_prefix_is_number_huh(argv[i], &prefix_bytesize); 
    if (!number_huh) continue; 
#if 0 
    {
      write_string(STDERR_FILENO, "prefix_bytesize = "); 
      write_long_long_int(STDERR_FILENO, prefix_bytesize); 
      write_eol(STDERR_FILENO); 
    }; 
#endif 
    const long long int llfixed_argv_value = llfixed__convert_buffer(argv[i], prefix_bytesize); 
#endif 
    llfixed_sum_value += llfixed_argv_value; 
    continue; 
  }; 

  llfixed__print(STDOUT_FILENO, llfixed_sum_value); 
  write_eol(STDOUT_FILENO); 
  //write_long_long_int(STDOUT_FILENO, llfixed_sum_value); 
  //write_eol(STDOUT_FILENO); 
  //write_long_long_int_old(STDOUT_FILENO, llfixed_sum_value); 
  //write_eol(STDOUT_FILENO); 
  return 0; 
}; 


