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
#include <complex.h>  // types «complex», «double complex», «long double complex», «float complex» 
#include <ctype.h> 
#include <errno.h> 
#include <float.h> // limits 
#include <iso646.h>  // Alternative spellings: and &&, xor ^, etc. 
#include <limits.h> 
#include <setjmp.h> 
#include <signal.h> 
#include <time.h> // clock & time --- 
#include <wchar.h> 
#include <wctype.h> 
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h> // time_t, time(), ctime() ;  ("man 3 time") donne la date d'ajd
#ifndef ctime_r
# define ctime_r(a,b) ((b == NULL ? 0 : strcpy(b, "FAILED ")), *a = time(NULL), ctime(a))
#endif
#include <dirent.h>

enum bool {true = (0 == 0), false = (0 != 0)};
typedef enum bool bool;

static bool fichier_existe_huh(const char * fichier_nom);
static uint64_t fichier_taille(const char * fichier_nom);
static char * fichier_lire(const char * fichier_nom);
static char * string_replace(const char * text, const char * old_str, const char * new_str);
static int nb_occurrences(const char * text, const char * old_str);
static char * strcopy(const char * str);
static char * strallouer(unsigned int taille);
static bool fichier_directory_huh(const char * fichier_nom);
static char * strconcat(const char * const str1, const char * const str2);
static char * strconcat3(const char * const str1, const char * const str2, const char * const str3);
static bool name_has_spaces_huh(const char * str);




#define SPACE_HUH(c) ((' ' == (c)) || ('\t' == (c)))

//#define READ() 

//static inline bool LOOK_FOR


// man 2 stat
// man 5 dir
// man 3 opendir
// man 5 dirent


int main(const int argc, const char * argv[]) {
  int nb;
  if (1 == argc) nb = 1;
  if (argc > 1) nb = argc - 1;

  const char * dirs_to_list[nb];
  {
    if (argc == 1) {
      dirs_to_list[0] = ".";
    }
    else {
      for (int i = 1; i < argc; i++)
	dirs_to_list[i-1] = argv[i];
    }
  }
  
  
  for (int i = 0; i < nb; i++) {
    const char * dir_name = dirs_to_list[i];
    DIR * rep = opendir(dir_name);
    
    if (rep == NULL) continue;
    
    for (;;) {
      struct dirent * ent;
      ent = readdir(rep);
      if (ent == NULL) break;
      if (0 == strcmp(ent->d_name, ".")) continue;
      if (0 == strcmp(ent->d_name, "..")) continue;
      if ((ent->d_type & DT_DIR) == 0) continue;
      
      char * new_name;
      //printf("'%c'\n", ent->d_name[ent->d_namlen-1]); continue;
      //if (ent->d_name[ent->d_namlen-1] == '/')
      if (dir_name[strlen(dir_name)-1] == '/')
	new_name = strconcat(dir_name, ent->d_name);
      else
	new_name = strconcat3(dir_name, "/", ent->d_name);

      //printf("'%s'\n", new_name); continue;
      
      //if (!(fichier_directory_huh(new_name))) continue;
      assert((fichier_directory_huh(new_name)));
      
      //printf("%s\n", ent->d_name);
      //printf("%s\n", new_name);
      if (name_has_spaces_huh(new_name)) {
	printf("\"%s\"\n", new_name);
      }
      else {
	printf("%s\n", new_name);
      }
    }
    
    closedir(rep);
  }
  
  return 0;
}




bool name_has_spaces_huh(const char * str) {
  const int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (SPACE_HUH(str[i])) return true;
  }
  return false;
}





char * strconcat(const char * const str1, const char * const str2) {
  const unsigned int len = strlen(str1) + strlen(str2);
  return strcat(strcpy(malloc(len + 1), str1), str2);
}

char * strconcat3(const char * const str1, const char * const str2, const char * const str3) {
  const unsigned int len = strlen(str1) + strlen(str2) + strlen(str3);
  return strcat(strcat(strcpy(malloc(len + 1), str1), str2), str3);
}

char * strcopy(const char * str) {
  const size_t len = strlen(str);
  const size_t len_octet = (len+1) * (sizeof(char));
  char * retour;

  retour = (char *) malloc(len_octet);
  
  memcpy(retour, str, len_octet);

  return retour;
}


char * strallouer(unsigned int taille) {
  char * alpha; 

  alpha = (char *) malloc((sizeof (char)) * (taille + 1));
  
  if (taille > 0) 
    alpha[0] = '\0'; 

  return alpha; 
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

bool fichier_directory_huh(const char * fichier_nom) {
  int ret; 
  struct stat sb;
  
  ret = stat(fichier_nom, &sb); 
  if (0 != ret) {
    //printf("FALSE\n");
    return false;
  }

  return ((sb.st_mode & S_IFDIR) != 0);
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





