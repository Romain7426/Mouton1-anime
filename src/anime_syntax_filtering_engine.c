#include "anime_global.h"
#include "anime.h"
#include "anime_token_type.h" 
#include "anime_token.h" 
#include "anime_syntax_filtering_engine.h"

#define DEBUG_PARSER 0

enum { ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE  = (1 << 11) }; 
static const uint8_t ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE__compiled_value = (uint8_t) ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE; 

struct anime_syntax_filtering_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  int_anime_error_t error_id; 
  char              error_str[ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE]; 
  uint8_t           error_buffer_size; 
  
  // SYNTAX_FILTERING 
  // «Syntax filtering» do two things: 
  //  a. it reorders tokens of infix expressions (it outputs postfix expressions that can be directly computed onto a stack machine) 
  //  b. it keeps track of the parenthesis system (allowing implementation of an «move to right neighbor» command) 
  // 
  // --- Mode --- 
  // We need to know if we are in transparent reading mode, or reading from the lalr buffer. 
  int8_t            syntax_filtering__mode; // 0 → 'regular' ; 1 → lalr 
  int8_t            syntax_filtering__lalr_completed_huh; 
  int_anime_token_t token_i; // In regular mode, current token. 
  // 
  // --- Parenthesis tracking --- 
  enum { ANIME__SYNTAX_FILTERING__PARENTHESIS_DEPTH = ANIME__EXPRESSION_NESTEDNESS_MAX }; 
  int_anime_token_t syntax_filtering__open_parenthesis__stack[ANIME__SYNTAX_FILTERING__PARENTHESIS_DEPTH]; 
  uint8_t           syntax_filtering__open_parenthesis__nb; 
  // 
  // --- Infix expressions reordering --- 
  // This is currently implemented using a lalr parser. Why? Because the current state of the 
  // automaton gives of a lot of meaning of what we are reading. (A LL(1) parser here would be 
  // useless. A local-LL(1) could be useful, but the implicit being built trees gonna be  
  // prefix, which is not what we want. Postfix ⇒ LALR ; Prefix ⇒ local-LL(1) ) 
  // 
  // We need: 
  //  - an output postfix buffer (needless to say, it contains an implicit postfix tree), 
  //  - an automaton path stack (to backtrack when reducing), 
  //  - an operator stack (incl. their arities) (in order to compare the priority, which is not implemented in the automaton states) 
  // 
  // NB: Actually, excepted the output postfix buffer, all that could be local variables. 
  // 
  // NB: As the output postfix buffer does not contain any arity information (on purpose, it contains only tokens), the 
  //     syntax-filtering engine could rewrite some token types (PLUS → PLUS_UNARY, which is a syntax information 
  //     and not a lexical information). 
  // 
  // * Output Postfix Buffer * 
  // The buffer could contain as many tokens as the input infix expression. 
  // And the whole input infix expression has to be analyzed. So that buffer size is bounded by the size (in tokens) of an expression. 
  enum { ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_SIZE = ANIME__LONGEST_INFIX_EXPRESSION }; 
  int_anime_token_t syntax_filtering__output_postfix_buffer__array[ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_SIZE]; 
  uint8_t           syntax_filtering__output_postfix_buffer__nb; 
  uint8_t           syntax_filtering__output_postfix_buffer__i; 
#if 0 
  // 
  // * Automaton Path Stack * 
  enum { ANIME__SYNTAX_FILTERING__AUTOMATON_PATH_STACK__SIZE = (ANIME__LONGEST_INFIX_EXPRESSION << 1) }; 
  enum { ANIME__SYNTAX_FILTERING__AUTOMATON_STATES_MAX = 32 }; 
  int8_t            syntax_filtering__automaton_path_stack__array[ANIME__SYNTAX_FILTERING__AUTOMATON_PATH_STACK__SIZE]; 
  int8_t            syntax_filtering__automaton_path_stack__nb; 
  // 
  // * Operator Stack * 
  enum { ANIME__SYNTAX_FILTERING__OPERATOR_STACK__SIZE = (ANIME__LONGEST_INFIX_EXPRESSION << 1) }; 
  int_anime_token_t syntax_filtering__operator_stack__array[ANIME__SYNTAX_FILTERING__OPERATOR_STACK__SIZE]; 
  uint8_t           syntax_filtering__operator_stack__arity[ANIME__SYNTAX_FILTERING__OPERATOR_STACK__SIZE]; 
  int8_t            syntax_filtering__operator_stack__nb; 
#endif 
  
  
  // *** Local-LL(1) *** 
  // Actually, a local-LL(1) algorithm would be exactly the same as the LA(1)LR(0) algorithm. 
  // 
  // First, we still need the automaton to get the current context. For instance, let's say we 
  // just read a terminal; how do we know that thing to be a left sub-tree or a right sub-tree? 
  // Or we read a minus operator; how do we figure that the binary one or the unary one? Or 
  // something else? Saving that context is the job of the automaton: each time we go deeper 
  // in a sub-expression, the context is saved on the path stack (as such, the depth of the 
  // path stack should be alike to the height of an expression). Reading the top of the path 
  // stack would answer all those above questions. 
  // 
  // Second, the point is that, when we read an operator, we do not know where on the right 
  // branch it belongs. In order to figure that out, we need to compare its priority with 
  // operators in this right branch. Noticing that left sub-trees are built and should be left 
  // touched. Therefore, we would need to two stacks: 
  //  - one stack for the right branch, 
  //  - one stack for the left sub-trees. 
  // But this matches exactly the two LA(1)LR(0) stacks: 
  //  - one stack for the operators about which we do not know what to do yet, 
  //  - one stack for the bottom-most already built trees. 
  // 
  // Therefore, this local-LL(1) is exactly the LA(1)LR(0) algorithm — the difference lies in 
  // the interpretation of the data structures: bottom-up instead of top-down. 
  
}; 


enum { ANIME_SYNTAX_FILTERING__SIZEOF = sizeof(anime_syntax_filtering_t) }; 
const int32_t anime_syntax_filtering__sizeof = ANIME_SYNTAX_FILTERING__SIZEOF;

anime_syntax_filtering_t * anime_syntax_filtering__make(const int stdlog_d) { 
  anime_syntax_filtering_t * this = (anime_syntax_filtering_t *) malloc(sizeof(*this)); 
  anime_syntax_filtering__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
}; 

anime_syntax_filtering_t * anime_syntax_filtering__make_b(const int bsize, void * bvalue, int * used_size_ref, const int stdlog_d) { 
  if (bsize < (int)sizeof(anime_syntax_filtering_t)) return NULL; 
  anime_syntax_filtering_t * this = (anime_syntax_filtering_t *) bvalue; 
  if (NULL != used_size_ref) *used_size_ref = sizeof(anime_syntax_filtering_t); 
  anime_syntax_filtering__make_r(this, stdlog_d); 
  return this; 
}; 

anime_syntax_filtering_t * anime_syntax_filtering__make_r(anime_syntax_filtering_t * this, const int stdlog_d) { 
  anime_syntax_filtering__bzero(this); 
  this -> malloced_flag = 0; 
  this -> stdlog_d = stdlog_d; 
  this -> error_buffer_size = (uint8_t) ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE; 
  this -> token_i = ANIME_TOKEN_I_BOF; 
  return this; 
}; 

void anime_syntax_filtering__bzero(anime_syntax_filtering_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
}; 

void anime_syntax_filtering__delete(anime_syntax_filtering_t * this) { 
  anime_syntax_filtering__delete_r(this); 
  if (1 == this -> malloced_flag) free(this); 
}; 

void anime_syntax_filtering__delete_r(anime_syntax_filtering_t * this) { 
  anime_syntax_filtering__bzero(this); 
}; 

int_anime_error_t anime_syntax_filtering__error_id(const anime_syntax_filtering_t * this) { 
  return this -> error_id; 
}; 

const char * anime_syntax_filtering__error_str(const anime_syntax_filtering_t * this) { 
  return this -> error_str; 
}; 

const char * anime_syntax_filtering__strcopy(anime_syntax_filtering_t * this, const char * cstr) { 
  assert(false); 
  return NULL; 
}; 




int_anime_error_t anime_syntax_filtering__switch_to_lalr_mode(anime_syntax_filtering_t * this) { 
  if (NULL == this) return ANIME__SYNTAX_FILTERING__NULL_THIS; 

  //int8_t            syntax_filtering__mode; // 0 → 'regular' ; 1 → lalr 
  if (this -> syntax_filtering__mode == 1) { goto error__lalr_mode_already_set; }; 
  this -> syntax_filtering__mode = 1; 
  this -> syntax_filtering__lalr_completed_huh = false; 
  if (this -> syntax_filtering__open_parenthesis__nb > 0) { 
    const int current_opening_token = this -> syntax_filtering__open_parenthesis__stack[this -> syntax_filtering__open_parenthesis__nb-1];
    if (this -> token_i == current_opening_token) { 
      this -> syntax_filtering__open_parenthesis__nb--; 
    }; 
  }; 
  
  return ANIME__OK; 
  
 error__lalr_mode_already_set: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__LALR_MODE_ALREADY_SET; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "LALR mode already set"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
}; 

int anime_syntax_filtering__lalr_mode_completed_huh(const anime_syntax_filtering_t * this) { 
  if (NULL ==      this) return ANIME__SYNTAX_FILTERING__NULL_THIS; 
  if (1 != this -> syntax_filtering__mode) return true; 
  return this -> syntax_filtering__lalr_completed_huh; 
}; 

int anime_syntax_filtering__lalr_mode_read_all_huh(const anime_syntax_filtering_t * this) { 
  if (NULL ==      this) return ANIME__SYNTAX_FILTERING__NULL_THIS; 
  if (1 != this -> syntax_filtering__mode) return true; 
  if (!this -> syntax_filtering__lalr_completed_huh) return false; 
#if 0 
  dprintf(stderr_d, "<anime_syntax_filtering__lalr_mode_read_all_huh>: this -> syntax_filtering__output_postfix_buffer__i  = %d" "\n", this -> syntax_filtering__output_postfix_buffer__i); 
  dprintf(stderr_d, "<anime_syntax_filtering__lalr_mode_read_all_huh>: this -> syntax_filtering__output_postfix_buffer__nb = %d" "\n", this -> syntax_filtering__output_postfix_buffer__nb); 
#endif 
  return (this -> syntax_filtering__output_postfix_buffer__i >= this -> syntax_filtering__output_postfix_buffer__nb); 
}; 






static int anime_syntax_filtering__parenthesis__opening[] = { 
  ANIME_TOKEN_BEGIN,       
  ANIME_TOKEN_OPENPAR, 
  ANIME_TOKEN_OPENBRACKET, 
  ANIME_TOKEN_REPEAT, 
  ANIME_TOKEN_RECORD, 
  ANIME_TOKEN_OPENBRACE 
}; 
enum { anime_syntax_filtering__parenthesis__opening__size = ARRAY_SIZE(anime_syntax_filtering__parenthesis__opening) }; 

static int anime_syntax_filtering__parenthesis__closing[] = { 
  ANIME_TOKEN_END, 
  ANIME_TOKEN_CLOSEPAR, 
  ANIME_TOKEN_CLOSEBRACKET, 
  ANIME_TOKEN_UNTIL, 
  ANIME_TOKEN_END, 
  ANIME_TOKEN_CLOSEBRACE 
}; 
enum { anime_syntax_filtering__parenthesis__closing__size = ARRAY_SIZE(anime_syntax_filtering__parenthesis__closing) }; 

static void assert_compile__dakjdds438sd(void) { 
  ASSERT_COMPILE(anime_syntax_filtering__parenthesis__opening__size == anime_syntax_filtering__parenthesis__closing__size); 
}; 

enum { anime_syntax_filtering__parenthesis__stack_size = 48 }; // RL: Nestedness. 

// Check if opening parenthesis and closing parenthesis match (it maintains a stack in order to do that). 
static int_anime_error_t anime_syntax_filtering__parenthesis__process(anime_syntax_filtering_t * this, const anime_token_env_t * token_env, const int token_i) { 
  if (ANIME_TOKEN_I_BOF     == token_i) return ANIME__OK; 
  if (ANIME_TOKEN_I_INVALID == token_i) return ANIME__OK; 
  if (token_i < 0) return ANIME__OK; 
  if (token_i >= anime_token__get_count(token_env)) return ANIME__OK; 
  const int token_type = anime_token__get_type(token_env, token_i); 
  
  if (int_member_array(token_type, anime_syntax_filtering__parenthesis__opening)) { 
    if (this -> syntax_filtering__open_parenthesis__nb >= ANIME__SYNTAX_FILTERING__PARENTHESIS_DEPTH) { goto error__parenthesis_stack_too_small; }; 
    this -> syntax_filtering__open_parenthesis__stack[this -> syntax_filtering__open_parenthesis__nb] = token_i; 
    this -> syntax_filtering__open_parenthesis__nb++; 
    return ANIME__OK; 
  }; 
  
  int closing_paren_i = 0; 
  for (;;) { 
    if (closing_paren_i >= anime_syntax_filtering__parenthesis__closing__size) return ANIME__OK; 
    if (token_type == anime_syntax_filtering__parenthesis__closing[closing_paren_i]) break; 
    closing_paren_i++; 
  }; 
  if (this -> syntax_filtering__open_parenthesis__nb <= 0) { goto error__missing_opening_parenthesis; }; 
  const int opening_token         = this -> syntax_filtering__open_parenthesis__stack[this -> syntax_filtering__open_parenthesis__nb-1]; 
  const int   actual_opening_type = anime_token__get_type(token_env, opening_token); 
  const int expected_opening_type = anime_syntax_filtering__parenthesis__opening[closing_paren_i]; 
  if (expected_opening_type != actual_opening_type) { goto error__mismatching_parenthesis; }; 
  this -> syntax_filtering__open_parenthesis__nb--; 
  return ANIME__OK; 
    
  

 error__parenthesis_stack_too_small: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__PARENTHESIS_STACK_TOO_SMALL; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "parenthesis stack is too small"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__missing_opening_parenthesis: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__MISSING_OPENING_PARENTHESIS; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "missing opening parenthesis"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__mismatching_parenthesis: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Mismatching parenthesis — Opening: %s [<%s>:%d:%d] ; Closing: %s [<%s>:%d:%d]", 
	     anime_token__type_get_cstr(actual_opening_type), 
	     anime_token__get_srcfile_cstr(token_env, opening_token), 
	     anime_token__get_line1(token_env, opening_token), 
	     anime_token__get_column0(token_env, opening_token), 
	     anime_token__type_get_cstr(token_type), 
	     anime_token__get_srcfile_cstr(token_env, token_i), 
	     anime_token__get_line1(token_env, token_i), 
	     anime_token__get_column0(token_env, token_i)); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    //{ dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
}; 

 
 
int_anime_error_t anime_syntax_filtering__skip_to_closing_paren(anime_syntax_filtering_t * this, const anime_token_env_t * token_env, int_anime_token_t * token_i_r) { 
  if (NULL == this) return ANIME__SYNTAX_FILTERING__NULL_THIS; 
  if (NULL == token_env) { goto error__null_token_env; }; 
  
  const int token_nb = anime_token__get_count(token_env); 
  if (0 == token_nb) { goto ambiguous__token_env_has_zero_token; }; 
  
  //int8_t            syntax_filtering__mode; // 0 → 'regular' ; 1 → lalr 
  if (1 == this -> syntax_filtering__mode) { 
    if (this -> syntax_filtering__lalr_completed_huh) { 
      if (this -> syntax_filtering__output_postfix_buffer__i >= this -> syntax_filtering__output_postfix_buffer__nb) { 
	this -> syntax_filtering__mode = 0; 
      }; 
    }; 
  }; 
  
  if (0 != this -> syntax_filtering__mode) { goto error__cannot_skip_to_closing_paren_in_lalr_mode; }; 

  if (ANIME_TOKEN_I_BOF == this -> token_i) { 
    this -> token_i = token_nb - 1; 
    if (NULL != token_i_r) { *token_i_r = this -> token_i; }; 
    return ANIME__OK; 
  }; 
  
  if (ANIME_TOKEN_I_INVALID == this -> token_i) { goto error__current_token_is_invalid; }; 
  
  if (this -> token_i <         0) { goto error__current_token_out_of_bounds; }; 
  if (this -> token_i >= token_nb) { goto error__current_token_out_of_bounds; }; 
  
  const int token_type = anime_token__get_type(token_env, this -> token_i); 
  
  if (this -> token_i == token_nb - 1) { 
    if (ANIME_TOKEN_EOF != token_type) { goto error__last_token_should_be_eof; }; 
    goto error__current_token_is_eof; 
  }; 
  
  int opening_paren_i = 0; 
  for (;;) { 
    if (opening_paren_i >= anime_syntax_filtering__parenthesis__opening__size) { goto error__current_token_not_an_opening_paren; }; 
    if (token_type == anime_syntax_filtering__parenthesis__opening[opening_paren_i]) break; 
    opening_paren_i++; 
  }; 
  const int expected_closing_type = anime_syntax_filtering__parenthesis__closing[opening_paren_i]; 
  const int openpar_depth = this -> syntax_filtering__open_parenthesis__nb - 1; 
  
  // Now, looking forward to the matching closing one. 
  int token_i = this -> token_i + 1; 
  for (;; token_i++) { 
    if (token_i >= token_nb) { goto error__openpar_has_no_closing_par; }; 
    const int token_type = anime_token__get_type(token_env, token_i); 
    if (int_member_array(token_type, anime_syntax_filtering__parenthesis__opening)) { 
      if (this -> syntax_filtering__open_parenthesis__nb >= ANIME__SYNTAX_FILTERING__PARENTHESIS_DEPTH) { goto error__parenthesis_stack_too_small; }; 
      this -> syntax_filtering__open_parenthesis__stack[this -> syntax_filtering__open_parenthesis__nb] = token_i; 
      this -> syntax_filtering__open_parenthesis__nb++; 
      continue; 
    }; 
    if (!int_member_array(token_type, anime_syntax_filtering__parenthesis__closing)) { continue; }; 
    const int closing_token_i    = token_i; 
    const int closing_token_type = anime_token__get_type(token_env, closing_token_i); 
    int closing_paren_i = 0; 
    for (;;) { 
      if (closing_paren_i    >= anime_syntax_filtering__parenthesis__closing__size) { goto error__current_token_not_a_closing_paren; }; 
      if (closing_token_type == anime_syntax_filtering__parenthesis__closing[closing_paren_i]) break; 
      closing_paren_i++; 
    }; 
    const int current_depth = this -> syntax_filtering__open_parenthesis__nb - 1; 
    if (openpar_depth < current_depth) { 
      const int opening_token_i    = this -> syntax_filtering__open_parenthesis__stack[this -> syntax_filtering__open_parenthesis__nb - 1]; 
      const int opening_token_type = anime_token__get_type(token_env, opening_token_i); 
      int opening_paren_i = 0; 
      for (;;) { 
	if (opening_paren_i    >= anime_syntax_filtering__parenthesis__opening__size) { goto error__current_token_not_an_opening_paren; }; 
	if (opening_token_type == anime_syntax_filtering__parenthesis__opening[opening_paren_i]) break; 
	opening_paren_i++; 
      }; 
      if (opening_paren_i != closing_paren_i) { goto error__mismatching_parenthesis; }; 
      this -> syntax_filtering__open_parenthesis__nb--; 
      continue; 
    }; 
    assert(openpar_depth == current_depth); 
    if (opening_paren_i != closing_paren_i) { goto error__mismatching_parenthesis; }; 
    this -> syntax_filtering__open_parenthesis__nb--; 
    this -> token_i = token_i; 
    if (NULL != token_i_r) { *token_i_r = token_i; }; 
    return ANIME__OK; 
  }; 
  
  
  assert(false); 
  return ~ANIME__OK; 

 error__openpar_has_no_closing_par: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__MISSING_CLOSING_PARENTHESIS; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Opening parenthesis at %d [%s] does not have any matching closing parenthesis (current nestedness: %d).", this -> token_i, anime_token__type_get_cstr(token_type), this -> syntax_filtering__open_parenthesis__nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__last_token_should_be_eof: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__LAST_TOKEN_SHOULD_BE_EOF; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token should be EOF — while it's %s", anime_token__type_get_cstr(token_type)); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };
  
 error__current_token_is_eof: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_EOF; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token is EOF "); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__current_token_is_invalid: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token is invalid"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

 error__current_token_out_of_bounds: {
    this -> error_id = ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_OUT_OF_BOUND; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token (%d) out of bounds (0 - %d) ", this -> token_i, token_nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };
  
 error__null_token_env: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__NULL_TOKEN_ENV; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Token_env is NULL"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

 ambiguous__token_env_has_zero_token: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__TOKEN_ENV_HAS_ZERO_TOKEN; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Ambiguous: Token_env does not contain any token."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };
  
 error__current_token_not_an_opening_paren: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "the current token is not an opening parenthesis"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__current_token_not_a_closing_paren: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__NOT_AN_CLOSING_PARENTHESIS; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "the current token is not a closing parenthesis"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__cannot_skip_to_closing_paren_in_lalr_mode: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__CANNOT_SKIP_TO_CLOSING_PARENTHESIS_IN_LALR_MODE; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Cannot skip to closing parenthesis in LALR mode"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

 error__parenthesis_stack_too_small: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__PARENTHESIS_STACK_TOO_SMALL; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "parenthesis stack is too small"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__mismatching_parenthesis: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "mismatching parenthesis"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    //{ dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
}; 



static int_anime_error_t anime_syntax_filtering__lalr_automaton(anime_syntax_filtering_t * this, anime_token_env_t * token_env, const int first_token, int_anime_token_t * end_token_r); 



int_anime_error_t anime_syntax_filtering__get_current_token(anime_syntax_filtering_t * this, anime_token_env_t * token_env, int_anime_token_t * token_i_r) { 
  if (NULL ==      this) return ANIME__SYNTAX_FILTERING__NULL_THIS; 
  if (NULL == token_i_r) { goto error_token_i_r_is_null; }; 
  if (ANIME_TOKEN_I_BOF     == this -> token_i) return anime_syntax_filtering__get_next_token(this, token_env, token_i_r); 
  if (ANIME_TOKEN_I_INVALID == this -> token_i) { goto error__current_token_is_invalid; }; 
  
  //int8_t            syntax_filtering__mode; // 0 → 'regular' ; 1 → lalr 
  if (1 == this -> syntax_filtering__mode) { 
    if (!this -> syntax_filtering__lalr_completed_huh) { 
      const int error_id = anime_syntax_filtering__lalr_automaton(this, token_env, this -> token_i, &this -> token_i); 
      if (error_id != ANIME__OK) { return error_id; }; 
      this -> syntax_filtering__lalr_completed_huh = true; 
    }; 
  }; 

  if (1 == this -> syntax_filtering__mode) { 
    if (this -> syntax_filtering__output_postfix_buffer__i >= this -> syntax_filtering__output_postfix_buffer__nb) { 
      this -> syntax_filtering__mode = 0; 
    } 
    else { 
      *token_i_r = this -> syntax_filtering__output_postfix_buffer__array[this -> syntax_filtering__output_postfix_buffer__i]; 
      return ANIME__OK; 
    }; 
  }; 
  
  if (0 == this -> syntax_filtering__mode) { 
    *token_i_r = this -> token_i; 
    return ANIME__OK; 
  };  
  
  assert(false); 
  return ~ANIME__OK; 
  

 error__current_token_is_invalid: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token is invalid"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error_token_i_r_is_null: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__NULL_TOKEN_I; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "'token_i_r' argument is NULL"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
}; 


  






int_anime_error_t anime_syntax_filtering__get_next_token(anime_syntax_filtering_t * this, anime_token_env_t * token_env, int_anime_token_t * token_i_r) { 
  if (NULL ==      this) return ANIME__SYNTAX_FILTERING__NULL_THIS; 
  if (NULL == token_env) { goto error__null_token_env; }; 
  if (NULL == token_i_r) { goto error_token_i_r_is_null; }; 
  const int token_nb = anime_token__get_count(token_env); 
  if (0 == token_nb) { goto ambiguous__token_env_has_zero_token; }; 
  
  //int8_t            syntax_filtering__mode; // 0 → 'regular' ; 1 → lalr 
  if (0 == this -> syntax_filtering__mode) { goto regular_mode; }; 
  
  if (1 == this -> syntax_filtering__mode) { 
    if (this -> syntax_filtering__lalr_completed_huh) { goto lalr_mode; }; 
    const int error_id = anime_syntax_filtering__lalr_automaton(this, token_env, this -> token_i, &this -> token_i); 
    if (error_id != ANIME__OK) { return error_id; }; 
    this -> syntax_filtering__lalr_completed_huh = true; 
    this -> syntax_filtering__output_postfix_buffer__i--; 
    goto lalr_mode; 
  }; 
  
  assert(false); 
  return ~ANIME__OK; 
  
 regular_mode: { 
    if (ANIME_TOKEN_I_BOF == this -> token_i) { 
      this -> token_i = 0; 
      *token_i_r = 0; 
      return anime_syntax_filtering__parenthesis__process(this, token_env, this -> token_i); 
    }; 
    if (ANIME_TOKEN_I_INVALID == this -> token_i) { goto error__current_token_is_invalid; }; 
    if (this -> token_i <         0) { goto error__current_token_out_of_bounds; }; 
    if (this -> token_i >= token_nb) { goto error__current_token_out_of_bounds; }; 
    if (this -> token_i == token_nb - 1) { 
      const int token_type = anime_token__get_type(token_env, this -> token_i); 
      if (ANIME_TOKEN_EOF != token_type) { goto error__last_token_should_be_eof; }; 
      *token_i_r = token_nb - 1; 
      return ANIME__OK; 
    }; 
    this -> token_i++; 
    //dprintf(stderr_d, "this -> token_i                                     = %d" "\n", this -> token_i); 
    *token_i_r = this -> token_i; 
    return anime_syntax_filtering__parenthesis__process(this, token_env, this -> token_i); 
  }; 
  
 lalr_mode: { 
    this -> syntax_filtering__output_postfix_buffer__i++; 
    if (this -> syntax_filtering__output_postfix_buffer__i >= this -> syntax_filtering__output_postfix_buffer__nb) { 
#if 0 
      dprintf(stderr_d, "this -> syntax_filtering__output_postfix_buffer__i  = %d" "\n", this -> syntax_filtering__output_postfix_buffer__i); 
      dprintf(stderr_d, "this -> syntax_filtering__output_postfix_buffer__nb = %d" "\n", this -> syntax_filtering__output_postfix_buffer__nb); 
      dprintf(stderr_d, "this -> token_i                                     = %d" "\n", this -> token_i); 
#endif 
      this -> syntax_filtering__mode = 0; 
      this -> token_i--; 
      goto regular_mode; 
    }; 
    const int token_i = this -> syntax_filtering__output_postfix_buffer__array[this -> syntax_filtering__output_postfix_buffer__i]; 
    *token_i_r = token_i; 
#if 0 
    // There should not be any parenthesis after reordering. 
    const int error_id = anime_syntax_filtering__parenthesis__process(this, token_i); 
    if (ANIME__OK != error_id) { return error_id; }; 
#endif 
    return ANIME__OK; 
  }; 

 ambiguous__token_env_has_zero_token: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__TOKEN_ENV_HAS_ZERO_TOKEN; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Ambiguous: Token_env does not contain any token."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };
  
 error__null_token_env: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__NULL_TOKEN_ENV; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Token_env is NULL"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

 error_token_i_r_is_null: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__NULL_TOKEN_I; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "'token_i_r' argument is NULL"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
 error__current_token_is_invalid: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token is invalid"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

 error__current_token_out_of_bounds: {
    this -> error_id = ANIME__SYNTAX_FILTERING__CURRENT_TOKEN_OUT_OF_BOUND; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token (%d) out of bounds (0 - %d) ", this -> token_i, token_nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };
 
 error__last_token_should_be_eof: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__LAST_TOKEN_SHOULD_BE_EOF; 
    if (NULL != token_i_r) { *token_i_r = ANIME_TOKEN_I_INVALID; }; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Current token should be EOF — while it's %s", anime_token__type_get_cstr(anime_token__get_type(token_env, this -> token_i))); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };

}; 






struct anime_custom_syntax_env_t; 
// *** CUSTOM SYNTAX *** 
enum { ANIME__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX =  12 }; 

enum { ANIME__CUSTON_SYNTAX__BASE      = ANIME_TOKEN__SYNTAX_KEYWORD__TOP - 1 }; 
 
enum { ANIME__CUSTOM_SYNTAX_NODE__BASE = ANIME__CUSTON_SYNTAX__BASE }; 
enum { ANIME__CUSTOM_SYNTAX_NODE__SIZE = 31 }; 
enum { ANIME__CUSTOM_SYNTAX_NODE__TOP  = ANIME__CUSTOM_SYNTAX_NODE__BASE + ANIME__CUSTOM_SYNTAX_NODE__SIZE }; 

enum { ANIME__CUSTOM_SYNTAX_RULE__BASE = ANIME__CUSTOM_SYNTAX_NODE__TOP }; 
enum { ANIME__CUSTOM_SYNTAX_RULE__SIZE = 33 }; //126 }; 
enum { ANIME__CUSTOM_SYNTAX_RULE__TOP  = ANIME__CUSTOM_SYNTAX_RULE__BASE + ANIME__CUSTOM_SYNTAX_RULE__SIZE }; 

struct anime_custom_syntax_env_t { 
  uint8_t custom_syntax_node__nb; 
  uint8_t custom_syntax_rules__array[ANIME__CUSTOM_SYNTAX_RULE__SIZE][3 + ANIME__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX]; 
  uint8_t custom_syntax_rules__nb; 
  uint8_t custom_syntax_trees__nb; 
  uint8_t custom_syntax_trees__array[ANIME__CUSTOM_SYNTAX_RULE__SIZE][2 + ANIME__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX]; 
  uint8_t custom_syntax_root__array[ANIME_TOKEN__SYNTAX_MASTER__SIZE]; 
}; 
typedef struct anime_custom_syntax_env_t anime_custom_syntax_env_t;
const        int32_t anime_custom_syntax_env__sizeof                  = sizeof(anime_custom_syntax_env_t); 
enum {               anime_custom_syntax_env__sizeof__compiler_const  = sizeof(anime_custom_syntax_env_t) }; 

anime_custom_syntax_env_t * anime_custom_syntax_env__make(const int stdlog_d) { 
  MALLOC_BZERO(anime_custom_syntax_env_t,this); 
  return this; 
}; 
 
void anime_custom_syntax_env__bzero(anime_custom_syntax_env_t * this) { 
  bzero(this, sizeof(*this)); 
}; 
 
void anime_custom_syntax_env__delete(anime_custom_syntax_env_t * this) { 
  free(this); 
}; 



static int_anime_error_t anime_syntax_filtering__lalr_automaton__aux(char * exception_data, anime_syntax_filtering_t * this, anime_token_env_t * token_env, const anime_custom_syntax_env_t * custom_syntax_env, int * current_token_ref); 

enum { anime_syntax_filtering__lalr_automaton__exception_data_size = sizeof(sigjmp_buf) + (1 << 9) }; 
int_anime_error_t anime_syntax_filtering__lalr_automaton(anime_syntax_filtering_t * this, anime_token_env_t * token_env, const int first_token, int_anime_token_t * end_token_r) { 
  int current_token = first_token; 
  anime_custom_syntax_env_t custom_syntax_env[1]; 
  anime_custom_syntax_env__bzero(custom_syntax_env); 
  char exception_data[anime_syntax_filtering__lalr_automaton__exception_data_size]; 
  *((int16_t*) exception_data + 0) = sizeof(exception_data); 
  *((int16_t*) exception_data + 2) = sizeof(sigjmp_buf); 
  sigjmp_buf * setjmp_env_ptr = (sigjmp_buf *) (exception_data + 4); 
  const int setjmp_value = sigsetjmp(*setjmp_env_ptr, 0); 
  if (0 == setjmp_value) { 
    const int error_id = anime_syntax_filtering__lalr_automaton__aux(exception_data, this, token_env, custom_syntax_env, /*current_token_ref*/&current_token); 
    *end_token_r = current_token; 
#if 0 
    dprintf(stderr_d, "this -> token_i = %d" "\n", current_token); 
#endif 
    return error_id; 
  } 
  else { 
    // RL: An exception was raised. 
    // RL: Basically, syntax error. 
    //dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_syntax_filtering_automaton_state__cstr[state], "]: ", "Unexpected token ", int_string__stack(next_token), " - I was expecting a name to identify the currently being defined constant value.", "\n"); return -1; 
    const char * msg = (const char *) (exception_data + 4 + sizeof(sigjmp_buf)); 
    dputs(stderr__fileno, msg); 
    dput_eol(stderr__fileno); 
    return setjmp_value; 
  }; 
  assert(false); 
  return -1; 
}; 




#define get_current_token_type() (*current_token_ref < 0 ? ANIME_TOKEN_NULL : *current_token_ref >= anime_token__get_count(token_env) ? ANIME_TOKEN_EOF : (anime_token__get_type(token_env, *current_token_ref))) 

// RL: TODO XXX FIXME 
//#define get_next_token_type__()  (assert(false),0) 
#define get_next_token_type__()  ((*current_token_ref < 0) ? ANIME_TOKEN_NULL : ((*current_token_ref + 1 >= anime_token__get_count(token_env)) ? ANIME_TOKEN_EOF : ((*current_token_ref)++, anime_token__get_type(token_env, *current_token_ref)))) 
#if DEBUG_PARSER >= 2 
#  define get_next_token_type()    (dputs_array(this -> stdlog_d, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">", ":<get_next_token>", ": ", "current_token_ref = ", int_string__stack(*current_token_ref), "\n"), (get_next_token_type__())) 
#else 
#  define get_next_token_type()    (get_next_token_type__())
#endif 



// --- Exceptions --- 

#define EXCEPTION__RAISE__(msg)						\
  strlcpy(exception_data + 4 + sizeof(sigjmp_buf), msg, *((int16_t*)exception_data) - 4 - sizeof(sigjmp_buf)); \
  siglongjmp(*((sigjmp_buf *) (exception_data + 4)), -1); 

#define EXCEPTION__RAISE(...) {						\
  const char * msg = strconcat__stack(__VA_ARGS__);			\
  strlcpy(exception_data + 4 + sizeof(sigjmp_buf), msg, *((int16_t*)exception_data) - 4 - sizeof(sigjmp_buf)); \
  siglongjmp(*((sigjmp_buf *) (exception_data + 4)), -1);		\
  }; 
 
#if DEBUG_PARSER >= 1 
#  define SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION "{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", " current_lalr_state: ", int_string__stack(current_lalr_state), "] }: ",
#else 
#  define SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION 
#endif 

#define SYNTAX__EXCEPTION__ASSERT(cond,user_msg) {			\
    if (!(cond)) {							\
    const int    token_i      = *current_token_ref;			\
    const int    token_type   = anime_token__get_type(token_env, token_i); \
    const char * srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); \
    const char * srcval_cstr  = anime_token__get_srcval_cstr(token_env, token_i); \
    const int    line1        = anime_token__get_line1(token_env, token_i); \
    const int    column0      = anime_token__get_column0(token_env, token_i); \
    const char * msg_array[]  = {					\
      SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION			\
      srcfile_cstr, ":", int_string__stack(line1), ":", int_string__stack(column0), ": ", (user_msg) }; \
    const char * msg          = strconcat__stack_nb(ARRAY_SIZE(msg_array), msg_array); \
    EXCEPTION__RAISE__(msg);						\
  };									\
  }; 

#define SYNTAX__EXPECTING_THIS_TOKEN(given_token_type,expected_token_type) { \
  if (given_token_type != expected_token_type) {			\
  const int    token_i      = *current_token_ref;				\
  const int    token_type   = anime_token__get_type(token_env, token_i);	\
  const char * srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); \
  const char * srcval_cstr  = anime_token__get_srcval_cstr(token_env, token_i); \
  const int    line1        = anime_token__get_line1(token_env, token_i);	\
  const int    column0      = anime_token__get_column0(token_env, token_i);	\
  const char * msg_array[]  = {						\
    SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION  \
    srcfile_cstr, ":", int_string__stack(line1), ":", int_string__stack(column0), ": ", \
    "Unexpected token: ", anime_token__type_get_cstr(given_token_type), "(", int_string__stack(given_token_type), ") -- Was expecting token: ", anime_token__type_get_cstr(expected_token_type), "(", int_string__stack(expected_token_type), ")" }; \
  const char * msg          = strconcat__stack_nb(ARRAY_SIZE(msg_array), msg_array);			\
  EXCEPTION__RAISE__(msg);					\
  };									\
  }; 

#define SYNTAX__EXPECTING_NOT_THIS_TOKEN(unexpected_token_type) {	\
    const int    token_i      = *current_token_ref;			\
    const int    token_type   = anime_token__get_type        (token_env, token_i); \
    const char * srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); \
    const char * srcval_cstr  = anime_token__get_srcval_cstr (token_env, token_i); \
    const int    line1        = anime_token__get_line1       (token_env, token_i); \
    const int    column0      = anime_token__get_column0     (token_env, token_i); \
    const char * msg_array[]  = {					\
      SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION \
      srcfile_cstr, ":", int_string__stack(line1), ":", int_string__stack(column0), ": ", \
      "Unexpected token: ", anime_token__type_get_cstr(unexpected_token_type), "(", int_string__stack(unexpected_token_type), ") -- Was expecting another token." }; \
    const char * msg          = strconcat__stack_nb(ARRAY_SIZE(msg_array), msg_array); \
    EXCEPTION__RAISE__(msg);						\
  }; 

#define SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(given_token_type, ...) {	\
    if (not(int_member_huh(given_token_type, __VA_ARGS__))) {		\
      const int expected_tokens_array[] = (const int []) { __VA_ARGS__ }; \
      const int expected_tokens_nb      = ARRAY_SIZE(((const int []) { __VA_ARGS__ })); \
      const int token_i = *current_token_ref;				\
      const int token_type = anime_token__get_type(token_env, token_i); \
      const char * srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); \
      const char * srcval_cstr = anime_token__get_srcval_cstr(token_env, token_i); \
      const int line1 = anime_token__get_line1(token_env, token_i);	\
      const int column0 = anime_token__get_column0(token_env, token_i); \
      const char * prefix_msg_array[] = {				\
        SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION  \
	srcfile_cstr, ":", int_string__stack(line1), ":", int_string__stack(column0), ": ", \
	"Unexpected token: ", anime_token__type_get_cstr(given_token_type), "(", int_string__stack(given_token_type), ") -- Was expecting one of these ", int_string__stack(expected_tokens_nb), " tokens: " }; \
      const int prefix_msg_array_nb = ARRAY_SIZE(prefix_msg_array);	\
      const int msg_array_nb = prefix_msg_array_nb + 5*expected_tokens_nb; \
      const char * msg_array[msg_array_nb];				\
      bcopy(prefix_msg_array, msg_array, sizeof(prefix_msg_array));	\
      for (int i = 0; i < expected_tokens_nb; i++) {			\
	const char * * p = msg_array + prefix_msg_array_nb + 5*i;	\
	*(p + 0) = anime_token__type_get_cstr(expected_tokens_array[i]); \
	*(p + 1) = "(";							\
	*(p + 2) = int_string__stack(expected_tokens_array[i]);		\
	*(p + 3) = ")";							\
	*(p + 4) = i == expected_tokens_nb-1 ? "" : ", ";		\
      };								\
      const char * msg = strconcat__stack_nb(msg_array_nb, msg_array);	\
      EXCEPTION__RAISE__(msg);						\
    };									\
  }; 



 
// *** CUSTOM SYNTAX *** 
extern int anime__custom_syntax__node_push(anime_custom_syntax_env_t * this) { 
  assert(this -> custom_syntax_node__nb < ANIME__CUSTOM_SYNTAX_NODE__SIZE); 
  const int node_id = ANIME__CUSTOM_SYNTAX_NODE__BASE + this -> custom_syntax_node__nb; 
  this -> custom_syntax_node__nb ++; 
  return node_id; 
}; 

int anime__custom_syntax__node_count(const anime_custom_syntax_env_t * this) { 
  return this -> custom_syntax_node__nb; 
}; 

int anime__custom_syntax__rule_push_array_nb(anime_custom_syntax_env_t * this, const int node_id, const int right_len, const int right_items[]) { 
  assert(this -> custom_syntax_rules__nb < ANIME__CUSTOM_SYNTAX_RULE__SIZE); 
  const int index   = this -> custom_syntax_rules__nb; 
  const int rule_id = ANIME__CUSTOM_SYNTAX_RULE__BASE + index; 
  this -> custom_syntax_rules__nb ++; 
  
  assert(right_len <= ANIME__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX);  

  // rule_id, left_symbol, right_length, right_symbols... 
  //this -> custom_syntax_rules__array[index] = (const int8_t[]) { rule_id, node_id, right_len }; 
  this -> custom_syntax_rules__array[index][0] = rule_id; 
  this -> custom_syntax_rules__array[index][1] = node_id; 
  this -> custom_syntax_rules__array[index][2] = right_len; 
  for (int i = 0; i < right_len; i++) { 
    this -> custom_syntax_rules__array[index][3 + i] = right_items[i]; 
  }; 
  //[3 + ANIME__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX + 1]; 
  
  return rule_id; 
}; 
 
int anime__custom_syntax__rule_count(const anime_custom_syntax_env_t * this) { 
  return this -> custom_syntax_rules__nb; 
}; 

int anime__custom_syntax__rule_lookup(const anime_custom_syntax_env_t * this, const int node_id, const int token_i) { 
  int epsilon_rule = -1; // RL: The rule «N → ε», if any. 
  int subexpr_rule = -1; // RL: A rule «N → S ...», if any. 
  for (int i = 0; i < this -> custom_syntax_rules__nb; i++) { 
    if (this -> custom_syntax_rules__array[i][1] != node_id) { continue; }; 
    if (this -> custom_syntax_rules__array[i][2] == 0) { epsilon_rule = this -> custom_syntax_rules__array[i][0]; continue; }; 
    if (this -> custom_syntax_rules__array[i][3] == 0) { subexpr_rule = this -> custom_syntax_rules__array[i][0]; continue; }; 
    if (this -> custom_syntax_rules__array[i][3] != token_i) { continue; }; 
    // RL: Found. 
    return this -> custom_syntax_rules__array[i][0];
  }; 
  return subexpr_rule < 0 ? epsilon_rule : subexpr_rule; 
}; 


extern void anime__custom_syntax__master_root_set(anime_custom_syntax_env_t * this, const int token_master_type_id, const int rule_id) { 
  const int index = token_master_type_id - ANIME_TOKEN__SYNTAX_MASTER__BASE; 
  this -> custom_syntax_root__array[index] = rule_id - ANIME__CUSTOM_SYNTAX_RULE__BASE; 
}; 

extern void anime__custom_syntax__tree_set__array_nb(anime_custom_syntax_env_t * this, const int rule_id, const int tree_type, const int items_len, const int items_indices[]) { 
  assert(rule_id >= ANIME__CUSTOM_SYNTAX_RULE__BASE); 
  assert(rule_id <  ANIME__CUSTOM_SYNTAX_RULE__TOP ); 
  const int index = rule_id - ANIME__CUSTOM_SYNTAX_RULE__BASE; 
  
  assert(items_len <= ANIME__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX);  
  const int rule_right_len = this -> custom_syntax_rules__array[index][2]; 
  for (int i = 0; i < items_len; i++) { 
    assert(items_indices[i] < rule_right_len); 
  }; 

  // tree_type, items_len, items_indices... 
  this -> custom_syntax_trees__array[index][0] = tree_type; 
  this -> custom_syntax_trees__array[index][1] = items_len; 
  for (int i = 0; i < items_len; i++) { 
    this -> custom_syntax_trees__array[index][2 + i] = items_indices[i]; 
  }; 
  //[3 + ANIME__CUSTOM_SYNTAX_TREE__RIGHT_LENGTH_MAX + 1]; 
}; 
 
int anime__custom_syntax__tree_count(const anime_custom_syntax_env_t * this) { 
  return this -> custom_syntax_trees__nb; 
}; 






static const int anime_syntax_filtering__postfix_operators[]   = { ANIME_TOKEN_INC, ANIME_TOKEN_DEC }; 
static const int anime_syntax_filtering__postfix_operators__nb = ARRAY_SIZE(anime_syntax_filtering__postfix_operators); 


static int_anime_error_t anime_syntax_filtering__lalr_automaton__aux(char * exception_data, anime_syntax_filtering_t * this, anime_token_env_t * token_env, const anime_custom_syntax_env_t * custom_syntax_env, int * current_token_ref) { 
  
#if DEBUG_PARSER >= 2 
  dputs_array(this -> stdlog_d, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[current_token: ", int_string__stack(*current_token_ref), "]\n"); 
#endif 


  // RL: This is where we need the LALR theory as we cannot reasonably use a LL1 analysis (any LL1 grammar matching that language looks terrible and does not fit our needs). 
  // RL: Infix tokens: 
  // expr  ANIME_TOKEN_OR           expr1 
  // expr  ANIME_TOKEN_AND          expr1 
  // expr  ANIME_TOKEN_XOR          expr1 
  // expr1 ANIME_TOKEN_EQUAL        expr2 
  // expr1 ANIME_TOKEN_DIFF         expr2 
  // expr1 ANIME_TOKEN_INF          expr2 
  // expr1 ANIME_TOKEN_SUP          expr2 
  // expr1 ANIME_TOKEN_INFEQ        expr2 
  // expr1 ANIME_TOKEN_SUPEQ        expr2 
  // expr2 token_plus_symbol  expr3 
  // expr2 token_minus_symbol expr3 
  // expr3 ANIME_TOKEN_IMULT        expr4  
  // expr3 ANIME_TOKEN_IDIV         expr4 
  // expr3 ANIME_TOKEN_IMOD         expr4 
  // expr3 ANIME_TOKEN_RMULT        expr4 
  // expr3 ANIME_TOKEN_RDIV         expr4 
  //       ANIME_TOKEN_NOT          expr4 
  //       ANIME_TOKEN_IPLUS        expr4 
  //       ANIME_TOKEN_IMOINS       expr4 
  //       ANIME_TOKEN_RPLUS        expr4 
  //       ANIME_TOKEN_RMOINS       expr4 
  // expr5 ANIME_TOKEN_PTR 
  //       ANIME_TOKEN_REF          expr5 
  // expr5 ANIME_TOKEN_OPENBRACKET  expr  ANIME_TOKEN_CLOSEBRACKET 
  // expr5 ANIME_TOKEN_POINT        nom 
  // appel_funproc__expr 
  // appel_methode__expr 
  //       ANIME_TOKEN_OPENPAR      expr  ANIME_TOKEN_CLOSEPAR 
  //       ANIME_TOKEN_TRUE 
  //       ANIME_TOKEN_FALSE 
  //       ANIME_TOKEN_ENTIER 
  //       ANIME_TOKEN_REEL 
  //       ANIME_TOKEN_CHAINE 
  //       ANIME_TOKEN_IDENT 
  //       ANIME_TOKEN_NIL 
  // --- 
  // RL: Premier(expr): // RL: TODO XXX FIXME: Add ANIME_TOKEN_BITCOMPLEMENT, bit_shift, assign, side_effect_assigns, etc. 
  //       ANIME_TOKEN_NOT 
  //       ANIME_TOKEN_IPLUS 
  //       ANIME_TOKEN_IMOINS 
  //       ANIME_TOKEN_RPLUS 
  //       ANIME_TOKEN_RMOINS 
  //       ANIME_TOKEN_OPENPAR 
  //       ANIME_TOKEN_TRUE 
  //       ANIME_TOKEN_FALSE 
  //       ANIME_TOKEN_ENTIER 
  //       ANIME_TOKEN_REEL 
  //       ANIME_TOKEN_CHAINE 
  //       ANIME_TOKEN_IDENT 
  //       ANIME_TOKEN_NIL 
  // 
  // RL: As per the LALR theory, two stacks are needed: (i) one for the outputs (trees being built); (ii) one for the current path in the automaton [used when reducing, in order to backtrack in the automaton]. 
  //const int8_t path__size = 63; // RL: This represents the nestedness of an expression. If an expression is more nested than that, then we wouldn't be able to parse it. 
  enum { path__size = 63 }; 
  int8_t path__array[path__size]; 
  int8_t path__nb = 0; 
  //const int8_t outputs__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
  enum { outputs__size = path__size }; 
  int16_t outputs__array[outputs__size]; 
  int8_t outputs__nb = 0; 
  // RL: Extra stacks, as the automaton could be simplified in adding variables instead of extending all these into states. 
  //const int8_t operator__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
  enum { operator__size = path__size }; 
  int8_t operator__array[operator__size]; 
  int8_t operator__nb = 0; 
  //const int8_t arity__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
  enum { arity__size = path__size }; 
  int8_t arity__array[arity__size]; 
  int8_t arity__nb = 0; 
  //const int8_t master__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
  enum { master__size = path__size }; 
  int8_t master__array[master__size]; 
  int8_t master__nb = 0; 
  //const int8_t rule_idx__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
  enum { rule_idx__size = path__size }; 
  int8_t rule_idx__array[rule_idx__size]; 
  int8_t rule_idx__nb = 0; 
  //const int8_t rule_pos__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
  enum { rule_pos__size = path__size }; 
  int8_t rule_pos__array[rule_pos__size]; 
  int8_t rule_pos__nb = 0; 
  // Output tree stack [node is at the top] 
  enum {   output_token_tree_stack__size = 127 }; 
  uint16_t output_token_tree_stack__array[output_token_tree_stack__size]; 
  uint8_t  output_token_tree_stack__arity[output_token_tree_stack__size]; 
  uint8_t  output_token_tree_stack__nb = 0; 
  // Automaton 
  int8_t  current_lalr_state; 
  int16_t current_symbol; 
#define PUSH_OUTPUT(x)   { assert( outputs__nb <  outputs__size);  outputs__array[ outputs__nb++] = (x); }; 
#define PUSH_PATH(x)     { assert(    path__nb <     path__size);     path__array[    path__nb++] = (x); }; 
#define PUSH_OPERATOR(x) { assert(operator__nb < operator__size); operator__array[operator__nb++] = (x); }; 
#define PUSH_ARITY(x)    { assert(   arity__nb <    arity__size);    arity__array[   arity__nb++] = (x); }; 
#define PUSH_MASTER(x)   { assert(  master__nb <   master__size);   master__array[  master__nb++] = (x); }; 
#define PUSH_RULE_IDX(x) { assert(rule_idx__nb < rule_idx__size); rule_idx__array[rule_idx__nb++] = (x); }; 
#define PUSH_RULE_POS(x) { assert(rule_pos__nb < rule_pos__size); rule_pos__array[rule_pos__nb++] = (x); }; 
#define POP_OUTPUT(x)    { assert( outputs__nb > 0); (x) =  outputs__array[-- outputs__nb]; }; 
#define POP_PATH(x)      { assert(    path__nb > 0); (x) =     path__array[--    path__nb]; }; 
#define POP_OPERATOR(x)  { assert(operator__nb > 0); (x) = operator__array[--operator__nb]; }; 
#define POP_ARITY(x)     { assert(   arity__nb > 0); (x) =    arity__array[--   arity__nb]; }; 
#define POP_MASTER(x)    { assert(  master__nb > 0); (x) =   master__array[--  master__nb]; }; 
#define POP_RULE_IDX(x)  { assert(rule_idx__nb > 0); (x) = rule_idx__array[--rule_idx__nb]; }; 
#define POP_RULE_POS(x)  { assert(rule_pos__nb > 0); (x) = rule_pos__array[--rule_pos__nb]; }; 
#define DROP_OUTPUT()    { assert( outputs__nb > 0);  outputs__nb--; }; 
#define DROP_OPERATOR(x) { assert(operator__nb > 0); operator__nb--; }; 
#define DROP_ARITY(x)    { assert(   arity__nb > 0);    arity__nb--; }; 
#define DROP_MASTER(x)   { assert(  master__nb > 0);   master__nb--; }; 
#define DROP_RULE_IDX(x) { assert(rule_idx__nb > 0); rule_idx__nb--; }; 
#define DROP_RULE_POS(x) { assert(rule_pos__nb > 0); rule_pos__nb--; }; 
#define INC_ARITY()      { assert(   arity__nb > 0); arity__array[arity__nb]++; }; 
#define OUTPUT_TREE_PUSH(token_root,arity,new_tree_r) { assert(output_token_tree_stack__nb < output_token_tree_stack__size); output_token_tree_stack__arity[output_token_tree_stack__nb] = (arity); output_token_tree_stack__array[output_token_tree_stack__nb] = (token_root); (new_tree_r) = output_token_tree_stack__nb; output_token_tree_stack__nb++; }; 
#define EXPR_CASE_GOTO(id) case id: goto glue(label__expr_state,id); break;  
#define EXPR_LABEL_STATE(id) glue(label__expr_state,id) 
  
  // Start! 
  current_lalr_state = 0; 
  current_symbol = get_current_token_type(); 
  PUSH_PATH(11); 
  
  for (;;) { 
#if DEBUG_PARSER >= 2
    dputs_array(this -> stdlog_d, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", " current_lalr_state: ", int_string__stack(current_lalr_state), " - current_token: ", int_string__stack(*current_token_ref), " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", "\n"); 
#endif 
#if DEBUG_PARSER >= 3 
    dputs_array(this -> stdlog_d, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(this -> stdlog_d, int_string__stack(path__array[i]), " -> "); }; dputs_array(this -> stdlog_d, " ]", "\n" ); 
#endif 
#if DEBUG_PARSER >= 3 
    dputs_array(this -> stdlog_d, "\t", "OUTPUTS: [ "); for (int i = 0; i < outputs__nb; i++) { dputs_array(this -> stdlog_d, int_string__stack(outputs__array[i]), " -> "); }; dputs_array(this -> stdlog_d, " ]", "\n" ); 
#endif 
    switch (current_lalr_state) { 
      EXPR_CASE_GOTO(0);  // RL: S → . S   _   S | . _ S | . S _ | . ( S ) | ... 
      EXPR_CASE_GOTO(1);  // RL: S →   S . _   S 
      EXPR_CASE_GOTO(6);  // RL: S →       _ . S 
      EXPR_CASE_GOTO(7);  // RL: S → ( S . ) 
      EXPR_CASE_GOTO(8);  // RL: S → ident ( . ... // <funcall>  
      EXPR_CASE_GOTO(9);  // RL: arg_list: expecting ', S+' or ')' -- A 'S' was read and is on the output stack. 
      EXPR_CASE_GOTO(10); // RL: arg_list: we have read at least one comma - expecting ', S+' or ')' -- An 'ident' and a 'arg_list' were read and are on the output stack. 
      EXPR_CASE_GOTO(11); // RL: An expression was recognized! 
      EXPR_CASE_GOTO(12); // RL: S →   S   _   S . 
      EXPR_CASE_GOTO(13); // RL: S →   S [  S . ] 
      EXPR_CASE_GOTO(14); // RL: S →   S ? . S :   S 
      EXPR_CASE_GOTO(15); // RL: S →   S ?   S : . S 
      EXPR_CASE_GOTO(16); // RL: SYNTAX_MASTER - INIT 
      EXPR_CASE_GOTO(17); // RL: SYNTAX_MASTER - INSIDE 
    }; 
    // Default case: unexpected 'current_lalr_state' 
    SYNTAX__EXCEPTION__ASSERT(false,"Unexpected 'current_lalr_state'"); 
    // RL: TODO FIXME XXX 
    assert(false); 
      
    
  EXPR_LABEL_STATE(0): { 
      if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
      
      //RL: Constant value? 
      if (int_member_huh(current_symbol, ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL, ANIME_TOKEN_NULL_PTR, ANIME_TOKEN_IDENT)) { 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(*current_token_ref,/*arity*/~0,new_tree); 	  
	PUSH_OUTPUT(new_tree); 
	current_lalr_state = 1; // We reduced, so now go there. 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      
      // RL: Prefix unary operator? 
      if (int_member_huh(current_symbol, ANIME_TOKEN_LOGICAL_NOT, ANIME_TOKEN_IPLUS, ANIME_TOKEN_IMOINS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_RMOINS)) { 
	PUSH_OPERATOR(current_symbol); 
	PUSH_OUTPUT(*current_token_ref); 
	PUSH_ARITY(1); 
	PUSH_PATH(1); // RL: Where we will go after having built the whole unary tree. 
	PUSH_PATH(6); // RL: Where we will go when the sub expression will be reduced. 
	current_lalr_state = 0; // RL: Right now, go there. 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
 
      // RL: Parenthesis? 
      if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	PUSH_OPERATOR(current_symbol); // RL: We need to tell the next operator that it should not look backward. 
	PUSH_ARITY(1); 
	PUSH_PATH(1); // RL: Where we will go after having built the whole parenthesis tree. 
	PUSH_PATH(7); // RL: Where we will go when the sub expression will be reduced. 
	current_lalr_state = 0; // RL: Right now, go there. 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      
      // RL: Lambda? 
      if (ANIME_TOKEN_LAMBDA == current_symbol) { 
#if 1 
	SYNTAX__EXCEPTION__ASSERT(false,"Lambda expression not implemented."); 
#else  
	const int lambda_decl_expr = anime_syntax_filtering__automaton__aux(exception_data, this, token_env, expr_lambda, current_token_ref, retval1_ref);
	current_symbol = get_current_token_type(); ; 
	//const int16_t new_tree = anime_expr_tree__push0(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__LAMBDA, lambda_decl); 
	const int16_t new_tree = lambda_decl_expr; 
	PUSH_OUTPUT(new_tree); 
	current_lalr_state = 1; 
	continue; 
#endif 
      }; 

      // RL: Master of a custom syntax? 
      if (ANIME_TOKEN__SYNTAX_MASTER__BASE <= current_symbol && current_symbol < ANIME_TOKEN__SYNTAX_MASTER__TOP) { 
	PUSH_PATH(1); // RL: Where we will go after having reduced the custom syntax. 
	current_lalr_state = 16; // RL: Right now, go there. 
	continue;
      }; 
      
      // RL: TODO XXX FIXME: We might need to handle empty expressions. We'll see. (If so, it might be done right at the start, not here.) 
      
      // RL: No case matched. So we abort the analysis and tell the user. 
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL, ANIME_TOKEN_IDENT, ANIME_TOKEN_LOGICAL_NOT, ANIME_TOKEN_IPLUS, ANIME_TOKEN_IMOINS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_RMOINS, ANIME_TOKEN_OPENPAR, ANIME_TOKEN_LAMBDA, ANIME_TOKEN_SYNTAX_MASTER); 

      // We should not be here. 
      assert(false); 
    };  
    
    
    
    
    
    
  EXPR_LABEL_STATE(1): { 
      // RL: We have read one expression (one S). Now we will read the operator applied to that left expression. 
      if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
      
      const int infix_binary_operator_huh = int_member_huh(current_symbol, ANIME_TOKEN_AFFECTATION, ANIME_TOKEN_AFFECTATION_SIMPLE, ANIME_TOKEN_AFFECTATION_IADD, ANIME_TOKEN_AFFECTATION_RADD, ANIME_TOKEN_AFFECTATION_ISUB, ANIME_TOKEN_AFFECTATION_RSUB, ANIME_TOKEN_AFFECTATION_IMULT, ANIME_TOKEN_AFFECTATION_RMULT, ANIME_TOKEN_AFFECTATION_IDIV, ANIME_TOKEN_AFFECTATION_RDIV, ANIME_TOKEN_AFFECTATION_IMOD, ANIME_TOKEN_AFFECTATION_L_AND, ANIME_TOKEN_AFFECTATION_L_OR, ANIME_TOKEN_AFFECTATION_L_XOR, ANIME_TOKEN_AFFECTATION_B_AND, ANIME_TOKEN_AFFECTATION_B_OR, ANIME_TOKEN_AFFECTATION_B_XOR, ANIME_TOKEN_AFFECTATION_B_RSHIFT, ANIME_TOKEN_AFFECTATION_B_LSHIFT, ANIME_TOKEN_LOGICAL_OR, ANIME_TOKEN_LOGICAL_AND, ANIME_TOKEN_LOGICAL_XOR, ANIME_TOKEN_BITWISE_OR, ANIME_TOKEN_BITWISE_AND, ANIME_TOKEN_BITWISE_XOR, ANIME_TOKEN_BITWISE_SHIFT_LEFT, ANIME_TOKEN_BITWISE_SHIFT_RIGHT, ANIME_TOKEN_EQUAL, ANIME_TOKEN_DIFF, ANIME_TOKEN_INF, ANIME_TOKEN_SUP, ANIME_TOKEN_INFEQ, ANIME_TOKEN_SUPEQ, ANIME_TOKEN_IPLUS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_IMINUS, ANIME_TOKEN_RMINUS, ANIME_TOKEN_IMULT, ANIME_TOKEN_RMULT, ANIME_TOKEN_IDIV, ANIME_TOKEN_RDIV, ANIME_TOKEN_IMOD, ANIME_TOKEN_POINT, ANIME_TOKEN_FLECHE); 
      
      // RL: Infix binary operator? 
      if (infix_binary_operator_huh) { 
	// RL: Do we reduce or do we shift? 
	//     The default behavior is to shift. 
	//     However, shifting could be an undesirable behavior to handle priorities: 
	//        " 1 * 2 + 3 " 
	//     In such case, we should not shift first, but reduce first. 
	//     In order to implement that, we just have to compare operator priorities: 
	//       if priority(previous_operator) > priority(current_operator) then reduce else shift 
	//     
	// RL: The above interpretation is the LA(1)LR(0) one. 
	//     Conversely, the local-LL(1) interpretation is we need to figure out the place of that 
	//     operator on the right branch: if its priority is lower than the bottom item on that 
	//     right branch, then the operator place is upper on the branch; and that bottom item can 
	//     be pushed on the stack of the left sub-trees. 
	int reduce_huh = false; 
	if (operator__nb > 0) { 
	  const int previous_operator = operator__array[operator__nb-1]; 
	  reduce_huh = (previous_operator >= current_symbol); // RL: Property of token-types: first the lowest priority, last the highest priority. 
	}; 
	if (reduce_huh) { 
	  POP_PATH(current_lalr_state); 
	  continue; 
	} 
	else { 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(2); 
	  PUSH_PATH(12); // RL: Where we will go after the whole infix expression will have been reduced. 
	  current_lalr_state = 0; // RL: Right now, go there. 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
      }; 
	
      // RL: Bracket array? 
      if (ANIME_TOKEN_OPENBRACKET == current_symbol) { 
	PUSH_OPERATOR(current_symbol); 
	PUSH_OUTPUT(*current_token_ref); 
	PUSH_ARITY(2); 
	PUSH_PATH(13); // RL: Where we will go after the sub-expression will have been reduced. 
	current_lalr_state = 0; // RL: Right now, go there. 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
	
      // RL: Parenthesis funcall? 
      if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	PUSH_PATH(1); // RL: Where we will go back after having built the whole fun-call tree. 
	current_lalr_state = 8; // RL: Now, go to arg parsing. 
	continue;
      }; 
	
      // RL: Inline-if operator? 
      if (ANIME_TOKEN_HUH == current_symbol) { 
	PUSH_OPERATOR(current_symbol); 
	PUSH_OUTPUT(*current_token_ref); 
	PUSH_ARITY(3); 
	PUSH_PATH(14); // RL: Where we will go after the first sub-expression will have been reduced. 
	current_lalr_state = 0; // RL: Right now, go there. 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      
      // RL: Postfix operator? 
      if (int_member_array_nb(current_symbol, anime_syntax_filtering__postfix_operators__nb, anime_syntax_filtering__postfix_operators)) { 
	int subtree; 
	POP_OUTPUT(subtree); 
	const int operator_token = *current_token_ref; 
	const int operator = current_symbol; 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(*current_token_ref,1,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	current_lalr_state = 1; // RL: Right now, go there. 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      
      // RL: Anything that is not expected triggers a reduction. 
      POP_PATH(current_lalr_state); 
      continue; 
      
      assert(false); 
    }; 
      
      






  EXPR_LABEL_STATE(6): { // RL: PREFIX OPERATOR got read 
      // RL: A unary symbol was read, and a sub-tree was built and is on the ouput stack. 
      // RL: So, we have to get that tree from the stack, make a new tree, and push it onto the stack. 
      // RL: After that, we should backtrack by one. 
      int subtree; 
      POP_OUTPUT(subtree); 
      int operator_token; 
      POP_OUTPUT(operator_token); 
      int operator; 
      POP_OPERATOR(operator); 
      DROP_ARITY(); 
      int16_t new_tree; 
      OUTPUT_TREE_PUSH(operator_token,1,new_tree); // By connexity, subtree should be at the top. 
      PUSH_OUTPUT(new_tree); 
      POP_PATH(current_lalr_state); // RL: Backtrack 
      continue; 
    }; 
      
  EXPR_LABEL_STATE(7): { // RL: A '(' and a 'S' were read. Now we expect a ')'. 
      if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
      SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_CLOSEPAR); 
      // RL: We do not touch the tree on the stack, as we won't build a superfluous tree. 
      // RL: Now, we backtrack by one. 
      int operator; 
      POP_OPERATOR(operator); 
      DROP_ARITY(); 
      POP_PATH(current_lalr_state); 
      current_symbol = get_next_token_type(); 
      continue; 
    }; 

  EXPR_LABEL_STATE(8): { // RL: funcall: S → ident . ( ... 
      // RL: Here, we expect a comma-separated list of expressions, that could be empty. 
      SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_OPENPAR); 
      current_symbol = get_next_token_type(); 
      // RL: Is it empty? 
      if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	int ident_subtree; 
	POP_OUTPUT(ident_subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(ident_subtree,0,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	POP_PATH(current_lalr_state); // backtracking 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      
      // RL: As it is not empty, we expect a list of arguments. 
      PUSH_OPERATOR(ANIME_TOKEN_VIRGULE); 
      PUSH_ARITY(0); 
      PUSH_PATH(9); // After having reduced 
      current_lalr_state = 0; // Current next step 
      continue;
    }; 
      
  EXPR_LABEL_STATE(9): { // RL: arg_list: S . , S OR ')' 
      // RL: OK. We've just read one 'S'. Now we expect a ')' or a ','. Anything else is an error. 
      if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
      
      INC_ARITY(); // Top operator is ANIME_TOKEN_VIRGULE 
      
      if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	int operator; 
	POP_OPERATOR(operator); 
	assert(ANIME_TOKEN_VIRGULE == operator); 
	int virgule_arity; 
	POP_ARITY(virgule_arity); 
	assert(1 == virgule_arity); 
	// By connectivity, all the subtrees are already on the output tree stack. 
	for (int i = 0; i < virgule_arity; i++) { 
	  int virgule_subtree; 
	  POP_OUTPUT(virgule_subtree); 
	}; 
	int ident_subtree; 
	POP_OUTPUT(ident_subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(ident_subtree,virgule_arity,new_tree); // By connexity, subtrees should be at the top. 
	PUSH_OUTPUT(new_tree); 
	POP_PATH(current_lalr_state); // backtracking 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      
      if (current_symbol == ANIME_TOKEN_VIRGULE) { 
	PUSH_PATH(10);          // After having reduced the next sub-tree 
	current_lalr_state = 0; // Current next step 
	current_symbol = -1;    // Current symbol got read. 
	continue; 
      }; 
      
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_VIRGULE,ANIME_TOKEN_CLOSEPAR);       
      assert(false); 
    }; 
    
    
    
  EXPR_LABEL_STATE(10): { // RL: arg_list with two or more items (at least one comma read): S . , S OR ) 
      // RL: OK, we've just read one 'S'. Before that, we read a ',', and before that we read a 'S'. 
      if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
      
      INC_ARITY(); // Top operator is ANIME_TOKEN_VIRGULE 
      
      if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	int operator; 
	POP_OPERATOR(operator); 
	assert(ANIME_TOKEN_VIRGULE == operator); 
	
	int virgule_arity; 
	POP_ARITY(virgule_arity); 
	
	// By connectivity, all the subtrees are already on the output tree stack. 
	for (int i = 0; i < virgule_arity; i++) { 
	  int virgule_subtree; 
	  POP_OUTPUT(virgule_subtree); 
	}; 
	int ident_subtree; 
	POP_OUTPUT(ident_subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(ident_subtree,virgule_arity,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	POP_PATH(current_lalr_state); // Going to the state after having reduced. 
	current_symbol = -1; // Current symbol got read. 
	continue; 
      }; 
	
      if (current_symbol == ANIME_TOKEN_VIRGULE) { 
	PUSH_PATH(10);           // After having reduced 
	current_lalr_state =  0; // Current next step 
	current_symbol     = -1; // Current symbol got read. 
	continue; 
      }; 
      
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_VIRGULE,ANIME_TOKEN_CLOSEPAR); 
      assert(false); 
    }; 


  EXPR_LABEL_STATE(11): { // RL: S EOF . 
      break; 
    }; 

  EXPR_LABEL_STATE(12): { // RL: S →   S   _   S . 
      int right_subtree; 
      POP_OUTPUT(right_subtree); 
      int operator_token; 
      POP_OUTPUT(operator_token); 
      int left_subtree; 
      POP_OUTPUT(left_subtree); 
      int operator; 
      POP_OPERATOR(operator); 
      DROP_ARITY(); 
      int16_t new_tree; 
      OUTPUT_TREE_PUSH(operator_token,2,new_tree); // By connexity, subtrees should be at the top. 
      PUSH_OUTPUT(new_tree); 
      current_lalr_state = 1; // RL: Right now, go there (the left part of the rule) 
      continue; 
    }; 
    
    
  EXPR_LABEL_STATE(13): { // RL: S →   S [  S . ] 
      if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
      
      SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_CLOSEBRACKET); 
      current_symbol = get_next_token_type(); // RL: Eating the token. 
      
      int right_subtree; 
      POP_OUTPUT(right_subtree); 
      int operator_token; 
      POP_OUTPUT(operator_token); 
      int left_subtree; 
      POP_OUTPUT(left_subtree); 
      int operator; 
      POP_OPERATOR(operator); 
      DROP_ARITY(); 
      int16_t new_tree; 
      OUTPUT_TREE_PUSH(operator_token,2,new_tree); // By connexity, subtrees should be at the top. 
      PUSH_OUTPUT(new_tree); 
      current_lalr_state = 1; // RL: Right now, go there (the left part of the rule) 
      continue; 
    }; 


  EXPR_LABEL_STATE(14): { // RL: S →   S ?  S . : S  
      SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_DEUXPOINTS); 
      current_symbol = get_next_token_type(); // RL: Eating the token. 
      PUSH_PATH(15); // RL: Where we will go after having recognized S 
      current_lalr_state = 0; // RL: Right now, go there (we have to recognize a S) 
      continue; 
    }; 
    
  EXPR_LABEL_STATE(15): { // RL: S →   S ?  S : S . 
      int right_subtree; 
      POP_OUTPUT(right_subtree); 
      int middle_subtree; 
      POP_OUTPUT(middle_subtree); 
      int operator_token; 
      POP_OUTPUT(operator_token); 
      int left_subtree; 
      POP_OUTPUT(left_subtree); 
      int operator; 
      POP_OPERATOR(operator); 
      DROP_ARITY(); 
      int16_t new_tree; 
      OUTPUT_TREE_PUSH(operator_token,2,new_tree); // By connexity, both subtrees should be at the top. 
      PUSH_OUTPUT(new_tree); 
      current_lalr_state = 1; // RL: Right now, go there (the left part of the rule) 
      continue; 
    }; 

  EXPR_LABEL_STATE(16): { // RL: S →   . SYNTAX_MASTER 
#if 0 
      assert(false); 
#else 
#if 0 
      dputs_array(this -> stdlog_d, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(this -> stdlog_d, int_string__stack(path__array[i]), " -> "); }; dputs_array(this -> stdlog_d, " ]", "\n" ); 
#endif 

      const int master_token_type_id = current_symbol; 
      const int master_index         = master_token_type_id - ANIME_TOKEN__SYNTAX_MASTER__BASE; 
      const int root_rule_index      = custom_syntax_env -> custom_syntax_root__array[master_index]; 
#if 0 
      dputs_array(this -> stdlog_d, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", 
		  " - current_lalr_state: ", int_string__stack(current_lalr_state), 
		  " - current_token: ", int_string__stack(*current_token_ref), 
		  " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", 
		  " - master_index: ", int_string__stack(master_index), 
		  " - root_rule_index: ", int_string__stack(root_rule_index), 
		  "\n"); 
#endif 

      //current_symbol = get_next_token_type(); // RL: Eating it. 
      PUSH_MASTER(master_index); 
      PUSH_RULE_IDX(root_rule_index); 
      //PUSH_RULE_POS(1); 
      PUSH_RULE_POS(0); 
      current_lalr_state = 17; // RL: Right now, go there 
      continue; 
#endif 
    }; 
	
  EXPR_LABEL_STATE(17): { // RL: S →   . SYNTAX_MASTER // SHIFT 
#if 0 
      assert(false); 
#else 
      //const int master_token_type_id = current_symbol; 
      const int master_index =   master__array[  master__nb - 1]; 
      const int rule_index   = rule_idx__array[rule_idx__nb - 1]; 
      const int rule_len     = custom_syntax_env -> custom_syntax_rules__array[rule_index][2]; 
      const int rule_pos     = rule_pos__array[rule_pos__nb - 1]; 
      const int expected_thg = rule_pos >= rule_len ? -1 : custom_syntax_env -> custom_syntax_rules__array[rule_index][3 + rule_pos]; 
      //const int node_id      = this -> custom_syntax_rules__array[rule_index][1]; 
#if 0 
      dputs_array(this -> stdlog_d, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", 
		  " - current_lalr_state: ", int_string__stack(current_lalr_state), 
		  " - current_token: ", int_string__stack(*current_token_ref), 
		  " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", 
		  " - master_index: ", int_string__stack(master_index), 
		  " - rule_index: ", int_string__stack(rule_index), 
		  " - rule_len: ", int_string__stack(rule_len), 
		  " - rule_pos: ", int_string__stack(rule_pos), 
		  " - expected_thg: ", int_string__stack(expected_thg), 
		  " - TOKEN_COUNT: ", int_string__stack(ANIME_TOKEN_TYPE_COUNT), 
		  " - SYNTAX_MASTER__TOP: ", int_string__stack(ANIME_TOKEN__SYNTAX_MASTER__TOP), 
		  " - TOKEN__SYNTAX_KEYWORD__TOP: ", int_string__stack(ANIME_TOKEN__SYNTAX_KEYWORD__TOP), 
		  " - CUSTOM_SYNTAX_NODE__BASE: ", int_string__stack(ANIME__CUSTOM_SYNTAX_NODE__BASE), 
		  " - CUSTOM_SYNTAX_NODE__TOP: ", int_string__stack(ANIME__CUSTOM_SYNTAX_NODE__TOP), 
		  " - CUSTOM_SYNTAX_RULE__TOP: ", int_string__stack(ANIME__CUSTOM_SYNTAX_RULE__TOP), 
		  "\n"); 
#endif 
      if (rule_len == 0) { 
	const int tree_type    = custom_syntax_env -> custom_syntax_trees__array[rule_index][0]; 
	const int subtrees_len = custom_syntax_env -> custom_syntax_trees__array[rule_index][1]; 
	//current_symbol = node_id; 
	if (0 == tree_type) { 
	  PUSH_OUTPUT(-1); 
	  DROP_RULE_POS(); 
	  DROP_RULE_IDX(); 
	  POP_PATH(current_lalr_state); 
	  continue; 
	}; 
	if (0 == subtrees_len) { 
	  //const int16_t new_tree = anime_syntax_filtering_chunk_env__push(this -> expr_tree_env, /*type*/tree_type); 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(*current_token_ref,-1,new_tree); // By connexity, subtree should be at the top. 
	  PUSH_OUTPUT(new_tree); 
	  DROP_RULE_POS(); 
	  DROP_RULE_IDX(); 
	  POP_PATH(current_lalr_state); 
	  current_symbol = tree_type; 
	  continue; 
	}; 
	//const int *   subtrees = &(this -> custom_syntax_trees__array[rule_index][2]); 
	int subtrees[subtrees_len]; 
	for (int i = 0; i < subtrees_len; i++) { 
	  subtrees[i] = custom_syntax_env -> custom_syntax_trees__array[rule_index][2 + i]; 
	}; 
	//const int16_t new_tree = anime_syntax_filtering_chunk_env__push_array(this -> expr_tree_env, /*type*/tree_type, subtrees_len, subtrees); 
	// RL: TODO XXX FIXME: Likely, this does not work. 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(*current_token_ref,-1,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	DROP_RULE_POS(); 
	DROP_RULE_IDX(); 
	POP_PATH(current_lalr_state); 
	continue; 
      }; 
      //if (expected_thg < 0) { 
      if (rule_pos >= rule_len) { 
	const int tree_type    = custom_syntax_env -> custom_syntax_trees__array[rule_index][0]; 
	const int subtrees_len = custom_syntax_env -> custom_syntax_trees__array[rule_index][1]; 
	if (0 == tree_type) { 
	  if (0 == subtrees_len) { 
	    PUSH_OUTPUT(-1); 
	    DROP_RULE_POS(); 
	    DROP_RULE_IDX(); 
	    POP_PATH(current_lalr_state); 
	    continue; 
	  }; 
	  assert(1 == subtrees_len); 
	  const int item_index = custom_syntax_env -> custom_syntax_trees__array[rule_index][2]; 
	  assert(item_index >= 0); 
	  assert(item_index < rule_len); 
	  int one_subtree; 
	  int the_sought_tree = -2; 
	  for (int i = 0; i < rule_len; i++) { 
	    POP_OUTPUT(one_subtree); 
	    if (rule_len - i - 1 != item_index) continue; 
	    the_sought_tree = one_subtree; 
	  }; 
	  PUSH_OUTPUT(the_sought_tree); 
	  DROP_RULE_POS(); 
	  DROP_RULE_IDX(); 
	  POP_PATH(current_lalr_state); 
	  continue; 
	}; 
	if (0 == subtrees_len) { 
	  //const int16_t new_tree = anime_syntax_filtering_chunk_env__push(this -> expr_tree_env, /*type*/tree_type); 
	  // RL: TODO XXX FIXME: Likely, this does not work. 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(*current_token_ref,-1,new_tree); // By connexity, subtree should be at the top. 
	  PUSH_OUTPUT(new_tree); 
	  DROP_RULE_POS(); 
	  DROP_RULE_IDX(); 
	  POP_PATH(current_lalr_state); 
	  continue; 
	}; 
	// RL: TODO XXX FIXME: This code works only if the indices are well-ordered. 
	int subtrees[subtrees_len]; 
	int one_subtree; 
	int j = subtrees_len - 1; 
	int item_index = custom_syntax_env -> custom_syntax_trees__array[rule_index][2 + j]; 
	for (int i = 0; i < rule_len; i++) { 
	  POP_OUTPUT(one_subtree); 
	  if (rule_len - i - 1 != item_index) continue; 
	  subtrees[j] = one_subtree; 
	  j--; 
	  item_index = custom_syntax_env -> custom_syntax_trees__array[rule_index][2 + j]; 
	}; 
	assert(j == -1); 
	//const int16_t new_tree = anime_syntax_filtering_chunk_env__push_array(this -> expr_tree_env, /*type*/tree_type, subtrees_len, subtrees); 
	// RL: TODO XXX FIXME: Likely, this does not work. 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(*current_token_ref,-1,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	DROP_RULE_POS(); 
	DROP_RULE_IDX(); 
	POP_PATH(current_lalr_state); 
	continue; 
      }; 
      if (0 == expected_thg) { 
	PUSH_PATH(17); 
	//DROP_RULE_POS(); 
	//PUSH_RULE_POS(rule_pos+1); 
	rule_pos__array[rule_pos__nb - 1]++; 
	current_lalr_state = 0; // RL: Right now, go there (we have a sub-tree S to recognize) 
	continue; 
      }; 
      if (current_symbol < 0) { current_symbol = get_next_token_type(); }; 
      if (expected_thg < ANIME_TOKEN__SYNTAX_KEYWORD__TOP) { 
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, expected_thg); 
	//DROP_RULE_POS(); 
	//PUSH_RULE_POS(rule_pos+1); 
	//const int16_t new_tree = anime_syntax_filtering_chunk_env__push1(this -> expr_tree_env, current_symbol, *current_token_ref); 
	//const int16_t new_tree = *current_token_ref; 
	// RL: TODO XXX FIXME: Likely, this does not work. 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(*current_token_ref,-1,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	rule_pos__array[rule_pos__nb - 1]++; 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 
      if (expected_thg >= ANIME__CUSTOM_SYNTAX_RULE__BASE) { 
	assert(false); 
	PUSH_PATH(17); 
	PUSH_RULE_IDX(expected_thg); 
	PUSH_RULE_POS(0); 
	continue; 
      }; 
      if (expected_thg >= ANIME__CUSTOM_SYNTAX_NODE__BASE) { 
#if 0 
	dputs_array(this -> stdlog_d, "HHHHHHHH---------------------------------------------------------------------------------------------------ERE\n"); 
#endif 
	// RL: Here, we have to code the union. 
	// RL: What would be great would be to code back-tracking. 
	//     It would not be that awful are rules are LL(1)-like, it's just more convenient to write the same rule a second time with a minor variant 
	//     than to factor out ourself the 'premier' set. 
	// RL: Obviously a better approach would be to code all the alived rules; and filter them while reading. 
	// RL: For the moment, it will be the strong-LL(1) approach, not very user-friendly, but which works and with a low complexity. 
	const int matching_rule_id = anime__custom_syntax__rule_lookup(custom_syntax_env, /*node_id*/expected_thg, /*token_i*/current_symbol); 
	if (matching_rule_id < 0) { SYNTAX__EXPECTING_NOT_THIS_TOKEN(current_symbol); }; 
	PUSH_PATH(17); 
	PUSH_RULE_IDX(matching_rule_id - ANIME__CUSTOM_SYNTAX_RULE__BASE); 
	rule_pos__array[rule_pos__nb - 1]++; 
	PUSH_RULE_POS(0); 
	continue; 
      }; 
	
	
      assert(false); 
	
      PUSH_PATH(17); // RL: Where we will go after having reduced. 
      current_lalr_state = 17; // RL: Right now, go there (iterating over what we have to recognize) 
      continue; 
#endif 
    }; 
	
    
    
    
    assert(false); 
  }; // for (;;) 

  
  
  
  
  // HERE WE ARE! 
#if DEBUG_PARSER >= 3 
  dputs_array(this -> stdlog_d, "output_token_tree_stack__nb       = ", int_string__stack(output_token_tree_stack__nb      ), "\n" ); 
  dputs_array(this -> stdlog_d, "output_token_tree_stack__array[0] = ", int_string__stack(output_token_tree_stack__array[0]), "\n" ); 
  dputs_array(this -> stdlog_d, "output_token_tree_stack__arity[0] = ", int_string__stack(output_token_tree_stack__arity[0]), "\n" ); 
#endif 

  DROP_OUTPUT(); 
  
  // Now, we just have to: 
  //  - copy the content of 'output_token_tree_stack' into 'syntax_filtering__output_postfix_buffer' 
  //  - change the token type of unary plus and unary minus 
  // 
  if (ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_SIZE < output_token_tree_stack__nb) { goto error__output_postfix_buffer_too_small; }; 
  for (int i = 0; i < output_token_tree_stack__nb; i++) { 
    this -> syntax_filtering__output_postfix_buffer__array[i] = output_token_tree_stack__array[i]; 
  }; 
  this -> syntax_filtering__output_postfix_buffer__nb = output_token_tree_stack__nb; 
  this -> syntax_filtering__output_postfix_buffer__i = 0; 
  for (int i = 0; i < output_token_tree_stack__nb; i++) { 
    if (1 != output_token_tree_stack__arity[i]) continue; 
    const int token_i    = output_token_tree_stack__array[i];
    const int token_type = anime_token__get_type(token_env, token_i); 
    if (ANIME_TOKEN_IPLUS  == token_type) { anime_token__syntax_filtering__adjust_type(token_env, token_i, ANIME_TOKEN_IPLUS_UNAIRE ); continue; }; 
    if (ANIME_TOKEN_RPLUS  == token_type) { anime_token__syntax_filtering__adjust_type(token_env, token_i, ANIME_TOKEN_RPLUS_UNAIRE ); continue; }; 
    if (ANIME_TOKEN_IMOINS == token_type) { anime_token__syntax_filtering__adjust_type(token_env, token_i, ANIME_TOKEN_IMOINS_UNAIRE); continue; }; 
    if (ANIME_TOKEN_RMOINS == token_type) { anime_token__syntax_filtering__adjust_type(token_env, token_i, ANIME_TOKEN_RMOINS_UNAIRE); continue; }; 
    continue; 
  };
  
  
  
  return ANIME__OK; 


 error__output_postfix_buffer_too_small: { 
    this -> error_id = ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_TOO_SMALL; 
    snprintf(this -> error_str, ANIME_SYNTAX_FILTERING__ERROR_BUFFER_SIZE, "Output postfix buffer too small (current size: %d — required: %d", ANIME__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_SIZE, output_token_tree_stack__nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
  
}; 










