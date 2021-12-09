#include <stdio.h>
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

static bool fichier_existe_huh(const char * fichier_nom);
static uint64_t fichier_taille(const char * fichier_nom);
static char * fichier_lire(const char * fichier_nom);
static char * string_replace(const char * text, const char * old_str, const char * new_str);
static int nb_occurrences(const char * text, const char * old_str);


static inline char * strcopy(const char * str) {
  const size_t len = strlen(str);
  const size_t len_octet = (len+1) * (sizeof(char));
  char * retour;

  retour = (char *) malloc(len_octet);
  
  memcpy(retour, str, len_octet);

  return retour;
}


static inline char * strallouer(unsigned int taille) {
  char * alpha; 

  alpha = (char *) malloc((sizeof (char)) * (taille + 1));
  
  if (taille > 0) 
    alpha[0] = '\0'; 

  return alpha; 
}


int main(const int argc, const char * argv[]) {
  assert(argc == 4);
  
  char * fichier_contenu;
  char * contenu_filtre;
  fichier_contenu = fichier_lire(argv[3]);
  contenu_filtre = string_replace(fichier_contenu, argv[1], argv[2]);
  
  printf("%s\n", contenu_filtre);

  return 0;
}




char * string_replace(const char * text, const char * old_str, const char * new_str) {
  const size_t text_len = strlen(text);
  const size_t old_str_len = strlen(old_str);
  const size_t new_str_len = strlen(new_str);

  const int nb_occ = nb_occurrences(text, old_str);

  const size_t new_len = text_len + nb_occ * (new_str_len - old_str_len);

  char * nv_text = (char *) malloc((new_len + 1) * (sizeof (char)));

  const char c = old_str[0];
  unsigned pos = 0;
  while (*text != '\0') {
    if ((*text == c) && ((new_len - pos) >= old_str_len) && (0 == memcmp(text, old_str, old_str_len))) {
      memcpy(nv_text + pos, new_str, new_str_len);
      pos += new_str_len;
      text += old_str_len;
    }
    else {
      nv_text[pos] = *text;
      pos++;
      text++;
    }
  }
  
  nv_text[pos] = '\0';
  
  return nv_text;
}


int nb_occurrences(const char * text, const char * old_str) {
  int nb = 0;
  const char c = old_str[0];
  const size_t len = strlen(old_str);

  while (*text != '\0') {
    if (*text == c) 
      if (0 == memcmp(text, old_str, len))
	nb++;
    text++;
  }
  return nb;
}


char * fichier_lire(const char * fichier_nom) { 
  FILE * fichier;
  uint64_t len;
  size_t ret;
  //  int64_t len_read;
  char * fichier_contenu;

  assert(fichier_nom != NULL);

  assert(fichier_existe_huh(fichier_nom)); 
  
  len = fichier_taille(fichier_nom); 


  if (len == 0) {
    return strcopy("");
  }

  fichier = fopen(fichier_nom, "r"); 

  assert(fichier != NULL);

  
  //fichier_contenu = (char *) malloc(sizeof(char) * (len + 1)); 
  //fichier_contenu = strallouer(len);
#define UINT_MAX_LOCAL ((uint64_t) ((unsigned) ((int) -1)))
  assert(len <= UINT_MAX_LOCAL);
#undef UINT_MAX_LOCAL
  
  fichier_contenu = strallouer(((unsigned) len));
  
  //size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
  //     The functions fread() and fwrite() advance the file position indicator
  //     for the stream by the number of bytes read or written.  They return the
  //     number of objects read or written.  If an error occurs, or the end-of-
  //     file is reached, the return value is a short object count (or zero).
  // en clair, il retourne le nombre exact de blocs qui ont été lus

#define SIZE_T_MAX_LOCAL (~ ((size_t) 0))
  assert(len <= SIZE_T_MAX_LOCAL);
#undef SIZE_T_MAX_LOCAL

  ret = fread(fichier_contenu, (size_t) len, 1, fichier);

    
  
  fclose(fichier);

  assert(ret == 1);
  fichier_contenu[len] = '\0';

  return fichier_contenu;
}




bool fichier_existe_huh(const char * fichier_nom) {
  int ret; 
  struct stat sb;

  ret = stat(fichier_nom, &sb); 
  return (ret == 0);
}

uint64_t fichier_taille(const char * fichier_nom) { 
  // moyen primitif: 
  //  fopen
  //  fseek(SEEK_END)
  //  ftell
  //  fclose
  // moyen évolué
  //  stat
  int ret; 
  struct stat sb;

  ret = stat(fichier_nom, &sb); 
  assert(ret == 0);

  return ((uint64_t) sb.st_size);
}
