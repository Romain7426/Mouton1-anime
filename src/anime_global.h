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
#include <signal.h> 
#include "lib__02__header.ci"
#include "lib__10__local_alloca.ci"
#include "lib__03.ci"
#include "lib__04__string_stack.ci"
#include "lib__05__error_state.ci"
#include "lib__06__exception.ci"

#define BUFFERED_OUTSTREAM__H 
#include "lib__07__buffered_outstream.ci"
#undef  BUFFERED_OUTSTREAM__H 

#include "lib__08__cstring.ci"
#include "lib__09__write_string.ci"
#include "lib__10__local_alloca.ci"

#define BUFFER_TO_FD__H 
#include "lib__11__buffer_to_fd.ci"
#undef  BUFFER_TO_FD__H 


#define PREFIX anime
//#define CDIR ".."
//#define HDIR "../../include"

#define LANG_ID 1
#define LANG_ID_FRA 1
#define LANG_ID_ENG 2
#define LANG(str_fra,str_eng) ((LANG_ID == LANG_ID_ENG) ? (str_eng) : (str_fra))

#define MALLOC_BZERO(ctype_t,this) ctype_t * this = NULL; this = (ctype_t *) malloc(sizeof(*this)); bzero(this, sizeof(*this)); 


typedef int8_t bool_t; 


enum { ANIME__EXPRESSION_NESTEDNESS_MAX = 16 }; 
extern const uint8_t ANIME__EXPRESSION_NESTEDNESS_MAX__compiled_value; 

// Length in tokens (it means we cannot analyze expressions longer than that). 
enum { ANIME__LONGEST_INFIX_EXPRESSION = 64 }; // 2^6 = 64 — therefore, it means roughly a six-height tree (on average). 
extern const uint8_t ANIME__LONGEST_INFIX_EXPRESSION__compiled_value; 

extern const int16_t anime_t_sizeof;


#endif /* ANIME_GLOBAL_H */
