#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include "lib.ci"
#include "lib__llfixed.ci"

static const char * argv0 = NULL; 

int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 4; 
  }; 
  argv0 = argv[0]; 
  goto label__body; 

  label__exit: { 
    return 0; 
  }; 
  
  label__error__too_many_args: { 
      write_string(STDERR_FILENO, argv0); 
      write_string(STDERR_FILENO, ": Too many args - ARGC is greater than 5: "); 
      write_long_long_int(STDERR_FILENO, argc); 
      write_eol(STDERR_FILENO); 
      return 5; 
  }; 
  
  label__body: { 
    if (5 <= argc) goto label__error__too_many_args; 
    
    if (1 == argc) { 
      write(STDOUT_FILENO, "1\n", 2); 
      goto label__exit; 
    }; 
    
    long long int dividend0; 
    { 
      const char * argv_i = argv[1]; 
      int16_t prefix_bytesize; 
      const int number_huh = llfixed__token_prefix_is_number_huh(argv_i, &prefix_bytesize); 
      const long long int llfixed_argv_value = (!number_huh) ? 0 : llfixed__convert_buffer(argv_i, prefix_bytesize); 
      dividend0 = llfixed_argv_value; 
    }; 
    
    if (2 == argc) { 
      llfixed__print(STDOUT_FILENO, dividend0); 
      write_eol(STDOUT_FILENO); 
      goto label__exit; 
    }; 
    
    long long int divisor0; 
    { 
      const char * argv_i = argv[2]; 
      int16_t prefix_bytesize; 
      const int number_huh = llfixed__token_prefix_is_number_huh(argv_i, &prefix_bytesize); 
      const long long int llfixed_argv_value = (!number_huh) ? 0 : llfixed__convert_buffer(argv_i, prefix_bytesize); 
      divisor0 = llfixed_argv_value; 
    }; 
    
    long long int expected_number_of_digits_to_be_printed = LLFIXED_BASE10_DIGITS__DEC; 
    if (4 == argc) { 
      const char * argv_i = argv[3]; 
      int8_t roundup_huh; 
      const int16_t prefix_bytesize = llint__token_get_number_prefix_bytesize(argv_i, &roundup_huh); 
      const long long int llint_argv_value = (roundup_huh?1:0) + convert_buffer_to_long_long_int(argv_i, prefix_bytesize); 
      expected_number_of_digits_to_be_printed = llint_argv_value; 
    }; 
    
    long long int quotient; 
    long long int remainder; 
    
    quotient  = dividend0 / divisor0; 
    remainder = dividend0 % divisor0; 
    if (0 >= expected_number_of_digits_to_be_printed) { 
      if ((remainder << 1) >= divisor0) quotient++; 
      write_long_long_int_ln(STDOUT_FILENO, quotient); 
      //llfixed__print(STDOUT_FILENO, quotient); 
      //write_eol(STDOUT_FILENO); 
      goto label__exit; 
    }; 
    
    write_long_long_int(STDOUT_FILENO, quotient); 
    write_string(STDOUT_FILENO, "."); 
    
    long long int dividend; 
    for (int i = 1; i < expected_number_of_digits_to_be_printed; i++) { 
      dividend  = remainder * 10; 
      quotient  = dividend / divisor0; 
      remainder = dividend % divisor0; 
      write_long_long_int(STDOUT_FILENO, quotient); 
    }; 
    
    dividend  = remainder * 10; 
    quotient  = dividend / divisor0; 
    remainder = dividend % divisor0; 
    
    long long int last_quotient = quotient; 
    dividend  = remainder * 10; 
    quotient  = dividend / divisor0; 
    remainder = dividend % divisor0; 
    if ((remainder << 1) >= divisor0) last_quotient++; 
    write_long_long_int(STDOUT_FILENO, last_quotient); 
    
    write_eol(STDOUT_FILENO); 
    
    goto label__exit;     
  }; 
  
}; 


