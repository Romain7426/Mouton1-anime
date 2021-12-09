#include <unistd.h>

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

#define CHAR_TO_DIGIT(__c__) (						\
			      ((__c__) >= '0' && (__c__) <= '9') ? (__c__) - '0' : \
			      ((__c__) >= 'A' && (__c__) <= 'F') ? (__c__) - 'A' + 10 : \
			      ((__c__) >= 'a' && (__c__) <= 'f') ? (__c__) - 'a' + 10 : \
			      '?')

enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 

static int write_long_long_int(long long int n) { 
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
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(STDOUT_FILENO, p, len); 
  return len; 
}; 

static int write_int(int n) { 
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
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(STDOUT_FILENO, p, len); 
  return len; 
}; 

static int write_string(const char * cstr) { 
  if (NULL == cstr) { 
    static const char s[] = "NULL"; 
    write(STDOUT_FILENO, s, sizeof(s) - 1); 
    return sizeof(s) - 1; 
  }; 
  
  const char * p = cstr; 
  for (;;) { if (*p == '\0') break; p++; }; 
  const int len = p - cstr; 
  write(STDOUT_FILENO, cstr, len); 
  return len; 
}; 

static int write_string_ln(const char * cstr) { 
  if (NULL == cstr) { 
    static const char s[] = "NULL" "\n"; 
    write(STDOUT_FILENO, s, sizeof(s) - 1); 
    return sizeof(s); 
  }; 
  
  const char * p = cstr; 
  for (;;) { if (*p == '\0') break; p++; }; 
  const int len = p - cstr; 
  write(STDOUT_FILENO, cstr, len); 
  write(STDOUT_FILENO, "\n", 1); 
  return len + 1; 
}; 

static int write_eol(void) { 
  write(STDOUT_FILENO, "\n", 1); 
  return 1; 
}; 


enum u_t { X }; 

int main(const int argc, const char * argv[]) { 
  write_int(sizeof(enum u_t)); 
  write_eol(); 
  return 0; 
}; 




