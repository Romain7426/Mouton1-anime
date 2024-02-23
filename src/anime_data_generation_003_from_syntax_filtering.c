#include "anime_global.h"
#include "anime.h"
#include "anime_type.h"
#include "anime_token.h"
#include "anime_token_type.h"
//#include "anime_token_input_buffering.h"
//#include "anime_token_parser.h"
#include "anime_syntax_filtering_engine.h"
#include "anime_data_generation_003_from_syntax_filtering.h"


#define GET_CURRENT_TOKEN_R() {						\
    *error_id_r = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (*error_id_r != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 

#define MOVE_TO_NEXT_TOKEN_R() {						\
    *error_id_r = anime_syntax_filtering__move_to_next_token(this, token_env, &token_i); \
    if (*error_id_r != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 

enum { EXPR_STACK_SIZE = ANIME__EXPRESSION_NESTEDNESS_MAX }; 


static int_anime_error_t anime_data__read_postfix_float(int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str, const int stdlog_d, anime_syntax_filtering_t * this, anime_token_env_t * token_env, float * floatval_r, const int stduser_d) { 
  if (NULL == error_id_r) { return ANIME__DATA_GENERATION__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  if (NULL ==       this) { *error_id_r = ANIME__DATA_GENERATION__NULL_SYNTAX_FILTERING; snprintf(error_str, error_size, "syntax_filtering argument is null."); return *error_id_r; }; 
  if (NULL ==  token_env) { *error_id_r = ANIME__DATA_GENERATION__NULL_TOKEN_ENV       ; snprintf(error_str, error_size, "token_env argument is null."); return *error_id_r; }; 
  if (NULL == floatval_r) { *error_id_r = ANIME__DATA_GENERATION__NULL_FLOATVAL_R      ; snprintf(error_str, error_size, "floatval_r argument is null."); return *error_id_r; }; 
  
  float stack__array[EXPR_STACK_SIZE]; 
  int   stack__nb; 
  stack__nb = 0; 
  
  int_anime_token_t token_i; 
  //const int_anime_token_t token_nb = anime_token__get_count(token_env); 
  
  GET_CURRENT_TOKEN_R(); 
  
  for (;;) { 
    const int_anime_token_type_t token_type = anime_token__get_type(token_env, token_i); 
    //dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_token__type_get_cstr(token_type)); 
    switch (token_type) { 
    case ANIME_TOKEN_ENTIER: 
    case ANIME_TOKEN_REEL__VIRG: 
    case ANIME_TOKEN_REEL__DOT: 
    case ANIME_TOKEN_REEL__E: { 
      const char * srcval = anime_token__get_srcval_cstr(token_env, token_i); 
      if (stack__nb >= EXPR_STACK_SIZE) { goto error_label__stack_overflow; }; 
      stack__array[stack__nb] = (atof(srcval)); 
#if 0 
      dprintf(stderr_d, "srcval = %s" "\n", srcval); 
      dprintf(stderr_d, "stack__array[%d] = %f" "\n", stack__nb, stack__array[stack__nb]); 
#endif 
      stack__nb++; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IPLUS_UNAIRE: 
    case ANIME_TOKEN_RPLUS_UNAIRE: 
      goto completed_huh; 

    case ANIME_TOKEN_IMOINS_UNAIRE: 
    case ANIME_TOKEN_RMOINS_UNAIRE: { 
      if (stack__nb < 1) { goto error_label__stack_underflow; }; 
      const int stack__i = stack__nb - 1; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %f" "\n", stack__i, stack__array[stack__i]); 
#endif 
      stack__array[stack__i] = - stack__array[stack__i]; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %f" "\n", stack__i, stack__array[stack__i]); 
#endif 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IPLUS: 
    case ANIME_TOKEN_RPLUS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left + op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IMOINS: 
    case ANIME_TOKEN_RMOINS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left - op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IMULT: 
    case ANIME_TOKEN_RMULT: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left * op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_RDIV: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left / op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    default: goto error_label__unexpected_token; 
    }; 
    
  completed_huh: 
    //if (anime_syntax_filtering__lalr_mode_completed_huh(this)) goto completed; 
    MOVE_TO_NEXT_TOKEN_R(); 
    if (anime_syntax_filtering__lalr_mode_read_all_huh(this)) goto all_was_read; 
  }; 
  
 //completed: 
 all_was_read: 
#if 0 
      dprintf(stderr_d, "stack__nb = %d" "\n", stack__nb); 
#endif 
  if (stack__nb < 1) { goto error_label__stack_not_enough_items; }; 
  if (stack__nb > 1) { goto error_label__stack_too_many_items  ; }; 
  *floatval_r  = stack__array[0]; 
#if 0 
      dprintf(stderr_d, "stack__array[0] = %f" "\n", stack__array[0]); 
      dprintf(stderr_d, "*floatval_r     = %f" "\n", *floatval_r); 
#endif 
  *error_id_r  = ANIME__OK; 
  *error_str   = '\0'; 
  return *error_id_r; 
  
  
  
 error_label__error_in_syntax_filtering: { 
    //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering");  
    strlcpy(error_str, anime_syntax_filtering__error_str(this), error_size); 
    return *error_id_r; 
  }; 
  
 error_label__stack_too_many_items: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_TOO_MANY_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
 error_label__stack_not_enough_items: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_overflow: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_OVERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_underflow: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_UNDERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
 
 error_label__unexpected_token: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_UNEXPECTED_TOKEN; 
    const int_anime_token_type_t token_type = anime_token__get_type(token_env, token_i); 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Unexpected token %s", anime_token__type_get_cstr(token_type)); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
}; 



static int_anime_error_t anime_data__read_postfix_entier(int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str, const int stdlog_d, anime_syntax_filtering_t * this, anime_token_env_t * token_env, int * intval_r, const int stduser_d) { 
  if (NULL == error_id_r) { return ANIME__DATA_GENERATION__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  if (NULL ==       this) { *error_id_r = ANIME__DATA_GENERATION__NULL_SYNTAX_FILTERING; snprintf(error_str, error_size, "syntax_filtering argument is null."); return *error_id_r; }; 
  if (NULL ==  token_env) { *error_id_r = ANIME__DATA_GENERATION__NULL_TOKEN_ENV       ; snprintf(error_str, error_size, "token_env argument is null."); return *error_id_r; }; 
  if (NULL ==   intval_r) { *error_id_r = ANIME__DATA_GENERATION__NULL_INTVAL_R        ; snprintf(error_str, error_size, "intval_r argument is null."); return *error_id_r; }; 

  
  int stack__array[EXPR_STACK_SIZE]; 
  int stack__nb; 
  stack__nb = 0; 
  
  int_anime_token_t token_i; 
  //const int_anime_token_t token_nb = anime_token__get_count(token_env); 
  
  GET_CURRENT_TOKEN_R(); 
  
  for (;;) { 
    const int_anime_token_type_t token_type = anime_token__get_type(token_env, token_i); 
    //dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_token__type_get_cstr(token_type)); 
    switch (token_type) { 
    case ANIME_TOKEN_ENTIER: 
    case ANIME_TOKEN_REEL__VIRG: 
    case ANIME_TOKEN_REEL__DOT: 
    case ANIME_TOKEN_REEL__E: { 
      const char * srcval = anime_token__get_srcval_cstr(token_env, token_i); 
      if (stack__nb >= EXPR_STACK_SIZE) { goto error_label__stack_overflow; }; 
      stack__array[stack__nb] = (atoi(srcval)); 
#if 0 
      dprintf(stderr_d, "srcval = %s" "\n", srcval); 
      dprintf(stderr_d, "stack__array[%d] = %d" "\n", stack__nb, stack__array[stack__nb]); 
#endif 
      stack__nb++; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IPLUS_UNAIRE: 
    case ANIME_TOKEN_RPLUS_UNAIRE: 
      goto completed_huh; 

    case ANIME_TOKEN_IMOINS_UNAIRE: 
    case ANIME_TOKEN_RMOINS_UNAIRE: { 
      if (stack__nb < 1) { goto error_label__stack_underflow; }; 
      const int stack__i = stack__nb - 1; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %d" "\n", stack__i, stack__array[stack__i]); 
#endif 
      stack__array[stack__i] = - stack__array[stack__i]; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %d" "\n", stack__i, stack__array[stack__i]); 
#endif 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IPLUS: 
    case ANIME_TOKEN_RPLUS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left + op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IMOINS: 
    case ANIME_TOKEN_RMOINS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left - op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IMULT: 
    case ANIME_TOKEN_RMULT: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left * op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IDIV: 
    case ANIME_TOKEN_RDIV: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left / op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case ANIME_TOKEN_IMOD: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left % op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    default: goto error_label__unexpected_token; 
    }; 
    
  completed_huh: 
    //if (anime_syntax_filtering__lalr_mode_completed_huh(this)) goto completed; 
    MOVE_TO_NEXT_TOKEN_R(); 
    if (anime_syntax_filtering__lalr_mode_read_all_huh(this)) goto all_was_read; 
  }; 
  
 //completed: 
 all_was_read: 
#if 0 
      dprintf(stderr_d, "stack__nb = %d" "\n", stack__nb); 
#endif 
  if (stack__nb < 1) { goto error_label__stack_not_enough_items; }; 
  if (stack__nb > 1) { goto error_label__stack_too_many_items  ; }; 
  *intval_r  = stack__array[0]; 
#if 0 
      dprintf(stderr_d, "stack__array[0] = %d" "\n", stack__array[0]); 
      dprintf(stderr_d, "*intval_r       = %d" "\n", *intval_r); 
#endif 
  *error_id_r  = ANIME__OK; 
  *error_str   = '\0'; 
  return *error_id_r; 
  
  
  
 error_label__error_in_syntax_filtering: { 
    //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering");  
    strlcpy(error_str, anime_syntax_filtering__error_str(this), error_size); 
    return *error_id_r; 
  }; 
  
 error_label__stack_too_many_items: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_TOO_MANY_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
 error_label__stack_not_enough_items: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_overflow: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_OVERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_underflow: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_UNDERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
 
 error_label__unexpected_token: { 
    *error_id_r = ANIME__DATA_GENERATION__STACK_UNEXPECTED_TOKEN; 
    const int_anime_token_type_t token_type = anime_token__get_type(token_env, token_i); 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: Unexpected token %s", anime_token__type_get_cstr(token_type)); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
}; 







#define MOVE_TO_NEXT_TOKEN() {						\
    error_id = anime_syntax_filtering__move_to_next_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 
 
#define GET_CURRENT_TOKEN() {						\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 

#define SWITCH_TO_LALR_MODE() {						\
    error_id = anime_syntax_filtering__switch_to_lalr_mode(this); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 


#define CHECK_IDENT(_ident_) {						\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if (ANIME_TOKEN_IDENT != token_type)    { error__expected_token_type  = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type;   }; \
    if (0 != strcasecmp((_ident_), srcval)) { error__expected_token_value = (_ident_);         goto error_label__non_matching_token_value;  }; \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define CHECK_SUGAR(_expected_token_type_) {				\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    if ((_expected_token_type_) != token_type) { error__expected_token_type = (_expected_token_type_); goto error_label__non_matching_token_type; }; \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define LOOKAHEAD_THEN_READ_SIGN() {					\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    int move_forward_huh = false;					\
    if      (ANIME_TOKEN_IMOINS        == token_type) { signval = -1; move_forward_huh = true; } \
    else if (ANIME_TOKEN_RMOINS        == token_type) { signval = -1; move_forward_huh = true; } \
    else if (ANIME_TOKEN_IMOINS_UNAIRE == token_type) { signval = -1; move_forward_huh = true; } \
    else if (ANIME_TOKEN_RMOINS_UNAIRE == token_type) { signval = -1; move_forward_huh = true; } \
    else { signval = 1; };						\
    if (move_forward_huh) {						\
      MOVE_TO_NEXT_TOKEN();						\
    };									\
  }; 

#define READ_FLOAT() {							\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_ENTIER     == token_type) { floatval = (float) (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { floatval = (float) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { floatval = (float) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { floatval = (float) (atof(srcval)); } \
    else { error__expected_token_type = ANIME_TOKEN_REEL__DOT; goto error_label__non_matching_token_type; }; \
    if (signval < 0) floatval = -floatval;				\
    MOVE_TO_NEXT_TOKEN();						\
  };

#define READ_LALR_FLOAT() {						\
    SWITCH_TO_LALR_MODE();						\
    error_id = anime_data__read_postfix_float(&anime_data -> error_id, anime_data -> error_size, anime_data -> error_str, anime_data -> stdlog_d, this, token_env, &floatval, stduser_d); \
    if (error_id != ANIME__OK) { goto error_label__error_in_postfix_computation; }; \
    /*dprintf(stderr_d, "floatval = %f" "\n", floatval);*/		\
    GET_CURRENT_TOKEN();						\
  }; 

#define READ_ENTIER() {							\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_ENTIER     == token_type) { intval =       (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { intval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { intval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { intval = (int) (atof(srcval)); } \
    else { error__expected_token_type = ANIME_TOKEN_ENTIER; goto error_label__non_matching_token_type; }; \
    if (signval < 0) intval = -intval;					\
    MOVE_TO_NEXT_TOKEN();						\
  };

#define READ_LALR_ENTIER() {						\
    SWITCH_TO_LALR_MODE();						\
    error_id = anime_data__read_postfix_entier(&anime_data -> error_id, anime_data -> error_size, anime_data -> error_str, anime_data -> stdlog_d, this, token_env, &intval, stduser_d); \
    if (error_id != ANIME__OK) { goto error_label__error_in_postfix_computation; }; \
    /*dprintf(stderr_d, "intval = %d" "\n", intval);*/			\
    GET_CURRENT_TOKEN();						\
  }; 

#define READ_BOOLEEN() {						\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_TRUE       == token_type) { boolval =                 true; } \
    else if (ANIME_TOKEN_FALSE      == token_type) { boolval =                false; } \
    else if (ANIME_TOKEN_ENTIER     == token_type) { boolval =       (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { boolval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { boolval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { boolval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_IDENT      == token_type) {			\
      if      ((0 == strcasecmp("vrai", srcval)) || (0 == strcasecmp("true" , srcval))) { boolval =  true; } \
      else if ((0 == strcasecmp("faux", srcval)) || (0 == strcasecmp("false", srcval))) { boolval = false; } \
      else { goto error_label__expecting_boolean; };			\
    }									\
    else { goto error_label__expecting_boolean; };			\
    MOVE_TO_NEXT_TOKEN();						\
  };

#define READ_IDENT() {							\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if (ANIME_TOKEN_IDENT != token_type) { error__expected_token_type = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type; }; \
    identval = srcval;							\
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define READ_STRING() {							\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if (ANIME_TOKEN_STRING_C != token_type) { error__expected_token_type = ANIME_TOKEN_STRING_C; goto error_label__non_matching_token_type; }; \
    strval = anime__convert_token_cstring_to_regular_string(anime_data, srcval); \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define LOOKAHEAD_IDENT(_ident_) {					\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    lookahead_match_huh = (ANIME_TOKEN_IDENT == token_type) && (0 == strcasecmp((_ident_), srcval)); \
  }; 

#define LOOKAHEAD_TYPE(_expected_token_type_) {				\
    error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != ANIME__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_token__get_type       (token_env, token_i);	\
    lookahead_match_huh = ((_expected_token_type_) == token_type);	\
  }; 

#define LOOKAHEAD_SUGAR LOOKAHEAD_TYPE 

 


int_anime_error_t anime_data_generation_003_from_syntax_filtering(anime_token_env_t * token_env, anime_t * anime_data, const int stduser_d) { 
  if (NULL ==  token_env) { return ANIME__DATA_GENERATION__NULL_TOKEN_ENV ; }; 
  if (NULL == anime_data) { return ANIME__DATA_GENERATION__NULL_ANIME_DATA; }; 
  int_anime_token_t token_i = 0; 
  int token_type; 
  int success_huh = false; 
  const char * srcval; 
  int signval = 1; 
  float floatval; 
  int intval; 
  int boolval; 
  const char * identval; 
  const char * strval; 
  int lookahead_match_huh = false; 
  int error__expected_token_type; 
  const char * error__expected_token_value; 
  int_anime_error_t error_id; 
#if 0 
  //char this_memory_space[anime_syntax_filtering__sizeof]; // For some unknown reasons, VLAs make «-fstack-protector» fail. 
  //char * this_memory_space = alloca(anime_syntax_filtering__sizeof); // This alloca failed. And zero-es got written on the stack... 
  enum { this_memory_space__bytesize = sizeof(anime_syntax_filtering_t) }; 
  char this_memory_space[this_memory_space__bytesize]; 
  anime_syntax_filtering_t * this = (anime_syntax_filtering_t *) &this_memory_space; 
  
  anime__bzero(anime_data); 
  anime_data -> filled_huh = -1; 
  anime_syntax_filtering__make_r(this, anime_data -> stdlog_d); 
#else
  //enum { this_memory_space__bytesize = sizeof(anime_syntax_filtering_t) }; // Unknown
  enum { this_memory_space__bytesize = 1 << 14 }; 
  char this_memory_space[this_memory_space__bytesize]; 
  anime_syntax_filtering_t * this = anime_syntax_filtering__make_b(this_memory_space__bytesize, this_memory_space, NULL, stduser_d); 

  //anime__bzero(anime_data); 
  anime_data -> actions_nb = 0; 
  anime_data -> events_nb = 0; 
  anime_data -> membres_nb = 0; 
  anime_data -> racines_nb = 0; 

  anime_data -> filled_huh = -1; 
#endif 

  const int_anime_token_t token_nb = anime_token__get_count(token_env); 
  if (0 >= token_nb) { goto error_label__not_enough_tokens; }; 
  anime_data -> filename = anime__string_stack__push_lookup(anime_data, anime_token__get_srcfile_cstr(token_env, 0)); 
  
  error_id = anime_syntax_filtering__get_current_token(this, token_env, &token_i); 
  if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
  
  int8_t   section_physique_nb  = 0; 
  int8_t   section_gameplay_nb  = 0; 
  int8_t   section_graphique_nb = 0; 
  int8_t   section_unknown_nb   = 0; 
  
  for (;;) { 
    if (token_i == token_nb - 1) { break; }; 
    LOOKAHEAD_IDENT("physique" ); if (lookahead_match_huh) { goto section_physique ; }; 
    LOOKAHEAD_IDENT("gameplay" ); if (lookahead_match_huh) { goto section_gameplay ; }; 
    LOOKAHEAD_IDENT("graphique"); if (lookahead_match_huh) { goto section_graphique; }; 
    goto section_unknown; 

  section_physique: { 
      section_physique_nb++; 
      if (section_physique_nb > 1) { 
	const int_anime_token_t section_name_token = token_i; 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Extraneous 'physique' section"); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
#if 1 
	MOVE_TO_NEXT_TOKEN();
	error_id = anime_syntax_filtering__skip_to_closing_paren(this, token_env, &token_i); 
	if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
	MOVE_TO_NEXT_TOKEN();
#else 
	dprintf(stderr_d, "DEBUG: " "TOKEN_I = %d" "\n", token_i); 
	token_i++; 
	dprintf(stderr_d, "DEBUG: " "TOKEN_I = %d" "\n", token_i); 
	error_id = anime_syntax_filtering__skip_to_closing_paren(this, token_env, &token_i); 
	dprintf(stderr_d, "DEBUG: " "ERROR_ID = %d" "\n", error_id); 
	dprintf(stderr_d, "DEBUG: " "ERROR_ID = ANIME__SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS = %d" "\n", ANIME__SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS); 
	dprintf(stderr_d, "DEBUG: " "TOKEN_I = %d" "\n", token_i); 
	if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
	dprintf(stderr_d, "DEBUG: " "TOKEN_I = %d" "\n", token_i); 
	token_i++; 
	dprintf(stderr_d, "DEBUG: " "TOKEN_I = %d" "\n", token_i); 
#endif 
	continue; 
      }; 
      
      CHECK_IDENT("physique"); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	CHECK_IDENT("zone"); CHECK_IDENT("de"); CHECK_IDENT("choc"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	  CHECK_IDENT("longueur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> choc_longueur = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("largeur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> choc_largeur  = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("hauteur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> choc_hauteur  = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("masse"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> masse = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      continue; 
    }; 
    
  section_gameplay: { 
      section_gameplay_nb++; 
      if (section_gameplay_nb > 1) { 
	const int_anime_token_t section_name_token = token_i; 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Extraneous 'gameplay' section"); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
	MOVE_TO_NEXT_TOKEN(); 
	error_id = anime_syntax_filtering__skip_to_closing_paren(this, token_env, &token_i); 
	if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
	MOVE_TO_NEXT_TOKEN(); 
	continue; 
      }; 
    
      CHECK_IDENT("gameplay"); 
      CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	CHECK_IDENT("points"    ); CHECK_IDENT("de"); CHECK_IDENT("vie"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_ENTIER(); anime_data -> vie = intval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("invincible"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_BOOLEEN(); anime_data -> invincible = boolval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("hostile"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_BOOLEEN(); anime_data -> hostile    = boolval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 

	for (;;) { 
	  LOOKAHEAD_IDENT("action" ); if (!lookahead_match_huh) break; 
	  
	  const uint8_t action_i = anime_data -> actions_nb; 
	  
	  if (action_i >= anime_actions_size) { 
	    CHECK_IDENT("action"); 
	    const int_anime_token_t action_token = token_i; 
	    const int error_location_strlen = action_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, action_token - 1), anime_token__get_line1(token_env, action_token - 1), anime_token__get_column0(token_env, action_token - 1)); 
	    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_strlen); 
	    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "WARNING: Too many 'action' fields — can store at most %u, and already storing %u — Extraneous 'action' fields will be ignored", (unsigned int)anime_actions_size, (unsigned int) anime_data -> actions_nb); 
	    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
	    MOVE_TO_NEXT_TOKEN(); // Skip to the opening parenthesis 
	    error_id = anime_syntax_filtering__skip_to_closing_paren(this, token_env, &token_i); 
	    if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
	    MOVE_TO_NEXT_TOKEN(); // Skipping the current closing parenthesis. 
	    continue; 
	  }; 
	  
	  anime_data -> actions_nb++; 
	  
	  CHECK_IDENT("action"); 
	  { 
	    LOOKAHEAD_SUGAR(ANIME_TOKEN_IDENT); 
	    if (lookahead_match_huh) { READ_IDENT(); anime_data -> actions_array_nom[action_i] = anime__string_stack__push_lookup(anime_data, identval); } 
	    else { READ_STRING(); anime_data -> actions_array_nom[action_i] = anime__string_stack__push_lookup(anime_data, strval); }; 
	  };
	  CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	    CHECK_IDENT("affichage"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> actions_array_affichage[action_i]  = anime__string_stack__push_lookup(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("icone"       ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> actions_array_icone    [action_i]  = anime__string_stack__push_lookup(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("gestionnaire"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	      CHECK_IDENT("fichier"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> actions_array_gestionnaire_fichier[action_i]  = anime__string_stack__push_lookup(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	      { LOOKAHEAD_SUGAR(ANIME_TOKEN_PROCEDURE); if (lookahead_match_huh) { MOVE_TO_NEXT_TOKEN(); } else  { CHECK_IDENT("procedure" ); }; }; CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> actions_array_gestionnaire_proc   [action_i]  = anime__string_stack__push_lookup(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 

	  
	}; 

      }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      continue; 
    }; 
      
  section_graphique: { 
      section_graphique_nb++; 
      if (section_graphique_nb > 1) { 
	const int_anime_token_t section_name_token = token_i; 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Extraneous 'graphique' section"); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
	MOVE_TO_NEXT_TOKEN(); 
	error_id = anime_syntax_filtering__skip_to_closing_paren(this, token_env, &token_i); 
	if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
	MOVE_TO_NEXT_TOKEN(); 
	continue; 
      }; 
      
      CHECK_IDENT("graphique"); 
      CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	for (;;) { 
	  LOOKAHEAD_IDENT("membre"); if (!(lookahead_match_huh)) { break; }; 
	  MOVE_TO_NEXT_TOKEN(); 
	  if (anime_data -> membres_nb >= anime_data -> membres_size) { goto error_label__membres_stack_overflow; }; 
	  READ_IDENT(); anime_data -> membres_nom[anime_data -> membres_nb] = anime__string_stack__push_lookup(anime_data, identval); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	    CHECK_IDENT("fils"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("image"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> membres_image[anime_data -> membres_nb] = anime__string_stack__push_lookup(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("largeur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> membres_largeur[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("hauteur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> membres_hauteur[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("angle"); CHECK_IDENT("max"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> membres_angle_max_y[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	  anime_data -> membres_nb ++; 
	}; 
	
	CHECK_IDENT("membres"); CHECK_IDENT("racines"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); 
	for (;;) { 
	  LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) { MOVE_TO_NEXT_TOKEN(); break; }; 
	  CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	    if (anime_data -> racines_nb >= anime_data -> racines_size) { goto error_label__racines_stack_overflow; }; 
	    CHECK_IDENT("qui"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_IDENT(); anime_data -> racines_qui[anime_data -> racines_nb] = anime__string_stack__push_lookup(anime_data, identval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("x"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> racines_x[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("y"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> racines_y[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("z"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> racines_z[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    CHECK_IDENT("angle"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_LALR_FLOAT(); anime_data -> racines_angle_y[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	  anime_data -> racines_nb ++; 
	  LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) { MOVE_TO_NEXT_TOKEN(); break; }; 
	  CHECK_SUGAR(ANIME_TOKEN_VIRGULE); 
	}; 
	
      }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      continue; 
    }; 

  section_unknown: { 
      section_unknown_nb++; 
      const int_anime_token_t section_name_token = token_i; 
      const char * section_name_token_srcval = anime_token__get_srcval_cstr(token_env, section_name_token); 
      const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
      const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
      snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Unknown '%s' section", section_name_token_srcval); 
      if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
      if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
      MOVE_TO_NEXT_TOKEN(); 
      error_id = anime_syntax_filtering__skip_to_closing_paren(this, token_env, &token_i); 
      if (ANIME__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
      MOVE_TO_NEXT_TOKEN(); 
      continue; 
    };  
    
  }; 

  if (0 == section_physique_nb ) { goto error_missing_section_physique ; }; 
  if (0 == section_gameplay_nb ) { goto error_missing_section_gameplay ; }; 
  if (0 == section_graphique_nb) { goto error_missing_section_graphique; }; 
  
  if (1 < section_physique_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There were %d 'physique' sections — Only the first one was used, following ones got discarded.", section_physique_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  
  if (1 < section_gameplay_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There were %d 'gameplay' sections — Only the first one was used, following ones got discarded.", section_gameplay_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  
  if (1 < section_graphique_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There were %d 'graphique' sections — Only the first one was used, following ones got discarded.", section_graphique_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  
  if (0 < section_unknown_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There were %d unknown sections — They all got discarded.", section_unknown_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  

  anime_data -> filled_huh = 2; 

  return ANIME__OK; 



 error_label__membres_stack_overflow: {
    anime_data -> error_id = ANIME__DATA_GENERATION__MEMBRES_OVERFLOW; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Too many 'membre'. I can register only %d membres. (To circumvent that, I must be compiled with a larger size.)", anime_data -> membres_size); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   

 error_label__racines_stack_overflow: {
    anime_data -> error_id = ANIME__DATA_GENERATION__RACINES_OVERFLOW; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Too many 'racines'. I can register only %d racines. (To circumvent that, I must be compiled with a larger size.)", anime_data -> racines_size); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   

 error_missing_section_physique: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_PHYSIQUE_SECTION; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Missing 'physique' section"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   
  
 error_missing_section_gameplay: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_GAMEPLAY_SECTION; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Missing 'gameplay' section"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   
  
 error_missing_section_graphique: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_GRAPHIQUE_SECTION; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Missing 'graphique' section"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   
  
 error_label__error_in_syntax_filtering: { 
#if 0 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering"); 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_syntax_filtering__error_str(this)); 
#endif 
    anime_data -> error_id = error_id; 
    strlcpy(anime_data -> error_str, anime_syntax_filtering__error_str(this), anime_data -> error_size); 
#if 0 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%d" "\n", __func__, anime_data -> error_size); 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); 
#endif 
    return anime_data -> error_id; 
  }; 

 error_label__error_in_postfix_computation: { 
    return anime_data -> error_id; 
  }; 
  
 error_label__not_enough_tokens: { 
    //const int token_count_left = token_nb - token_i; 
    anime_data -> error_id = ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS; 
    const int error_location_len = token_i <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i - 1), anime_token__get_line1(token_env, token_i - 1), anime_token__get_column0(token_env, token_i - 1)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "End-of-file reached, while parsing not completed"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  }; 

 error_label__too_many_tokens: { 
    const int token_count_left = token_nb - token_i; 
    anime_data -> error_id = ANIME__DATA_GENERATION__TOO_MANY_TOKENS;   
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Parsing done, but still non-read tokens (%d too many tokens)", token_count_left); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  }; 

 error_label__expecting_boolean:  {
    const char * error__expected_token_type_cstr = "BOOLEAN"; 
    const char * error__got_token_type_cstr      = anime_token__type_get_cstr(token_type); 
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };

 error_label__non_matching_token_type: {
    const char * error__expected_token_type_cstr = anime_token__type_get_cstr(error__expected_token_type); 
    const char * error__got_token_type_cstr      = anime_token__type_get_cstr(                token_type); 
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };

 error_label__non_matching_token_value: {
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE; 
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token value — Expecting: '%s' ; Got: '%s'", error__expected_token_value, srcval); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };


}; 










