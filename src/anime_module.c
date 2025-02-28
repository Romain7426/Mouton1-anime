#include "anime_global.h"
#include "anime.h"
#include "anime_module.h"
#include "anime_type.h"
#include "anime_lexer_module.h"
#include "anime_syntax_module.h"

#include "anime_module_type.hi"

#include "anime_module_type.ci"
#include "anime_module_string.ci" 
#include "anime_module_subr.ci" 
//#include "anime_module_error.ci" 
#include "anime_module_print.ci" 
#include "anime_module_print_field.ci" 
#include "anime_module_consistency.ci" 
#include "anime_module_dump_and_restore.ci"
#include "anime_module_lexeme.ci"
#include "anime_generation_module.h"

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


const int8_t ANIME_LINE_LEN_MAX__compiled_value = ANIME_LINE_LEN_MAX; 










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
  int_anime_error_t error_id; 
  goto label__body; 

#if 0
 label__error__input_error: { 
    this -> error_id = ANIME__TOKEN__INPUT__ERROR; 
    snprintf(this -> error_str, this -> error_size, "Error while initializing input buffer for tokenizing"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
#endif
  
  
 label__body: { 
    this -> filename = anime__string_stack__push_lookup(this, input_name); 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[LEXEMES]" "\n"); }; 
    error_id = anime__lexer__fill_from_fd(this, input_fd); 
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { anime__lexeme__print_all(this, this -> stdlog_d); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[STRUCTURE]" "\n"); }; 
    error_id = anime__syntax__structure_check_and_fill(this, /*stdwarning_d*/stduser_d, /*stderror_d*/stduser_d); 
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Reconstruction de la structure: réalisée" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Cohérence de la structure: vérifiée" "\n"); }; 
    if (this -> stdlog_d > 0) { anime__syntax__print(this, this -> stdlog_d); }; 

    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[EXPRESSION -> SYNTAXE]" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Pour commencer, nous devons déterminer l'arité des symboles d'addition et de soustraction (unaire ou binaire?)." "\n"); }; 
    error_id = anime__syntax_expr__arity__compute(this);
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Arités calculées" "\n"); }; 
    error_id = anime__syntax_expr__check_syntax(this); 
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Chaque expression est correctement écrite." "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> // Pour le moment, cette fonction ne détecte pas:  MaSSe := 240. (* +) 1;" "\n"); }; 
    if (true) { dputs(STDERR_FILENO, "---> // Pour le moment, cette fonction ne détecte pas:  MaSSe := 240. (* +) 1;" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> ." "\n"); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[NOMS DES CHAMPS]" "\n"); }; 
    error_id = anime__generation__field_names__compute(this); 
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Noms des champs: calculés" "\n"); }; 
    
    this -> filled_huh = 2; // RL: À supprimer. 
    error_id = anime__post_syntax__consistency_check(this, stduser_d); 
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Absence d’incohérence entre les noms des champs: vérifiée" "\n"); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[VALEURS DES CHAMPS]" "\n"); }; 
    error_id = anime__generation__field_values__compute(this); 
    if (error_id != ANIME__OK) { return error_id; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Valeurs des champs: calculées" "\n"); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[TERMINÉ]" "\n"); }; 
    if (this -> stdlog_d > 0) { anime__print_d(this, this -> stdlog_d); }; 
    
    return error_id; 
  };   
    
}; 


void anime__check_and_assert(const int8_t debug_print_huh, const int stddebug_d) { 
  if (ANIME_BYTESIZE < anime_bytesize_actual) { 
    if (debug_print_huh) { 
      dprintf(stddebug_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s>()>}: anime_bytesize: %d" "\n",  __func__, (int) ANIME_BYTESIZE); 
      dprintf(stddebug_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s>()>}: anime_bytesize_actual: %d" "\n",  __func__, (int) anime_bytesize_actual); 
    }; 
    assert(false); 
  }; 

  assert(ANIME_LINE_LEN_MAX == ANIME_LINE_LEN_MAX__compiled_value); 

  assert(ANIME_VERSION_MAJOR == ANIME_VERSION_MAJOR__compiled_value); 
  assert(ANIME_VERSION_MINOR <= ANIME_VERSION_MINOR__compiled_value); 
  //assert(ANIME_VERSION_REVISION <= ANIME_VERSION_REVISION__compiled_value); 


  anime__lexer__check_and_assert(); 
}; 



#define ANIME__ERROR__C
#define EXTERN extern
#include "anime_module_error.ci"
#undef  EXTERN
#undef  ANIME__ERROR__C
