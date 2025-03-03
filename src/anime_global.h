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



typedef int8_t bool_t; 





#define DISPLAY_TRACE(__stdlog_d__,__error_id__) {			\
    enum { TRACE_BYTESIZE = 1 << 11 };					\
    char trace[TRACE_BYTESIZE];						\
    snprintf(trace, TRACE_BYTESIZE, "{" __FILE__ ":%d:<%s()>}: " "%s" "\n", error_sub__line, __func__, int_anime_error__get_cstr(__error_id__)); \
    if (__stdlog_d__ > 0) { dputs(__stdlog_d__, trace); };		\
  };									\
  /* END OF MACRO*/ 


#define RAISE_ERROR(__stdlog_d__,__error_id__) { error_id = (__error_id__); error_sub__line = __LINE__; error_stdlog_d = (__stdlog_d__); goto label__error__raise; }; 

#define RAISE_ERROR_MSG(__stdlog_d__,__error_id__,__error_msg__) { error_id = (__error_id__); error_sub__line = __LINE__; error_stdlog_d = (__stdlog_d__); error_msg = (__error_msg__); goto label__error__raise; }; 

#define ERROR_RAISE RAISE_ERROR

#define label__error__sub label__error__raise 

#if 0
{
  int_anime_error_t error_id; 
  const char *      error_msg = NULL; 
  int               error_stdlog_d = -1; 
  int16_t           error_sub__line = -1; 
 label__error__raise: { 
    if (NULL != error_msg) { dputs(error_stdlog_d, error_msg); }; 
      DISPLAY_TRACE(error_stdlog_d, error_id); 
      return error_id; 
    }; 
};
#endif 



#endif /* ANIME_GLOBAL_H */
