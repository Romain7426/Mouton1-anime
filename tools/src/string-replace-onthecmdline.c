#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // int8_t, etc., intmax_t , uintmax_t, 
#include <inttypes.h> // uint8_t, ..., uintmax_t i = UINTMAX_MAX; // this type always exists 
#include <stddef.h> // offsetof(type, member-designator) 
#include <stdio.h> // remove, int rename(const char *old, const char *new); , 
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <math.h>     // cosf, ..., int signbit(real-floating x); , isnormal(neither zero, subnormal, infinite, nor NaN)., int isnan(real-floating x); , int isinf(real-floating x); int isfinite(real-floating x); 
#include <ctype.h>    // tolower, toupper
#include <assert.h>  // dépend de la valeur de la macro NDEBUG 
#ifndef __TINYC__ // For some reasons, TCC fails to read this file. 
#include <complex.h>  // types «complex», «double complex», «long double complex», «float complex» 
#endif 
#include <ctype.h> 
#include <errno.h> 
#include <float.h> // limits 
#include <iso646.h>  // Alternative spellings: and &&, xor ^, etc. 
#include <limits.h> 
#include <setjmp.h> 
#include <signal.h> 
#include <time.h> // clock & time --- 
#ifndef __PCC__ // For some reasons, PCC fails to read these files. 
#include <wchar.h> 
#include <wctype.h> 
#endif
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h> // time_t, time(), ctime() ;  ("man 3 time") donne la date d'ajd
#ifndef ctime_r
# define ctime_r(a,b) ((b == NULL ? 0 : strcpy(b, "FAILED ")), *a = time(NULL), ctime(a))
#endif

enum bool {true = (0 == 0), false = (0 != 0)};
typedef enum bool bool;

static char * string_replace(const char * text, const char * old_str, const char * new_str);
static int nb_occurrences(const char * text, const char * old_str);




int main(const int argc, const char * argv[]) {
  if (4 != argc) {
    printf("usage: %s working-string old-str new-str\n", argv[0]);
    return -1;
  }
  
  char * contenu_filtre;
  contenu_filtre = string_replace(argv[1], argv[2], argv[3]);
  printf("%s\n", contenu_filtre);
  free(contenu_filtre);

  return 0;
}




char * string_replace(const char * text, const char * old_str, const char * new_str) {
  const size_t text_len = strlen(text);
  const size_t old_str_len = strlen(old_str);
  const size_t new_str_len = strlen(new_str);
  
  const int nb_occ = nb_occurrences(text, old_str);
  
  const size_t new_len = text_len + nb_occ * (new_str_len - old_str_len);
#if 0
  fprintf(stderr, "nb occ: %d\n", nb_occ);
  printf("old len: %lu\n", old_str_len);
  printf("new len: %lu\n", new_str_len);
  printf("text len: %lu\n", text_len);
  printf("new len: %lu\n", new_len);
#endif
  
  char * nv_text = (char *) malloc((new_len + 1) * (sizeof (char)));
  nv_text[new_len] = '\0';
  
  const char c = old_str[0];
  size_t old_pos = 0;
  size_t new_pos = 0;
  while (text[old_pos] != '\0') {
    if ((text[old_pos] == c) && ((text_len - old_pos) >= old_str_len) && (0 == memcmp(&(text[old_pos]), old_str, old_str_len))) {
      memcpy(nv_text + new_pos, new_str, new_str_len);
      new_pos += new_str_len;
      //text += old_str_len;
      old_pos += old_str_len;
    }
    else {
      nv_text[new_pos] = text[old_pos];
      new_pos++;
      old_pos++;
    }
    assert(new_pos <= new_len);
    assert(old_pos <= text_len);
  }
  assert(new_pos == new_len);
  nv_text[new_pos] = '\0';
  
  return nv_text;
}


int nb_occurrences(const char * text, const char * old_str) {
  const size_t text_len = strlen(text);
  const size_t len = strlen(old_str);
  const char c = old_str[0];
  
  int nb = 0;
  size_t pos = 0;
  while (text[pos] != '\0') {
    if ((text[pos] == c) && ((text_len - pos) >= len) && (0 == memcmp(&(text[pos]), old_str, len))) {
      nb++;
      pos += len;
    }
    else { 
      pos++; 
    }
  }
  assert(pos == text_len);
  return nb;
}



