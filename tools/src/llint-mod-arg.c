#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include "lib.ci"

static const char * argv0 = NULL; 

int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 4; 
  }; 
  argv0 = argv[0]; 
  long long int llint_outcome_value = 1; 
  goto label__body; 

  label__exit: { 
    write_long_long_int(STDOUT_FILENO, llint_outcome_value); 
    write_eol(STDOUT_FILENO); 
    return 0; 
  }; 
  
  label__body: { 
    if (1 == argc) goto label__exit; 
    
    { 
      int8_t roundup_huh; 
      const int16_t prefix_bytesize = llint__token_get_number_prefix_bytesize(argv[1], &roundup_huh); 
      const long long int llint_argv_value = (roundup_huh?1:0) + convert_buffer_to_long_long_int(argv[1], prefix_bytesize); 
      llint_outcome_value = llint_argv_value; 
    }; 
    
    if (2 == argc) goto label__exit; 

  for (int i = 2; i < argc; i++) { 
#if 0 
    if (!char_array0__number_huh(argv[i])) continue; 
    const long long int argv_llint_value = convert_buffer_to_long_long_int(argv[i], cstrlen(argv[i])); 
    llint_outcome_value += argv_llint_value; 
#elif 0 
    long long int argv_llint_value; 
    int int_bytesize; 
    const int number_type = char_array0__number_type(argv[i], &int_bytesize); 
    switch (number_type) {
    default: assert(false); 
    case 1: case 2: case 5: continue; 
    case 3: case 4: case 6: argv_llint_value = convert_buffer_to_long_long_int(argv[i], int_bytesize); break; 
    case 7: argv_llint_value = 1 + convert_buffer_to_long_long_int(argv[i], int_bytesize); break; 
    }; 
    llint_outcome_value += argv_llint_value; 
#else 
    int8_t roundup_huh; 
    const int16_t prefix_bytesize = llint__token_get_number_prefix_bytesize(argv[i], &roundup_huh); 
    const long long int llint_argv_value = (roundup_huh?1:0) + convert_buffer_to_long_long_int(argv[i], prefix_bytesize); 
    llint_outcome_value %= llint_argv_value; 
#endif 
    continue; 
  }; 
  
  goto label__exit; 
  }; 
}; 


