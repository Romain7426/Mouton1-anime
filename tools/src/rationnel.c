#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

enum { BUF_SIZE = INT16_MAX }; 

static int write_int(long long int n) { 
  static char buffer[BUF_SIZE] = {}; 
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




static int print_quotient(const int sign, const int dividende, const int diviseur, const int digits); 

 
int main(const int argc, const char * argv[]) { 
  if (3 != argc && 4 != argc) { 
    write_string("\t" "usage: "); 
    write_string(argv[0]); 
    write_string(" `dividende' `diviseur' [`digits']" "\n"); 
    return 0; 
  }; 
  
  const int argv1 = atoi(argv[1]); 
  const int argv2 = atoi(argv[2]); 
  const int argv3 = 4 == argc ? atoi(argv[3]) : -1; 
  const int digits = argv3; 
  
  if (0 == argv2) { 
    const int sign      = (0 == argv1) ? 0 : (0 > argv1 ? -1 : 1); 
    const int dividende = (0 == argv1) ? 0 : (0 > argv1 ? -argv1 : argv1); 
    print_quotient(sign, dividende, 0, digits); 
    return 0; 
  }; 
  if (0  > argv2) { 
    const int sign      = (0 == argv1) ? 0 : (0 > argv1 ? 1 : -1); 
    const int dividende = (0 == argv1) ? 0 : (0 > argv1 ? -argv1 : argv1); 
    const int diviseur  = -argv2; 
    print_quotient(sign, dividende, diviseur, digits); 
    return 0; 
  }; 
  { 
    const int sign      = (0 == argv1) ? 0 : (0 > argv1 ? -1 : 1); 
    const int dividende = (0 == argv1) ? 0 : (0 > argv1 ? -argv1 : argv1); 
    const int diviseur  = argv2; 
    print_quotient(sign, dividende, diviseur, digits); 
    return 0; 
  }; 

  return -1; 
}; 






int print_quotient(const int sign, const int dividende, const int diviseur, const int digits) { 
  static uint8_t  tableau_des_quotients     [BUF_SIZE]; 
  static int      tableau_des_restes        [BUF_SIZE]; 
  static uint16_t tableau_des_restes_indices[BUF_SIZE]; 
  
  if (0 == diviseur) { 
    if (0 == sign) { 
      return write_string_ln("0/0"); 
    }; 
    if (0 > sign) { 
      return write_string_ln("-∞"); 
    };
    { 
      return write_string_ln("+∞"); 
    }; 
  }; 

  if (0 == sign) { 
    return write_string_ln("0"); 
  }; 
  
  // = (int *) malloc(diviseur * (sizeof (int)));
  bzero(tableau_des_restes, sizeof(tableau_des_restes)); 
  
  const int quotient0 = dividende / diviseur; 
  const int reste0    = dividende % diviseur; 
  
  int i; 
  int quotient = quotient0; 
  int reste    =    reste0; 
  i = 0; 
  for (;;) { 
    reste    *= 10; 
    quotient  = (reste / diviseur); 
    reste     = (reste % diviseur); 
    i++; 
    if (i >= BUF_SIZE) { break; }; 
    tableau_des_quotients     [    i] = quotient; 
    tableau_des_restes        [    i] =    reste; 
    if (reste >= BUF_SIZE) { break; }; 
    if (0 != tableau_des_restes_indices[reste]) break; 
    tableau_des_restes_indices[reste] =        i; 
  }; 
  
  
  const uint16_t i_0 = tableau_des_restes_indices[reste]; 
  const uint16_t i_1 = i_0 + 1; 
  const uint16_t i_n = i; 
  const uint16_t longueur_de_la_periode = i_n - i_1 + 1; 
#if 1 
  printf("Indice de début du cycle: %d\n", i_1); 
  printf("Longueur de la période: %d\n", longueur_de_la_periode);
#endif

#if 0 
  printf("%d / %d = ", dividende, diviseur);
  printf("%d.", tableau_des_quotients[1]);
  for (int j = 2; j <= i; j++)
    printf("%d", tableau_des_quotients[j]);
  printf("…\n");

  printf("Période = ");
  for (int j = tableau_des_restes_indices[reste] + 1; j <= i; j++)
    printf("%d", tableau_des_quotients[j]);
  printf("…\n");
#endif




  printf("%d / %d = ", dividende, diviseur); 
  fflush(NULL); 



  if (digits < 0) { 
    if (0 == reste0) { 
      write_int(quotient0); 
      write_eol(); 
      return 0; 
    }; 
    
    //printf("%d.", tableau_des_quotients[1]); 
    printf("%d.", quotient0); 
    fflush(NULL); 
    for (int j = 1; j <= i_0; j++) { 
      write_int(tableau_des_quotients[j]); 
      //printf("%d", tableau_des_quotients[j]); 
    }; 
    
    if (0 == reste) { 
      //write_int(tableau_des_quotients[i_0]); 
      write_eol(); 
      return 0; 
    }; 
    
    printf("…"); 
    fflush(NULL); 
    for (int j = i_1; j <= i_n; j++) { 
      write_int(tableau_des_quotients[j]); 
      //printf("%d", tableau_des_quotients[j]); 
    }; 
    printf("…\n"); 

    return 0; 
  }; 




  if (0 == digits) { 
    write_int(quotient0); 
    write_eol(); 
    return 0; 
  }; 



  {
    if (0 == reste0) { 
      write_int(quotient0); 
      write_string("."); 
      for (int j = 0; j < digits; j++) { 
	write_string("0"); 
      }; 
      write_eol(); 
      return 0; 
    }; 
    
    //printf("%d.", tableau_des_quotients[1]); 
    printf("%d.", quotient0); 
    fflush(NULL); 
    for (int j = 1; j <= i_0; j++) { 
      write_int(tableau_des_quotients[j]); 
      //printf("%d", tableau_des_quotients[j]); 
      if (j == digits) goto label_write_eol; 
    }; 
    
    if (0 == reste) { 
      //write_int(tableau_des_quotients[i_0]); 
      for (int j = i_0; j <= digits; j++) { 
	write_string("0"); 
      }; 
      write_eol(); 
      return 0; 
    }; 
    
    for (int j = i_1; j <= digits; j++) { 
      //for (int j = i_0; j < i_n; j++) { 
      //const int ind = ((j - i_0) % longueur_de_la_periode) + i_0; 
      const int ind = ((j - i_1) % longueur_de_la_periode) + i_1; 
      write_int(tableau_des_quotients[ind]); 
      //printf("%d", tableau_des_quotients[j]); 
    }; 
    
  label_write_eol: 
    write_eol(); 
    return 0; 
 };   
  
  
  
  
  return 0; 
}; 
 

