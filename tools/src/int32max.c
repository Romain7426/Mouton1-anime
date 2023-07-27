#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 

#include <errno.h> 

#include "lib.ci" 


int main(const int argc, const char * argv[]) { 
  //write_long_long_int_ln(STDOUT_FILENO, INT16_MAX); 
  //write_long_long_int_ln(STDOUT_FILENO, (~(1 << 15))); 
  //write_long_long_int_ln(STDOUT_FILENO, ((1 << 15)-1)); 
  //write_long_long_int_ln(STDOUT_FILENO, ((1 << 15)<<2)); 
  //write_long_long_int_ln(STDOUT_FILENO, INT16_MAX << 1); 
  //write_long_long_int_ln(STDOUT_FILENO, 0); 
  //write_long_long_int_ln(STDOUT_FILENO, 1); 
  //write_long_long_int_ln(STDOUT_FILENO, (~(0LL))); 
  //write_long_long_int_ln(STDOUT_FILENO, ((~(0UL))>>(1ULL))); 
  int32_t n; 
  n = 1; 
  n <<= 31; 
  n --; 
  //n = ((~n) >> 1); 
  write_long_long_int_ln(STDOUT_FILENO, n); 
  //write_long_long_int_ln(STDOUT_FILENO, (((long long)n)<<0) + ((1 << 15)<<2) ); 
  //write_long_long_int_ln(STDOUT_FILENO, 65536LL * 65536LL); 
  return 0; 
}; 


