#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include "lib.ci"
#include "lib__llfixed.ci"

static const char * argv0; 



static int llfixed_stack__operation_do(const int operation_symbol) { 

  switch (operation_symbol) { 
  default: assert(false); 
  case OPERATION_SYMBOL__ZERO: assert(LLFIXED_STACK_UNITSIZE > llfixed_stack_nb); llfixed_stack[llfixed_stack_nb] = 0; llfixed_stack_nb++; break; 
  case OPERATION_SYMBOL__NAN: assert(LLFIXED_STACK_UNITSIZE > llfixed_stack_nb); llfixed_stack[llfixed_stack_nb] = LLFIXED_NAN; llfixed_stack_nb++; break; 
  case OPERATION_SYMBOL__INC: assert(0 < llfixed_stack_nb); llfixed_stack[llfixed_stack_nb - 1] += LLFIXED_UNIT; break; 
  case OPERATION_SYMBOL__DEC: assert(0 < llfixed_stack_nb); llfixed_stack[llfixed_stack_nb - 1] -= LLFIXED_UNIT; break; 
  case OPERATION_SYMBOL__ADD: { assert(2 <= llfixed_stack_nb); const long long int a = llfixed_stack[llfixed_stack_nb - 1]; const long long int b = llfixed_stack[llfixed_stack_nb - 2]; llfixed_stack[llfixed_stack_nb - 2] = a + b; llfixed_stack_nb--; break; }; 
  case OPERATION_SYMBOL__SUB: { assert(2 <= llfixed_stack_nb); const long long int a = llfixed_stack[llfixed_stack_nb - 1]; const long long int b = llfixed_stack[llfixed_stack_nb - 2]; llfixed_stack[llfixed_stack_nb - 2] = a - b; llfixed_stack_nb--; break; }; 
  case OPERATION_SYMBOL__MULT: { assert(2 <= llfixed_stack_nb); const long long int a = llfixed_stack[llfixed_stack_nb - 1]; const long long int b = llfixed_stack[llfixed_stack_nb - 2]; llfixed_stack[llfixed_stack_nb - 2] = llfixed__mult(a, b); llfixed_stack_nb--; break; }; 
  case OPERATION_SYMBOL__DIV: { assert(2 <= llfixed_stack_nb); const long long int a = llfixed_stack[llfixed_stack_nb - 1]; const long long int b = llfixed_stack[llfixed_stack_nb - 2]; llfixed_stack[llfixed_stack_nb - 2] = llfixed__div(a, b); llfixed_stack_nb--; break; }; 
/*
  OPERATION_SYMBOL__MOD, 
  OPERATION_SYMBOL__QUOTIENT, 
  OPERATION_SYMBOL__LOG10, 
  OPERATION_SYMBOL__LOG2, 
  OPERATION_SYMBOL__SHIFT10_RIGHT, 
  OPERATION_SYMBOL__SHIFT2_RIGHT, 
  OPERATION_SYMBOL__SHIFT10_LEFT, 
  OPERATION_SYMBOL__SHIFT2_LEFT, 
*/
  }; 
  
  return 0; 
}; 

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
    llfixed_stack_nb = 0; 
    
    for (int arg_i = 1; arg_i < argc; arg_i++) { 
      const char * argv_i = argv[argc - arg_i]; 
      int8_t roundup_huh; 
      const int16_t prefix_bytesize = llfixed__token_get_number_prefix_bytesize(argv_i, &roundup_huh); 
      if (0 < prefix_bytesize) { 
	const long long int llfixed_argv_value = llfixed__convert_buffer(argv_i, prefix_bytesize); 
	if (LLFIXED_STACK_UNITSIZE <= llfixed_stack_nb) goto label__error__stack_overflow; 
	llfixed_stack[llfixed_stack_nb] = llfixed_argv_value; 
	llfixed_stack_nb++; 
	continue; 
      }; 
      const int8_t operation_symbol = operation_symbol__token_match(argv_i); 
      if ((OPERATION_SYMBOL__NULL >= operation_symbol) || (OPERATION_SYMBOL__COUNT <= operation_symbol)) { 
 	write_string(STDERR_FILENO, argv0); 
 	write_string(STDERR_FILENO, ": something got wrong while trying to match token '"); 
 	write_string(STDERR_FILENO, argv_i); 
 	write_string(STDERR_FILENO, "' (argv[");
	write_long_long_int(STDERR_FILENO, arg_i); 
 	write_string(STDERR_FILENO, "]) - got operation_symbol: ");
	write_long_long_int(STDERR_FILENO, operation_symbol); 
	write_eol(STDERR_FILENO); 
	goto label__error__exit; 
      }; 
      if (OPERATION_SYMBOL__ERROR__EMPTY_SYMBOL == operation_symbol) continue; 
      if (OPERATION_SYMBOL__ERROR__NOT_AN_OPERATION_SYMBOL == operation_symbol) { 
 	write_string(STDERR_FILENO, argv0); 
 	write_string(STDERR_FILENO, ": operation symbol not recognized: '"); 
 	write_string(STDERR_FILENO, argv_i); 
 	write_string(STDERR_FILENO, "' (argv[");
	write_long_long_int(STDERR_FILENO, arg_i); 
 	write_string(STDERR_FILENO, "])");
	write_eol(STDERR_FILENO); 
	goto label__error__exit; 
      }; 
      const int operation_status = llfixed_stack__operation_do(operation_symbol); 
      if (0 != operation_status) { 
 	write_string(STDERR_FILENO, argv0); 
 	write_string(STDERR_FILENO, ": operation '"); 
 	write_string(STDERR_FILENO, argv_i); 
 	write_string(STDERR_FILENO, "' (argv[");
	write_long_long_int(STDERR_FILENO, arg_i); 
 	write_string(STDERR_FILENO, "]) failed - returned status: ");
	write_long_long_int(STDERR_FILENO, operation_status); 
	write_eol(STDERR_FILENO); 
	goto label__error__exit; 
      }; 
      continue; 
    }; 

    for (int16_t i = 0; i < llfixed_stack_nb; i++) { 
      const int16_t llfixed_stack_i = llfixed_stack_nb - i - 1; 
      llfixed__print(STDOUT_FILENO, llfixed_stack[llfixed_stack_i]); 
      write_eol(STDOUT_FILENO); 
    }; 

    goto label__exit; 
  }; 
  
}; 


