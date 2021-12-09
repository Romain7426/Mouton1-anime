#include <unistd.h>

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 
 
static const char eol[] = "\n"; 
static const char virgule[] = ", "; 


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
  write(1, p, len); 
  return 0; 
}; 

#define CHAR_TO_DIGIT(__c__) ((__c__) < 10 ? '0' + (__c__) : 'A' + (__c__) - 10)
static int write_int_b16(unsigned int n) { 
  char * p; 
  p = buffer + BUF_SIZE; 
  p--; 
  *p = '\0'; 
  p--; 
  *p = CHAR_TO_DIGIT(n & 15); 
  n >>= 4; 
  p--; 
  *p = CHAR_TO_DIGIT(n & 15); 
  n >>= 4; 
  
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(1, p, len); 
  return 0; 
}; 



int main(const int argc, const char * argv[]) { 
  static unsigned char c; 
  static unsigned char line_off = 0; 
  {
    const ssize_t read_nb = read(STDIN_FILENO, &c, 1); 
    if ( 0 == read_nb) { return  0; }; 
    if (-1 == read_nb) { return -1; }; 
    if ( 1 != read_nb) { return -2; }; 
    
    write(STDOUT_FILENO, "0x", 2); 
    write_int_b16(c); 
    line_off++; 
  }; 
  for (;;) { 
    const ssize_t read_nb = read(STDIN_FILENO, &c, 1); 
    if ( 0 == read_nb) break; 
    if (-1 == read_nb) { return -1; }; 
    if ( 1 != read_nb) { return -2; }; 
    
    if (20 == line_off) { 
      write(STDOUT_FILENO, "," "\n" "0x", 4); 
      line_off = 0; 
    } 
    else { 
      write(STDOUT_FILENO, ", 0x", 4); 
    }; 
    write_int_b16(c); 
    line_off++; 
  }; 
  if (0 != line_off) { 
    write(STDOUT_FILENO, "\n", 1); 
  }; 
  return 0; 
}; 

