#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include <errno.h> 

// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_wait.h.html
#include <sys/wait.h> 

#ifndef __bool_true_false_are_defined /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdbool.h.html */ 
enum { true  = (0 == 0) }; 
enum { false = (0 != 0) }; 
#  define __bool_true_false_are_defined 1
#endif 

#define ASSERT_COMPILE(a) { int tab[((a) ? 1 : (-1))]; }; 

#define assert(__cond__) { if (!(__cond__)) { write(STDERR_FILENO, "assertion failed\n", 17); _exit(1); }; }; 

#define  INT16_MAX__M   (0x0FFF) 
enum {   INT16_MAX__E = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                        (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 

#define UINT16_MAX__M   (0xFFFF) 
enum {  UINT16_MAX__E = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                        (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) + (1   << 15) }; 

#ifndef INT16_MAX
#  define INT16_MAX INT16_MAX__E
#endif

#ifndef UINT16_MAX
#  define UINT16_MAX UINT16_MAX__E
#endif


enum { WRITE_BUF_SIZE = INT16_MAX }; 
static char write_buffer[WRITE_BUF_SIZE] = {}; 
enum { write_buffer_size = sizeof(write_buffer) }; 

#define DIGIT_TO_STRING(d) (			\
			    (d) == 0 ? "0" :	\
			    (d) == 1 ? "1" :	\
			    (d) == 2 ? "2" :	\
			    (d) == 3 ? "3" :	\
			    (d) == 4 ? "4" :	\
			    (d) == 5 ? "5" :	\
			    (d) == 6 ? "6" :	\
			    (d) == 7 ? "7" :	\
			    (d) == 8 ? "8" :	\
			    (d) == 9 ? "9" :	\
			    "?")

#define DIGIT_TO_CHAR(d) (((d) >= 0 && (d) <= 9) ? '0' + (d) : '?') 


static int write_eol(const int file_des) { 
  write(file_des, "\n", 1); 
  return 1; 
}; 

static int write_string(const int file_des, const char * cstr) { 
  if (NULL == cstr) { 
    static const char s[] = "NULL"; 
    write(file_des, s, sizeof(s) - 1); 
    return sizeof(s) - 1; 
  }; 
  
  const char * p = cstr; 
  for (;;) { if (*p == '\0') break; p++; }; 
  const int len = p - cstr; 
  write(file_des, cstr, len); 
  return len; 
}; 

static int write_string_ln(const int file_des, const char * cstr) { 
  const int len1 = write_string(file_des, cstr); 
  const int len2 = write_eol(file_des); 
  return len1 + len2; 
}; 

#define LOG10_OF_2_AS_MACRO  0.301029995663981195213738894724493026768189881462108541310427461127108189274424509486927252118186172040684
// log10(256) = log10(2^8) = 8 * log10(2) = 8 * 0.301029… = 2.408239968… ≤ 2.5 
// => sizeof(n) * log10(256) ≤ 2.5 x sizeof(n) 

static void write_long_long_int__compile_check(void) { 
  ASSERT_COMPILE(WRITE_BUF_SIZE >= (((sizeof(long long int)) << 1) + ((sizeof(long long int)) >> 1) + 1 + 1)); 
}; 

static int write_long_long_int(const int file_des, long long int n) { 
  //assert(BUF_SIZE >= (((sizeof(n)) << 1) + ((sizeof(n)) >> 1) + 1 + 1)); 
  //if (BUF_SIZE <= 3) return 2; 

#if 0   
  if (0 == n) { 
    write(file_des, "0", 1); 
    return 1; 
  }; 
#endif 
  
  const int8_t neg_huh = (n < 0); 
  if (neg_huh) n = -n; 
  
  char * p; 
  p = write_buffer + WRITE_BUF_SIZE; 
  p--; 
  *p = '\0';
  p--; 
  for (;;) { 
    *p = '0' + (n % 10); 
    n = n / 10; 
    if (0 == n) break; 
    if (p == write_buffer) { return ~0; }; 
    p--; 
  }; 
  
  if (neg_huh) { 
    if (p == write_buffer) { return ~0; }; 
    p--; 
    *p = '-';
  }; 
  
  const int len = WRITE_BUF_SIZE - (p - write_buffer) - 1; 
  write(file_des, p, len); 
  return len; 
}; 

static int write_long_long_int_ln(const int file_des, const long long int n) { 
  const int len1 = write_long_long_int(file_des, n); 
  const int len2 = write_eol(file_des); 
  return len1 + len2; 
}; 

static void write__compile_check(void) { 
  ASSERT_COMPILE(WRITE_BUF_SIZE >= 3); 
}; 

static int cstrlen(const char * cstr) { 
  if (cstr == NULL) return -1; 
  const char * p = cstr; 
  for (;;) { if (*p == '\0') break; p++; }; 
  const int len = p - cstr; 
  return len;
}; 

static void bytecopy(const char * byte_src, char * byte_dest, const int bytesize) { 
  for (int i = 0; i < bytesize; i++) { 
    *byte_dest = *byte_src; 
    byte_dest++; 
    byte_src++; 
  }; 
}; 

static int16_t lookup_newline_char(const char * buffer, const int16_t buffer_bytesize, const int16_t start_pos) { 
  if (0 > buffer_bytesize) return -3; 
  if (0 == buffer_bytesize) return -2; 
  int16_t current_index; 
  for (int16_t current_index = start_pos; current_index < buffer_bytesize; current_index++) { 
    if ('\n' == buffer[current_index]) return current_index; 
  }; 
  return -1; 
}; 


int main(const int argc, const char * argv[]) { 
  if (argc < 1) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    _exit(4); 
    return 4; 
  }; 
  if (argc >= 2) { 
    write_string(STDERR_FILENO, argv[0]); 
    write_string(STDERR_FILENO, ": take no (zero) argument (got "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_string(STDERR_FILENO, ")"); 
    write_eol(STDERR_FILENO); 
    _exit(5); 
    return 5; 
  }; 
  assert(1 == argc); 
  
  const char * mapped_prog__const = argv[1]; 
  const size_t mapped_prog__strlen1 = 1 + cstrlen(mapped_prog__const); 
  char mapped_prog__mutable[mapped_prog__strlen1]; 
  bytecopy(mapped_prog__const, mapped_prog__mutable, mapped_prog__strlen1); 
  
  enum { READ_BUFFER_BYTESIZE = (1 << 14) }; 
  static char read_buffer[READ_BUFFER_BYTESIZE]; 
  int16_t read_buffer_start_pos = 0; 
  int16_t read_buffer_end_pos = -1; 
  int16_t read_buffer_nb = 0; 
  for (;;) { 
    if (false) { 
      write_string(STDERR_FILENO, argv[0]); 
      write_string(STDERR_FILENO, "loop -> "); 
      write_long_long_int(STDERR_FILENO, 0); 
      write_string(STDERR_FILENO, ""); 
      write_eol(STDERR_FILENO); 
    }; 
    
    // REFILL BUFFER? 
    if (read_buffer_start_pos >= read_buffer_nb) { 
      const ssize_t byteread_count = read(STDIN_FILENO, read_buffer, READ_BUFFER_BYTESIZE); 
      if (-1 == byteread_count) { /* error */; _exit(errno); return 1; }; 
      if ( 0  > byteread_count) { /* WTF?  */; _exit(errno); return 2; }; 
      if ( 0 == byteread_count) { /* EOF   */; _exit(0);     return 0; }; 
      if (byteread_count == READ_BUFFER_BYTESIZE) { 
	if ('\n' != read_buffer[byteread_count - 1]) { 
	  write_string(STDERR_FILENO, argv[0]); 
	  write_string(STDERR_FILENO, ": READ_BUFFER_BYTESIZE TOO SMALL: "); 
	  write_long_long_int(STDERR_FILENO, READ_BUFFER_BYTESIZE); 
	  write_eol(STDERR_FILENO); 
	  _exit(3); 
	  return 3; 
	}; 
      }; 
      read_buffer_start_pos =  0; 
      read_buffer_end_pos   = -1; 
      read_buffer_nb        = byteread_count; 
    }; 
    
    // Where is newline? 
    const int16_t newline_pos = lookup_newline_char(read_buffer, read_buffer_nb, read_buffer_start_pos); 
    if (-1 > newline_pos) { 
      write_string(STDERR_FILENO, argv[0]); 
      write_string(STDERR_FILENO, ": Bad newline_pos: "); 
      write_long_long_int(STDERR_FILENO, newline_pos); 
      write_eol(STDERR_FILENO); 
      _exit(-3); 
      return -3; 
    }; 
    
    read_buffer_end_pos = (0 <= newline_pos) ? newline_pos : (read_buffer_nb - 1); 
    const int16_t line_bytesize = read_buffer_end_pos - read_buffer_start_pos + 1; 
    
    { // pipe & fork & exec 
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
    assert(false);
    return 1; 
  };
  assert(false); 
  return 1; 
}; 


