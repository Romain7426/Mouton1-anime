#include "anime_inc.hi"
#include "anime.h"
#include "anime_type.h"
#include "anime_syntax_module.h"
#include "anime_lexer_module_token_type.hi"


static int_anime_error_t anime__syntax__braces_are_balanced_huh(const anime_t * this); 
static int_anime_error_t anime__syntax__structure_check_and_fill__aux(anime_t * anime_data, const int stdwarning_d, const int stderror_d); 

int_anime_error_t anime__syntax__structure_check_and_fill(anime_t * anime_data, const int stdwarning_d, const int stderror_d) { 
  int_anime_error_t error_id; 
  
  error_id = anime__syntax__braces_are_balanced_huh(anime_data); 
  if (ANIME__OK != error_id) return error_id; 
  //anime_data -> filled_huh = 2; 

  error_id = anime__syntax__structure_check_and_fill__aux(anime_data, stdwarning_d, stderror_d); 
  if (ANIME__OK != error_id) return error_id;   
  //anime_data -> filled_huh = 2; 

  return ANIME__OK; 
}; 






// ********************************************
// EXPR - ARITY COMPUTATION 


static int_anime_error_t anime__syntax_expr__arity__compute__one(anime_t * this, const int_expr_t expr_id) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int_anime_error_t error_id; 

  const int_lexeme_t lexeme_start_i = this -> expr_lexeme_start_i[expr_id]; 
  const int8_t       lexemes_nb     = this -> expr_lexemes_nb    [expr_id]; 
  goto label__body; 
  
  int16_t error_sub__line = -1;
 label__error__sub: {
#if 1 
    DISPLAY_TRACE(this -> stdlog_d, error_id); 
#else
    enum { ERROR_STR_BYTESIZE = 2048 }; 
    char error_str[ERROR_STR_BYTESIZE]; 
    snprintf(error_str, ERROR_STR_BYTESIZE, "<%s>: " "%s[%d]: " "%s: %s" "\n", anime__filename_get(this), error_id > 0 ? LANG("Attention","Warning") : LANG("Erreur","Error"), error_id, int_anime_error__get_cstr(error_id), anime__error_cstr_get(this)); 
    if (this -> stdlog_d > 0) {  dputs9(this -> stdlog_d, "{", __FILE__, ":", STRINGIFY(__LINE__), ":<", __func__, "()>}: ", error_str, "\n"); }; 
#endif
    return error_id; 
  }; 
  
  
 label__body: { 
    // FRA: Le principe est simple - l'opérateur est unaire si: 
    // FRA:  - si il est au début d'une expression (ou d'une sous-expression) 
    // FRA:  - si, dans une liste d'opérateurs consécutifs, il n'est pas le premier 
    // FRA:  - si il est précédé par une parenthèse 
    // FRA: Et c'est tout. 
    
    for (int_lexeme_t shift_i = 0; shift_i < lexemes_nb; shift_i++) { 
      const int_lexeme_t token_i = lexeme_start_i + shift_i; 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 

      const int8_t constant_value_huh = CONSTANT_VALUE_HUH(token_type); 
      if (constant_value_huh) continue; 
      
      const int8_t infix_binary_operator_huh = BINARY_OPERATOR_HUH(token_type);
      if (infix_binary_operator_huh) continue; 

      const int8_t unary_or_binary_operator_huh = UNARY_AND_BINARY_OPERATOR_HUH(token_type); 
      if (not(unary_or_binary_operator_huh)) continue; 

      const int_anime_token_type_t unary_token_type  = CONVERT_TO_UNARY_TYPE(token_type); 
      const int_anime_token_type_t binary_token_type = CONVERT_TO_BINARY_TYPE(token_type); 
      { 
	if (lexeme_start_i == token_i) { this -> lexeme_stack__type[token_i] = unary_token_type; continue; }
	
	const int_anime_token_type_t token_prec_type = this -> lexeme_stack__type[token_i-1]; 
	
	const int8_t openpar_huh = (int_member_huh((token_prec_type), ANIME_TOKEN_OPENPAR, ANIME_TOKEN_OPENBRACKET,ANIME_TOKEN_OPENBRACE)); 
	if (openpar_huh) { this -> lexeme_stack__type[token_i] = unary_token_type; continue; };
	
	const int8_t infix_binary_operator_huh = BINARY_OPERATOR_HUH(token_prec_type);
	if (infix_binary_operator_huh) { this -> lexeme_stack__type[token_i] = unary_token_type; continue; };
	
	const int8_t prefix_unary_operator_huh = UNARY_PREFIX_OPERATOR_HUH(token_prec_type);
	if (prefix_unary_operator_huh) { this -> lexeme_stack__type[token_i] = unary_token_type; continue; };
	
	const int8_t unary_or_binary_operator_huh = UNARY_AND_BINARY_OPERATOR_HUH(token_prec_type); 
	if (unary_or_binary_operator_huh) { this -> lexeme_stack__type[token_i] = unary_token_type; continue; };
	
	this -> lexeme_stack__type[token_i] = binary_token_type; 
	continue; 
      }; 
      
      
    };
    
    return ANIME__OK; 
  }; 
};


int_anime_error_t anime__syntax_expr__arity__compute(anime_t * this) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int_anime_error_t error_id; 
  goto label__body; 
  
  int16_t error_sub__line = -1;
 label__error__sub: {
#if 1 
    DISPLAY_TRACE(this -> stdlog_d, error_id); 
#else
    enum { ERROR_STR_BYTESIZE = 2048 }; 
    char error_str[ERROR_STR_BYTESIZE]; 
    snprintf(error_str, ERROR_STR_BYTESIZE, "<%s>: " "%s[%d]: " "%s: %s" "\n", anime__filename_get(this), error_id > 0 ? LANG("Attention","Warning") : LANG("Erreur","Error"), error_id, int_anime_error__get_cstr(error_id), anime__error_cstr_get(this)); 
    if (this -> stdlog_d > 0) {  dputs9(this -> stdlog_d, "{", __FILE__, ":", STRINGIFY(__LINE__), ":<", __func__, "()>}: ", error_str, "\n"); }; 
#endif
    return error_id; 
  }; 
  
 label__body: { 
    for (int_expr_t expr_id = 0; expr_id < this -> expr_nb; expr_id++) { 
      error_id = anime__syntax_expr__arity__compute__one(this, expr_id); 
      if (ANIME__OK != error_id) return error_id;
    }; 
    return ANIME__OK; 
  }; 
}; 
  
    




// *************************************************** 
// EXPRESSION -> SYNTAX CHECK

static bool_t anime__syntax_expr__has_token_huh(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb, const int_anime_token_type_t sought_token_type) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  for (int_lexeme_t i = 0; i < expr_lexemes_nb; i++) {
    //dputs3(STDERR_FILENO, "i = ", int_string(i), "\n"); 
    const int_anime_token_type_t current_token_type = this -> lexeme_stack__type[expr_lexeme_start_i + i]; 
    if (sought_token_type == current_token_type) return true;
  };
  return false; 
};

static int8_t anime__syntax_expr__count_token(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb, const int_anime_token_type_t sought_token_type) { 
  int8_t count = 0; 
  for (int_lexeme_t i = 0; i < expr_lexemes_nb; i++) {
    const int_anime_token_type_t current_token_type = this -> lexeme_stack__type[expr_lexeme_start_i + i]; 
    if (sought_token_type == current_token_type) count++;
  };
  return count; 
};

static int8_t anime__syntax_expr__count_constants(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb) { 
  int8_t count = 0; 
  for (int_lexeme_t i = 0; i < expr_lexemes_nb; i++) {
    const int_anime_token_type_t token_type = this -> lexeme_stack__type[expr_lexeme_start_i + i]; 
    const bool_t const_huh = CONSTANT_VALUE_HUH(token_type); 
    if (not(const_huh)) continue; 
    count++;
  };
  return count; 
};

static int8_t anime__syntax_expr__count_binary(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb) { 
  int8_t count = 0; 
  for (int_lexeme_t i = 0; i < expr_lexemes_nb; i++) {
    const int_anime_token_type_t token_type = this -> lexeme_stack__type[expr_lexeme_start_i + i]; 
    const bool_t binary_huh = BINARY_OPERATOR_HUH(token_type); 
    if (not(binary_huh)) continue; 
    count++;
  };
  return count; 
};

static int_anime_error_t anime__syntax_expr__balanced_huh(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb) { 
  int_lexeme_t           open__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  int_anime_token_type_t open__type  [ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  uint8_t                open__nb; 
  goto label__body; 


 label__error__nestedness_too_deep: {
    return ANIME__SYNTAX__EXPR_TOO_DEEP; 
  };
  
 label__error__missing_close: { 
    const int_anime_token_type_t token_type = open__type[open__nb-1]; 
    if (ANIME_TOKEN_OPENPAR == token_type) return ANIME__SYNTAX__EXPR_MISSING_CLOSEPAR; 
    return ANIME__SYNTAX__EXPR_MISSING_CLOSEBRACKET; 
  };
  
  int_anime_token_type_t error__missing_open__close_token_type; 
 label__error__missing_open: { 
    const   int_anime_token_type_t error__missing_open__open_token_type = UNARY_OUTFIX_OPERATOR__CLOSE_GET_MATCHING_OPEN(error__missing_open__close_token_type);
    if (ANIME_TOKEN_OPENPAR == error__missing_open__open_token_type) return ANIME__SYNTAX__EXPR_MISSING_OPENPAR; 
    return ANIME__SYNTAX__EXPR_MISSING_OPENBRACKET; 
  };

 label__error__mismatch: { 
    const int_anime_token_type_t token_type = open__type[open__nb-1]; 
    if (ANIME_TOKEN_OPENPAR == token_type) return ANIME__SYNTAX__EXPR_MISMATCH_OPENPAR_CLOSEBRACKET;
    return ANIME__SYNTAX__EXPR_MISMATCH_OPENBRACKET_CLOSEPAR; 
  }; 
  
 label__body: { 
    open__nb = 0; 
  
    for (int_lexeme_t shift_i = 0; shift_i < expr_lexemes_nb; shift_i++) { 
      const int_lexeme_t token_i = expr_lexeme_start_i + shift_i; 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_OPENPAR  == token_type) goto label__open; 
      if (ANIME_TOKEN_CLOSEPAR == token_type) goto label__close; 
      if (ANIME_TOKEN_OPENBRACKET  == token_type) goto label__open; 
      if (ANIME_TOKEN_CLOSEBRACKET == token_type) goto label__close; 
      continue; 
    
    label__open: { 
	if (ANIME__EXPRESSION_NESTEDNESS_MAX <= open__nb) goto label__error__nestedness_too_deep; 
	open__lexeme[open__nb] = token_i; 
	open__type  [open__nb] = token_type; 
	open__nb++; 
	continue; 
      };
    
    label__close: { 
	if (0 >= open__nb) { error__missing_open__close_token_type = token_type; goto label__error__missing_open; }; 
	open__nb--; 
	const int_anime_token_type_t open_token_type = UNARY_OUTFIX_OPERATOR__CLOSE_GET_MATCHING_OPEN(token_type); 
	if (open_token_type != open__type[open__nb]) goto label__error__mismatch; 
	continue; 
      }; 
    }; 
    
    // FRA: Ce cas ne devrait pas survenir puisque nous avons compté les parenthèses en amont.
    if (0 < open__nb) goto label__error__missing_close;
    assert(0 == open__nb); 
    return ANIME__OK; 
  };  
}; 



static bool_t anime__syntax_expr__neighboring_constants_huh(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb) { 
  goto label__body; 
  
 label__body: { 
    bool_t prev_was_const = false; 
    
    for (int_lexeme_t shift_i = 0; shift_i < expr_lexemes_nb; shift_i++) { 
      const int_lexeme_t token_i = expr_lexeme_start_i + shift_i; 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 
      const bool_t const_huh = CONSTANT_VALUE_HUH(token_type); 
      if (not(const_huh)) { prev_was_const = false; continue; }; 
      if (prev_was_const) return true;
      prev_was_const = true;
      continue;
    }; 
    
    return false; 
  };  
}; 

static bool_t anime__syntax_expr__neighboring_binop_huh(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb) { 
  goto label__body; 
  
 label__body: { 
    bool_t prev_was_binop = false; 
    
    for (int_lexeme_t shift_i = 0; shift_i < expr_lexemes_nb; shift_i++) { 
      const int_lexeme_t token_i = expr_lexeme_start_i + shift_i; 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 
      const bool_t binop_huh = BINARY_OPERATOR_HUH(token_type); 
      if (not(binop_huh)) { prev_was_binop = false; continue; }; 
      if (prev_was_binop) return true;
      prev_was_binop = true;
      continue; 
    }; 
    
    return false; 
  };  
}; 


static int_anime_error_t anime__syntax_expr__sous_expression_huh(const anime_t * this, const int_lexeme_t expr_lexeme_start_i, const int8_t expr_lexemes_nb) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int_anime_error_t      error_id; 
  int_lexeme_t            open__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  int_lexeme_t           close__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  int8_t                 syntax_ok_huh[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  uint8_t                open_nb; 
  goto label__body; 

  int16_t error_sub__line; 
  
 label__fill_sous_expr: {
    for (int_lexeme_t shift_i = 0; shift_i < expr_lexemes_nb; shift_i++) { 
      const int_lexeme_t token_i = expr_lexeme_start_i + shift_i; 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_OPENPAR  == token_type) goto label__open; 
      if (ANIME_TOKEN_CLOSEPAR == token_type) goto label__close; 
      if (ANIME_TOKEN_OPENBRACKET  == token_type) goto label__open; 
      if (ANIME_TOKEN_CLOSEBRACKET == token_type) goto label__close; 
      continue; 

    label__error__nestedness_too_deep: {
	error_id = ANIME__SYNTAX__EXPR_TOO_DEEP; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };
      
    label__error__missing_open: { 
	error_id =  (ANIME_TOKEN_CLOSEPAR == token_type) ? ANIME__SYNTAX__EXPR_MISSING_OPENPAR : ANIME__SYNTAX__EXPR_MISSING_OPENBRACKET; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };

    label__open: { 
	if (ANIME__EXPRESSION_NESTEDNESS_MAX <= open_nb) { error_sub__line = __LINE__; goto label__error__nestedness_too_deep; }; 
	open__lexeme[open_nb] = token_i; 
	close__lexeme[open_nb] = -1; 
	open_nb++; 
	continue; 
      };
      
    label__close: { 
	if (0 >= open_nb) { error_sub__line = __LINE__; goto label__error__missing_open; }; 
	int8_t j = open_nb; 
	for (;;) {
	  j--;
	  if (0 > j) { error_sub__line = __LINE__; goto label__error__missing_open; }; 
	  if (-1 != close__lexeme[j]) continue;
	  close__lexeme[j] = token_i; 
	  break; 
	};
	continue; 
      }; 

    };

      
    for (;;) { 
      int8_t j = open_nb; 
      for (;;) {
	j--;
	if (0 > j) break; 
	if (-1 != close__lexeme[j]) continue;
	{ error_sub__line = __LINE__; goto label__error__missing_close; }; 
      };
      break;

    label__error__missing_close: { 
	const int_anime_token_type_t token_type = this -> lexeme_stack__type[j]; 
  	error_id = (ANIME_TOKEN_OPENPAR == token_type) ? ANIME__SYNTAX__EXPR_MISSING_CLOSEPAR : ANIME__SYNTAX__EXPR_MISSING_CLOSEBRACKET; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };

    };
    
    goto label__fill_done;
  };
  
  
  int_lexeme_t token_start_i;
  int_lexeme_t token_end_i;
  bool_t sous_expr_check_huh; 
  int_lexeme_t unexpected_token; 
  enum { STATE_1_DEBUT, STATE_2_APRES_BINOP, STATE_3_APRES_CONST }; 
 label__sous_expr_check: {
    sous_expr_check_huh = false; 
    unexpected_token = -1; 
    int8_t current_state = STATE_1_DEBUT; 
    for (int_lexeme_t j = token_start_i + 1; j < token_end_i; j++) { 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[j]; 
      if (STATE_1_DEBUT       == current_state) goto label__state1;
      if (STATE_2_APRES_BINOP == current_state) goto label__state2;
      if (STATE_3_APRES_CONST == current_state) goto label__state3;
      goto label__error__etat_inconnu; 
      
    label__state1: { 
	assert(STATE_1_DEBUT == current_state); 
	// Ici, on est au début d'une expression. 
	if (UNARY_PREFIX_OPERATOR_HUH(token_type)) continue; 
	if (BINARY_OPERATOR_HUH(token_type)) { unexpected_token = j; goto label__error__unexpected_binop; }; 
	if (CONSTANT_VALUE_HUH(token_type)) { current_state = STATE_3_APRES_CONST; continue; }; 
	if (UNARY_OUTFIX_OPERATOR_HUH__OPEN(token_type)) {
	  for (int8_t q = 0; q < open_nb; q++) { 
	    if (j == open__lexeme[q]) { j = close__lexeme[q]; current_state = STATE_3_APRES_CONST; continue; };
	  };
	  { unexpected_token = j; goto label__error__openpar_not_found; }; 
	};
	{ unexpected_token = j; goto label__error__unexpected_token; }; 
      };

    label__state2: { 
	assert(STATE_2_APRES_BINOP == current_state); 
	assert(false); 
      };

    label__state3: { 
	assert(STATE_3_APRES_CONST == current_state); 
	// Ici, on vient de lire une constante. 
	// Et donc, deux possibilités: soit (i) un opérateur binaire, soit (ii) la fin de l'expression. 
	if (j + 1 == token_end_i) { sous_expr_check_huh = true; break; }; 
	if (BINARY_OPERATOR_HUH(token_type)) { current_state = STATE_1_DEBUT; continue; }; 
	{ unexpected_token = j; goto label__error__unexpected_token; }; 
      };

    label__error__etat_inconnu: {
	error_id = ANIME__SYNTAX__EXPR_ETAT_INCONNU; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };

    label__error__unexpected_token: {
	error_id = ANIME__SYNTAX__EXPR_UNEXPECTED_TOKEN; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };
      
    label__error__unexpected_binop: {
	error_id = ANIME__SYNTAX__EXPR_UNEXPECTED_BINOP; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };

    label__error__openpar_not_found: {
	error_id = ANIME__SYNTAX__EXPR_OPENPAR_NOT_FOUND; 
	//this -> error_id = error_id; *this -> error_str = '\0'; 
	DISPLAY_TRACE(this -> stdlog_d, error_id); 
	return error_id; 
      };

      assert(false);
    };

    goto label__sous_expr_check__done; 
  };
  
  
 label__body: {
    goto label__fill_sous_expr; label__fill_done: {}; 
    if (0 == open_nb) return ANIME__OK; 
    
    { 
      int8_t t = open_nb;
      for (;;) { 
	t--; 
	if (0 > t) break;
	token_start_i = open__lexeme [t]; 
	token_end_i   = close__lexeme[t]; 
	goto label__sous_expr_check; label__sous_expr_check__done: {}; 
      };
    };

    return ANIME__OK;;
  };
};


static int_anime_error_t anime__syntax_expr__check_syntax__one(const anime_t * this, const int_expr_t expr_id) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int_anime_error_t error_id; 
  goto label__body; 

  int16_t error_sub__line = -1;
 label__error__sub: { 
    DISPLAY_TRACE(this -> stdlog_d, error_id); 
    return error_id; 
  }; 

 label__body: {  
    const int_lexeme_t expr_lexeme_start_i = this -> expr_lexeme_start_i[expr_id]; 
    const int8_t       expr_lexemes_nb     = this -> expr_lexemes_nb    [expr_id]; 

#if 0
    if (23 == expr_lexeme_start_i) {
      dputs3(STDERR_FILENO, "expr_id: ", int_string(expr_id), "\n"); 
      dputs3(STDERR_FILENO, "expr_lexemes_nb:    ", int_string(expr_lexemes_nb), "\n"); 
      assert(false); 
    };
#endif 
  
    const bool_t has_openbrace_huh = anime__syntax_expr__has_token_huh(this, expr_lexeme_start_i, expr_lexemes_nb, ANIME_TOKEN_OPENBRACE); 
    if (has_openbrace_huh) { return ANIME__SYNTAX__EXPR_HAS_OPENBRACE; }; 

    const bool_t has_closebrace_huh = anime__syntax_expr__has_token_huh(this, expr_lexeme_start_i, expr_lexemes_nb, ANIME_TOKEN_CLOSEBRACE); 
    if (has_closebrace_huh) { return ANIME__SYNTAX__EXPR_HAS_CLOSEBRACE; }; 

    const int8_t  openbracket_count = anime__syntax_expr__count_token(this, expr_lexeme_start_i, expr_lexemes_nb, ANIME_TOKEN_OPENBRACKET); 
    const int8_t closebracket_count = anime__syntax_expr__count_token(this, expr_lexeme_start_i, expr_lexemes_nb, ANIME_TOKEN_CLOSEBRACKET); 
    if (openbracket_count > closebracket_count) { return ANIME__SYNTAX__EXPR_TOO_MANY_OPENBRACKETS; }; 
    if (openbracket_count < closebracket_count) { return ANIME__SYNTAX__EXPR_TOO_MANY_CLOSEBRACKETS; }; 

    const int8_t  openpar_count = anime__syntax_expr__count_token(this, expr_lexeme_start_i, expr_lexemes_nb, ANIME_TOKEN_OPENPAR); 
    const int8_t closepar_count = anime__syntax_expr__count_token(this, expr_lexeme_start_i, expr_lexemes_nb, ANIME_TOKEN_CLOSEPAR); 
    if (openpar_count > closepar_count) { return ANIME__SYNTAX__EXPR_TOO_MANY_OPENPARS; }; 
    if (openpar_count < closepar_count) { return ANIME__SYNTAX__EXPR_TOO_MANY_CLOSEPARS; }; 
  
    error_id = anime__syntax_expr__balanced_huh(this, expr_lexeme_start_i, expr_lexemes_nb);  
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 

    const bool_t neighboring_constants_huh = anime__syntax_expr__neighboring_constants_huh(this, expr_lexeme_start_i, expr_lexemes_nb); 
    if (neighboring_constants_huh) { return ANIME__SYNTAX__EXPR_NEIGHBORING_CONSTANTS; }; 
  
    const bool_t neighboring_binop_huh = anime__syntax_expr__neighboring_binop_huh(this, expr_lexeme_start_i, expr_lexemes_nb); 
    if (neighboring_binop_huh) { return ANIME__SYNTAX__EXPR_NEIGHBORING_BINARY_OP; }; 
  
    const int8_t constants_count = anime__syntax_expr__count_constants(this, expr_lexeme_start_i, expr_lexemes_nb); 
    const int8_t binary_count    = anime__syntax_expr__count_binary   (this, expr_lexeme_start_i, expr_lexemes_nb); 
    if (constants_count > 1 + binary_count) { return ANIME__SYNTAX__EXPR_TOO_MANY_CONSTANTS; }; 
    if (constants_count < 1 + binary_count) { return ANIME__SYNTAX__EXPR_TOO_MANY_BINARY_OP; }; 
  
#if 0  
    if (23 == expr_lexeme_start_i) {
      dputs3(STDERR_FILENO, "constants_count: ", int_string(constants_count), "\n"); 
      dputs3(STDERR_FILENO, "binary_count:    ", int_string(binary_count), "\n"); 
      assert(false); 
    };
#endif 
  
    error_id = anime__syntax_expr__sous_expression_huh(this, expr_lexeme_start_i, expr_lexemes_nb);
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
  
    return ANIME__OK; 
  }; 
};




// Pour le moment, cette fonction ne détecte pas:  MaSSe := 240. (* +) 1;
// Car il faudrait rentrer dans chaque sous-expression, réduire, puis itérer.
// (Ce qui revient à faire un automte.) 
int_anime_error_t anime__syntax_expr__check_syntax(const anime_t * this) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  int_anime_error_t error_id = ANIME__OK; 
  
  for (int_expr_t expr_id = 0; expr_id < this -> expr_nb; expr_id++) { 
    error_id = anime__syntax_expr__check_syntax__one(this, expr_id); 
#if 0 
    if (3 == expr_id) {
      dputs5(STDERR_FILENO, "error_id: ", int_string(error_id), " - ", int_anime_error__get_cstr(error_id), "\n"); 
      assert(false); 
    };
#endif 
    if (ANIME__OK != error_id) return error_id;
  }; 
  
  return error_id; 
};









// *************************************************** 
// BRACES STRUCTURE 

// RL: Il est nécessaire de vérifier l’équilibrage des accolades: 
//      -- On peut construire le sens d’une structure dont les accolades ne sont pas équilibrées. 
//         Il ne sert alors à rien de poursuivre l’analyse. 
//      -- Des accolades équilibrées permettent d’implémenter des fonctions ‘skip_to’, 
//         lesquelles sont utilisées par l’analyseur syntaxique pour ignorer une section. 

static int_anime_error_t anime__syntax__braces_are_balanced_huh(const anime_t * this) { 
  int_lexeme_t           openbrace__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  uint8_t                openbrace__nb; 
  goto label__body; 

 label__error__nestedness_too_deep: {
    assert(false); 
  };
  
 label__error__missing_closebrace: { 
    assert(false); 
  };
  
 label__error__missing_openbrace: { 
    assert(false); 
  };
  
 label__body: { 
    const int_lexeme_t token_nb = this -> lexeme_stack__nb; 
    int_lexeme_t token_i; 
    openbrace__nb = 0; 
  
    for (token_i = 0; token_i < token_nb; token_i++) { 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_OPENBRACE  == token_type) goto label__openbrace; 
      if (ANIME_TOKEN_CLOSEBRACE == token_type) goto label__closebrace; 
      continue; 
    
    label__openbrace: { 
	if (ANIME__EXPRESSION_NESTEDNESS_MAX <= openbrace__nb) goto label__error__nestedness_too_deep; 
	openbrace__lexeme[openbrace__nb] = token_i; 
	openbrace__nb++; 
	continue; 
      };
    
    label__closebrace: { 
	if (0 >= openbrace__nb) goto label__error__missing_openbrace; 
	openbrace__nb--; 
	continue; 
      }; 
      
    }; 
    if (0 < openbrace__nb) goto label__error__missing_closebrace;
    assert(0 == openbrace__nb); 
    return ANIME__OK; 
  };  
}; 



// SKIP TO END OF TOP_LEVEL SECTION: il faut trouver '}' au niveau top-level, soit ';'  au niveau top-level. 

// SKIP TO END OF INSTRUCTION: il faut trouver ';'  au même niveau. (Toutes les instructions se terminent par un ';'.) 


static int_lexeme_t anime__syntax__skip_to_end_of_top_level_section(const anime_t * this, const int_lexeme_t token_i_start) { 
  int_lexeme_t           openbrace__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  uint8_t                openbrace__nb; 
  const int_lexeme_t token_nb = this -> lexeme_stack__nb; 
  assert(0 <= token_i_start); 
  assert(token_nb > token_i_start); 
  int_lexeme_t token_i; 
  int_anime_token_type_t token_type;
  goto label__body; 


 label__error__nestedness_too_deep: {
    return -1; 
  };

 label__error__missing_openbrace: { 
    return token_nb; 
  };
  
 label__error__missing_closebrace: { 
    return token_nb; 
  };
  
 label__error__not_enough_tokens: { 
    return token_nb; 
  }; 

 label__error__lonely_closebrace: { 
    return -1; 
  };

 label__body: {
    openbrace__nb = 0;
    // RL: Recherche du premier ';' ou du premier '{'. 
    for (token_i = token_i_start; token_i < token_nb; token_i++) { 
      token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_PTVIRG     == token_type) return token_i; 
      if (ANIME_TOKEN_OPENBRACE  == token_type) goto label__first_openbrace_found; 
      if (ANIME_TOKEN_CLOSEBRACE == token_type) goto label__error__lonely_closebrace; 
    }; 
    goto label__error__not_enough_tokens;
  };

 label__first_openbrace_found: { 
    assert(ANIME_TOKEN_OPENBRACE == token_type); 
    
    for (; token_i < token_nb; token_i++) { 
      token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_OPENBRACE == token_type) { 
	if (ANIME__EXPRESSION_NESTEDNESS_MAX <= openbrace__nb) goto label__error__nestedness_too_deep; 
	openbrace__lexeme[openbrace__nb] = token_i;
	openbrace__nb++; 
	continue; 
      };
      if (ANIME_TOKEN_CLOSEBRACE == token_type) { 
	if (0 >= openbrace__nb) goto label__error__missing_openbrace; 
	if (1 == openbrace__nb) return token_i; 
	openbrace__nb--; 
	continue; 
      };
    };
    goto label__error__missing_closebrace; 
  }; 
  
  assert(false); 
}; 


static int_lexeme_t anime__syntax__skip_to_start_of_top_level_section(const anime_t * this, const int_lexeme_t token_i_start) { 
  const int_lexeme_t token_nb = this -> lexeme_stack__nb; 
  assert(0 <= token_i_start); 
  assert(token_nb > token_i_start); 
  int_lexeme_t token_i; 
  int_anime_token_type_t token_type;
  goto label__body; 

 label__error__not_enough_tokens: { 
    return token_nb; 
  }; 

 label__error__lonely_closebrace: { 
    return -1; 
  };

 label__body: {
    // RL: Recherche du premier ';' ou du premier '{'. 
    for (token_i = token_i_start; token_i < token_nb; token_i++) { 
      token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_PTVIRG     == token_type) return token_i; 
      if (ANIME_TOKEN_OPENBRACE  == token_type) return token_i; 
      if (ANIME_TOKEN_CLOSEBRACE == token_type) goto label__error__lonely_closebrace; 
    }; 
    goto label__error__not_enough_tokens;
  };

  assert(false); 
}; 


static int_lexeme_t anime__syntax__skip_to_end_of_instruction(const anime_t * this, const int_lexeme_t token_i_start) { 
  int_lexeme_t       openbrace__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  uint8_t            openbrace__nb; 
  const int_lexeme_t token_nb = this -> lexeme_stack__nb; 
  assert(0 <= token_i_start); 
  assert(token_nb > token_i_start); 
  int_lexeme_t token_i; 
  int_anime_token_type_t token_type;
  goto label__body; 


 label__error__nestedness_too_deep: {
    return -1; 
  };

 label__error__missing_openbrace: { 
    return token_nb; 
  };
  
 label__error__missing_closebrace: { 
    return token_nb; 
  };
  
 label__error__not_enough_tokens: { 
    return token_nb; 
  }; 

 label__error__missing_ptvirg: { 
    return -1; 
  }; 
  
 label__body: {
    //if (23 == token_i_start) assert(false); 
    openbrace__nb = 0;
    token_i = token_i_start; 
    goto label__upper_level; 
  };
  
 label__upper_level: {
    // RL: Recherche du premier ';' ou du premier '{', ou du premier '}'  
    for (; token_i < token_nb; token_i++) { 
      token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_PTVIRG     == token_type) return token_i; 
      if (ANIME_TOKEN_OPENBRACE  == token_type) goto label__first_openbrace_found; 
      if (ANIME_TOKEN_CLOSEBRACE == token_type) goto label__error__missing_ptvirg; 
    }; 
    goto label__error__not_enough_tokens;
  };

 label__first_openbrace_found: { 
    assert(ANIME_TOKEN_OPENBRACE == token_type); 
    
    //token_i++; 
    for (; token_i < token_nb; token_i++) { 
      token_type = this -> lexeme_stack__type[token_i]; 
      if (ANIME_TOKEN_OPENBRACE == token_type) { 
	if (ANIME__EXPRESSION_NESTEDNESS_MAX <= openbrace__nb) goto label__error__nestedness_too_deep; 
	openbrace__lexeme[openbrace__nb] = token_i;
	openbrace__nb++; 
	continue; 
      };
      if (ANIME_TOKEN_CLOSEBRACE == token_type) { 
	if (0 >= openbrace__nb) goto label__error__missing_openbrace; 
	openbrace__nb--; 
	if (0 == openbrace__nb) { token_i++; goto label__upper_level; }; 
	continue; 
      };
    };
    goto label__error__missing_closebrace; 
  }; 
  
  assert(false); 
}; 






// *************************************************** 
// SYNTAX CHECK AND FILL 


#define MOVE_TO_NEXT_TOKEN() {						\
    token_i++;								\
  }; 

#define GET_TOKEN_SRCVAL(token_i) (anime_data -> lexeme_value_stack + (anime_data -> lexeme_stack__value[token_i]))
 
#define CHECK_IDENT(_ident_) {						\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    srcval     = GET_TOKEN_SRCVAL(token_i);				\
    if (ANIME_TOKEN_IDENT != token_type)    { error__expected_token_type  = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type;   }; \
    if (0 != strcasecmp((_ident_), srcval)) { error__expected_token_value = (_ident_);         goto error_label__non_matching_token_value;  }; \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define CHECK_SUGAR(_expected_token_type_) {				\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    if ((_expected_token_type_) != token_type) { error__expected_token_type = (_expected_token_type_); goto error_label__non_matching_token_type; }; \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define LOOKAHEAD_IDENT(_ident_) {					\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    srcval     = GET_TOKEN_SRCVAL(token_i);				\
    lookahead_match_huh = (ANIME_TOKEN_IDENT == token_type) && (0 == strcasecmp((_ident_), srcval)); \
  }; 

#define LOOKAHEAD_TYPE(_expected_token_type_) {				\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    lookahead_match_huh = ((_expected_token_type_) == token_type);	\
  }; 

#define LOOKAHEAD_SUGAR LOOKAHEAD_TYPE 



#define READ_EXPRESSION(field_name) {					\
    expression_start = token_i;						\
    /* dputs3(STDERR_FILENO, "expression_start: ", int_string(expression_start), "\n");	*/ \
    token_i = anime__syntax__skip_to_end_of_instruction(anime_data, expression_start); \
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    assert(token_type == ANIME_TOKEN_PTVIRG || token_type == ANIME_TOKEN_CLOSEBRACE); \
    expression_len = token_i - expression_start;			\
    const int_expr_t expr_id = anime_expr_push(anime_data, expression_start, expression_len); \
    anime_data -> glue2(field_name,__expr) = expr_id;			\
  };									\
  /* END OF MACRO */


#define READ_EXPRESSION__ARRAY(field_name,item_i) {			\
    expression_start = token_i;						\
    token_i = anime__syntax__skip_to_end_of_instruction(anime_data, expression_start); \
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i]; \
    assert(token_type == ANIME_TOKEN_PTVIRG || token_type == ANIME_TOKEN_CLOSEBRACE); \
    expression_len = token_i - expression_start;			\
    const int_expr_t expr_id = anime_expr_push(anime_data, expression_start, expression_len); \
    anime_data -> glue2(field_name,__expr)[item_i] = expr_id;		\
  };									\
  /* END OF MACRO */


#define READ_EXPRESSION__OPEN(field_name) {				\
    expression_start = token_i;						\
    token_i = anime__syntax__skip_to_start_of_top_level_section(anime_data, expression_start); \
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    assert(token_type == ANIME_TOKEN_PTVIRG || token_type == ANIME_TOKEN_OPENBRACE); \
    expression_len = token_i - expression_start;			\
    const int_expr_t expr_id = anime_expr_push(anime_data, expression_start, expression_len); \
    anime_data -> glue2(field_name,__expr)[item_i] = expr_id;		\
  };									\
  /* END OF MACRO */


#define READ_EXPRESSION__ARRAY__OPEN(field_name,item_i) {		\
    expression_start = token_i;						\
    token_i = anime__syntax__skip_to_start_of_top_level_section(anime_data, expression_start); \
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i];		\
    assert(token_type == ANIME_TOKEN_PTVIRG || token_type == ANIME_TOKEN_OPENBRACE); \
    expression_len = token_i - expression_start;			\
    const int_expr_t expr_id = anime_expr_push(anime_data, expression_start, expression_len); \
    anime_data -> glue2(field_name,__expr)[item_i] = expr_id;		\
  };									\
  /* END OF MACRO */









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


int_anime_error_t anime__syntax__structure_check_and_fill__aux(anime_t * anime_data, const int stdwarning_d, const int stderror_d) { 
  LOCAL_ALLOCA__DECLARE(int16_t,INT16_MAX); 
  if (NULL == anime_data) { return ANIME__DATA_GENERATION__NULL_ANIME_DATA; }; 
  int_lexeme_t token_i = 0; 
  int_anime_token_type_t token_type;
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
  int_lexeme_t expression_start; 
  int8_t expression_len; 

  const char * input_filename_cstr = anime__filename_get(anime_data); 
  const int stdlog_d = anime_data -> stdlog_d; 
  
  char warning__msg[256]; 
  char error__msg[256]; 
  
  anime_data -> actions_nb = 0; 
  anime_data -> events_nb = 0; 
  anime_data -> membres_nb = 0; 
  anime_data -> racines_nb = 0; 
  
  const int_lexeme_t token_nb = anime_data -> lexeme_stack__nb; 
  if (0 >= token_nb) { goto error_label__not_enough_tokens; }; 

  int8_t   section_physique_nb  = 0; 
  int8_t   section_gameplay_nb  = 0; 
  int8_t   section_graphique_nb = 0; 
  int8_t   section_unknown_nb   = 0; 
  
  goto label__body; 


 label__body: {   
    token_i = 0; 
    goto label__top_level; label__top_level_ret: {}; 
    goto label__sections_check_and_print; label__sections_check_and_print_ret: {}; 
    //anime_data -> filled_huh = 2; 
    return ANIME__OK; 
  };


  
 label__top_level: { 
    for (;;) { 
      if (token_i == token_nb) { break; }; 
      LOOKAHEAD_TYPE(ANIME_TOKEN_EOF); if (lookahead_match_huh) { goto label__top_level_ret; }; 
      LOOKAHEAD_TYPE(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) { token_i++; continue; }; 
      LOOKAHEAD_IDENT("physique" ); if (lookahead_match_huh) { goto section_physique ; }; 
      LOOKAHEAD_IDENT("gameplay" ); if (lookahead_match_huh) { goto section_gameplay ; }; 
      LOOKAHEAD_IDENT("graphique"); if (lookahead_match_huh) { goto section_graphique; }; 
      goto section_unknown; 
    };
    goto label__error__missing_eof; 
  };
   
  
 section_physique: { 
    section_physique_nb++; 
    if (section_physique_nb > 1) goto section_physique__too_many; 
    
    CHECK_IDENT("physique"); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
      CHECK_IDENT("zone"); CHECK_IDENT("de"); CHECK_IDENT("choc"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	CHECK_IDENT("longueur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(choc_longueur); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("largeur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(choc_largeur); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("hauteur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(choc_hauteur); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("masse"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(masse); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
    goto label__top_level; 
  }; 
  
  
 section_gameplay: { 
    section_gameplay_nb++; 
    if (section_gameplay_nb > 1) goto section_gameplay__too_many; 
    
    CHECK_IDENT("gameplay"); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
      CHECK_IDENT("points"    ); CHECK_IDENT("de"); CHECK_IDENT("vie"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(vie); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("invincible"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(invincible); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("hostile"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION(hostile); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      
      for (;;) { 
	LOOKAHEAD_IDENT("action" ); if (!lookahead_match_huh) break; 
	
	const uint8_t action_i = anime_data -> actions_nb; 
	if (action_i >= ANIME_ACTIONS_SIZE) goto actions__overflow; 
	anime_data -> actions_nb++; 
	
	CHECK_IDENT("action"); READ_EXPRESSION__ARRAY__OPEN(actions_nom,action_i); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	  CHECK_IDENT("affichage"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(actions_affichage,action_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("icone"       ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(actions_icone,action_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("gestionnaire"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	    CHECK_IDENT("fichier"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(actions_gestionnaire_fichier,action_i);CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	    { LOOKAHEAD_SUGAR(ANIME_TOKEN_PROCEDURE); if (lookahead_match_huh) { MOVE_TO_NEXT_TOKEN(); } else  { CHECK_IDENT("procedure" ); }; }; CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(actions_gestionnaire_proc,action_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) token_i++; 
	continue; 
	
      actions__overflow: { 
	  goto actions__overflow__print_warning_message; actions__overflow__print_warning_message__ret: {}; 
	  goto actions__skip_to_end_of_action; actions__skip_to_end_of_action__ret: {}; 
	  token_i++;
	  LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) token_i++; 
	  continue; 
	}; 
      }; 
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
    goto label__top_level; 
  }; 


 section_graphique: { 
    section_graphique_nb++; 
    if (section_graphique_nb > 1) goto section_graphique__too_many; 
      
    CHECK_IDENT("graphique"); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 

      for (;;) { 
	LOOKAHEAD_IDENT("membre"); if (!(lookahead_match_huh)) { break; }; 

	if (anime_data -> membres_nb >= anime_data -> membres_size) goto membres__overflow; 
	const int8_t membre_i = anime_data -> membres_nb; 
	anime_data -> membres_nb++; 
	    
	CHECK_IDENT("membre"); READ_EXPRESSION__ARRAY__OPEN(membres_nom,membre_i); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	  LOOKAHEAD_IDENT("fils"   ); if (lookahead_match_huh) { token_i++; CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); }; 
	  CHECK_IDENT("image"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(membres_image,membre_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("largeur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(membres_largeur,membre_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("hauteur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(membres_hauteur,membre_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("angle"); CHECK_IDENT("max"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(membres_angle_max_y,membre_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) token_i++; 
	continue; 

      membres__overflow: { 
	  goto membres__overflow__print_warning_message; membres__overflow__print_warning_message__ret: {}; 
	  goto membres__skip_to_end_of_action; membres__skip_to_end_of_action__ret: {}; 
	  token_i++;
	  LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) token_i++; 
	  continue; 
	}; 
      }; 
	
      CHECK_IDENT("membres"); CHECK_IDENT("racines"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); 
      for (;;) { 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) { token_i++; break; }; 
	CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	  if (anime_data -> racines_nb >= anime_data -> racines_size) goto racines__overflow; 
	  const int8_t racine_i = anime_data -> racines_nb; 
	  anime_data -> racines_nb++; 
	  CHECK_IDENT("qui"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(racines_qui,racine_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("x"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(racines_x,racine_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("y"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(racines_y,racine_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("z"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(racines_z,racine_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("angle"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_EXPRESSION__ARRAY(racines_angle_y,racine_i); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) { token_i++; break; }; 
	CHECK_SUGAR(ANIME_TOKEN_VIRGULE); 
	continue;
	    
      racines__overflow: { 
	  goto racines__overflow__print_warning_message; racines__overflow__print_warning_message__ret: {}; 
	  goto racines__skip_to_end_of_action; racines__skip_to_end_of_action__ret: {}; 
	  token_i++;
	  LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); if (lookahead_match_huh) token_i++; 
	  continue; 
	}; 
      }; 
	
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
    goto label__top_level; 
  }; 


  
 section_unknown: { 
    section_unknown_nb++; 
    snprintf(warning__msg, sizeof(warning__msg), "Unknown section: '%s'", GET_TOKEN_SRCVAL(token_i)); 
    WARNING_MESSAGE_PRINT(); 
    goto skip_to_next_top_level_section_and_loop; 
  }; 

 section_graphique__too_many: { 
    strlcpy(warning__msg, "Extraneous 'graphique' section",sizeof(warning__msg));
    WARNING_MESSAGE_PRINT(); 
    goto skip_to_next_top_level_section_and_loop; 
  }; 

 section_gameplay__too_many: {
    strlcpy(warning__msg, "Extraneous 'gameplay' section",sizeof(warning__msg));
    WARNING_MESSAGE_PRINT(); 
    goto skip_to_next_top_level_section_and_loop; 
  }; 

 section_physique__too_many: { 
    strlcpy(warning__msg, "Extraneous 'physique' section",sizeof(warning__msg)); 
    WARNING_MESSAGE_PRINT(); 
    goto skip_to_next_top_level_section_and_loop; 
  }; 

 actions__overflow__print_warning_message: {
    snprintf(warning__msg, sizeof(warning__msg), "WARNING: Too many 'action' fields — can store at most %u, and already storing %u — Extraneous 'action' fields will be ignored", (unsigned int)ANIME_ACTIONS_SIZE, (unsigned int) anime_data -> actions_nb); 
    WARNING_MESSAGE_PRINT(); 
    goto actions__overflow__print_warning_message__ret;
  };      

 actions__skip_to_end_of_action: { 
    token_i = anime__syntax__skip_to_end_of_top_level_section(anime_data, token_i); 
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i]; 
    assert(ANIME_TOKEN_PTVIRG == token_type || ANIME_TOKEN_CLOSEBRACE == token_type); 
    goto actions__skip_to_end_of_action__ret; 
  }; 

 membres__overflow__print_warning_message: {
    snprintf(warning__msg, sizeof(warning__msg), "WARNING: Too many 'action' fields — can store at most %u, and already storing %u — Extraneous 'action' fields will be ignored", (unsigned int)ANIME_MEMBRES_SIZE, (unsigned int) anime_data -> membres_nb); 
    WARNING_MESSAGE_PRINT(); 
    goto membres__overflow__print_warning_message__ret;
  };      

 membres__skip_to_end_of_action: { 
    token_i = anime__syntax__skip_to_end_of_top_level_section(anime_data, token_i); 
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i]; 
    assert(ANIME_TOKEN_PTVIRG == token_type || ANIME_TOKEN_CLOSEBRACE == token_type); 
    goto membres__skip_to_end_of_action__ret; 
  }; 

 racines__overflow__print_warning_message: {
    snprintf(warning__msg, sizeof(warning__msg), "WARNING: Too many 'action' fields — can store at most %u, and already storing %u — Extraneous 'action' fields will be ignored", (unsigned int)ANIME_RACINES_SIZE, (unsigned int) anime_data -> racines_nb); 
    WARNING_MESSAGE_PRINT(); 
    goto racines__overflow__print_warning_message__ret;
  };      

 racines__skip_to_end_of_action: { 
    token_i = anime__syntax__skip_to_end_of_top_level_section(anime_data, token_i); 
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; \
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; \
    token_type = anime_data -> lexeme_stack__type[token_i]; 
    assert(ANIME_TOKEN_PTVIRG == token_type || ANIME_TOKEN_CLOSEBRACE == token_type); 
    goto racines__skip_to_end_of_action__ret; 
  }; 

 skip_to_next_top_level_section_and_loop: { 
    token_i = anime__syntax__skip_to_end_of_top_level_section(anime_data, token_i); 
    if (token_i <         0) { goto label__error__instruction_syntax_error; }; 
    if (token_i >= token_nb) { goto label__error__instruction_syntax_error; }; 
    token_type = anime_data -> lexeme_stack__type[token_i]; 
    assert(ANIME_TOKEN_PTVIRG == token_type || ANIME_TOKEN_CLOSEBRACE == token_type); 
    token_i++; 
    goto label__top_level; 
  };

  
  
 label__sections_check_and_print: { 
    if (0 == section_physique_nb ) { goto error_missing_section_physique ; }; 
    if (0 == section_gameplay_nb ) { goto error_missing_section_gameplay ; }; 
    if (0 == section_graphique_nb) { goto error_missing_section_graphique; }; 
  
    if (1 < section_physique_nb) { 
      snprintf(warning__msg, sizeof(warning__msg), "There were %d 'physique' sections — Only the first one was used, following ones got discarded.", section_physique_nb); 
      WARNING_MESSAGE_PRINT(); 
    };  
  
    if (1 < section_gameplay_nb) {       
      snprintf(warning__msg, sizeof(warning__msg), "There were %d 'gameplay' sections — Only the first one was used, following ones got discarded.", section_gameplay_nb); 
      WARNING_MESSAGE_PRINT(); 
    };  
  
    if (1 < section_graphique_nb) { 
      snprintf(warning__msg, sizeof(warning__msg), "There were %d 'graphique' sections — Only the first one was used, following ones got discarded.", section_graphique_nb); 
      WARNING_MESSAGE_PRINT(); 
    };  
  
    if (0 < section_unknown_nb) { 
      snprintf(warning__msg, sizeof(warning__msg), "There were %d unknown sections — They all got discarded.", section_unknown_nb); 
      WARNING_MESSAGE_PRINT(); 
    };  

    goto label__sections_check_and_print_ret; 
  };


 error_missing_section_physique: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_PHYSIQUE_SECTION; 
    strlcpy(error__msg, "Missing 'physique' section", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT__NO_LINE(); 
    return anime_data -> error_id; 
  };   
  
 error_missing_section_gameplay: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_GAMEPLAY_SECTION; 
    strlcpy(error__msg, "Missing 'gameplay' section", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT__NO_LINE(); 
    return anime_data -> error_id; 
  };   
  
 error_missing_section_graphique: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_GRAPHIQUE_SECTION; 
    strlcpy(error__msg, "Missing 'graphique' section", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT__NO_LINE(); 
    return anime_data -> error_id; 
  };   


 error_label__not_enough_tokens: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS; 
    strlcpy(error__msg, "End-of-file reached, while parsing not completed", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return anime_data -> error_id; 
  }; 

 label__error__missing_eof: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS; 
    strlcpy(error__msg, "EOF Token missing (while end of tokens reached)", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return anime_data -> error_id; 
  }; 

 error_label__non_matching_token_type: {
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const char * error__expected_token_type_cstr = anime_token__type_get_cstr(error__expected_token_type); 
    const char * error__got_token_type_cstr      = anime_token__type_get_cstr(                token_type); 
    snprintf(error__msg, sizeof(error__msg), "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    ERROR_MESSAGE_PRINT(); 
    return anime_data -> error_id; 
  };

 error_label__non_matching_token_value: {
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE; 
    snprintf(error__msg, sizeof(error__msg), "Non-matching token value — Expecting: '%s' ; Got: '%s'", error__expected_token_value, GET_TOKEN_SRCVAL(token_i)); 
    ERROR_MESSAGE_PRINT(); 
    return anime_data -> error_id; 
  };

  label__error__instruction_syntax_error: { 
    anime_data -> error_id = ANIME__SYNTAX__GENERIC_ERROR; 
    strlcpy(error__msg, "Syntax error", sizeof(error__msg)); 
    ERROR_MESSAGE_PRINT(); 
    return anime_data -> error_id; 
  };
  
}; 




// *************************************************** 
// PRINT 


#define PRINT_LEXEMES(field_name) {					\
    const int_expr_t expr_id = this -> glue2(field_name,__expr);	\
    const int_lexeme_t lex_start = this -> expr_lexeme_start_i[expr_id]; \
    const int_lexeme_t lex_nb = this -> expr_lexemes_nb[expr_id];	\
    int_lexeme_t pos = lex_start;					\
    for (int_lexeme_t i = 0; i < lex_nb; i++) {				\
      const int_lexeme_value_t v = this -> lexeme_stack__value[pos + i]; \
      const char * t = this -> lexeme_value_stack + v;			\
      write_string(stdprint_d, t);					\
    };									\
  };									\
  /* END OF MACRO */ 

#define PRINT_LEXEMES_ARRAY(field_name,__index__) {			\
    const int_expr_t expr_id = this -> glue2(field_name,__expr)[__index__];	\
    const int_lexeme_t lex_start = this -> expr_lexeme_start_i[expr_id]; \
    const int_lexeme_t lex_nb = this -> expr_lexemes_nb[expr_id];	\
    int_lexeme_t pos = lex_start;					\
    for (int_lexeme_t i = 0; i < lex_nb; i++) {				\
      const int_lexeme_value_t v = this -> lexeme_stack__value[pos + i]; \
      const char * t = this -> lexeme_value_stack + v;			\
      write_string(stdprint_d, t);					\
    };									\
  };									\
  /* END OF MACRO */ 

void anime__syntax__print(const anime_t * this, const int stdprint_d) { 

  dputs(stdprint_d, "physique {" "\n");
  dputs(stdprint_d, "  zone de choc := {" "\n");
  dputs(stdprint_d, "    longueur := "); PRINT_LEXEMES(choc_longueur); dputs(stdprint_d, ";" "\n"); 
  dputs(stdprint_d, "    largeur := "); PRINT_LEXEMES(choc_largeur); dputs(stdprint_d, ";" "\n"); 
  dputs(stdprint_d, "    hauteur := "); PRINT_LEXEMES(choc_hauteur); dputs(stdprint_d, ";" "\n"); 
  dputs(stdprint_d, "  };" "\n"); 
  dputs(stdprint_d, "  masse := "); PRINT_LEXEMES(masse); dputs(stdprint_d, ";" "\n"); 
  dputs(stdprint_d, "}" "\n");


  dputs(stdprint_d, "gameplay {" "\n");
  dputs(stdprint_d, "  points de vie := "); PRINT_LEXEMES(vie); dputs(stdprint_d, ";" "\n"); 
  dputs(stdprint_d, "  invincible := "); PRINT_LEXEMES(invincible); dputs(stdprint_d, ";" "\n"); 
  dputs(stdprint_d, "  hostile := "); PRINT_LEXEMES(hostile); dputs(stdprint_d, ";" "\n"); 

  for (int8_t action_i = 0; action_i < this -> actions_nb; action_i++) { 
    dputs(stdprint_d, "  action "); PRINT_LEXEMES_ARRAY(actions_nom,action_i); dputs(stdprint_d, " {" "\n"); 
    dputs(stdprint_d, "    affichage := "); PRINT_LEXEMES_ARRAY(actions_affichage,action_i); dputs(stdprint_d, ";" "\n"); 
    dputs(stdprint_d, "    icone := "); PRINT_LEXEMES_ARRAY(actions_icone,action_i); dputs(stdprint_d, ";" "\n"); 
    dputs(stdprint_d, "    gestionnaire := { fichier := "); PRINT_LEXEMES_ARRAY(actions_gestionnaire_fichier,action_i); dputs(stdprint_d, "; procedure := "); PRINT_LEXEMES_ARRAY(actions_gestionnaire_proc,action_i); dputs(stdprint_d, "; };" "\n"); 
    dputs(stdprint_d, "  }" "\n"); 
  };
  dputs(stdprint_d, "}" "\n");


  dputs(stdprint_d, "graphique {" "\n");
  
  for (int8_t membre_i = 0; membre_i < this -> membres_nb; membre_i++) { 
    dputs(stdprint_d, "  membre "); PRINT_LEXEMES_ARRAY(membres_nom,membre_i); dputs(stdprint_d, " {" "\n"); 
    dputs(stdprint_d, "    image := "); PRINT_LEXEMES_ARRAY(membres_image,membre_i); dputs(stdprint_d, ";" "\n"); 
    dputs(stdprint_d, "    largeur := "); PRINT_LEXEMES_ARRAY(membres_largeur,membre_i); dputs(stdprint_d, ";" "\n");
    dputs(stdprint_d, "    hauteur := "); PRINT_LEXEMES_ARRAY(membres_hauteur,membre_i); dputs(stdprint_d, ";" "\n");
    dputs(stdprint_d, "    angle max y := "); PRINT_LEXEMES_ARRAY(membres_angle_max_y,membre_i); dputs(stdprint_d, ";" "\n");
    dputs(stdprint_d, "  }" "\n"); 
  };

  dputs(stdprint_d, "  membres racines := " "\n"); 
  for (int8_t racine_i = 0; racine_i < this -> racines_nb; racine_i++) { 
    dputs(stdprint_d, "    {"); 
    dputs(stdprint_d, "qui := "); PRINT_LEXEMES_ARRAY(racines_qui,racine_i); dputs(stdprint_d, ";"); 
    dputs(stdprint_d, " x := "); PRINT_LEXEMES_ARRAY(racines_x,racine_i); dputs(stdprint_d, ";"); 
    dputs(stdprint_d, " y := "); PRINT_LEXEMES_ARRAY(racines_y,racine_i); dputs(stdprint_d, ";"); 
    dputs(stdprint_d, " z := "); PRINT_LEXEMES_ARRAY(racines_z,racine_i); dputs(stdprint_d, ";"); 
    dputs(stdprint_d, " angle y := "); PRINT_LEXEMES_ARRAY(racines_angle_y,racine_i); dputs(stdprint_d, ";"); 
    dputs(stdprint_d, "}"); 
    if (racine_i + 1 < this -> racines_nb) dputs(stdprint_d, "," "\n"); 
  };
  dputs(stdprint_d, ";" "\n"); 

  dputs(stdprint_d, "}" "\n");

};





// *************************************************** 
// MISC 


static int int_lexeme_type__member_array_nb(const int_anime_token_type_t n, const int8_t size, const int_anime_token_type_t int_array[]) {
  for (int8_t i = 0; i < size; i++) { 
    if (n == int_array[i]) return true; 
  }; 
  return false; 
}; 
#define int_lexeme_type__member_array(n,int_array) (int_lexeme_type__member_array_nb(((n)),(ARRAY_SIZE((int_array))),((int_array))))
#define int_lexeme_type__member_huh(n,...) int_lexeme_type__member_array((n), ((const int_anime_token_type_t []) { __VA_ARGS__ })) 



static int_anime_error_t anime__syntax__is_well_parenthesised_huh(const anime_t * this) { 
  int_lexeme_t           openpar__lexeme[ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  int_anime_token_type_t openpar__type  [ANIME__EXPRESSION_NESTEDNESS_MAX]; 
  uint8_t                openpar__nb; 
  goto label__body; 

 label__error__nestedness_too_deep: {
    assert(false); 
  };

 label__error__ptvirg__unclosed_paren: { 
    assert(false); 
  };

 label__error__pending_closepar: {  
    assert(false); 
  };

 label__error__mismatching_paren: { 
    assert(false); 
  };

 label__body: { 
    const int_lexeme_t token_nb = this -> lexeme_stack__nb; 
    int_lexeme_t token_i = 0; 
    openpar__nb = 0; 
  
    for (;token_i < token_nb; token_i++) { 
      const int_anime_token_type_t token_type = this -> lexeme_stack__type[token_i]; 
      const int8_t openpar_huh  = int_lexeme_type__member_huh(token_type,ANIME_TOKEN_OPENPAR,ANIME_TOKEN_OPENBRACKET,ANIME_TOKEN_OPENBRACE); 
      const int8_t ptvirg_huh   = int_lexeme_type__member_huh(token_type,ANIME_TOKEN_PTVIRG);
      const int8_t closepar_huh = int_lexeme_type__member_huh(token_type,ANIME_TOKEN_CLOSEPAR,ANIME_TOKEN_CLOSEBRACKET,ANIME_TOKEN_CLOSEBRACE); 
    
      if (openpar_huh ) goto label__openpar; 
      if (ptvirg_huh  ) goto label__ptvirg; 
      if (closepar_huh) goto label__closepar;
      continue; 
    
    label__openpar: { 
	if (ANIME__EXPRESSION_NESTEDNESS_MAX <= openpar__nb) goto label__error__nestedness_too_deep; 
	openpar__lexeme[openpar__nb] = token_i; 
	openpar__type  [openpar__nb] = token_type; 
	openpar__nb++; 
	continue; 
      };
    
    label__ptvirg: { 
	if (0 < openpar__nb) { 
	  const int_anime_token_type_t previous = openpar__type[openpar__nb - 1]; 
	  if (int_lexeme_type__member_huh(previous,ANIME_TOKEN_OPENPAR,ANIME_TOKEN_OPENBRACKET)) goto label__error__ptvirg__unclosed_paren; 
	}; 
	continue; 
      };
    
    label__closepar: { 
	if (0 >= openpar__nb) goto label__error__pending_closepar; 
	const int_anime_token_type_t previous = openpar__type[openpar__nb - 1]; 
	for (;;) { 
	  if (ANIME_TOKEN_CLOSEPAR     == token_type) { if (ANIME_TOKEN_OPENPAR     != previous) goto label__error__mismatching_paren; break; } 
	  if (ANIME_TOKEN_CLOSEBRACKET == token_type) { if (ANIME_TOKEN_OPENBRACKET != previous) goto label__error__mismatching_paren; break; } 
	  if (ANIME_TOKEN_CLOSEBRACE   == token_type) { if (ANIME_TOKEN_OPENBRACE   != previous) goto label__error__mismatching_paren; break; } 
	};
	openpar__nb--;
	continue; 
      };
    }; 

    assert(0 == openpar__nb); 
    return ANIME__OK; 
  };  
}; 


void anime__syntax__check_and_assert(void) {
};
