#include "anime_global.h"
#include "anime.h"
#include "anime_type.h"
#include "anime_lexer.h"
#include "anime_token.h"
#include "anime_token_input_buffering.h"
#include "anime_token_parser.h"
//#include "anime_tree.h"
//#include "anime_tree_parser.h"
//#include "anime_data_generation_001_from_tokens.h"
//#include "anime_data_generation_002_from_trees.h"
#include "anime_data_generation_003_from_syntax_filtering.h"

#include "anime_module_string.ci" 
#include "anime_module_subr.ci" 
#include "anime_module_error.ci" 
#include "anime_module_print.ci" 
#include "anime_module_print_field.ci" 
#include "anime_module_consistency.ci" 
#include "anime_module_dump_and_restore.ci"

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
#define PROGRAM_COPYRIGHT_YEAR2 "2024"
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
ASSERT_COMPILE__TOPLEVEL(ANIME_BYTESIZE_ACTUAL <= ANIME_BYTESIZE); 

const int8_t ANIME_LINE_LEN_MAX__compiled_value = ANIME_LINE_LEN_MAX; 


anime_t * anime__make(const int stdlog_d) {  
  MALLOC_BZERO(anime_t,this); 
  anime__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
};  

anime_t * anime__make_r(anime_t * this, const int stdlog_d) { 
  bzero(this, sizeof(*this)); 
  
  this -> this_bytesize = ENDIANNESS__NATIVE_TO_LITTLE__UINT32(sizeof(*this)); 
  this -> this_typename_bytesize = sizeof(this -> this_typename); 
  strlcpy(this -> this_typename, "anime_t", sizeof(this -> this_typename)); 
  this -> version_major    = ANIME_VERSION_MAJOR; 
  this -> version_minor    = ANIME_VERSION_MINOR; 
  this -> version_revision = ANIME_VERSION_REVISION; 
  this -> endianness_flag  = ANIME__ENDIANNESS_NATIVE; 
  
  this -> stdlog_d = stdlog_d; 
  this -> error_size = ANIME__ERROR_BUFFER_SIZE; 

  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb = 1; 
  this -> copyright = anime__string_stack__push_nolookup(this, anime_copyright); 

  this -> lexeme_value_stack[0] = '\0';
  this -> lexeme_value_stack__size = ANIME__LEXEME_VALUE_STACK_SIZE; 
  this -> lexeme_value_stack__nb = 1; 

  this -> lexeme_stack__size = ANIME__LEXEME_STACK_SIZE; 
  this -> lexeme_stack__nb   = 0; 

  this -> actions_size = ANIME_ACTIONS_SIZE; 
  this -> actions_nb   = 0; 
  this -> events_size  = ANIME_EVENTS_SIZE;
  this -> events_nb    = 0; 
  this -> membres_size = ANIME_MEMBRES_SIZE; 
  this -> membres_nb   = 0; 
  this -> racines_size = ANIME_RACINES_SIZE; 
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







const char *      anime__filename_get      (const anime_t * this) { return anime__string_stack__get(this, this -> filename); }; 
const char *      anime__copyright_get     (const anime_t * this) { return anime__string_stack__get(this, this -> copyright); }; 
int_anime_error_t anime__error_id_get      (const anime_t * this) { return this -> error_id; }; 
const char *      anime__error_cstr_get    (const anime_t * this) { return this -> error_str; }; 
float             anime__choc_longueur__get(const anime_t * this) { return this -> choc_longueur; }; 
float             anime__choc_largeur__get (const anime_t * this) { return this -> choc_largeur; }; 
float             anime__choc_hauteur__get (const anime_t * this) { return this -> choc_hauteur; }; 
float             anime__masse__get        (const anime_t * this) { return this -> masse; }; 
int16_t           anime__vie__get          (const anime_t * this) { return this -> vie; }; 
int8_t            anime__invincible__get   (const anime_t * this) { return this -> invincible; }; 
int8_t            anime__hostile__get      (const anime_t * this) { return this -> hostile; }; 


#define ANIME__ARRAY_GET__BODY(field_array,field_nb,field_i) { if (0 > field_i) return NULL; if (this -> field_nb <= field_i) return NULL; return anime__string_stack__get(this, this -> field_array[field_i]); } 

int8_t       anime__actions_nb__get                  (const anime_t * this) { return this -> actions_nb; }; 
const char * anime__actions_nom__get                 (const anime_t * this, const int8_t action_i) ANIME__ARRAY_GET__BODY(actions_array_nom,actions_nb,action_i); 
const char * anime__actions_affichage__get           (const anime_t * this, const int8_t action_i) ANIME__ARRAY_GET__BODY(actions_array_affichage,actions_nb,action_i); 
const char * anime__actions_icone__get               (const anime_t * this, const int8_t action_i) ANIME__ARRAY_GET__BODY(actions_array_icone,actions_nb,action_i); 
const char * anime__actions_gestionnaire_fichier__get(const anime_t * this, const int8_t action_i) ANIME__ARRAY_GET__BODY(actions_array_gestionnaire_fichier,actions_nb,action_i); 
const char * anime__actions_gestionnaire_proc__get   (const anime_t * this, const int8_t action_i) ANIME__ARRAY_GET__BODY(actions_array_gestionnaire_proc,actions_nb,action_i); 

int8_t       anime__events_nb__get                     (const anime_t * this) { return this -> events_nb; }; 
const char * anime__events_nom__get                    (const anime_t * this, const int8_t event_i) ANIME__ARRAY_GET__BODY(events_array_nom,events_nb,event_i); 
const char * anime__events_genere_type__get            (const anime_t * this, const int8_t event_i) ANIME__ARRAY_GET__BODY(events_array_genere_type,events_nb,event_i); 
const char * anime__events_genere_code_fichier__get    (const anime_t * this, const int8_t event_i) ANIME__ARRAY_GET__BODY(events_array_genere_code_fichier,events_nb,event_i); 
const char * anime__events_genere_code_proc__get       (const anime_t * this, const int8_t event_i) ANIME__ARRAY_GET__BODY(events_array_genere_code_proc,events_nb,event_i); 
const char * anime__events_traitement_code_fichier__get(const anime_t * this, const int8_t event_i) ANIME__ARRAY_GET__BODY(events_array_traitement_code_fichier,events_nb,event_i); 
const char * anime__events_traitement_code_proc__get   (const anime_t * this, const int8_t event_i) ANIME__ARRAY_GET__BODY(events_array_traitement_code_proc,events_nb,event_i); 

int8_t       anime__membres_nb__get         (const anime_t * this) { return this -> membres_nb; }; 
const char * anime__membres_nom__get        (const anime_t * this, const int8_t membre_i) ANIME__ARRAY_GET__BODY(membres_nom,membres_nb,membre_i); 
const char * anime__membres_image__get      (const anime_t * this, const int8_t membre_i) ANIME__ARRAY_GET__BODY(membres_image,membres_nb,membre_i); 
const char * anime__membres_largeur__get    (const anime_t * this, const int8_t membre_i) ANIME__ARRAY_GET__BODY(membres_largeur,membres_nb,membre_i); 
const char * anime__membres_hauteur__get    (const anime_t * this, const int8_t membre_i) ANIME__ARRAY_GET__BODY(membres_hauteur,membres_nb,membre_i); 
const char * anime__membres_angle_max_y__get(const anime_t * this, const int8_t membre_i) ANIME__ARRAY_GET__BODY(membres_angle_max_y,membres_nb,membre_i); 

int8_t       anime__racines_nb__get     (const anime_t * this) { return this -> racines_nb; }; 
const char * anime__racines_qui__get    (const anime_t * this, const int8_t racine_i) ANIME__ARRAY_GET__BODY(racines_qui,racines_nb,racine_i); 
const char * anime__racines_x__get      (const anime_t * this, const int8_t racine_i) ANIME__ARRAY_GET__BODY(racines_x,racines_nb,racine_i); 
const char * anime__racines_y__get      (const anime_t * this, const int8_t racine_i) ANIME__ARRAY_GET__BODY(racines_y,racines_nb,racine_i); 
const char * anime__racines_z__get      (const anime_t * this, const int8_t racine_i) ANIME__ARRAY_GET__BODY(racines_z,racines_nb,racine_i); 
const char * anime__racines_angle_y__get(const anime_t * this, const int8_t racine_i) ANIME__ARRAY_GET__BODY(racines_angle_y,racines_nb,racine_i); 

#undef ANIME__EVENTARRAY_GET__BODY




int8_t anime__actions_push(anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc) {  
  if (ANIME_ACTIONS_SIZE <= this -> actions_nb) return -1; 
  const int8_t action_i = this -> actions_nb; 
  this -> actions_array_nom                 [action_i] = anime__string_stack__push_lookup(this, nom); 
  this -> actions_array_affichage           [action_i] = anime__string_stack__push_lookup(this, affichage); 
  this -> actions_array_icone               [action_i] = anime__string_stack__push_lookup(this, icone); 
  this -> actions_array_gestionnaire_fichier[action_i] = anime__string_stack__push_lookup(this, gestionnaire_fichier); 
  this -> actions_array_gestionnaire_proc   [action_i] = anime__string_stack__push_lookup(this, gestionnaire_proc); 
  this -> actions_nb++; 
  return action_i; 
};  

int8_t anime__events_push(anime_t * this, const char * events_nom, const int8_t events_genere_type, const char * events_genere_code_fichier, const char * events_genere_code_proc, const char * events_traitement_fichier, const char * events_traitement_proc) {  
  if (ANIME_EVENTS_SIZE <= this -> events_nb) return -1; 
  const int8_t event_i = this -> events_nb; 
  this -> events_array_nom                    [event_i] = anime__string_stack__push_lookup(this, events_nom); 
  this -> events_array_genere_type            [event_i] = events_genere_type; 
  this -> events_array_genere_code_fichier    [event_i] = anime__string_stack__push_lookup(this, events_genere_code_fichier); 
  this -> events_array_genere_code_proc       [event_i] = anime__string_stack__push_lookup(this, events_genere_code_proc); 
  this -> events_array_traitement_code_fichier[event_i] = anime__string_stack__push_lookup(this, events_traitement_fichier); 
  this -> events_array_traitement_code_proc   [event_i] = anime__string_stack__push_lookup(this, events_traitement_proc); 
  this -> events_nb++; 
  return event_i; 
};  

int8_t anime__membres_push(anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y) {  
  if (ANIME_MEMBRES_SIZE <= this -> membres_nb) return -1; 
  const int8_t membre_i = this -> membres_nb; 
  this -> membres_nom        [membre_i] = anime__string_stack__push_lookup(this, nom); 
  this -> membres_image      [membre_i] = anime__string_stack__push_lookup(this, image); 
  this -> membres_largeur    [membre_i] = largeur; 
  this -> membres_hauteur    [membre_i] = hauteur; 
  this -> membres_angle_max_y[membre_i] = angle_max_y; 
  this -> membres_nb++; 
  return membre_i; 
};  

int8_t anime__racines_push(anime_t * this, const char * qui, const float x, const float y, const float z, const float angle_y) {  
  if (ANIME_RACINES_SIZE <= this -> racines_nb) return -1; 
  const int8_t racine_i = this -> racines_nb; 
  this -> racines_qui    [racine_i] = anime__string_stack__push_lookup(this, qui); 
  this -> racines_x      [racine_i] = x; 
  this -> racines_y      [racine_i] = y; 
  this -> racines_z      [racine_i] = z; 
  this -> racines_angle_y[racine_i] = angle_y; 
  this -> racines_nb++; 
  return racine_i; 
}; 


int8_t anime__membres_lookup(const anime_t * this, const char * nom) {  
  for (int membre_i = 0; membre_i < this -> membres_nb; membre_i++) { 
    if (0 == strcmp(nom, anime__string_stack__get(this, this -> membres_nom[membre_i]))) return membre_i; 
  }; 
  return -1; 
};  
 













int_anime_error_t anime__fill_from_file(anime_t * this, const char * filepathname, const int stduser_d) { 
  assert(false); 
  return 0; 
};

int_anime_error_t anime__fill_from_buffer(anime_t * this, const char * input_name, const char * buffer, const int16_t buffer_bytesize, const int stduser_d) { 
  goto label__body; 

label__error__cannot_make_pipe: { 
    this -> error_id = ANIME__TOKEN_PARSER__CANNOT_MAKE_PIPE; 
    return this -> error_id; 
  }; 

label__pipe_buffer_size_ok: { 
    int buffer_pipe[2]; // RL: [0] is output (read end), [1] is input (write end) 
    if (-1 == pipe(buffer_pipe)) goto label__error__cannot_make_pipe; 
    write(buffer_pipe[1], buffer, buffer_bytesize); 
    this -> error_id = anime__fill_from_fd(this, input_name, buffer_pipe[0], stduser_d); 
    close(buffer_pipe[0]);
    close(buffer_pipe[1]);
    return this -> error_id;
  }; 

 label__pipe_buffer_size_is_too_small: { 
    const int my_buffer_fd = buffer_to_fd__open(buffer, buffer_bytesize); 
    if (0 > my_buffer_fd) goto label__error__cannot_make_pipe; 
    this -> error_id = anime__fill_from_fd(this, input_name, my_buffer_fd, stduser_d); 
    buffer_to_fd__close(my_buffer_fd); 
    return this -> error_id;
  }; 

label__body: {   
    if (UINTMAX_C(PIPEBUFFERSIZE) <= (uintmax_t)buffer_bytesize) goto label__pipe_buffer_size_ok; 
    goto label__pipe_buffer_size_is_too_small; 
  }; 
}; 

int_anime_error_t anime__fill_from_fd(anime_t * this, const char * input_name, const int input_fd, const int stduser_d) { 
  LOCAL_ALLOCA__DECLARE(uint16_t,UINT16_MAX); 
  int_anime_error_t         error_id; 
  anime_token_input_env_t   input_env[1]; 
  //dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
  char                    * token_env_b = LOCAL_ALLOCA(anime_token_env__sizeof); 
  anime_token_env_t       * token_env; 
  int input_i = -1; 
  goto label__body; 

 error_label__input_error: { 
    this -> error_id = ANIME__TOKEN__INPUT__ERROR; 
    snprintf(this -> error_str, this -> error_size, "Error while initializing input buffer for tokenizing: %d", input_i); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  

 label__body: { 
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
  
    //const int input_i = anime_token_input__stack_push__filedes(input_env, input_fd, input_name); 
    input_i = anime_token_input__stack_push__filedes(input_env, input_fd, input_name); 
    if (input_i < 0) goto error_label__input_error; 
  
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



