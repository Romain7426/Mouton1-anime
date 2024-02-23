#ifndef ANIME_H
#define ANIME_H

enum { ANIME_VERSION_MAJOR    = 3 }; 
enum { ANIME_VERSION_MINOR    = 0 }; 
enum { ANIME_VERSION_REVISION = 1 }; 
extern const uint8_t ANIME_VERSION_MAJOR__compiled_value; 
extern const uint8_t ANIME_VERSION_MINOR__compiled_value; 
extern const uint8_t ANIME_VERSION_REVISION__compiled_value; 

extern const char       anime_version[]; 
extern const uint16_t   anime_copyright__strlen; 
extern const char     * anime_version__get(void); 
extern void             anime_version__print(const int stduser_d); 

extern const char       anime_copyright[]; 
extern const uint16_t   anime_copyright__strlen; 
extern const char     * anime_copyright__get(void); 
extern void             anime_copyright__print(const int stduser_d); 

extern const char       anime_url[]; 
extern const uint16_t   anime_url__strlen; 
extern const char     * anime_url__get(void); 
extern void             anime_url__print(const int stduser_d); 

extern const char       anime_example[]; 
extern const uint16_t   anime_example__strlen; 
extern const char     * anime_example__get(void); 
extern void             anime_example__print(const int stduser_d); 


enum {               anime_bytesize = (1 << 14) }; 
extern const int16_t anime_bytesize_actual; 

static void anime__check_and_assert(const int8_t debug_print_huh, const int stddebug_d); 





// ERROR CODES & RETURN VALUES 
// See «man 2 wait» & «man 3 exit». 
// The exit value is gotten by the parent using the macro WEXITSTATUS(…), 
// which returns the lower 8 bits of the exit status. All other bits are 
// used as status information on the process. 
// The WEXITSTATUS(…) value is gotten from the lower 8 bits of the exit 
// call. 
// The system, the environment, can interpret the WEXITSTATUS(…) 8-bit value as 
// signed or unsigned — that depends. Thus: 
//  - Only the 0-127 range is sure. 
//  - The 128-255 range (the -128_-1 range) could be interpreted as positive or negative. 
// However, in the program, the sign interpretation of these values depends only 
// on the type declaration, «int8_t error_id» or «uint8_t error_id» — so they are safe. 
enum { 
  ANIME__OK = 0, 
  // Unspecified 
  ANIME__ERROR_GENERIC = INT8_MIN, 
  // Errors 
  ANIME__STRCOPY = INT8_MIN + 1, 
  ANIME__STRING_STACK_TOO_SMALL, 
  ANIME__FD_NEG, 
  ANIME__FDOPEN, 
  ANIME__NULL_FIELD_NAME, 
  ANIME__UNKNOWN_FIELD, 
  ANIME__INDEX_OF_OUT_BOUNDS,
  ANIME__NULL_ERROR_ID_R, 
  ANIME__ERROR_SIZE_LOWER_THAN_1, 
  ANIME__NULL_INPUT_ENV, 
  ANIME__NULL_TOKEN_ENV, 
  ANIME__TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM, 
  ANIME__TOKEN_PARSER__TOKEN_MATCHES_NO_PATTERN, 
  ANIME__TOKEN_PARSER__ERROR_TOKEN, 
  ANIME__TOKEN_PARSER__STACK_OVERFLOW, 
  ANIME__DATA_GENERATION__NULL_SYNTAX_FILTERING, 
  ANIME__DATA_GENERATION__NULL_TOKEN_ENV, 
  ANIME__DATA_GENERATION__NULL_ANIME_DATA, 
  ANIME__DATA_GENERATION__NULL_FLOATVAL_R, 
  ANIME__DATA_GENERATION__NULL_INTVAL_R, 
  ANIME__DATA_GENERATION__NULL_ERROR_ID_R, 
  ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1, 
  ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS, 
  ANIME__DATA_GENERATION__TOO_MANY_TOKENS, 
  ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE, 
  ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE, 
  ANIME__DATA_GENERATION__NULL_TREE_ENV, 
  ANIME__DATA_GENERATION__TREE_ENV__EMPTY,
  ANIME__DATA_GENERATION__TREE_ENV__BEING_FILLED,
  ANIME__DATA_GENERATION__TREE_ENV__NOT_FILLED,
  ANIME__DATA_GENERATION__NOT_ENOUGH_TREES, 
  ANIME__DATA_GENERATION__TREE__WRONG_TREE_TYPE,
  ANIME__DATA_GENERATION__MISSING_PHYSIQUE_SECTION, 
  ANIME__DATA_GENERATION__MISSING_GAMEPLAY_SECTION, 
  ANIME__DATA_GENERATION__MISSING_GRAPHIQUE_SECTION, 
  ANIME__DATA_GENERATION__STACK_OVERFLOW, 
  ANIME__DATA_GENERATION__STACK_UNDERFLOW, 
  ANIME__DATA_GENERATION__STACK_UNEXPECTED_TOKEN, 
  ANIME__DATA_GENERATION__STACK_TOO_MANY_ITEMS, 
  ANIME__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS, 
  ANIME__DATA_GENERATION__MEMBRES_OVERFLOW, 
  ANIME__DATA_GENERATION__RACINES_OVERFLOW, 
  ANIME__TREE__NO_SPACE_LEFT, 
  ANIME__TREE__WRONG_ADDRESS, 
  ANIME__SYNTAX_FILTERING__NULL_THIS, 
  ANIME__SYNTAX_FILTERING__NULL_TOKEN_ENV, 
  ANIME__SYNTAX_FILTERING__NULL_TOKEN_I, 
  ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_TOO_SMALL, 
  ANIME__SYNTAX_FILTERING__PARENTHESIS_STACK_TOO_SMALL, 
  ANIME__SYNTAX_FILTERING__MISSING_CLOSING_PARENTHESIS, 
  ANIME__SYNTAX_FILTERING__MISSING_OPENING_PARENTHESIS, 
  ANIME__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS, 
  ANIME__SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS, 
  ANIME__SYNTAX_FILTERING__NOT_AN_CLOSING_PARENTHESIS, 
  ANIME__SYNTAX_FILTERING__CANNOT_SKIP_TO_CLOSING_PARENTHESIS_IN_LALR_MODE, 
  ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_OUT_OF_BOUND, 
  ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID, 
  ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_EOF, 
  ANIME__SYNTAX_FILTERING__LAST_TOKEN_SHOULD_BE_EOF, 
  ANIME__SYNTAX_FILTERING__LALR_MODE_ALREADY_SET, 
  ANIME__MAIN__OPTIONS__PARSING_ERROR, 
  ANIME__MAIN__OPTIONS__UNKNOWN, 
  ANIME__MAIN__OPTIONS__EXIT_QUICK, 
  ANIME__MAIN__CANNOT_OPEN_INPUT_FILE, 
  ANIME__TOKEN__PARSER__ERROR, 
  ANIME__TOKEN__INPUT__ERROR, 
  // Warnings 
  ANIME__NULL_STRUCT = 1, 
  ANIME__EMPTY_STRUCTURE, 
  ANIME__FILLING_NOT_COMPLETED, 
  ANIME__HAS_BREAKING_UNCONSISTENCIES, 
  ANIME__HAS_NON_BREAKING_UNCONSISTENCIES, 
  ANIME__SYNTAX_FILTERING__TOKEN_ENV_HAS_ZERO_TOKEN, 
}; 

typedef int8_t int_anime_error_t;
extern const char * int_anime_error__get_cstr(const int_anime_error_t error_id); 


struct anime_t; 
typedef struct anime_t anime_t; 


extern void         anime__print_f         (const anime_t * this, FILE * out_stream); 
extern void         anime__print_d         (const anime_t * this, const int fd); 
extern anime_t *    anime__make            (const int stdlog_d); 
extern anime_t *    anime__make_r          (anime_t * this, const int stdlog_d); 
extern anime_t *    anime__make_b          (char * anime_buffer, const int16_t anime_buffer_bytesize, int16_t * anime_buffer_bytesize_used_r, const int stdlog_d); 
extern void         anime__delete          (anime_t * this);  
extern void         anime__delete_r        (anime_t * this);  
extern void         anime__delete_b        (anime_t * this);  
extern void         anime__bzero           (anime_t * this);  
extern const char * anime__strcopy         (anime_t * this, const char * cstr); 

extern const char *             anime__filename_get(const anime_t * this); 
extern       int_anime_error_t  anime__error_id_get(const anime_t * this); 
extern const char *             anime__error_cstr_get(const anime_t * this); 


extern void anime__actions_push  (      anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc); 
extern void anime__events_push   (      anime_t * this, const char * events_nom, const int events_genere_type, const char * events_genere_code_fichier, const char * events_genere_code_proc, const char * events_traitement_fichier, const char * events_traitement_proc); 
extern void anime__membres_push  (      anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y); 
extern int  anime__membres_lookup(const anime_t * this, const char * nom); 
extern void anime__racines_push  (      anime_t * this, const char * qui, const float x, const float y, const float z, const float angle_y); 

extern int_anime_error_t anime__consistency_check(anime_t * this, const int stduser_d); 

extern int_anime_error_t anime__fill_from_file(anime_t * this, const char * input_name, const int input_fd, const int stduser_d); 
extern int_anime_error_t anime__fill_from_buffer(anime_t * this, const char * input_name, const char * buffer, const int16_t buffer_bytesize, const int stduser_d); 

extern int_anime_error_t anime__print_field_value_by_name(const anime_t * this, const char * field_name, const int stdprint_d, const int stduser_d, int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str); 



extern const char * anime__convert_token_cstring_to_regular_string(anime_t * this, const char * cstr); 


static void anime__check_and_assert(const int8_t debug_print_huh, const int stddebug_d) { 
  if (anime_bytesize < anime_bytesize_actual) { 
    if (debug_print_huh) { 
      dprintf(stddebug_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s>()>}: anime_bytesize: %d" "\n",  __func__, (int) anime_bytesize); 
      dprintf(stddebug_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s>()>}: anime_bytesize_actual: %d" "\n",  __func__, (int) anime_bytesize_actual); 
    }; 
    assert(anime_bytesize >= anime_bytesize_actual); 
  }; 
  
  assert(ANIME_VERSION_MAJOR == ANIME_VERSION_MAJOR__compiled_value); 
  assert(ANIME_VERSION_MINOR <= ANIME_VERSION_MINOR__compiled_value); 
  //assert(ANIME_VERSION_REVISION <= ANIME_VERSION_REVISION__compiled_value); 
}; 


#endif /* ANIME_H */
