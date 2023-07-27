#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include <errno.h> 

// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_wait.h.html
#include <sys/wait.h> 

// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/setjmp.h.html
#include <setjmp.h>

#include "lib.ci" 

static const char * argv0 = NULL; 

enum { EXCEPTION_MESSAGE_STRING_BUFFER_BYTESIZE = 32767 }; 
static char       exception_message_string_buffer[EXCEPTION_MESSAGE_STRING_BUFFER_BYTESIZE] = { }; 
static int16_t    exception_message_string_nb = 0; 
static int        exception_code = 0; 
static sigjmp_buf exception_data; 

enum { 
  EXCEPTION_CODE__NONE = 0, 
  EXCEPTION_CODE__READ_BUFFER_TOO_SMALL, 
  EXCEPTION_CODE__NEWLINE_LOOKUP_ISSUE, 
  EXCEPTION_CODE__STDIN_LINE_DATA_BUFFER_TOO_SMALL, 
  EXCEPTION_CODE__READING_ERROR, 
  EXCEPTION_CODE__FORK_FAILED, 
  EXCEPTION_CODE__MAPPED_ARGV_ARRAY_TOO_SMALL, 
  EXCEPTION_CODE__COUNT 
}; 

static void exception_raise(const int exception_code_given) { 
  exception_code = exception_code_given; 
  siglongjmp(exception_data, 1); 
  /* NOT REACHED */
}; 

static void exception_message_raz(void) { 
  exception_message_string_nb = 0; 
}; 

static void exception_message_push_char_array(const char * char_array, const int char_array_bytesize) { 
  if (0 >= char_array_bytesize) return; 
  const int16_t available_bytesize = EXCEPTION_MESSAGE_STRING_BUFFER_BYTESIZE - exception_message_string_nb; 
  const int will_copy_bytesize = MIN(char_array_bytesize, available_bytesize); 
  bytecopy(char_array, exception_message_string_buffer + exception_message_string_nb, will_copy_bytesize); 
}; 

static void exception_message_push_string(const char * msg) { 
  if (NULL == msg) return; 
  const int msg_len = cstrlen(msg); 
  if (0 >= msg_len) return; 
  exception_message_push_char_array(msg, msg_len); 
}; 

static void exception_message_push_string_old(const char * msg) { 
  for (;;) { 
    if (0 == exception_message_string_nb) {
      stringcopy(msg, exception_message_string_buffer, EXCEPTION_MESSAGE_STRING_BUFFER_BYTESIZE); 
      break; 
    }; 
    
    if (EXCEPTION_MESSAGE_STRING_BUFFER_BYTESIZE == exception_message_string_nb) break; 

    const char last_char = exception_message_string_buffer[exception_message_string_nb - 1]; 
    if ('\0' == last_char) exception_message_string_nb--; 
    stringcopy(msg, exception_message_string_buffer + exception_message_string_nb, EXCEPTION_MESSAGE_STRING_BUFFER_BYTESIZE - exception_message_string_nb); 
    
    break; 
  }; 

  //const char last_char = exception_message_string_buffer[exception_message_string_nb - 1]; 
  //assert('\0' == last_char); 
}; 

static void exception_message_push_llint(const long long int n) { 
  char buffer[WRITE_LONG_LONG_INT_BUFFER__BYTESIZE_MIN]; 
  const int written_bytesize = write_long_long_int_into_buffer(buffer, sizeof(buffer),  n); 
  if (0 >= written_bytesize) return; 
  // removing last '\0' 
  const int len = written_bytesize - 1; 
  const char last_char = buffer[len]; 
  exception_message_push_char_array(buffer, last_char == '\0' ? len : written_bytesize); 
}; 


enum { MAPPED_ARGV_DATA_BUFFER_BYTESIZE = 32767 }; 
static char mapped_argv_data_buffer[MAPPED_ARGV_DATA_BUFFER_BYTESIZE] = {}; 
static int16_t mapped_argv_data_buffer_nb = 0; 

enum { MAPPED_ARGV_ARRAY_BUFFER_BYTESIZE = 32767 }; 
enum { MAPPED_ARGV_ARRAY_UNIT_BYTESIZE = sizeof(char *) }; 
enum { MAPPED_ARGV_ARRAY_UNITSIZE = MAPPED_ARGV_ARRAY_BUFFER_BYTESIZE / MAPPED_ARGV_ARRAY_UNIT_BYTESIZE }; 
static char mapped_argv_array_buffer[MAPPED_ARGV_ARRAY_BUFFER_BYTESIZE] = {}; 
static char * * mapped_argv_array = (char * *) mapped_argv_array_buffer; 
static int16_t mapped_argv_array_nb = 0; 

static void mapped_argv__please_fill(const int argc, const char * argv[]) { 
  // DATA_BUFFER 
  const int mapped_argc = argc - 1; 
  const char * * mapped_argv__const = argv + 1; 
  int16_t mapped_argv_data_bytesize[mapped_argc]; 
  for (int i = 0; i < mapped_argc; i++) { 
      mapped_argv_data_bytesize[i] = 1 + cstrlen(mapped_argv__const[i]); 
  }; 
  int16_t mapped_argv_data_bytesize_sum = 0; 
  for (int i = 0; i < mapped_argc; i++) { 
    mapped_argv_data_bytesize_sum += mapped_argv_data_bytesize[i]; 
  }; 
  assert(mapped_argv_data_bytesize_sum < MAPPED_ARGV_DATA_BUFFER_BYTESIZE); 
  { 
    char * p = mapped_argv_data_buffer; for (int i = 0 ; i < mapped_argc; i++) { 
      bytecopy(mapped_argv__const[i], p, mapped_argv_data_bytesize[i]); 
      p += mapped_argv_data_bytesize[i]; 
    }; 
    assert(mapped_argv_data_bytesize_sum == (p - mapped_argv_data_buffer)); 
  }; 
  mapped_argv_data_buffer_nb = mapped_argv_data_bytesize_sum; 
  
  // ARRAY 
  { 
    char * p = mapped_argv_data_buffer; for (int i = 0 ; i < mapped_argc; i++) { 
      mapped_argv_array[i] = p; 
      p += mapped_argv_data_bytesize[i]; 
    }; 
  }; 
  mapped_argv_array_nb = mapped_argc; 
}; 



enum { STDIN_LINE_DATA_BUFFER_BYTESIZE = 32767 }; 
static char stdin_line_data_buffer[STDIN_LINE_DATA_BUFFER_BYTESIZE] = {}; 
static int16_t stdin_line_data_buffer_nb = 0; 

enum { STDIN_LINE_ARRAY_BUFFER_BYTESIZE = 32767 }; 
enum { STDIN_LINE_ARRAY_UNIT_BYTESIZE = sizeof(char *) }; 
enum { STDIN_LINE_ARRAY_UNITSIZE = STDIN_LINE_ARRAY_BUFFER_BYTESIZE / STDIN_LINE_ARRAY_UNIT_BYTESIZE }; 
static char stdin_line_array_buffer[STDIN_LINE_ARRAY_BUFFER_BYTESIZE] = {}; 
static char * * stdin_line_array = (char * *) stdin_line_array_buffer; 
static int16_t stdin_line_array_nb = 0; 

static void stdin_line__push_char_array(const char * read_buffer, const int16_t read_buffer_nb) { 
  assert(0 < read_buffer_nb); 
  const int16_t available_bytesize = STDIN_LINE_DATA_BUFFER_BYTESIZE - stdin_line_data_buffer_nb; 
  if (read_buffer_nb >= available_bytesize) { 
    exception_message_raz(); 
    exception_message_push_string(argv0); 
    exception_message_push_string(": STDIN_LINE_DATA_BUFFER is too small: "); 
    exception_message_push_llint(STDIN_LINE_DATA_BUFFER_BYTESIZE); 
    exception_message_push_string("\n"); 
    exception_raise(EXCEPTION_CODE__STDIN_LINE_DATA_BUFFER_TOO_SMALL); 
    /* NOT REACHED */
  }; 
  
  char * stdin_line = stdin_line_data_buffer + stdin_line_data_buffer_nb; 
  bytecopy(read_buffer, stdin_line, read_buffer_nb); 
  stdin_line_array[stdin_line_array_nb] = stdin_line; 
  stdin_line_array_nb++; 
  stdin_line_data_buffer_nb += read_buffer_nb; 
  stdin_line_data_buffer[stdin_line_data_buffer_nb] = '\0'; 
  stdin_line_data_buffer_nb++; 
}; 


static void stdin_line__please_read_stdin_then_fill(void) { 
  // A dedicated buffer for reading is needed as the lines read on stdin does not have a null-ending character, which one must be added.  
  // Furthermore, while reading, more than one line can be read. 
  enum { READ_BUFFER_BYTESIZE = (1 << 14) }; 
  ASSERT_COMPILE(READ_BUFFER_BYTESIZE > 0); 
  static char read_buffer[READ_BUFFER_BYTESIZE]; 
  int16_t read_buffer_start_pos = 0; 
  int16_t read_buffer_end_pos = -1; 
  int16_t read_buffer_nb = 0; 
  int stdin_eof_huh = false; 
  
  for (;;) { 
    goto label__for_body; 
    
  label__error__read_buffer_too_small: { 
      assert(0 == read_buffer_start_pos); 
      assert(read_buffer_nb == READ_BUFFER_BYTESIZE); 
      assert(stdin_eof_huh == false); 
      exception_message_raz(); 
      exception_message_push_string(argv0); 
      exception_message_push_string(": READ_BUFFER_BYTESIZE too small: "); 
      exception_message_push_llint(READ_BUFFER_BYTESIZE); 
      exception_message_push_string("\n"); 
      exception_raise(EXCEPTION_CODE__READ_BUFFER_TOO_SMALL); 
      /* NOT REACHED */
    }; 

  label__error__reading_error: { 
      exception_message_raz(); 
      exception_message_push_string(argv0); 
      exception_message_push_string(": Error while reading stdin - ERRNO: "); 
      exception_message_push_llint(errno); 
      exception_message_push_string("\n"); 
      exception_raise(EXCEPTION_CODE__READING_ERROR); 
      /* NOT REACHED */
    }; 
    
  label__for_refill: { 
      const size_t available_bytesize = READ_BUFFER_BYTESIZE - read_buffer_nb; 
      assert(available_bytesize > 0); // Should have been caught beforehand. 
      const ssize_t byteread_count = read(STDIN_FILENO, read_buffer + read_buffer_nb, available_bytesize); 
      if (-1 == byteread_count) /* error */ { goto label__error__reading_error; }; 
      if ( 0  > byteread_count) /* WTF?  */ { goto label__error__reading_error; }; 
      if ( 0 == byteread_count) /* EOF   */ { stdin_eof_huh = true; continue; }; 
      /* ELSE */ read_buffer_nb += byteread_count; continue; 
    }; 
    
  label__for_rotate_then_refill: { 
      assert(0 < read_buffer_start_pos); 
      const int16_t bytesize_to_rotate = read_buffer_nb - read_buffer_start_pos; 
      assert(0 < bytesize_to_rotate); 
      bytecopy(read_buffer + read_buffer_start_pos, read_buffer, bytesize_to_rotate); 
      read_buffer_start_pos =  0; 
      read_buffer_end_pos   = -1; 
      read_buffer_nb        = bytesize_to_rotate; 
      goto label__for_refill; 
    }; 
      
  label__copy_read_buffer_into_line_buffer: { 
      assert(read_buffer_start_pos < read_buffer_nb); 
      // Looking up for next newline char in the read-buffer. 
      const int16_t newline_pos = lookup_newline_char(read_buffer, read_buffer_nb, read_buffer_start_pos); 
      if (-1 > newline_pos) { 
	exception_message_raz(); 
	exception_message_push_string(argv0); 
	exception_message_push_string(": Bad newline_pos: "); 
	exception_message_push_llint(newline_pos); 
	exception_message_push_string("\n"); 
	exception_raise(EXCEPTION_CODE__NEWLINE_LOOKUP_ISSUE); 
	/* NOT REACHED */
      }; 
      
      if (-1 == newline_pos) { 
	if (!stdin_eof_huh) { 
	  if (read_buffer_start_pos > 0) goto label__for_rotate_then_refill; 
	  if (read_buffer_nb < READ_BUFFER_BYTESIZE) goto label__for_refill; 
	  /* ELSE */ goto label__error__read_buffer_too_small; 
	}; 
	assert(stdin_eof_huh); 
      }; 
      
      read_buffer_end_pos = (0 <= newline_pos) ? newline_pos : (read_buffer_nb - 1); 
      
      const int16_t bytesize_to_copy = read_buffer_end_pos - read_buffer_start_pos + 1; 
      stdin_line__push_char_array(read_buffer + read_buffer_start_pos, bytesize_to_copy); 
      
      read_buffer_start_pos = read_buffer_end_pos + 1; 
      continue; 
    }; 

  label__for_body: { 
      if (read_buffer_start_pos >= read_buffer_nb) { 
	if (stdin_eof_huh) break; 
	read_buffer_start_pos =  0; 
	read_buffer_end_pos   = -1; 
	read_buffer_nb        =  0; 
	goto label__for_refill; 
      }; 

      goto label__copy_read_buffer_into_line_buffer; 
    };  
    
  }; // FOR 
  
}; 



#if 0 
static char * * mapped_argv_array = (char * *) mapped_argv_array_buffer; 
static int16_t mapped_argv_array_nb = 0; 

static char * * stdin_line_array = (char * *) stdin_line_array_buffer; 
static int16_t stdin_line_array_nb = 0; 
#endif 

static void mapped_argv_array__fill_with_lines(void) { 
  const int16_t mapped_argv_array_available_nb = MAPPED_ARGV_ARRAY_UNITSIZE - mapped_argv_array_nb; 
  if (mapped_argv_array_available_nb <= stdin_line_array_nb) { 
    exception_message_raz(); 
    exception_message_push_string(argv0); 
    exception_message_push_string(": too many lines and not enough argv: LINE_NB: "); 
    exception_message_push_llint(stdin_line_array_nb); 
    exception_message_push_string(" - AVAILABLE ARGV_NB: "); 
    exception_message_push_llint(mapped_argv_array_available_nb); 
    exception_message_push_string("\n"); 
    exception_raise(EXCEPTION_CODE__MAPPED_ARGV_ARRAY_TOO_SMALL); 
    /* NOT REACHED */
  }; 
  
  { int16_t from_i = 0; int16_t to_i = mapped_argv_array_nb; for (; from_i < stdin_line_array_nb; from_i++, to_i++) { 
      mapped_argv_array[to_i] = stdin_line_array[from_i]; 
  }; }; 
  
  mapped_argv_array_nb += stdin_line_array_nb; 
  
  mapped_argv_array[mapped_argv_array_nb] = NULL; 
  
  mapped_argv_array_nb++; 
}; 




static void pipe_fork_exec(void) { 
  //execvp("echo", ((char *  []){ "echo", "Hello world!", NULL })); 
  // On success, the function execvp does not return as it 
  // substitutes the current process. 
  // Therefore, execvp must be run in a fork. 
  goto label__body; 

  
  label__error__fork_failed: { 
    exception_message_raz(); 
    exception_message_push_string(argv0); 
    exception_message_push_string(": fork failed - ERRNO: "); 
    exception_message_push_llint(errno); 
    exception_message_push_string("\n"); 
    exception_raise(EXCEPTION_CODE__FORK_FAILED); 
    /* NOT REACHED */
  }; 
  

  label__error__execvp_failed: { 
    exception_message_raz(); 
    exception_message_push_string(argv0); 
    exception_message_push_string(": execvp failed - ERRNO: "); 
    exception_message_push_llint(errno); 
    exception_message_push_string("\n"); 
    exception_raise(EXCEPTION_CODE__FORK_FAILED); 
    /* NOT REACHED */
  }; 


  label__error__waitpid_failed: { 
    exception_message_raz(); 
    exception_message_push_string(argv0); 
    exception_message_push_string(": waitpid failed - ERRNO: "); 
    exception_message_push_llint(errno); 
    exception_message_push_string("\n"); 
    exception_raise(EXCEPTION_CODE__FORK_FAILED); 
    /* NOT REACHED */
  }; 


  label__success: { 
    return; 
  }; 
  

  label__body: { 
#if 1 
    //const int execvp_retval = execvp(mapped_prog__const, ((char * []){ mapped_prog__mutable, line_buffer, NULL })); 
    //const int execvp_retval = execvp(mapped_prog__const, ((char * []){ mapped_prog__mutable, NULL })); 
    const int execvp_retval = execvp(mapped_argv_array[0], mapped_argv_array); 
    goto label__error__execvp_failed; // On sucess, execvp should not return. 
    /* NOT REACHED */
#else 
    const pid_t fork_retval__pid = fork(); 
    if (-1 == fork_retval__pid) /* FAILURE */ { goto label__error__fork_failed; }; 
    if (0 == fork_retval__pid) /* NEW CHILD */ { 
      //const int execvp_retval = execvp(mapped_prog__const, ((char * []){ mapped_prog__mutable, line_buffer, NULL })); 
      //const int execvp_retval = execvp(mapped_prog__const, ((char * []){ mapped_prog__mutable, NULL })); 
      const int execvp_retval = execvp(mapped_argv_array[0], mapped_argv_array); 
      goto label__error__execvp_failed; // On sucess, execvp should not return. 
    }; 
    /* ELSE */ /* PARENT PROCESS */ { 
      assert(0 < fork_retval__pid); 
      const pid_t waitpid_retval__pid = waitpid(fork_retval__pid, NULL, 0); 
      if (waitpid_retval__pid == fork_retval__pid) { goto label__success; }; 
      goto label__error__waitpid_failed; 
    }; 
    /* NOT REACHED */
#endif 
  }; 
  /* NOT REACHED */
}; 
  


int main(const int argc, const char * argv[]) { 
  if (argc < 1) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 4; 
  }; 
  argv0 = argv[0]; 
  
  volatile int sigsetjmp_retval = sigsetjmp(exception_data, /*savemask*/false); 
  if (0 == sigsetjmp_retval) goto label__main_body; 
  /* ELSE */ goto label__main_exception; 
  
  
 label__main_exception: { 
    write_string(STDERR_FILENO, exception_message_string_buffer); 
    return exception_code; 
  }; 
  
  
 label__main_body: { 
    if (1 == argc) { 
      write_string(STDERR_FILENO, argv[0]); 
      write_string(STDERR_FILENO, ": Please provide at least one (1) argument (the program to be line-mapped). (Possible other given arguments will be mapped as arguments to the mapped program.)"); 
      write_eol(STDERR_FILENO); 
      return 5; 
    }; 

    mapped_argv__please_fill(argc, argv); 

    // To apply the mapped program, we first need to buffer in memory all the read stdin-lines. 
    stdin_line__please_read_stdin_then_fill(); 
    
    if (false) { 
      for (int i = 0; i < stdin_line_array_nb; i++) { 
	write_string(STDOUT_FILENO, stdin_line_array[i]); 
      }; 
      write_string_ln(STDOUT_FILENO, "Hello!"); 
      return 0; 
    } 
    
    mapped_argv_array__fill_with_lines(); 
    
    if (false) {
      for (int i = 0; i < mapped_argv_array_nb; i++) { 
	write_string(STDOUT_FILENO, mapped_argv_array[i]); 
      }; 
      write_string_ln(STDOUT_FILENO, "Hello!"); 
      return 0; 
    }

    pipe_fork_exec(); 
    
    return 0; 
  }; 
  
}; 


