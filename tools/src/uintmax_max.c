#include "lib.ci"

int main(const int argc, const char * argv[]) { 
  const int8_t octets_nb = sizeof(intmax_t); 
  const int8_t bits_nb   = (octets_nb << 3); 
  const uintmax_t max = ~UINTMAX_C(0); 
#if 0 
  char buffer[INT16_MAX];
  const int len = write_long_long_unsigned_int_into_buffer(buffer, sizeof(buffer), max); 
  //const int len = write_long_long_unsigned_int_into_buffer(buffer, sizeof(buffer), UINT64_MAX); 
  //const int len = write_long_long_int_into_buffer(buffer, sizeof(buffer), INT64_MAX); 
  write(STDOUT_FILENO, buffer, len); 
  return 0; 
#endif
  write_lluint_ln(STDOUT_FILENO, max); 
  return 0; 
};
