#include <unistd.h>

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 

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






static char tab_3dec[3] = {}; 
 
static void tab_3dec__bzero(void) { 
  tab_3dec[0] = '0'; 
  tab_3dec[1] = '0'; 
  tab_3dec[2] = '0'; 
}; 

static unsigned char tab_3dec__convert(const int len) { 
  unsigned char n = 0; 
  if (len >= 1) { const int m = tab_3dec[0] - '0'; n = m; }; 
  if (len >= 2) { const int m = tab_3dec[1] - '0'; n = m + (n << 3) + (n << 1); }; 
  if (len >= 3) { const int m = tab_3dec[2] - '0'; n = m + (n << 3) + (n << 1); }; 
  return n; 
}; 

int main(const int argc, const char * argv[]) { 
  static unsigned char          c; 
  static ssize_t          read_nb; 
  static int           tab_3dec_i; 
  for (;;) { 
    tab_3dec__bzero(); 
    tab_3dec_i = -1; 
    for (;;) { 
      tab_3dec_i++; 
      if (3 == tab_3dec_i) break; 
      read_nb = read(STDIN_FILENO, &c, 1); 
      if (1 != read_nb) { break; }; 
      const int in_range_huh = (c >= '0') && (c <= '1'); 
      if (!in_range_huh) break; 
      tab_3dec[tab_3dec_i] = c; 
    }; 
    if (tab_3dec_i > 0) { 
      const unsigned char u = tab_3dec__convert(tab_3dec_i); 
      write(STDOUT_FILENO, &u, 1); 
    }; 
    if ( 0 == read_nb) { return  0; }; 
    if (-1 == read_nb) { return -1; }; 
    if ( 1 != read_nb) { return -2; }; 
  }; 
  return 0; 
}; 




