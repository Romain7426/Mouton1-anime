#include "lib.ci"
 
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
  uint32_t n; 
  n = 0; 
  n --; 
  //n = ((~n) >> 1); 
  write_long_long_int_ln(STDOUT_FILENO, n); 
  //write_long_long_int_ln(STDOUT_FILENO, (((long long)n)<<0) + ((1 << 15)<<2) ); 
  //write_long_long_int_ln(STDOUT_FILENO, 65536LL * 65536LL); 
  //write_long_long_int_ln(STDOUT_FILENO, 65535LL * 65535LL); 
  return 0; 
}; 


