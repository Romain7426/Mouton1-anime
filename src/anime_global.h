#ifndef ANIME_GLOBAL_H
#define ANIME_GLOBAL_H

#include "lib__01__pre_header.ci"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <limits.h> // NL_TEXTMAX 
#include <fcntl.h>
#include <errno.h>
#include <stdint.h> // INT64_MAX, etc. 
#include <inttypes.h> // int8_t, etc 
#include <ctype.h>
//#include <sys/types.h>
#include <time.h>
#include "lib__02__header.ci"
#include "lib__03.ci"
#include "lib__04__string_stack.ci"
#include "lib__05__error_state.ci"
#include "lib__06__exception.ci"

#define PREFIX anime
#define CDIR ".."
#define HDIR "../../include"
#define CONCAT(s,t) s ## t

#ifndef STRINGIFY
#define STRINGIFY(s) STRINGIFY_AUX(s)
#define STRINGIFY_AUX(s) #s
#endif 

#define BYTELEN(s)   (sizeof(s)) 
#define ARRAYLEN(s)  (sizeof(s)/sizeof(*s)) 
#define ARRAY_SIZE    ARRAYLEN 
//#define STRLEN(s)  (ARRAYLEN(s)-1) 
// Beware of a string like "bob\0and\0mary", with which the preprocessor STRLEN will never behave like the compile-one (12 vs 3). 
// Therefore this one is kind of more accurate. 




enum booleen {faux = 0, vrai = -1};
typedef enum booleen booleen;



#define ASSERT_COMPILE(a) { int tab[((a) ? 1 : (-1))]; }; 




extern FILE * yyanimein;
extern FILE * yyanimeout;

extern  int anime_get_nb_lignes(void);
extern  int anime_get_nb_chars(void);
extern  int anime_get_nb_chars_tot(void);
extern  int anime_get_yyleng(void);
extern  char * anime_get_yytext(void);
extern void anime_restart_lexer(void);

extern int yyanimeparse(void);

extern int yyanimelex(void);
extern void yyanimerestart(FILE *new_file);

//extern int memnbelts;
extern void anime_parser_reset(void);


#define pi 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068 
#define e 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427 



extern FILE * yyanimein;
extern FILE * yyanimeout;
#define stderr_FILE stderr

#define BIGLIB_STRING(s) BIGLIB_STRINGX(s)
#define BIGLIB_STRINGX(s) #s

#define anime_mess(...)							\
  fprintf(yyanimeout == NULL ? stderr_FILE : yyanimeout, "ANIME_DESCRIPTION: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": "  __VA_ARGS__); 
//putc('\n', yyanimeout); 
//#define anime_err(format_mess,...)  fprintf(yyanimeout, "ERREUR: " "ANIME_DESCRIPTION: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " __FUNC__ ": " format_mess "\n", __VA_ARGS__);
#define anime_err(...)							\
  if (!yyanimeout) fprintf(yyanimeout , "ERREUR: " "ANIME_DESCRIPTION: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__) ; \
  fprintf(                 stderr_FILE,            "ANIME_DESCRIPTION: " __FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__func__) ": " __VA_ARGS__); 
  //putc('\n', yyanimeout); 
#define message anime_mess 

#define MALLOC_BZERO(ctype_t,this) ctype_t * this = NULL; this = (ctype_t *) malloc(sizeof(*this)); bzero(this, sizeof(*this)); 



struct anime_t;
extern struct anime_t * yyanime_global_objet_being_filled_up_while_parsing;



#ifndef min 
# define min(a,b) (((a)<(b))?(a):(b)) 
#endif 
#ifndef MIN 
# define MIN min 
#endif 

#ifndef max 
# define max(a,b) (((a)>(b))?(a):(b)) 
#endif 
#ifndef MAX 
# define MAX max 
#endif 

#ifndef max3 
# define max3(a1,a2,a3) (((a3)>(a2))?(MAX((a1),(a3))):(MAX((a1),(a2)))) 
#endif 
#ifndef MAX3 
# define MAX3 max3 
#endif 

#ifndef max4 
# define max4(a1,a2,a3,a4) MAX3((a1),(a2),(((a4)>(a3))?(a4):(a3))) 
#endif 
#ifndef MAX4 
# define MAX4 max4 
#endif 

#ifndef max5 
# define max5(a1,a2,a3,a4,a5) MAX4((a1),(a2),(a3),(MAX((a4),(a5)))) 
#endif 
#ifndef MAX5 
# define MAX5 max5 
#endif 

#ifndef max6 
# define max6(a1,a2,a3,a4,a5,a6) MAX5((a1),(a2),(a3),(a4),(MAX((a5),(a6)))) 
#endif 
#ifndef MAX6 
# define MAX6 max6 
#endif 

#ifndef max7 
# define max7(a1,a2,a3,a4,a5,a6,a7) MAX6((a1),(a2),(a3),(a4),(a5),(MAX((a6),(a7)))) 
#endif 
#ifndef MAX7 
# define MAX7 max7 
#endif 

#ifndef max8
# define max8(a1,a2,a3,a4,a5,a6,a7,a8) MAX7((a1),(a2),(a3),(a4),(a5),(a6),(MAX((a7),(a8)))) 
#endif 
#ifndef MAX8 
# define MAX8 max8 
#endif 



#endif /* ANIME_GLOBAL_H */
