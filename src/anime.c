#include "anime_global.h"
#include "anime.h"
#include "anime_type.h"
#include "anime_token.h"
#include "anime_token_input_buffering.h"
#include "anime_token_parser.h"
//#include "anime_tree.h"
//#include "anime_tree_parser.h"
//#include "anime_data_generation_001_from_tokens.h"
//#include "anime_data_generation_002_from_trees.h"
#include "anime_data_generation_003_from_syntax_filtering.h"

#include "anime_string.ci" 
#include "anime_subr.ci" 
#include "anime_error.ci" 
#include "anime_print.ci" 
#include "anime_print_field.ci" 
#include "anime_consistency.ci" 

const uint8_t ANIME_VERSION_MAJOR__compiled_value    = (uint8_t) ANIME_VERSION_MAJOR; 
const uint8_t ANIME_VERSION_MINOR__compiled_value    = (uint8_t) ANIME_VERSION_MINOR; 
const uint8_t ANIME_VERSION_REVISION__compiled_value = (uint8_t) ANIME_VERSION_REVISION; 

const uint8_t ANIME__EXPRESSION_NESTEDNESS_MAX__compiled_value = (uint8_t) ANIME__EXPRESSION_NESTEDNESS_MAX; 
const uint8_t ANIME__LONGEST_INFIX_EXPRESSION__compiled_value  = (uint8_t) ANIME__LONGEST_INFIX_EXPRESSION; 

#define PROGRAM_NAME "Anime (lib part of ‘Mouton1’ — whose purpose is to read anime data description files into C data structures)" 
#undef  PROGRAM_NAME
#define PROGRAM_NAME "Mouton1_-_Anime" 
static const char program_name[] = PROGRAM_NAME; 
enum { program_name__cstrlen = ARRAY_SIZE(program_name) - 1 }; 
#define PROGRAM_COPYRIGHT_YEAR1 "2003"
#define PROGRAM_COPYRIGHT_YEAR2 "2023"
#define PROGRAM_URL "https://github.com/Romain7426/Mouton1-anime" 

#if 1
const char anime_copyright[] = 
"_Software_       : " PROGRAM_NAME "                                    " "\n"
"_License_        : ISC-like license                                   " "\n"
"                   https://en.wikipedia.org/wiki/ISC_license          " "\n"
"_URL_            : " PROGRAM_URL "        " "\n"
"_Copyright years_: " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " " "\n"
"_Description_    : Lib of ‘Mouton1’, whose purpose is to read anime files into structured arrays of bytes. " "\n"
"                                                                        " "\n"
"Mouton1 — Anime " "\n"
"Copyright (c) " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " " "\n"
"                                                                        " "\n"
"Permission to use, copy, modify, and distribute this software for any   " "\n"
"purpose with or without fee is hereby granted without any restrictions. " "\n"
"                                                                        " "\n"
"THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES" "\n"
"WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF        " "\n"
"MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR " "\n"
"ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES  " "\n"
"WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN   " "\n"
"ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF " "\n"
"OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.          " "\n"
"                                                                        " "\n"
"NB: We do not care of what you do with this code as long as             " "\n"
"    you do not prevent us nor others from using it.                     " "\n"
;
#else 
const char anime_copyright[] = 
"_Software_: " PROGRAM_NAME "\n"
"_License_: " "ISC License" "\n"
"_URL_: " PROGRAM_URL "\n"
"_Copyright years_: " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 "\n"
"" "\n"
PROGRAM_NAME "\n"
"Copyright (c) " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " " "\n"
"All rights reserved." "\n"
"" "\n"
"Redistribution and use in source and binary forms, with or without" "\n"
"modification, are permitted provided that the following conditions" "\n"
"are met:" "\n"
"1. Redistributions of source code must retain the above copyright" "\n"
"   notice, this list of conditions and the following disclaimer." "\n"
"2. Redistributions in binary form must reproduce the above copyright" "\n"
"   notice, this list of conditions and the following disclaimer in the" "\n"
"   documentation and/or other materials provided with the distribution." "\n"
"" "\n"
"THIS SOFTWARE IS PROVIDED BY THE _AUTHORS_ ``AS IS'' AND ANY EXPRESS" "\n"
"OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED" "\n"
"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE" "\n"
"DISCLAIMED. IN NO EVENT SHALL THE _AUTHORS_ BE LIABLE FOR ANY DIRECT," "\n"
"INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES" "\n"
"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR" "\n"
"SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)" "\n"
"HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT," "\n"
"STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING" "\n"
"IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE" "\n"
"POSSIBILITY OF SUCH DAMAGE." "\n" 
"" "\n" 
"NB: We do not care of what you do with this code as long as " "\n" 
"    you do not prevent us nor others from using it." "\n" 
;
#endif
enum {           anime_copyright__strlen__const_value = ARRAY_SIZE(anime_copyright) - 1 }; // environ 1570 
const uint16_t   anime_copyright__strlen = (uint16_t) anime_copyright__strlen__const_value; 
const char     * anime_copyright__get(void) { return anime_copyright; }; 
void             anime_copyright__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_copyright, anime_copyright__strlen__const_value); if ('\n' != *(anime_copyright + anime_copyright__strlen__const_value - 1)) write(stduser_d, "\n", 1); }; }; 

const char       anime_url[] = PROGRAM_URL; 
enum {           anime_url__strlen__const_value = ARRAY_SIZE(anime_url) - 1 }; 
const uint16_t   anime_url__strlen = anime_url__strlen__const_value; 
const char     * anime_url__get(void) { return anime_url; }; 
void             anime_url__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_url, anime_url__strlen__const_value); write(stduser_d, "\n", 1); }; }; 


#define DIGIT_TO_STRING(d) (			\
			    (d) == 0 ? "0" :	\
			    (d) == 1 ? "1" :	\
			    (d) == 2 ? "2" :	\
			    (d) == 3 ? "3" :	\
			    (d) == 4 ? "4" :	\
			    (d) == 5 ? "5" :	\
			    (d) == 6 ? "6" :	\
			    (d) == 7 ? "7" :	\
			    (d) == 8 ? "8" :	\
			    (d) == 9 ? "9" :	\
			    "?")

#define DIGIT_TO_CHAR(d) (((d) >= 0 && (d) <= 9) ? '0' + (d) : '?') 
    
const char       anime_version[] = { DIGIT_TO_CHAR(ANIME_VERSION_MAJOR), '.', DIGIT_TO_CHAR(ANIME_VERSION_MINOR), '.', DIGIT_TO_CHAR(ANIME_VERSION_REVISION), '\0' }; 
enum {           anime_version__strlen__const_value = ARRAY_SIZE(anime_version) - 1 }; 
const uint16_t   anime_version__strlen = anime_version__strlen__const_value; 
const char     * anime_version__get(void) { return anime_version; }; 
void             anime_version__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_version, anime_version__strlen__const_value); write(stduser_d, "\n", 1); }; };


const char       anime_example[] = 
#include "chaman.anime.ci"
; 
enum {           anime_example__strlen__const_value = ARRAY_SIZE(anime_example) - 1 }; 
const uint16_t   anime_example__strlen = anime_example__strlen__const_value; 
const char     * anime_example__get(void) { return anime_example; }; 
void             anime_example__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_example, anime_example__strlen__const_value); write(stduser_d, "\n", 1); }; }; 


enum { ANIME_BYTESIZE_ACTUAL = sizeof(anime_t) }; 
const int16_t anime_bytesize_actual = ANIME_BYTESIZE_ACTUAL; 

anime_t * anime__make(const int stdlog_d) {  
  MALLOC_BZERO(anime_t,this); 
  anime__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
};  

anime_t * anime__make_r(anime_t * this, const int stdlog_d) { 
  bzero(this, sizeof(*this)); 
  
  this -> this_bytesize = ENDIANNESS__NATIVE_TO_LITTLE__UINT16(sizeof(*this)); 
  this -> this_typename_bytesize = sizeof(this -> this_typename); 
  strlcpy(this -> this_typename, "anime_t", sizeof(this -> this_typename)); 
  this -> version_major = ANIME_VERSION_MAJOR; 
  this -> version_minor = ANIME_VERSION_MINOR; 
  this -> version_revision = ANIME_VERSION_REVISION; 
  this -> endianness_flag = ANIME__ENDIANNESS_NATIVE; 
  
  this -> stdlog_d = stdlog_d; 
  this -> error_size = ANIME__ERROR_BUFFER_SIZE; 

  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb = 1; 
  this -> copyright = anime__string_stack__push_nolookup(this, anime_copyright); 

#if 0 
  this -> lexer_stack[0] = '\0'; 
  this -> lexer_stack_nb = 1; 
#else 
  this -> lexer_lexeme_stack[0] = '\0';
  this -> lexer_lexeme_stack__size = ANIME__LEXER_LEXEME_STACK_SIZE; 
  this -> lexer_lexeme_stack__nb = 1; 

  this -> lexer_stack__size = ANIME__LEXER_STACK_SIZE; 
  this -> lexer_stack__nb   = 0; 
#endif 

  this -> actions_nb   = 0; 
  this -> events_nb    = 0; 
  this -> membres_size = anime_membres_size; 
  this -> membres_nb   = 0; 
  this -> racines_size = anime_racines_size; 
  this -> racines_nb   = 0; 
  
  return this; 
};  

anime_t * anime__make_b(char * anime_buffer, const int16_t anime_buffer_bytesize, int16_t * anime_buffer_bytesize_used_r, const int stdlog_d) { 
  if (((size_t) anime_buffer_bytesize) < (sizeof(anime_t))) return NULL; 
  anime_t * this = (anime_t *) anime_buffer; 
  anime__make_r(this, stdlog_d); 
  if (NULL != anime_buffer_bytesize_used_r) *anime_buffer_bytesize_used_r = (sizeof(anime_t)); 
  return this; 
}; 

void anime__delete_b(anime_t * this) { 
  anime__delete_r(this); 
}; 

void anime__delete_r(anime_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
}; 

void anime__delete(anime_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  anime__delete_r(this); 
  if (1 == malloced_flag) free(this); 
};  

void anime__bzero(anime_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
}; 



const char * anime__filename_get(const anime_t * this) { 
  return anime__string_stack__get(this, this -> filename); 
}; 

int_anime_error_t  anime__error_id_get(const anime_t * this) { 
  return this -> error_id; 
}; 
 
const char * anime__error_cstr_get(const anime_t * this) { 
  return this -> error_str; 
}; 








void anime__actions_push(anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc) {  
  assert(this -> actions_nb < anime_actions_size); 
  const int i = this -> actions_nb; 
  this -> actions_array_nom      [i] = anime__string_stack__push_lookup(this, nom); 
  this -> actions_array_affichage[i] = anime__string_stack__push_lookup(this, affichage); 
  this -> actions_array_icone    [i] = anime__string_stack__push_lookup(this, icone); 
  this -> actions_array_gestionnaire_fichier[i] = anime__string_stack__push_lookup(this, gestionnaire_fichier); 
  this -> actions_array_gestionnaire_proc   [i] = anime__string_stack__push_lookup(this, gestionnaire_proc); 
  this -> actions_nb++; 
};  

void anime__events_push(anime_t * this, const char * events_nom, const int events_genere_type, const char * events_genere_code_fichier, const char * events_genere_code_proc, const char * events_traitement_fichier, const char * events_traitement_proc) {  
  assert(this -> events_nb < anime_events_size); 
  const int i = this -> events_nb; 
  this -> events_array_nom[i] = anime__string_stack__push_lookup(this, events_nom); 
  this -> events_array_genere_type[i] = events_genere_type; 
  this -> events_array_genere_code_fichier[i] = anime__string_stack__push_lookup(this, events_genere_code_fichier); 
  this -> events_array_genere_code_proc[i] = anime__string_stack__push_lookup(this, events_genere_code_proc); 
  this -> events_array_traitement_code_fichier[i] = anime__string_stack__push_lookup(this, events_traitement_fichier); 
  this -> events_array_traitement_code_proc[i] = anime__string_stack__push_lookup(this, events_traitement_proc); 
  this -> events_nb++; 
};  

void anime__membres_push(anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y) {  
  assert(this -> membres_nb < anime_membres_size); 
  const int i = this -> membres_nb; 
  this -> membres_nom[i] = anime__string_stack__push_lookup(this, nom); 
  this -> membres_image[i] = anime__string_stack__push_lookup(this, image); 
  this -> membres_largeur[i] = largeur; 
  this -> membres_hauteur[i] = hauteur; 
  this -> membres_angle_max_y[i] = angle_max_y; 
  this -> membres_nb++; 
};  

int anime__membres_lookup(const anime_t * this, const char * nom) {  
  for (int i = 0; i < this -> membres_nb; i++) { 
    if (0 == strcmp(nom, anime__string_stack__get(this, this -> membres_nom[i]))) return i; 
  }; 
  return -1; 
};  
 
void anime__racines_push(anime_t * this, const char * qui, const float x, const float y, const float z, const float angle_y) {  
  assert(this -> racines_nb < anime_racines_size); 
  const int i = this -> racines_nb; 
  this -> racines_qui[i] = anime__string_stack__push_lookup(this, qui); 
  this -> racines_x[i] = x; 
  this -> racines_y[i] = y; 
  this -> racines_z[i] = z; 
  this -> racines_angle_y[i] = angle_y; 
  this -> racines_nb++; 
}; 












#if 0 
anime_t * anime__make_from_file(const char * filename, const char * log_filename) {  
  MALLOC_BZERO(anime_t,this); 
  const int retval = anime__fill_from_file(this, filename, log_filename); 
  if (retval < 0) { 
    free(this); 
    return NULL; 
  }; 
  return this; 
}; 
#endif 



//#define VLA__YES
//#define ALLOCA__YES
#define LOCAL_ALLOCA__YES

#define LOCAL_ALLOCA__DECLARE(LOCAL_ALLOCA_SIZEOF)			\
  enum { LOCAL_ALLOCA__BYTE_SIZE = (LOCAL_ALLOCA_SIZEOF) }; char local_alloca__mem[LOCAL_ALLOCA__BYTE_SIZE]; uint16_t local_alloca__left = LOCAL_ALLOCA__BYTE_SIZE; uint16_t local_alloca__used = 0; uint16_t local_alloca__requested; 

#define LOCAL_ALLOCA(REQUESTED_SIZEOF)					\
  (local_alloca__requested = (REQUESTED_SIZEOF), ((local_alloca__requested > local_alloca__left) ? NULL : (local_alloca__left -= local_alloca__requested, local_alloca__used += local_alloca__requested,  local_alloca__mem + local_alloca__used - local_alloca__requested))) 



int_anime_error_t anime__fill_from_file(anime_t * this, const char * input_name, const int input_fd, const int stduser_d) { 
  LOCAL_ALLOCA__DECLARE(UINT16_MAX); 
  int_anime_error_t         error_id; 
  anime_token_input_env_t   input_env[1]; 
  //dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
#if defined VLA__YES
  char                      token_env_b[anime_token_env__sizeof]; // For some unknown reasons, VLAs make «-fstack-protector» fail. 
#elif defined ALLOCA__YES
  char                    * token_env_b = alloca(anime_token_env__sizeof); 
#elif defined LOCAL_ALLOCA__YES
  char                    * token_env_b = LOCAL_ALLOCA(anime_token_env__sizeof); 
#endif 
  anime_token_env_t       * token_env; 

#if 0
  dputs_array(stderr_d, "TOKEN_ENV_SIZEOF = ", int_string(sizeof(token_env_b)), "\n"); 
  dputs_array(stderr_d, "TOKEN_ENV_B IS NULL HUH = ", bool_string(token_env_b == NULL), "\n"); 
  dputs_array(stderr_d, "local_alloca__requested = ", int_string(local_alloca__requested), "\n"); 
  dputs_array(stderr_d, "anime_token_env__sizeof = ", int_string(anime_token_env__sizeof), "\n"); 
  dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
  dputs_array(stderr_d, "local_alloca__used = ", int_string(local_alloca__used), "\n"); 
#endif 

  
  anime_token_input_env__make_r(input_env, this -> stdlog_d); 
  
  token_env = anime_token_env__make_b(anime_token_env__sizeof, token_env_b, NULL, this -> stdlog_d); 
  assert(NULL != token_env); 
  //dputs_array(stderr_d, "TOKEN_ENV IS NULL HUH = ", bool_string(token_env == NULL), "\n"); 
  
  this -> filename = anime__string_stack__push_lookup(this, input_name); 
  
  const int input_i = anime_token_input__stack_push__filedes(input_env, input_fd, input_name); 
  if (input_i < 0) { goto error_label__input_error; }; 
  
  error_id = anime_token__parser(token_env, input_env, input_i, &this -> error_id, this -> error_size, this -> error_str); 
  if (error_id != ANIME__OK) { return error_id; }; 
  
  if (this -> stdlog_d > 0) { anime_token__print_all_tokens(this -> stdlog_d, token_env); fflush(NULL); }; 
  
  assert(NULL != token_env); 
  assert(NULL != this); 
  error_id = anime_data_generation_003_from_syntax_filtering(token_env, this, stduser_d); 
  if (error_id != ANIME__OK) { return error_id; }; 
	
  error_id = anime__consistency_check(this, stduser_d); 
  return error_id; 
  
  
 error_label__input_error: { 
    this -> error_id = ANIME__TOKEN__INPUT__ERROR; 
    snprintf(this -> error_str, this -> error_size, "Error while initializing input buffer for tokenizing: %d", input_i); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
}; 




int_anime_error_t anime__fill_from_buffer(anime_t * this, const char * input_name, const char * buffer, const int16_t buffer_bytesize, const int stduser_d) { 
  LOCAL_ALLOCA__DECLARE(UINT16_MAX); 
  int_anime_error_t         error_id; 
  anime_token_input_env_t   input_env[1]; 
  //dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
#if defined VLA__YES
  char                      token_env_b[anime_token_env__sizeof]; // For some unknown reasons, VLAs make «-fstack-protector» fail. 
#elif defined ALLOCA__YES
  char                    * token_env_b = alloca(anime_token_env__sizeof); 
#elif defined LOCAL_ALLOCA__YES
  char                    * token_env_b = LOCAL_ALLOCA(anime_token_env__sizeof); 
#endif 
  anime_token_env_t       * token_env; 

#if 0
  dputs_array(stderr_d, "TOKEN_ENV_SIZEOF = ", int_string(sizeof(token_env_b)), "\n"); 
  dputs_array(stderr_d, "TOKEN_ENV_B IS NULL HUH = ", bool_string(token_env_b == NULL), "\n"); 
  dputs_array(stderr_d, "local_alloca__requested = ", int_string(local_alloca__requested), "\n"); 
  dputs_array(stderr_d, "anime_token_env__sizeof = ", int_string(anime_token_env__sizeof), "\n"); 
  dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
  dputs_array(stderr_d, "local_alloca__used = ", int_string(local_alloca__used), "\n"); 
#endif 

  int input_i = -1; 
  
  goto label__body; 


 error_label__input_error: { 
    this -> error_id = ANIME__TOKEN__INPUT__ERROR; 
    snprintf(this -> error_str, this -> error_size, "Error while initializing input buffer for tokenizing: %d", input_i); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  


  label__body: { 
    if (0 >= buffer_bytesize) return -1; 
  
    anime_token_input_env__make_r(input_env, this -> stdlog_d); 
    
    token_env = anime_token_env__make_b(anime_token_env__sizeof, token_env_b, NULL, this -> stdlog_d); 
    assert(NULL != token_env); 
    //dputs_array(stderr_d, "TOKEN_ENV IS NULL HUH = ", bool_string(token_env == NULL), "\n"); 
    
    this -> filename = anime__string_stack__push_lookup(this, input_name); 

    
    //const int input_i = anime_token_input__stack_push__filedes(input_env, input_fd, input_name); 
    int input_i = anime_token_input__stack_push__memory(input_env, buffer_bytesize, buffer, input_name); 
    if (input_i < 0) { goto error_label__input_error; }; 
    
    error_id = anime_token__parser(token_env, input_env, input_i, &this -> error_id, this -> error_size, this -> error_str); 
    if (error_id != ANIME__OK) { return error_id; }; 
    
    if (this -> stdlog_d > 0) { anime_token__print_all_tokens(this -> stdlog_d, token_env); fflush(NULL); }; 
    
    assert(NULL != token_env); 
    assert(NULL != this); 
    error_id = anime_data_generation_003_from_syntax_filtering(token_env, this, stduser_d); 
    if (error_id != ANIME__OK) { return error_id; }; 
    
    error_id = anime__consistency_check(this, stduser_d); 
    return error_id; 
  };
  
}; 


