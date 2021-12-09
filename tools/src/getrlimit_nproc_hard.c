#include <unistd.h>
#include <sys/resource.h>

#define ASSERT_COMPILE(a) { int tab[((a) ? 1 : (-1))]; }; 

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 

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
  ASSERT_COMPILE(BUF_SIZE >= (((sizeof(long long int)) << 1) + ((sizeof(long long int)) >> 1) + 1 + 1 + 1)); 
}; 

static int write_long_long_int(const int file_des, long long int n) { 
  //assert(BUF_SIZE >= (((sizeof(n)) << 1) + ((sizeof(n)) >> 1) + 1 + 1)); 
  //if (BUF_SIZE <= 3) return 2; 

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



 
// man 2 getrlimit 
// int getrlimit(int resource, struct rlimit *rlp); 
// 
//           struct rlimit {
//                   rlim_t  rlim_cur;       /* current (soft) limit */
//                   rlim_t  rlim_max;       /* hard limit */
//           };
// 
// «hard limit» -> defined by root — cannot be changed by user. 
// «soft limit» -> value used by softwares — default value defined by root, can be changed by user (always lower than «hard limit») 
// 
// => These information are per process. 

static void main__compile_check(void) { 
  ASSERT_COMPILE(BUF_SIZE >= 3); 
}; 

int main(const int argc, const char * argv[]) { 
#ifndef RLIMIT_NPROC 
  write_string_ln(STDOUT_FILENO, "undefined"); 
  return 0; 
#else 
  struct rlimit rl; 
  const int retval = getrlimit(RLIMIT_NPROC, &rl); 
  if (0 != retval) { return retval; }; 
  //const rlim_t rlim_val = rl.rlim_cur; 
  const rlim_t rlim_val = rl.rlim_max; 
  if (RLIM_INFINITY == rlim_val) { 
    write_string_ln(STDOUT_FILENO, "infinity"); 
  } 
  else if (RLIM_SAVED_CUR == rlim_val) { 
    write_string_ln(STDOUT_FILENO, "RLIM_SAVED_CUR"); 
  } 
  else if (RLIM_SAVED_MAX == rlim_val) { 
    write_string_ln(STDOUT_FILENO, "RLIM_SAVED_MAX"); 
  } 
  else { 
    write_long_long_int_ln(STDOUT_FILENO, rlim_val); 
  }; 
  return 0; 
#endif 
}; 


