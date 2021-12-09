#include <unistd.h>

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

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

#define DIGIT_TO_CHAR(__c__) ((__c__) < 10 ? '0' + (__c__) : 'A' + (__c__) - 10)
static int write_uint_b16(unsigned int n) { 
  char * p; 
  p = buffer + BUF_SIZE; 
  p--; 
  *p = '\0'; 
  p--; 
  *p = DIGIT_TO_CHAR(n & 15); 
  n >>= 4; 
  p--; 
  *p = DIGIT_TO_CHAR(n & 15); 
  n >>= 4; 
  
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(1, p, len); 
  return 0; 
}; 

static int write_uint8_b16(unsigned char n) { 
  char b16_buffer[9]; // = { '0', '0', '0', '0', '0', '0', '0', '0', '\0'}; 
  enum { b16_BUF_SIZE = 3 }; 
  char * p; 
  p = b16_buffer + b16_BUF_SIZE; 
  p--; 
  *p = '\0'; 
  p--; 
  *p = DIGIT_TO_CHAR(n & 15); 
  n >>= 4; 
  p--; 
  *p = DIGIT_TO_CHAR(n & 15);   
  write(1, p, 2); 
  return 0; 
}; 

static int write_uint8_b2(unsigned char n) { 
  char b2_buffer[9]; // = { '0', '0', '0', '0', '0', '0', '0', '0', '\0'}; 
  enum { b2_BUF_SIZE = 9 }; 
  char * p; 
  p = b2_buffer + b2_BUF_SIZE; 
  p--; 
  *p = '\0'; 
  for (int i = 0; i < 8; i++) { 
    p--; 
    *p = DIGIT_TO_CHAR(n & 1); 
    n >>= 1; 
  }; 
  const int len = 8; 
  write(1, p, len); 
  return 0; 
}; 

int main(const int argc, const char * argv[]) { 
  static unsigned char c; 
  static ssize_t read_nb; 
  static char line_off; 
  for (;;) { 
    line_off = -1; 
    for (;;) { 
      line_off++; 
      if (16 == line_off) break; 
      read_nb = read(STDIN_FILENO, &c, 1); 
      if (1 != read_nb) { break; }; 
      write_uint8_b16(c); 
      if (7 == line_off)  
	write_string("  "); 
      else
	write_string(" "); 
    }; 
    if (line_off > 0) { 
      write_eol(); 
    }; 
    if ( 0 == read_nb) { return  0; }; 
    if (-1 == read_nb) { return -1; }; 
    if ( 1 != read_nb) { return -2; }; 
  }; 
  
  return 0; 
}; 



