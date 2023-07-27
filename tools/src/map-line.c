#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include <errno.h> 

// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_wait.h.html
#include <sys/wait.h> 

#include "lib.ci" 

int main(const int argc, const char * argv[]) { 
  //execvp("echo", ((char *  []){ "echo", "Hello world!", NULL })); 
  // On success, the function execvp does not return as it 
  // substitutes the current process. 
  // Therefore, execvp must be run in a fork. 
  if (argc < 1) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    _exit(4); 
    return 4; 
  }; 
  if (1 == argc) { 
    write_string(STDERR_FILENO, argv[0]); 
    write_string(STDERR_FILENO, ": Please provide at least one (1) argument (the program to be line-mapped)."); 
    write_eol(STDERR_FILENO); 
    _exit(5); 
    return 5; 
  }; 
  if (argc > 2) { 
    write_string(STDERR_FILENO, argv[0]); 
    write_string(STDERR_FILENO, ": only takes one (1) argument (got "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_string(STDERR_FILENO, ")"); 
    write_eol(STDERR_FILENO); 
    _exit(5); 
    return 5; 
  }; 
  const char * mapped_prog__const = argv[1]; 
  const size_t mapped_prog__strlen1 = 1 + cstrlen(mapped_prog__const); 
  char mapped_prog__mutable[mapped_prog__strlen1]; 
  bytecopy(mapped_prog__const, mapped_prog__mutable, mapped_prog__strlen1); 
  
  enum { READ_BUFFER_BYTESIZE = (1 << 14) }; 
  ASSERT_COMPILE(READ_BUFFER_BYTESIZE > 0); 
  static char read_buffer[READ_BUFFER_BYTESIZE]; 
  int16_t read_buffer_start_pos = 0; 
  int16_t read_buffer_end_pos = -1; 
  int16_t read_buffer_nb = 0; 
  int stdin_eof_huh = false; 
  for (;;) { 
    goto label_for_body; 
    
    label_for_refill: { 
      const size_t available_bytesize = READ_BUFFER_BYTESIZE - read_buffer_nb; 
      assert(available_bytesize > 0); // Should have been caught beforehand. 
      const ssize_t byteread_count = read(STDIN_FILENO, read_buffer + read_buffer_nb, available_bytesize); 
      if (-1 == byteread_count) { /* error */; _exit(errno); return 1; }; 
      if ( 0  > byteread_count) { /* WTF?  */; _exit(errno); return 2; }; 
      if ( 0 == byteread_count) /* EOF */ { 
	stdin_eof_huh = true; 
 	if (0 == read_buffer_nb) { _exit(0); return 0; }; 
      }; 
      //read_buffer_start_pos =  0; 
      //read_buffer_end_pos   = -1; 
      read_buffer_nb        += byteread_count; 
      continue; 
    }; 
    
    label_for_rotate_then_refill: { 
      assert(0 < read_buffer_start_pos); 
      //static void bytecopy(const char * byte_src, char * byte_dest, const int bytesize); 
      const int16_t bytesize_to_rotate = read_buffer_nb - read_buffer_start_pos; 
      assert(0 < bytesize_to_rotate); 
      bytecopy(read_buffer + read_buffer_start_pos, read_buffer, bytesize_to_rotate); 
      read_buffer_start_pos =  0; 
      read_buffer_end_pos   = -1; 
      read_buffer_nb        = bytesize_to_rotate; 
      goto label_for_refill; 
    }; 

    label_for_pipe_fork_exec: { // pipe & fork & exec 
      const int16_t line_bytesize = read_buffer_end_pos - read_buffer_start_pos + 1; 
      int fd[2]; 
      pipe(fd); 
      write(fd[0], read_buffer + read_buffer_start_pos, line_bytesize); 
      close(fd[0]); 
      const pid_t fork_retval__pid = fork(); 
      if (-1 == fork_retval__pid) { // Failure 
	_exit(errno); 
	return 1; 
      }; 
      if (0 == fork_retval__pid) { // New child 
	dup2(fd[1], STDIN_FILENO); 
	//const int execvp_retval = execvp(mapped_prog__const, ((char * []){ mapped_prog__mutable, line_buffer, NULL })); 
	const int execvp_retval = execvp(mapped_prog__const, ((char * []){ mapped_prog__mutable, NULL })); 
	// On sucess, execvp should not return. 
	assert(-1 == execvp_retval); 
	_exit(errno); 
	return 1; 
      }; 
      // PARENT PROCESS 
      assert(0 < fork_retval__pid); 
      const pid_t waitpid_retval__pid = waitpid(fork_retval__pid, NULL, 0); 
      close(fd[1]); 
      if (waitpid_retval__pid == fork_retval__pid) { 
	read_buffer_start_pos = read_buffer_end_pos + 1; 
	continue; 
      }; 
      if (-1 == waitpid_retval__pid) { 
	_exit(errno); 
	return 1; 
      }; 
      { 
	write_string(STDERR_FILENO, argv[0]); 
	write_string(STDERR_FILENO, ": Unexpected waitpid_retval__pid: "); 
	write_long_long_int(STDERR_FILENO, waitpid_retval__pid); 
	write_eol(STDERR_FILENO); 
	_exit(-3); 
	return -3; 
      }; 
      assert(false); 
      return 1; 
    }; 
    
    label_for_body: { 
    if (false) { 
      write_string(STDERR_FILENO, argv[0]); 
      write_string(STDERR_FILENO, "loop -> "); 
      write_long_long_int(STDERR_FILENO, 0); 
      write_string(STDERR_FILENO, ""); 
      write_eol(STDERR_FILENO); 
    }; 
    
    // BUFFER ALL READ? 
    if (read_buffer_start_pos >= read_buffer_nb) { 
      if (stdin_eof_huh) { _exit(0); return 0; }; 
      read_buffer_start_pos =  0; 
      read_buffer_end_pos   = -1; 
      read_buffer_nb        =  0; 
      goto label_for_refill; 
    }; 
    
    // Where is newline? 
    const int16_t newline_pos = lookup_newline_char(read_buffer, read_buffer_nb, read_buffer_start_pos); 
    if (-1 > newline_pos) { 
      write_string(STDERR_FILENO, argv[0]); 
      write_string(STDERR_FILENO, ": Bad newline_pos: "); 
      write_long_long_int(STDERR_FILENO, newline_pos); 
      write_eol(STDERR_FILENO); 
      _exit(3); 
      return 3; 
    }; 
    
    if (-1 == newline_pos) { 
      if (!stdin_eof_huh) { 
	if (read_buffer_start_pos > 0) goto label_for_rotate_then_refill; 
	if (read_buffer_nb < READ_BUFFER_BYTESIZE) goto label_for_refill; 
	assert(0 == read_buffer_start_pos); 
	assert(read_buffer_nb == READ_BUFFER_BYTESIZE); 
	assert(stdin_eof_huh == false); 
	write_string(STDERR_FILENO, argv[0]); 
	write_string(STDERR_FILENO, ": READ_BUFFER_BYTESIZE too small: "); 
	write_long_long_int(STDERR_FILENO, READ_BUFFER_BYTESIZE); 
	write_eol(STDERR_FILENO); 
      }; 
      assert(stdin_eof_huh); 
    }; 
    
    read_buffer_end_pos = (0 <= newline_pos) ? newline_pos : (read_buffer_nb - 1); 
    
    goto label_for_pipe_fork_exec; 
    }; 
    
  }; 
  
  assert(false); 
  return 1; 
}; 


