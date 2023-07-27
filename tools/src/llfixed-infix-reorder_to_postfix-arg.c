#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include "lib.ci"
#include "lib__llfixed.ci"

static const char * argv0; 


enum { OPERATION_SYMBOL_STACK_UNITSIZE = LLFIXED_STACK_UNITSIZE }; 
static       int8_t operation_symbol_stack     [OPERATION_SYMBOL_STACK_UNITSIZE] = {}; 
static const char * operation_symbol_stack_argv[OPERATION_SYMBOL_STACK_UNITSIZE] = {}; 
static       int8_t operation_symbol_stack_nb = 0; 

static void operation_symbol_stack__check_and_assert(void) { 
  operation_symbol_stack_nb = OPERATION_SYMBOL_STACK_UNITSIZE; 
  assert(operation_symbol_stack_nb == OPERATION_SYMBOL_STACK_UNITSIZE); 
}; 

enum { OUTPUT_STACK_UNITSIZE = LLFIXED_STACK_UNITSIZE }; 
static const char * output_stack[OUTPUT_STACK_UNITSIZE] = {}; 
static int8_t output_stack_nb = 0; 

static void output_stack__check_and_assert(void) { 
  output_stack_nb = OUTPUT_STACK_UNITSIZE; 
  assert(output_stack_nb == OUTPUT_STACK_UNITSIZE); 
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
  operation_symbol_stack__check_and_assert(); 
  output_stack__check_and_assert(); 
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
    output_stack_nb = 0; 
    operation_symbol_stack_nb = 0; 
    
    for (int arg_i = 1; arg_i < argc; arg_i++) { 
      const char * argv_i = argv[arg_i]; 
      const int16_t prefix_bytesize = llfixed__token_get_number_prefix_bytesize(argv_i, NULL); 
      if (0 < prefix_bytesize) { 
	if (OUTPUT_STACK_UNITSIZE <= output_stack_nb) goto label__error__stack_overflow; 
	output_stack[output_stack_nb] = argv_i; 
	output_stack_nb++; 
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
      if (0 == operation_symbol_stack_nb) { 
	if (OPERATION_SYMBOL_STACK_UNITSIZE <= operation_symbol_stack_nb) goto label__error__stack_overflow; 
	operation_symbol_stack     [operation_symbol_stack_nb] = operation_symbol; 
	operation_symbol_stack_argv[operation_symbol_stack_nb] = argv_i; 
	operation_symbol_stack_nb++; 
	continue; 
      }; 
      const int8_t top = operation_symbol_stack[operation_symbol_stack_nb - 1]; 
      if (top < operation_symbol) { 
	if (OPERATION_SYMBOL_STACK_UNITSIZE <= operation_symbol_stack_nb) goto label__error__stack_overflow; 
	operation_symbol_stack     [operation_symbol_stack_nb] = operation_symbol; 
	operation_symbol_stack_argv[operation_symbol_stack_nb] = argv_i; 
	operation_symbol_stack_nb++; 
	continue; 
      }; 
      if (top >= operation_symbol) { 
	operation_symbol_stack_nb--; 
	if (OUTPUT_STACK_UNITSIZE <= output_stack_nb) goto label__error__stack_overflow; 
	output_stack[output_stack_nb] = operation_symbol_stack_argv[operation_symbol_stack_nb]; 
	output_stack_nb++; 
	operation_symbol_stack     [operation_symbol_stack_nb] = operation_symbol; 
	operation_symbol_stack_argv[operation_symbol_stack_nb] = argv_i; 
	operation_symbol_stack_nb++; 
	continue; 
      }; 
      /* NOT REACHED */
    }; 

#if 0 
    write_string(STDOUT_FILENO, "operation_symbol_stack_nb = "); 
    write_long_long_int(STDOUT_FILENO, operation_symbol_stack_nb); 
    write_eol(STDOUT_FILENO); 
#endif
#if 0 
    write_string(STDOUT_FILENO, "output_stack_nb = "); 
    write_long_long_int(STDOUT_FILENO, output_stack_nb); 
    write_eol(STDOUT_FILENO); 
#endif 

    for (; 0 < operation_symbol_stack_nb;) { 
      operation_symbol_stack_nb--; 
      if (OUTPUT_STACK_UNITSIZE <= output_stack_nb) goto label__error__stack_overflow; 
      output_stack[output_stack_nb] = operation_symbol_stack_argv[operation_symbol_stack_nb]; 
      output_stack_nb++; 
    }; 
    
#if 0 
    write_string(STDOUT_FILENO, "output_stack_nb = "); 
    write_long_long_int(STDOUT_FILENO, output_stack_nb); 
    write_eol(STDOUT_FILENO); 
#endif 

    for (int16_t i = 0; i < output_stack_nb; i++) { 
      write_string_ln(STDOUT_FILENO, output_stack[i]); 
    }; 

    goto label__exit; 
  }; 
  
}; 


