#include <unistd.h> /* https://en.wikipedia.org/wiki/Unistd.h */ /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */

#ifndef __bool_true_false_are_defined /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdbool.h.html */ 
enum { true = (0 == 0) }; 
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


enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 
enum { buffer_size = sizeof(buffer) }; 

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
  ASSERT_COMPILE(BUF_SIZE >= (((sizeof(long long int)) << 1) + ((sizeof(long long int)) >> 1) + 1 + 1)); 
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
  p = buffer + BUF_SIZE; 
  p--; 
  *p = '\0';
  p--; 
  for (;;) { 
    *p = '0' + (n % 10); 
    n = n / 10; 
    if (0 == n) break; 
    if (p == buffer) { return ~0; }; 
    p--; 
  }; 
  
  if (neg_huh) { 
    if (p == buffer) { return ~0; }; 
    p--; 
    *p = '-';
  }; 
  
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(file_des, p, len); 
  return len; 
}; 

static int write_long_long_int_ln(const int file_des, const long long int n) { 
  const int len1 = write_long_long_int(file_des, n); 
  const int len2 = write_eol(file_des); 
  return len1 + len2; 
}; 



 
static void main__compile_check(void) { 
  ASSERT_COMPILE(BUF_SIZE >= 3); 
}; 

int main(const int argc, const char * argv[]) { 
  uint16_t line_bytesize_max; 
  uint16_t line_bytesize_current; 
  goto label__start; 

  assert(false); 
  
  label__exit: { 
    if (line_bytesize_current > line_bytesize_max) { 
      line_bytesize_max = line_bytesize_current; 
    }; 
    write_long_long_int_ln(STDOUT_FILENO, line_bytesize_max); 
    return 0; 
  }; 
  
  assert(false); 
  
  label__start: {} 
  line_bytesize_max = 0; 
  line_bytesize_current = 0; 
  for (;;) { 
    const ssize_t buffer_len = read(STDIN_FILENO, buffer, buffer_size); 
    if (-1 == buffer_len) /* error */ { goto label__exit; }; 
    if ( 0 == buffer_len) /* EOF   */ { goto label__exit; }; 
    const char * p = buffer; 
    for (int16_t i = 0; i < buffer_len; i++, p++) { 
      line_bytesize_current ++; 
      if (*p == '\n') { 
	if (line_bytesize_current > line_bytesize_max) { 
	  line_bytesize_max = line_bytesize_current; 
	}; 
	line_bytesize_current = 0; 
	continue; 
      }; 
    }; 
  }; 
    
  assert(false); 
}; 


