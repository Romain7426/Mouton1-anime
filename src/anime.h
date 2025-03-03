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

enum {               ANIME_BYTESIZE = (1 << 14) + (1 << 13) }; 
extern const int16_t anime_bytesize_actual; 

enum { ANIME_LINE_LEN_MAX = INT8_MAX - 1 - 1 - 1 }; // \r\n\0 
extern const int8_t ANIME_LINE_LEN_MAX__compiled_value; 

extern void anime__check_and_assert(const int8_t debug_print_huh, const int stddebug_d); 





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
// 
// PCC: warning: identifier exceeds C99 5.2.4.1: 63 [ https://rgambord.github.io/c99-doc/sections/5/2/4/1/index.html ] 


//typedef int8_t int_anime_error_t;

#define ANIME__ERROR__LIST						\
  X(ANIME__OK, = 0)							\
    /* Unspecified */							\
    X(ANIME__ERROR_GENERIC, = INT8_MIN)					\
    /* Errors */							\
    X(ANIME__STRCOPY, = INT8_MIN + 1)					\
    X(ANIME__STRING_STACK_TOO_SMALL,)					\
    X(ANIME__FD_NEG,)							\
    X(ANIME__FDOPEN,)							\
    X(ANIME__CANNOT_OPEN_INPUT_FILE,)					\
    X(ANIME__CANNOT_MAKE_PIPE,)						\
    X(ANIME__NULL_FIELD_NAME,)						\
    X(ANIME__UNKNOWN_FIELD,)						\
    X(ANIME__INDEX_OF_OUT_BOUNDS,)					\
    X(ANIME__NULL_ERROR_ID_R,)						\
    X(ANIME__ERROR_SIZE_LOWER_THAN_1,)					\
    X(ANIME__NULL_INPUT_ENV,)						\
  X(ANIME__NULL_TOKEN_ENV,)						\
  X(ANIME__TOKEN_PARSER__CANNOT_MAKE_PIPE,)				\
  X(ANIME__TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM,)		\
  X(ANIME__TOKEN_PARSER__TOKEN_MATCHES_NO_PATTERN,)			\
  X(ANIME__TOKEN_PARSER__ERROR_TOKEN,)					\
  X(ANIME__TOKEN_PARSER__STACK_OVERFLOW,)				\
  X(ANIME__FIELD_NAME__IDENT_EXPECTED,)					\
  X(ANIME__FIELD_NAME__TOKEN_ID_NEG,)					\
  X(ANIME__FIELD_NAME__TOKEN_ID_OUT_OF_BOUND,)				\
  X(ANIME__FIELD_NAME__AT_LEAST_ONE_TOKEN,)				\
  X(ANIME__FIELD_NAME__AT_MOST_ONE_TOKEN,)				\
  X(ANIME__FIELD_VALUE__TOKEN_ID_NEG,)					\
    X(ANIME__FIELD_VALUE__TOKEN_ID_OUT_OF_BOUND,)			\
    X(ANIME__DATA_GENERATION__NULL_SYNTAX_FILTERING,)			\
    X(ANIME__DATA_GENERATION__NULL_TOKEN_ENV,)				\
    X(ANIME__DATA_GENERATION__NULL_ANIME_DATA,)				\
    X(ANIME__DATA_GENERATION__NULL_FLOATVAL_R,)				\
    X(ANIME__DATA_GENERATION__NULL_INTVAL_R,)				\
    X(ANIME__DATA_GENERATION__NULL_ERROR_ID_R,)				\
    X(ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1,)			\
    X(ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS,)			\
  X(ANIME__DATA_GENERATION__TOO_MANY_TOKENS,)				\
  X(ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE,)			\
  X(ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE,)			\
  X(ANIME__DATA_GENERATION__NULL_TREE_ENV,)				\
  X(ANIME__DATA_GENERATION__TREE_ENV__EMPTY,)				\
  X(ANIME__DATA_GENERATION__TREE_ENV__BEING_FILLED,)			\
  X(ANIME__DATA_GENERATION__TREE_ENV__NOT_FILLED,)			\
  X(ANIME__DATA_GENERATION__NOT_ENOUGH_TREES,)				\
  X(ANIME__DATA_GENERATION__TREE__WRONG_TREE_TYPE,)			\
  X(ANIME__DATA_GENERATION__MISSING_PHYSIQUE_SECTION,)			\
    X(ANIME__DATA_GENERATION__MISSING_GAMEPLAY_SECTION,)		\
    X(ANIME__DATA_GENERATION__MISSING_GRAPHIQUE_SECTION,)		\
    X(ANIME__DATA_GENERATION__STACK_OVERFLOW,)				\
    X(ANIME__DATA_GENERATION__STACK_UNDERFLOW,)				\
    X(ANIME__DATA_GENERATION__STACK_UNEXPECTED_TOKEN,)			\
    X(ANIME__DATA_GENERATION__STACK_TOO_MANY_ITEMS,)			\
    X(ANIME__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS,)			\
    X(ANIME__DATA_GENERATION__MEMBRES_OVERFLOW,)			\
    X(ANIME__DATA_GENERATION__UNEXPECTED_TOKEN,)			\
    X(ANIME__DATA_GENERATION__MISSING_OPENPAR,)			\
  X(ANIME__DATA_GENERATION__RACINES_OVERFLOW,)				\
  X(ANIME__TREE__NO_SPACE_LEFT,)					\
  X(ANIME__TREE__WRONG_ADDRESS,)					\
  X(ANIME__SYNTAX_FILTERING__NULL_THIS,)				\
  X(ANIME__SYNTAX_FILTERING__NULL_TOKEN_ENV,)				\
  X(ANIME__SYNTAX_FILTERING__NULL_TOKEN_I,)				\
  X(ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_TOO_SMALL,)		\
  X(ANIME__SYNTAX_FILTERING__PARENTHESIS_STACK_TOO_SMALL,)		\
  X(ANIME__SYNTAX_FILTERING__MISSING_CLOSING_PARENTHESIS,)		\
  X(ANIME__SYNTAX_FILTERING__MISSING_OPENING_PARENTHESIS,)		\
  X(ANIME__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS,)			\
    X(ANIME__SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS,)		\
    X(ANIME__SYNTAX_FILTERING__NOT_AN_CLOSING_PARENTHESIS,)		\
    X(ANIME__SYNTAX_FILTERING__CANNOT_SKIP_TO_CLOSING_PARENTHESIS_IN_LALR_MODE,) \
    X(ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_OUT_OF_BOUND,)		\
    X(ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID,)		\
    X(ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_EOF,)			\
    X(ANIME__SYNTAX_FILTERING__LAST_TOKEN_SHOULD_BE_EOF,)		\
  X(ANIME__SYNTAX_FILTERING__LALR_MODE_ALREADY_SET,)			\
  X(ANIME__MAIN__OPTIONS__PARSING_ERROR,)				\
  X(ANIME__MAIN__OPTIONS__RUNNING_ERROR,)				\
  X(ANIME__MAIN__OPTIONS__UNKNOWN,)					\
  X(ANIME__MAIN__OPTIONS__EXIT_QUICK,)					\
  X(ANIME__MAIN__CANNOT_OPEN_INPUT_FILE,)				\
  X(ANIME__MAIN__CANNOT_PARSE_INPUT_FILE,)				\
  X(ANIME__MAIN__ANIME_BUFFER_IS_TOO_SMALL,)				\
  X(ANIME__MAIN__STDIN_IS_TTY,)						\
  X(ANIME__MAIN__FILENAME_EMPTY,)					\
  X(ANIME__MAIN__FILENAME_NULL,)					\
  X(ANIME__MAIN__RESTORE_FAILED,)					\
  X(ANIME__MAIN__DUMP_FAILED,)						\
    X(ANIME__TOKEN__PARSER__ERROR,)					\
    X(ANIME__TOKEN__INPUT__ERROR,)					\
    X(ANIME__DUMP__BUFFER_TOO_SMALL,)					\
    X(ANIME__DUMP__DUMPING_TO_TTY,)					\
    X(ANIME__DUMP__ENDIANNESS_UNKNOWN,)					\
    X(ANIME__RESTORE__BUFFER_TOO_SMALL,)				\
  X(ANIME__RESTORE__READING_FROM_TTY,)					\
    X(ANIME__RESTORE__ERROR_WHILE_READING_INPUT,)			\
    X(ANIME__RESTORE__INPUT_TOO_SMALL,)					\
  X(ANIME__RESTORE__ENDIANNESS_UNKNOWN,)				\
    X(ANIME__LEXER__GENERIC_ERROR,)					\
    X(ANIME__LEXER__BAD_INPUT_FD,)					\
  X(ANIME__LEXER__LINE_TOO_LARGE,)					\
  X(ANIME__SYNTAX__GENERIC_ERROR,)					\
  X(ANIME__SYNTAX__EXPR_HAS_OPENBRACE,)					\
  X(ANIME__SYNTAX__EXPR_HAS_CLOSEBRACE,)				\
  X(ANIME__SYNTAX__EXPR_TOO_MANY_OPENBRACKETS,)				\
  X(ANIME__SYNTAX__EXPR_TOO_MANY_CLOSEBRACKETS,)			\
  X(ANIME__SYNTAX__EXPR_TOO_MANY_OPENPARS,)				\
  X(ANIME__SYNTAX__EXPR_TOO_MANY_CLOSEPARS,)				\
  X(ANIME__SYNTAX__EXPR_TOO_DEEP,)					\
  X(ANIME__SYNTAX__EXPR_MISSING_CLOSEPAR,)				\
  X(ANIME__SYNTAX__EXPR_MISSING_CLOSEBRACKET,)				\
  X(ANIME__SYNTAX__EXPR_MISSING_OPENPAR,)				\
    X(ANIME__SYNTAX__EXPR_MISSING_OPENBRACKET,)				\
    X(ANIME__SYNTAX__EXPR_MISMATCH_OPENBRACKET_CLOSEPAR,)		\
    X(ANIME__SYNTAX__EXPR_MISMATCH_OPENPAR_CLOSEBRACKET,)		\
  X(ANIME__SYNTAX__EXPR_NEIGHBORING_CONSTANTS,)				\
    X(ANIME__SYNTAX__EXPR_NEIGHBORING_BINARY_OP,)			\
    X(ANIME__SYNTAX__EXPR_TOO_MANY_CONSTANTS,)				\
    X(ANIME__SYNTAX__EXPR_TOO_MANY_BINARY_OP,)				\
    X(ANIME__SYNTAX__EXPR_ETAT_INCONNU,)				\
    X(ANIME__SYNTAX__EXPR_UNEXPECTED_BINOP,)				\
    X(ANIME__SYNTAX__EXPR_OPENPAR_NOT_FOUND,)				\
    X(ANIME__SYNTAX__EXPR_UNEXPECTED_TOKEN,)				\
    /* Warnings */							\
    X(ANIME__NULL_STRUCT, = 1)						\
  X(ANIME__EMPTY_STRUCTURE,)						\
  X(ANIME__FILLING_NOT_COMPLETED,)					\
  X(ANIME__HAS_BREAKING_UNCONSISTENCIES,)				\
  X(ANIME__HAS_NON_BREAKING_UNCONSISTENCIES,)				\
  X(ANIME__SYNTAX_FILTERING__TOKEN_ENV_HAS_ZERO_TOKEN,)			\
  X(ANIME__DUMP__ENDIANNESS_IS_UNSPECIFIED,)				\
  X(ANIME__RESTORE__ENDIANNESS_IS_UNSPECIFIED,)				\
  X(ANIME__RESTORE__ENDIANNESS_IS_NATIVE,)				\
  /* LAST_LINE*/

#define ANIME__ERROR__H
#define EXTERN extern
#include "anime_module_error.ci"
#undef  EXTERN
#undef  ANIME__ERROR__H

static void int_anime_error__check_and_assert(void); 


#if 0
extern const char * int_anime_error__get_cstr(const int_anime_error_t error_id); 
#else
//#  define int_anime_error__get_cstr int_anime__error__get_cstr
#endif 


struct anime_t; 
typedef struct anime_t anime_t; 


extern void         anime__print_f         (const anime_t * this, FILE * out_stream); 
extern void         anime__print_d         (const anime_t * this, const int fd); 
extern anime_t *    anime__make_m          (const int stdlog_d, void * (*malloc_to_use)(size_t)); 
extern anime_t *    anime__make_r          (anime_t * this, const int stdlog_d); 
extern anime_t *    anime__make_b          (char * anime_buffer, const int16_t anime_buffer_bytesize, int16_t * anime_buffer_bytesize_used_r, const int stdlog_d); 
extern void         anime__delete_m        (anime_t * this, void (*free_to_use)(void * ptr)); 
extern void         anime__delete_r        (anime_t * this);  
extern void         anime__delete_b        (anime_t * this);  
extern void         anime__bzero           (anime_t * this);  
extern const char * anime__strcopy         (anime_t * this, const char * cstr); 

extern int_anime_error_t anime__dump_to_fd(const anime_t * this, const int stddata_out_d); 
extern int_anime_error_t anime__dump_to_buffer(const anime_t * this, char * buffer, const int16_t buffer_bytesize, int16_t * used_bytesize_r);
extern int_anime_error_t anime__restore_from_fd(anime_t * this, const int stddata_in_d);
extern int_anime_error_t anime__restore_from_buffer(anime_t * this, const char * buffer, const int16_t buffer_bytesize, int16_t * used_bytesize_r);

extern const char *      anime__filename_get      (const anime_t * this); 
extern const char *      anime__copyright_get     (const anime_t * this); 
extern int_anime_error_t anime__error_id_get      (const anime_t * this); 
extern const char *      anime__error_cstr_get    (const anime_t * this); 
extern float             anime__choc_longueur__get(const anime_t * this); 
extern float             anime__choc_largeur__get (const anime_t * this); 
extern float             anime__choc_hauteur__get (const anime_t * this); 
extern float             anime__masse__get        (const anime_t * this); 
extern int16_t           anime__vie__get          (const anime_t * this); 
extern int8_t            anime__invincible__get   (const anime_t * this); 
extern int8_t            anime__hostile__get      (const anime_t * this); 

extern int8_t       anime__actions_nb__get                  (const anime_t * this);
extern const char * anime__actions_nom__get                 (const anime_t * this, const int8_t action_i);
extern const char * anime__actions_affichage__get           (const anime_t * this, const int8_t action_i);
extern const char * anime__actions_icone__get               (const anime_t * this, const int8_t action_i);
extern const char * anime__actions_gestionnaire_fichier__get(const anime_t * this, const int8_t action_i);
extern const char * anime__actions_gestionnaire_proc__get   (const anime_t * this, const int8_t action_i);

extern int8_t       anime__events_nb__get                     (const anime_t * this);
extern const char * anime__events_nom__get                    (const anime_t * this, const int8_t event_i);
extern const char * anime__events_genere_type__get            (const anime_t * this, const int8_t event_i);
extern const char * anime__events_genere_code_fichier__get    (const anime_t * this, const int8_t event_i);
extern const char * anime__events_genere_code_proc__get       (const anime_t * this, const int8_t event_i);
extern const char * anime__events_traitement_code_fichier__get(const anime_t * this, const int8_t event_i);
extern const char * anime__events_traitement_code_proc__get   (const anime_t * this, const int8_t event_i);

extern int8_t       anime__membres_nb__get         (const anime_t * this);
extern const char * anime__membres_nom__get        (const anime_t * this, const int8_t membre_i);
extern const char * anime__membres_image__get      (const anime_t * this, const int8_t membre_i);
extern const char * anime__membres_largeur__get    (const anime_t * this, const int8_t membre_i);
extern const char * anime__membres_hauteur__get    (const anime_t * this, const int8_t membre_i);
extern const char * anime__membres_angle_max_y__get(const anime_t * this, const int8_t membre_i);

extern int8_t       anime__racines_nb__get     (const anime_t * this);
extern const char * anime__racines_qui__get    (const anime_t * this, const int8_t racine_i);
extern const char * anime__racines_x__get      (const anime_t * this, const int8_t racine_i);
extern const char * anime__racines_y__get      (const anime_t * this, const int8_t racine_i);
extern const char * anime__racines_z__get      (const anime_t * this, const int8_t racine_i);
extern const char * anime__racines_angle_y__get(const anime_t * this, const int8_t racine_i);



extern int_anime_error_t anime__consistency_check(anime_t * this, const int stduser_d); 

extern int_anime_error_t anime__fill_from_fd    (anime_t * this, const char * input_name, const int input_fd, const int stduser_d); 
extern int_anime_error_t anime__fill_from_buffer(anime_t * this, const char * input_name, const char * buffer, const int16_t buffer_bytesize, const int stduser_d); 
extern int_anime_error_t anime__fill_from_file  (anime_t * this, const char * filepathname, const int stduser_d); 

extern int_anime_error_t anime__print_field_value_by_name(const anime_t * this, const char * field_name, const int stdprint_d, const int stduser_d, int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str); 



extern const char * anime__convert_token_cstring_to_regular_string(anime_t * this, const char * cstr); 

extern void anime__endianness_byte_swap(anime_t * this); 




enum { ANIME__EXPRESSION_NESTEDNESS_MAX = 16 }; 
extern const uint8_t ANIME__EXPRESSION_NESTEDNESS_MAX__compiled_value; 

// Length in tokens (it means we cannot analyze expressions longer than that). 
enum { ANIME__LONGEST_INFIX_EXPRESSION = 64 }; // 2^6 = 64 — therefore, it means roughly a six-height tree (on average). 
extern const uint8_t ANIME__LONGEST_INFIX_EXPRESSION__compiled_value; 

extern const int16_t anime_t_sizeof;





#endif /* ANIME_H */
