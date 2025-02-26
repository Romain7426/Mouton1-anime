#include "lib.ci"

int main(const int argc, const char * argv[]) { 
  const int8_t octets_nb = sizeof(intmax_t); 
  const int8_t bits_nb   = (octets_nb << 3); 
  intmax_t max = INTMAX_C(1); 
  max <<= (bits_nb - 1); 
  max --; 
  write_llint_ln(STDOUT_FILENO, max); 
  return 0; 
};
