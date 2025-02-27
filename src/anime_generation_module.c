#include "anime_global.h"
#include "anime.h"
#include "anime_type.h"
#include "anime_generation_module.h"
#include "anime_lexer_module.h"



#include "anime_generation_module_infix_to_postfix.ci"


// ********************************************
// FIELD NAMES 

#define DO_ARRAY_ITEM(field_name,__item_i__) {				\
    const int_lexeme_t lexeme_i   = this -> glue2(field_name,__lexeme_i)  [__item_i__]; \
    const int8_t       lexemes_nb = this -> glue2(field_name,__lexemes_nb)[__item_i__]; \
    if (0                        >  lexeme_i) goto label__error__token_id_is_negative; \
    if (this -> lexeme_stack__nb <= lexeme_i) goto label__error__token_id_is_out_of_bound; \
    if (0 == lexemes_nb) goto label__error__at_least_one_token_is_required;		\
    if (1  < lexemes_nb) goto label__error__need_at_most_one_token;	\
    const int_anime_token_type_t lexeme_type = this -> lexeme_stack__type[lexeme_i]; \
    if (ANIME_TOKEN_IDENT == lexeme_type) {				\
      const char * lexeme_value = this -> lexeme_value_stack + this -> lexeme_stack__value[lexeme_i]; \
      /*dprintf(stderr_d, "lexeme_value = '%s'\n", lexeme_value); */		\
      this -> field_name[__item_i__] = anime__string_stack__push_lookup(this, lexeme_value); \
      /*dprintf(stderr_d, "this -> field_name[__item_i__] = '%d'\n", (int) this -> field_name[__item_i__]); */ \
    }									\
    else if (ANIME_TOKEN_STRING_C == lexeme_type) {			\
      const char * lexeme_value = this -> lexeme_value_stack + this -> lexeme_stack__value[lexeme_i]; \
      char filtered_str[ANIME_LINE_LEN_MAX];				\
      convert_quoted_encoded_string_to_regular_string(lexeme_value, filtered_str, sizeof(filtered_str)); \
      this -> field_name[__item_i__] = anime__string_stack__push_lookup(this, filtered_str); \
    }									\
    else goto label__error__expecting_ident;				\
  };									\
/* END OF MACRO */


int_anime_error_t anime__generation__field_names__compute(anime_t * this) { 
  goto label__body; 
  
 label__error__expecting_ident: { 
    return ANIME__FIELD_NAME__IDENT_EXPECTED; 
  }; 
  
 label__error__token_id_is_negative: {
    return ANIME__FIELD_NAME__TOKEN_ID_NEG; 
  }; 

 label__error__token_id_is_out_of_bound: {
    return ANIME__FIELD_NAME__TOKEN_ID_OUT_OF_BOUND; 
  };

 label__error__at_least_one_token_is_required: { 
    return ANIME__FIELD_NAME__AT_LEAST_ONE_TOKEN; 
  }; 
  
 label__error__need_at_most_one_token: { 
    return ANIME__FIELD_NAME__AT_MOST_ONE_TOKEN; 
  }; 

 label__body: {   
    for (int8_t action_i = 0; action_i < this -> actions_nb; action_i++) DO_ARRAY_ITEM(actions_array_nom,action_i);
    for (int8_t  event_i = 0;  event_i < this ->  events_nb;  event_i++) DO_ARRAY_ITEM( events_array_nom,event_i);
    for (int8_t membre_i = 0; membre_i < this -> membres_nb; membre_i++) DO_ARRAY_ITEM(membres_nom,membre_i);
    for (int8_t racine_i = 0; racine_i < this -> racines_nb; racine_i++) DO_ARRAY_ITEM(racines_qui,racine_i);  
    return ANIME__OK; 
  };
  
}; 


#undef DO_ARRAY_ITEM






// ******************************************** 
// FIELD VALUES - EXPR - VALUE COMPUTATION 

static int_anime_error_t anime__generation__convert_infix_to_postfix(const anime_t * this, const int_lexeme_t lexeme_i, const int8_t lexeme_len, int_lexeme_t * postfix_buffer, const int8_t postfix_buffer_itemsize, int8_t * postfix_buffer_nb_r); 
static int_anime_error_t anime__generation__eval_postfix_float(anime_t * this, const int_lexeme_t * postfix_buffer, const int8_t postfix_buffer_nb, float * floatval_r, const int stduser_d, const int stdlog_d); 
static int_anime_error_t anime__generation__eval_postfix_expr(anime_t * this, const int_lexeme_t * postfix_buffer, const int8_t postfix_buffer_nb, float * floatval_r, int16_t * int16val_r, int8_t * boolval_r, const int stduser_d, const int stdlog_d); 

#define INFIX_BUFFER_PRINT(infix_buffer,infix_buffer_nb) {		\
    dputs3(STDERR_FILENO, "infix_buffer[", int_string(infix_buffer_nb),"] = {" "\n"); \
    for (int i = 0; i < infix_buffer_nb; i++) {				\
      dputs_array(STDERR_FILENO, "\t" "[", int_string(i), "] = ", int_string(infix_buffer[i]), "\n"); \
    };									\
    dputs(STDERR_FILENO, "};" "\n");					\
  };									\
  /* END OF MACRO */

#define POSTFIX_BUFFER_PRINT(postfix_buffer,postfix_buffer_nb) {	\
    dputs3(STDERR_FILENO, "postfix_buffer[", int_string(postfix_buffer_nb),"] = {" "\n"); \
    for (int i = 0; i < postfix_buffer_nb; i++) {			\
      dputs_array(STDERR_FILENO, "\t" "[", int_string(i), "] = ", int_string(postfix_buffer[i]), "\n"); \
    };									\
    dputs(STDERR_FILENO, "};" "\n");					\
  };									\
  /* END OF MACRO */

#define CONVERT_INFIX_TO_POSTFIX(__lexeme_i__, __lexemes_nb__)		\
  int_lexeme_t postfix_buffer[ANIME__LONGEST_INFIX_EXPRESSION];		\
  int8_t       postfix_buffer_nb;					\
  error_id = anime__generation__convert_infix_to_postfix(this, __lexeme_i__, __lexemes_nb__, postfix_buffer, ANIME__LONGEST_INFIX_EXPRESSION, &postfix_buffer_nb); \
  if (ANIME__OK != error_id) goto label__error__infix_to_postfix_failed; \
  /* END OF MACRO */

#define READ_LALR_FLOAT(__lexeme_i__, __lexemes_nb__) {			\
    CONVERT_INFIX_TO_POSTFIX(__lexeme_i__, __lexemes_nb__);		\
    error_id = anime__generation__eval_postfix_float(this, postfix_buffer, postfix_buffer_nb, &floatval, /*stduser_d*/-1, this -> stdlog_d); \
    if (ANIME__OK != error_id) goto label__error__error_in_postfix_computation; \
  };									\
  /* END OF MACRO */

#define READ_LALR_INT(__lexeme_i__, __lexemes_nb__) {			\
    CONVERT_INFIX_TO_POSTFIX(__lexeme_i__, __lexemes_nb__);		\
    error_id = anime__generation__eval_postfix_expr(this, postfix_buffer, postfix_buffer_nb, /*floatval_r*/NULL, /*int16val_r*/&intval, /*boolval_r*/NULL, /*stduser_d*/-1, this -> stdlog_d); \
    if (ANIME__OK != error_id) goto label__error__error_in_postfix_computation; \
  };									\
  /* END OF MACRO */

#define READ_LALR_BOOL(__lexeme_i__, __lexemes_nb__) {			\
    CONVERT_INFIX_TO_POSTFIX(__lexeme_i__, __lexemes_nb__);		\
    error_id = anime__generation__eval_postfix_expr(this, postfix_buffer, postfix_buffer_nb, /*floatval_r*/NULL, /*int16val_r*/NULL, /*boolval_r*/&boolval, /*stduser_d*/-1, this -> stdlog_d); \
    if (ANIME__OK != error_id) goto label__error__error_in_postfix_computation; \
  };									\
  /* END OF MACRO */

#define READ_LALR_VALUE(__lexeme_i__, __lexemes_nb__) {			\
    CONVERT_INFIX_TO_POSTFIX(__lexeme_i__, __lexemes_nb__);		\
    /* POSTFIX_BUFFER_PRINT(postfix_buffer,postfix_buffer_nb);	*/	\
    error_id = anime__generation__eval_postfix_expr(this, postfix_buffer, postfix_buffer_nb, /*floatval_r*/&floatval, /*int16val_r*/&intval, /*boolval_r*/&boolval, /*stduser_d*/-1, this -> stdlog_d); \
    if (ANIME__OK != error_id) goto label__error__error_in_postfix_computation; \
  };									\
  /* END OF MACRO */



int_anime_error_t anime__generation__field_values__compute(anime_t * this) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  float   floatval; 
  int16_t   intval; 
  int8_t   boolval; 
  int_anime_error_t error_id; 
  goto label__body; 

 label__error__infix_to_postfix_failed: {
    return error_id; 
  }; 

 label__error__error_in_postfix_computation: { 
    return this -> error_id; 
  }; 

 label__error__token_id_is_negative: {
    //dputs(2, "ANIME__FIELD_VALUE__TOKEN_ID_NEG ="); dputn(2, ANIME__FIELD_VALUE__TOKEN_ID_NEG); dput_eol(2); 
    return ANIME__FIELD_VALUE__TOKEN_ID_NEG; 
  }; 

 label__error__token_id_is_out_of_bound: { 
    //dputs(2, "ANIME__FIELD_VALUE__TOKEN_ID_OUT_OF_BOUND ="); dputn(2, ANIME__FIELD_VALUE__TOKEN_ID_OUT_OF_BOUND); dput_eol(2); 
    return ANIME__FIELD_VALUE__TOKEN_ID_OUT_OF_BOUND; 
  }; 

 label__body: { 
    const int_lexeme_t lexeme_stack__nb = this -> lexeme_stack__nb; 
#if 0 
    const int_lexeme_t lexeme_i   = this -> masse__lexeme_i; 
    const int8_t       lexemes_nb = this -> masse__lexemes_nb;
    if (0 > lexeme_i) goto label__error__token_id_is_negative; 
    READ_LALR_FLOAT(lexeme_i, lexemes_nb); 
    this -> masse = floatval; 
#endif 
    
#define COMPUTE_FLOAT(__field_name__) {					\
      const int_lexeme_t lexeme_i   = this -> glue2(__field_name__,__lexeme_i); \
      const int8_t       lexemes_nb = this -> glue2(__field_name__,__lexemes_nb); \
      if (0                >  lexeme_i             ) goto label__error__token_id_is_negative; \
      if (lexeme_stack__nb <= lexeme_i + lexemes_nb) goto label__error__token_id_is_out_of_bound; \
      READ_LALR_FLOAT(lexeme_i, lexemes_nb);				\
      this -> __field_name__ = floatval;				\
    }; 
    
#define COMPUTE_INT(__field_name__) {					\
      const int_lexeme_t lexeme_i   = this -> glue2(__field_name__,__lexeme_i); \
      const int8_t       lexemes_nb = this -> glue2(__field_name__,__lexemes_nb); \
      if (0                >  lexeme_i             ) goto label__error__token_id_is_negative; \
      if (lexeme_stack__nb <= lexeme_i + lexemes_nb) goto label__error__token_id_is_out_of_bound; \
      READ_LALR_INT(lexeme_i, lexemes_nb);				\
      this -> __field_name__ = intval;					\
    }; 
    
#define COMPUTE_BOOL(__field_name__) {					\
      const int_lexeme_t lexeme_i   = this -> glue2(__field_name__,__lexeme_i); \
      const int8_t       lexemes_nb = this -> glue2(__field_name__,__lexemes_nb); \
      if (0                >  lexeme_i             ) goto label__error__token_id_is_negative; \
      if (lexeme_stack__nb <= lexeme_i + lexemes_nb) goto label__error__token_id_is_out_of_bound; \
      READ_LALR_BOOL(lexeme_i, lexemes_nb);				\
      this -> __field_name__ = boolval;					\
    }; 

#define COMPUTE_ARRAY_ITEM(__field_name__,__item_i__,__type_val__) {	\
      const int_lexeme_t lexeme_i   = this -> glue2(__field_name__,__lexeme_i  )[__item_i__]; \
      const int8_t       lexemes_nb = this -> glue2(__field_name__,__lexemes_nb)[__item_i__]; \
      if (0                >  lexeme_i             ) goto label__error__token_id_is_negative; \
      if (lexeme_stack__nb <= lexeme_i + lexemes_nb) goto label__error__token_id_is_out_of_bound; \
      READ_LALR_VALUE(lexeme_i, lexemes_nb);				\
      this -> __field_name__[__item_i__] = __type_val__;		\
  };									\
  /* END OF MACRO */
    
    COMPUTE_FLOAT(choc_longueur);
    COMPUTE_FLOAT(choc_largeur);
    COMPUTE_FLOAT(choc_hauteur);
    COMPUTE_FLOAT(masse); 
    COMPUTE_INT(vie); 
    COMPUTE_BOOL(invincible); 
    COMPUTE_BOOL(hostile); 

#if 0
  float              membres_largeur    [ANIME_MEMBRES_SIZE]; 
  float              membres_hauteur    [ANIME_MEMBRES_SIZE]; 
  float              membres_angle_max_y[ANIME_MEMBRES_SIZE]; 

    for (int8_t action_i = 0; action_i < this -> actions_nb; action_i++) DO_ARRAY_ITEM(actions_array_nom,action_i);
    for (int8_t  event_i = 0;  event_i < this ->  events_nb;  event_i++) DO_ARRAY_ITEM( events_array_nom,event_i);
    for (int8_t membre_i = 0; membre_i < this -> membres_nb; membre_i++) DO_ARRAY_ITEM(membres_nom,membre_i);
    for (int8_t racine_i = 0; racine_i < this -> racines_nb; racine_i++) DO_ARRAY_ITEM(racines_qui,racine_i);  
#endif 

    //anime__syntax__print(this, STDERR_FILENO);  

#if 1
    for (int8_t membre_i = 0; membre_i < this -> membres_nb; membre_i++) { 
      COMPUTE_ARRAY_ITEM(membres_largeur,membre_i,floatval);
      COMPUTE_ARRAY_ITEM(membres_hauteur,membre_i,floatval);
      //dputs(STDERR_FILENO, "membre_i: "); dputn(STDERR_FILENO, membre_i); dput_eol(STDERR_FILENO); 
      COMPUTE_ARRAY_ITEM(membres_angle_max_y,membre_i,floatval);
    };
#endif

    for (int8_t racine_i = 0; racine_i < this -> racines_nb; racine_i++) { 
      COMPUTE_ARRAY_ITEM(racines_x,racine_i,floatval);
      COMPUTE_ARRAY_ITEM(racines_y,racine_i,floatval);
      COMPUTE_ARRAY_ITEM(racines_z,racine_i,floatval);
      COMPUTE_ARRAY_ITEM(racines_angle_y,racine_i,floatval);
    };
    
#undef COMPUTE_ARRAY_ITEM
#undef COMPUTE_BOOL
#undef COMPUTE_INT
#undef COMPUTE_FLOAT
    
    return ANIME__OK; 
  };
}; 








#define GENERIC_MESSAGE_PRINT(__out_d__,__msg__) {			\
  int location_len;							\
  if (0 == token_nb) {							\
    location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{'%s' contains no data}: ", input_filename_cstr); \
  }									\
  else if (0 > token_i) {						\
    location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{'%s':-1:-1}: ", input_filename_cstr); \
  }									\
  else {								\
    const int_lexeme_t location_token = token_nb <= token_i ? token_nb - 1 : token_i; \
    const int16_t line1 = anime_data -> lexeme_stack__line1[location_token]; \
    const int8_t  col0  = anime_data -> lexeme_stack__col0[location_token]; \
    location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", input_filename_cstr, (int) line1, (int) col0); \
  };									\
  strlcpy(anime_data -> error_str + location_len, __msg__, MAX(0,ANIME__ERROR_BUFFER_SIZE - location_len)); \
  if (__out_d__ > 0) { dprintf(__out_d__, "%s" "\n", anime_data -> error_str); }; \
  if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; \
};									\
/* END OF MACRO */

#define WARNING_MESSAGE_PRINT() GENERIC_MESSAGE_PRINT(stdwarning_d,warning__msg) 

#define ERROR_MESSAGE_PRINT() GENERIC_MESSAGE_PRINT(stderror_d,error__msg) 

#define ERROR_MESSAGE_PRINT__NO_LINE() {				\
    strlcpy(anime_data -> error_str, error__msg, ANIME__ERROR_BUFFER_SIZE); \
    if (stderror_d > 0) { dprintf(stderror_d, "%s" "\n", anime_data -> error_str); }; \
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; \
  };									\
  /* END OF MACRO */








// ********************************************
// EVAL POSTFIX EXPR 

 
enum { EXPR_STACK_SIZE = ANIME__EXPRESSION_NESTEDNESS_MAX }; 

#define PUSH_GENERIC_STACK(__name__,__value__) {			\
    if (glue3(stack__,__name__,_nb) >= EXPR_STACK_SIZE) { goto error_label__stack_overflow; }; \
    glue2(stack__,__name__)[glue3(stack__,__name__,_nb)] = (__value__);			\
    glue3(stack__,__name__,_nb)++;					\
  };									\
/* END OF MACRO */

#define PUSH_FLOAT_STACK(__value__) PUSH_GENERIC_STACK(float,__value__)

#define PUSH_INT16_STACK(__value__) PUSH_GENERIC_STACK(int16,__value__)

#define PUSH_BOOL_STACK(__value__) PUSH_GENERIC_STACK(bool,__value__)

#define UNARY_OPERATOR_GENERIC_STACK(__type__,__name__,__result_expr__) {	\
	if (glue3(stack__,__name__,_nb) < 1) { goto error_label__stack_underflow; }; \
	const int stack__i = glue3(stack__,__name__,_nb) - 1;		\
	const __type__ stack_top = glue2(stack__,__name__)[stack__i];	\
	glue2(stack__,__name__)[stack__i] = (__result_expr__);			\
      };								\
      /* END OF MACRO */

#define UNARY_OPERATOR_FLOAT_STACK(__result_expr__) UNARY_OPERATOR_GENERIC_STACK(float,float,__result_expr__)

#define UNARY_OPERATOR_INT16_STACK(__result_expr__) UNARY_OPERATOR_GENERIC_STACK(int16_t,int16,__result_expr__)

#define UNARY_OPERATOR_BOOL_STACK(__result_expr__) UNARY_OPERATOR_GENERIC_STACK(int8_t,bool,__result_expr__)



#define BINARY_OPERATOR_GENERIC_STACK(__type__,__name__,__result_expr__) {	\
	if (glue3(stack__,__name__,_nb) < 2) { goto error_label__stack_underflow; }; \
	const int stack__i = glue3(stack__,__name__,_nb) - 1;		\
	const __type__ op_left = glue2(stack__,__name__)[stack__i-1];	\
	const __type__ op_right = glue2(stack__,__name__)[stack__i];	\
	glue2(stack__,__name__)[stack__i-1] = (__result_expr__);		\
	glue3(stack__,__name__,_nb)--;					\
      };								\
      /* END OF MACRO */

#define BINARY_OPERATOR_FLOAT_STACK(__result_expr__) BINARY_OPERATOR_GENERIC_STACK(float,float,__result_expr__)

#define BINARY_OPERATOR_INT16_STACK(__result_expr__) BINARY_OPERATOR_GENERIC_STACK(int16_t,int16,__result_expr__)

#define BINARY_OPERATOR_BOOL_STACK(__result_expr__) BINARY_OPERATOR_GENERIC_STACK(int8_t,bool,__result_expr__)



static int_anime_error_t anime__generation__eval_postfix_expr(anime_t * this, const int_lexeme_t * postfix_buffer, const int8_t postfix_buffer_nb, float * floatval_r, int16_t * int16val_r, int8_t * boolval_r, const int stduser_d, const int stdlog_d) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int_anime_error_t * error_id_r = &this -> error_id; const uint16_t error_size = this -> error_size; char * error_str = this -> error_str; 
  if (NULL == error_id_r) { return        ANIME__DATA_GENERATION__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  //if (NULL ==       this) { *error_id_r = ANIME__DATA_GENERATION__NULL_SYNTAX_FILTERING; snprintf(error_str, error_size, "syntax_filtering argument is null."); return *error_id_r; }; 
  //if (NULL ==  token_env) { *error_id_r = ANIME__DATA_GENERATION__NULL_TOKEN_ENV       ; snprintf(error_str, error_size, "token_env argument is null."); return *error_id_r; }; 
  //if (NULL == floatval_r) { *error_id_r = ANIME__DATA_GENERATION__NULL_FLOATVAL_R      ; snprintf(error_str, error_size, "floatval_r argument is null."); return *error_id_r; }; 
  
  
  char warning__msg[256]; 
  char error__msg[256]; 
  
  anime_t * anime_data = this; 
  const int_lexeme_t token_nb = this -> lexeme_stack__nb; 
  const char * input_filename_cstr = anime__filename_get(anime_data); 
  //const int stdlog_d = anime_data -> stdlog_d; 
  const int stderror_d = anime_data -> stdlog_d; 
  int_lexeme_t token_i; 
  int_anime_token_type_t token_type; 
    
  
  
  float   stack__float[EXPR_STACK_SIZE]; 
  int16_t stack__int16[EXPR_STACK_SIZE]; 
  int8_t  stack__bool [EXPR_STACK_SIZE]; 
  int     stack__float_nb; 
  int     stack__int16_nb; 
  int     stack__bool_nb; 
  stack__float_nb = 0; 
  stack__int16_nb = 0; 
  stack__bool_nb  = 0; 
  
  int8_t postfix_buffer_i; 
  goto label__body; 

  

 label__body: { 
  postfix_buffer_i = -1; 
  for (;;) { 
    postfix_buffer_i++; 
    if (postfix_buffer_nb <= postfix_buffer_i) goto label__eof_reached; 
    token_i    = postfix_buffer[postfix_buffer_i]; 
    token_type = this -> lexeme_stack__type[token_i]; 
    
    switch (token_type) { 
    case ANIME_TOKEN_TRUE: { 
      label__token_true: 
      PUSH_FLOAT_STACK(1.0f / 0.0f); 
      PUSH_INT16_STACK(INT16_MAX); 
      PUSH_BOOL_STACK(true); 
      continue; 
    };
      
    case ANIME_TOKEN_FALSE: { 
      label__token_false:
      PUSH_FLOAT_STACK(0); 
      PUSH_INT16_STACK(0); 
      PUSH_BOOL_STACK(false); 
      continue; 
    }; 
      
    case ANIME_TOKEN_IDENT: { 
      const char * lexeme_value = this -> lexeme_value_stack + this -> lexeme_stack__value[token_i]; 
      if (0 == strcasecmp("vrai" , lexeme_value)) goto label__token_true; 
      if (0 == strcasecmp("oui"  , lexeme_value)) goto label__token_true; 
      if (0 == strcasecmp("true" , lexeme_value)) goto label__token_true; 
      if (0 == strcasecmp("yes"  , lexeme_value)) goto label__token_true; 
      if (0 == strcasecmp("faux" , lexeme_value)) goto label__token_false; 
      if (0 == strcasecmp("non"  , lexeme_value)) goto label__token_false; 
      if (0 == strcasecmp("false", lexeme_value)) goto label__token_false; 
      if (0 == strcasecmp("no"   , lexeme_value)) goto label__token_false; 
      if (0 == strcasecmp("longueur", lexeme_value)) { 
	PUSH_FLOAT_STACK(this -> choc_longueur); 
	PUSH_INT16_STACK(this -> choc_longueur); 
	PUSH_BOOL_STACK(0 != this -> choc_longueur); 
	continue; 
      }; 
      goto error_label__unexpected_token; 
      continue; 
    }; 

    case ANIME_TOKEN_STRING_C: {			
      const char * lexeme_value = this -> lexeme_value_stack + this -> lexeme_stack__value[token_i]; 
      char filtered_str[ANIME_LINE_LEN_MAX];				
      convert_quoted_encoded_string_to_regular_string(lexeme_value, filtered_str, sizeof(filtered_str)); 
      if (0 == strcasecmp("vrai" , filtered_str)) goto label__token_true; 
      if (0 == strcasecmp("oui"  , filtered_str)) goto label__token_true; 
      if (0 == strcasecmp("true" , filtered_str)) goto label__token_true; 
      if (0 == strcasecmp("yes"  , filtered_str)) goto label__token_true; 
      if (0 == strcasecmp("faux" , filtered_str)) goto label__token_false; 
      if (0 == strcasecmp("non"  , filtered_str)) goto label__token_false; 
      if (0 == strcasecmp("false", filtered_str)) goto label__token_false; 
      if (0 == strcasecmp("no"   , filtered_str)) goto label__token_false; 
      goto error_label__unexpected_token; 
      continue; 
    };

      
    case ANIME_TOKEN_ENTIER: 
    case ANIME_TOKEN_REEL__VIRG: 
    case ANIME_TOKEN_REEL__DOT: 
    case ANIME_TOKEN_REEL__E: { 
      //dputs3(STDERR_FILENO, "AVANT - stack__float_nb: ", int_string(stack__float_nb), "\n"); 
      const char * token_value = this -> lexeme_value_stack + this -> lexeme_stack__value[token_i]; 
      PUSH_FLOAT_STACK(atof(token_value)); 
      PUSH_INT16_STACK(atoi(token_value)); 
      PUSH_BOOL_STACK(0 == atoi(token_value) ? false : true); 
      //dputs3(STDERR_FILENO, "APRES - stack__float_nb: ", int_string(stack__float_nb), "\n"); 
      continue; 
    }; 
      
    case ANIME_TOKEN_IPLUS_UNAIRE: 
    case ANIME_TOKEN_RPLUS_UNAIRE: 
      continue; 
      
    case ANIME_TOKEN_IMOINS_UNAIRE: 
    case ANIME_TOKEN_RMOINS_UNAIRE: { 
      //dputs3(STDERR_FILENO, "RMOINS - AVANT - stack__float_nb: ", int_string(stack__float_nb), "\n"); 
      UNARY_OPERATOR_FLOAT_STACK(-stack_top);
      UNARY_OPERATOR_INT16_STACK(-stack_top);
      UNARY_OPERATOR_BOOL_STACK(stack_top);
      //dputs3(STDERR_FILENO, "RMOINS - APRES - stack__float_nb: ", int_string(stack__float_nb), "\n"); 
      continue; 
    }; 
      
    case ANIME_TOKEN_IPLUS_BINAIRE: 
    case ANIME_TOKEN_RPLUS_BINAIRE: { 
      BINARY_OPERATOR_FLOAT_STACK(op_left + op_right); 
      BINARY_OPERATOR_INT16_STACK(op_left + op_right); 
      BINARY_OPERATOR_BOOL_STACK(op_left || op_right); 
      continue; 
    }; 
      
    case ANIME_TOKEN_IMOINS_BINAIRE: 
    case ANIME_TOKEN_RMOINS_BINAIRE: { 
      BINARY_OPERATOR_FLOAT_STACK(op_left - op_right); 
      BINARY_OPERATOR_INT16_STACK(op_left - op_right); 
      BINARY_OPERATOR_BOOL_STACK(op_left || op_right); 
      continue; 
    }; 
      
    case ANIME_TOKEN_IMULT: 
    case ANIME_TOKEN_RMULT: { 
      BINARY_OPERATOR_FLOAT_STACK(op_left * op_right); 
      BINARY_OPERATOR_INT16_STACK(op_left * op_right); 
      BINARY_OPERATOR_BOOL_STACK(op_left && op_right); 
      continue; 
    }; 
      
    case ANIME_TOKEN_RDIV: { 
      BINARY_OPERATOR_FLOAT_STACK(op_left / op_right); 
      BINARY_OPERATOR_INT16_STACK(op_left / op_right); 
      BINARY_OPERATOR_BOOL_STACK(op_right == op_left ? true : op_left); 
      continue; 
    }; 
      
    default: goto error_label__unexpected_token; 
    }; 
    /* NOT REACHED */ assert(false); 
  };
  /* NOT REACHED */ assert(false); 
  };


label__eof_reached: { 
    if (stack__float_nb < 1) { goto error_label__stack_not_enough_items; }; 
    if (stack__float_nb > 1) { goto error_label__stack_too_many_items  ; }; 
    if (stack__int16_nb < 1) { goto error_label__stack_not_enough_items; }; 
    if (stack__int16_nb > 1) { goto error_label__stack_too_many_items  ; }; 
    if (stack__bool_nb  < 1) { goto error_label__stack_not_enough_items; }; 
    if (stack__bool_nb  > 1) { goto error_label__stack_too_many_items  ; }; 
    if (NULL != floatval_r) *floatval_r  = stack__float[0]; 
    if (NULL != int16val_r) *int16val_r  = stack__int16[0]; 
    if (NULL !=  boolval_r)  *boolval_r  = stack__bool [0]; 
    *error_id_r  = ANIME__OK; 
    *error_str   = '\0'; 
    return *error_id_r; 
  }; 
  

  

 error_label__stack_too_many_items: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_TOO_MANY_ITEMS; 
    strlcpy(error__msg, "[Float stack]: No value to return as there are more than one item on the stack", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return *error_id_r; 
  }; 
  
 error_label__stack_not_enough_items: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS; 
    strlcpy(error__msg, "[Float stack]: No value to return as there is nothing on the stack", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return *error_id_r; 
  }; 

 error_label__stack_overflow: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_OVERFLOW; 
    strlcpy(error__msg, "[Float stack]: Stack overflow", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return *error_id_r; 
  }; 

 error_label__stack_underflow: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_UNDERFLOW; 
    strlcpy(error__msg, "[Float stack]: Stack underflow", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return *error_id_r; 
  }; 
 
 error_label__unexpected_token: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_UNEXPECTED_TOKEN; 
    const char * token_value = this -> lexeme_value_stack + this -> lexeme_stack__value[token_i]; 
    snprintf(error__msg, sizeof(error__msg), "[Float stack]: Unexpected token %s [%s]", anime_token__type_get_cstr(token_type), token_value); 
    ERROR_MESSAGE_PRINT(); 
    return *error_id_r; 
  }; 
  
}; 



static int_anime_error_t anime__generation__eval_postfix_float(anime_t * this, const int_lexeme_t * postfix_buffer, const int8_t postfix_buffer_nb, float * floatval_r, const int stduser_d, const int stdlog_d) { 
  if (NULL == floatval_r) { this -> error_id = ANIME__DATA_GENERATION__NULL_FLOATVAL_R; snprintf(this -> error_str, this -> error_size, "floatval_r argument is null."); return this -> error_id; }; 
  return anime__generation__eval_postfix_expr(this, postfix_buffer, postfix_buffer_nb, floatval_r, /*int16val_r*/NULL, /*boolval_r*/NULL, stduser_d, stdlog_d); 
}; 

