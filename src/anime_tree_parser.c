#include "anime_global.h"
#include "anime.h"
#include "anime_token_type.h"
#include "anime_token.h"
#include "anime_tree.h"
#include "anime_tree_parser.h"

#define DEBUG_PARSER 1 

enum { 
  ANIME_PARSER__AUTOMATON_STATE__NULL, 
  ANIME_PARSER__AUTOMATON_STATE__START, 
  section_list, 
  section_one, 
  property_list, 
  property_one, 
  property_value, 
  property_value_braced, 
  expression, 
  expr, 
  ANIME_PARSER__AUTOMATON_STATE__COUNT 
}; 

static const char * anime_parser_automaton_state__cstr[] = {
  "AUTOMATON_STATE__NULL", 
  "AUTOMATON_STATE__START", 
  "section_list", 
  "section_one", 
  "property_list", 
  "property_one", 
  "property_value", 
  "property_value_braced", 
  "expression", 
  "expr", 
  NULL 
};

enum { anime_parser_automaton_state__size = ARRAY_SIZE(anime_parser_automaton_state__cstr) }; 
static void assert_compile__dkushdsuf2387645kjhsdfr(void) {
  ASSERT_COMPILE(ANIME_PARSER__AUTOMATON_STATE__COUNT <= INT8_MAX); //127); // 256 // INT8_MAX 
  ASSERT_COMPILE(anime_parser_automaton_state__size == ANIME_PARSER__AUTOMATON_STATE__COUNT + 1); 
}; 

const char * anime_parser_automaton_state__get_cstr(const int automaton_state) { 
  return anime_parser_automaton_state__cstr[automaton_state]; 
}; 


const int anime_parser__postfix_operators[]   = { ANIME_TOKEN_INC, ANIME_TOKEN_DEC }; 
const int anime_parser__postfix_operators__nb = ARRAY_SIZE(anime_parser__postfix_operators); 








enum { ANIME_PARSER__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX =  12 }; 

enum { ANIME_PARSER__SYMBOL__BASE = ANIME_TOKEN__SYNTAX_KEYWORD__TOP - 1 }; 
 
enum { ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE = ANIME_PARSER__SYMBOL__BASE }; 
enum { ANIME_PARSER__CUSTOM_SYNTAX_NODE__SIZE = 31 }; 
enum { ANIME_PARSER__CUSTOM_SYNTAX_NODE__TOP  = ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE + ANIME_PARSER__CUSTOM_SYNTAX_NODE__SIZE }; 

enum { ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE = ANIME_PARSER__CUSTOM_SYNTAX_NODE__TOP }; 
enum { ANIME_PARSER__CUSTOM_SYNTAX_RULE__SIZE = 33 }; //126 }; 
enum { ANIME_PARSER__CUSTOM_SYNTAX_RULE__TOP  = ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE + ANIME_PARSER__CUSTOM_SYNTAX_RULE__SIZE }; 


enum { anime_parser_env__memory__array_size = (1 << 13) }; 

struct anime_parser_env_t {
  uint16_t memory__array_nb;   // RL: Top of the array. 
  char     memory__array[anime_parser_env__memory__array_size]; 
  
  anime_tree_env_t * anime_tree_env; 
  
  // CUSTOM SYNTAX 
  uint8_t custom_syntax_node__nb; 
  uint8_t custom_syntax_rules__array[ANIME_PARSER__CUSTOM_SYNTAX_RULE__SIZE][3 + ANIME_PARSER__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX]; 
  uint8_t custom_syntax_rules__nb; 
  uint8_t custom_syntax_trees__nb; 
  uint8_t custom_syntax_trees__array[ANIME_PARSER__CUSTOM_SYNTAX_RULE__SIZE][2 + ANIME_PARSER__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX]; 
  uint8_t custom_syntax_root__array[ANIME_TOKEN__SYNTAX_MASTER__SIZE]; 
}; 
const        int32_t anime_parser_env__sizeof                  = sizeof(anime_parser_env_t); 
enum {               anime_parser_env__sizeof__compiler_const  = sizeof(anime_parser_env_t) }; 

anime_parser_env_t * anime_parser_env__make(const int stdlog_d) { 
  MALLOC_BZERO(anime_parser_env_t,this); 
  
  int buffer_used_bytes; 
  int buffer_size = sizeof(this -> memory__array); 
  char * buffer = this -> memory__array; 

  { 
    const int ms = anime_tree_env__sizeof_alloc(-1); 
    this -> anime_tree_env = anime_tree_env__make_b(buffer_size, buffer, &buffer_used_bytes, ms, stdlog_d); 
    buffer += buffer_used_bytes; 
    buffer_size -= buffer_used_bytes; 
    this -> memory__array_nb += buffer_used_bytes; 
  }; 
  
  assert(0 <= buffer_size); 
  
  return this; 
}; 
 
void anime_parser_env__delete(anime_parser_env_t * this) { 
  free(this); 
}; 

const anime_tree_env_t * anime_parser_env__get_tree_env(const anime_parser_env_t * this) { 
  if (NULL == this) { return NULL; }; 
  return this -> anime_tree_env; // Beware! This belongs to parser_env, as it allocated in "this -> memory__array". 
}; 




// *** CUSTOM SYNTAX *** 

extern int anime_parser__custom_syntax__node_push(anime_parser_env_t * this) { 
  assert(this -> custom_syntax_node__nb < ANIME_PARSER__CUSTOM_SYNTAX_NODE__SIZE); 
  const int node_id = ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE + this -> custom_syntax_node__nb; 
  this -> custom_syntax_node__nb ++; 
  return node_id; 
}; 

int anime_parser__custom_syntax__node_count(const anime_parser_env_t * this) { 
  return this -> custom_syntax_node__nb; 
}; 

int anime_parser__custom_syntax__rule_push_array_nb(anime_parser_env_t * this, const int node_id, const int right_len, const int right_items[]) { 
  assert(this -> custom_syntax_rules__nb < ANIME_PARSER__CUSTOM_SYNTAX_RULE__SIZE); 
  const int index   = this -> custom_syntax_rules__nb; 
  const int rule_id = ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE + index; 
  this -> custom_syntax_rules__nb ++; 
  
  assert(right_len <= ANIME_PARSER__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX);  

  // rule_id, left_symbol, right_length, right_symbols... 
  //this -> custom_syntax_rules__array[index] = (const int8_t[]) { rule_id, node_id, right_len }; 
  this -> custom_syntax_rules__array[index][0] = rule_id; 
  this -> custom_syntax_rules__array[index][1] = node_id; 
  this -> custom_syntax_rules__array[index][2] = right_len; 
  for (int i = 0; i < right_len; i++) { 
    this -> custom_syntax_rules__array[index][3 + i] = right_items[i]; 
  }; 
  //[3 + ANIME_PARSER__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX + 1]; 
  
  return rule_id; 
}; 
 
int anime_parser__custom_syntax__rule_count(const anime_parser_env_t * this) { 
  return this -> custom_syntax_rules__nb; 
}; 

int anime_parser__custom_syntax__rule_lookup(const anime_parser_env_t * this, const int node_id, const int token_i) { 
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


extern void anime_parser__custom_syntax__master_root_set(anime_parser_env_t * this, const int token_master_type_id, const int rule_id) { 
  const int index = token_master_type_id - ANIME_TOKEN__SYNTAX_MASTER__BASE; 
  this -> custom_syntax_root__array[index] = rule_id - ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE; 
}; 

extern void anime_parser__custom_syntax__tree_set__array_nb(anime_parser_env_t * this, const int rule_id, const int tree_type, const int items_len, const int items_indices[]) { 
  assert(rule_id >= ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE); 
  assert(rule_id <  ANIME_PARSER__CUSTOM_SYNTAX_RULE__TOP ); 
  const int index = rule_id - ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE; 
  
  assert(items_len <= ANIME_PARSER__CUSTOM_SYNTAX_RULE__RIGHT_LENGTH_MAX);  
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
  //[3 + ANIME_PARSER__CUSTOM_SYNTAX_TREE__RIGHT_LENGTH_MAX + 1]; 
}; 
 
int anime_parser__custom_syntax__tree_count(const anime_parser_env_t * this) { 
  return this -> custom_syntax_trees__nb; 
}; 











// *** PARSING *** 


enum { decl__arg_ident_list__size = 15 };  






static int anime_parser__automaton__get_next_token(const anime_token_env_t * token_env, int * current_token_ref) { 
  *current_token_ref += 1; 
  ASSERT_DEBUG_ABORT_IF_TRUE(*current_token_ref < 0) { return ANIME_TOKEN_NULL; }; 
  //if (*current_token_ref >= token_env -> nb) { return ANIME_TOKEN_EOF; }; 
  if (*current_token_ref >= anime_token__get_count(token_env)) { return ANIME_TOKEN_EOF; }; 
  //return token_env -> type[*current_token_ref]; 
  return anime_token__get_type(token_env, *current_token_ref); 
}; 


#define CASE_GOTO(id) case id: goto glue(label__state,id); break;  
#define LABEL_STATE(id) glue(label__state,id) 

//int yyanimelex(void);
//#define yyanimelex()         anime_parser__automaton__get_next_token(token_env, &current_token)
#define yyanimelex()           anime_parser__automaton__get_next_token(token_env, current_token_ref) 
#define get_current_token_type() (*current_token_ref < 0 ? ANIME_TOKEN_NULL : *current_token_ref >= anime_token__get_count(token_env) ? ANIME_TOKEN_EOF : anime_token__get_type(token_env, *current_token_ref)) 
#if DEBUG_PARSER >= 2 
#define get_next_token_type()    (dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">", ":<get_next_token>", "\n"), anime_parser__automaton__get_next_token(token_env, current_token_ref)) 
#else 
#define get_next_token_type()    anime_parser__automaton__get_next_token(token_env, current_token_ref) 
#endif 

      




// *** PARSER *** 

#define EXCEPTION__RAISE__(msg)						\
  strlcpy(exception_data + 4 + sizeof(sigjmp_buf), msg, *((int16_t*)exception_data) - 4 - sizeof(sigjmp_buf)); \
  siglongjmp(*((sigjmp_buf *) (exception_data + 4)), -1); 

#define EXCEPTION__RAISE(...) {						\
  const char * msg = strconcat__stack(__VA_ARGS__);			\
  strlcpy(exception_data + 4 + sizeof(sigjmp_buf), msg, *((int16_t*)exception_data) - 4 - sizeof(sigjmp_buf)); \
  siglongjmp(*((sigjmp_buf *) (exception_data + 4)), -1);		\
  }; 
 
#define SYNTAX__EXPECTING_THIS_TOKEN__OLD(given_token_type,expected_token_type) { \
    if (given_token_type != expected_token_type) {			\
      EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Unexpected token: ", anime_token__type_get_cstr(given_token_type), "(", int_string__stack(given_token_type), ") -- Was expecting token: ", anime_token__type_get_cstr(expected_token_type), "(", int_string__stack(expected_token_type), ")"); \
    };									\
  }; 

#if DEBUG_PARSER >= 1 
#define SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION "{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "] }: ",
#else 
#define SYNTAX__EXPECTING_THIS_TOKEN__SRC_LOCATION 
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



//       const char * msg_array[msg_array_nb] = { __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Unexpected token: ", anime_token__type_get_cstr(given_token_type), "(", int_string__stack(given_token_type), ") -- Was expecting of these tokens:" }; 


#define SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS__OLD(given_token_type, ...) {	\
    if (not(int_member_huh(given_token_type, __VA_ARGS__))) {		\
      const int expected_tokens_array[] = (const int []) { __VA_ARGS__ }; \
      const int expected_tokens_nb      = ARRAY_SIZE(((const int []) { __VA_ARGS__ })); \
      const char * prefix_msg_array[] = { __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Unexpected token: ", anime_token__type_get_cstr(given_token_type), "(", int_string__stack(given_token_type), ") -- Was expecting one of these ", int_string__stack(expected_tokens_nb), " tokens: " }; \
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


#define SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(given_token_type, ...) {	\
    if (not(int_member_huh(given_token_type, __VA_ARGS__))) {		\
      const int expected_tokens_array[] = { __VA_ARGS__ }; \
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


void f(void) { 
 please_reduce2: 
  return;
}; 

static int anime_parser__automaton__aux(char * exception_data, anime_parser_env_t * this, const anime_token_env_t * token_env, const int state, int * current_token_ref, int *retval1_ref) { 
  int16_t expr_tree = -1; 
  int16_t type_expr_tree = -1; 
  //int current_token = -1; 

#if DEBUG_PARSER >= 2 
  dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], " - current_token: ", int_string__stack(*current_token_ref), "]\n"); 
#endif 

  switch (state) { 
    CASE_GOTO(ANIME_PARSER__AUTOMATON_STATE__START); 
    CASE_GOTO(section_list); 
    CASE_GOTO(section_one); 
    CASE_GOTO(property_list); 
    CASE_GOTO(property_one); 
    CASE_GOTO(property_value); 
    CASE_GOTO(property_value_braced); 
    CASE_GOTO(expression); 
    CASE_GOTO(expr); 
#if 0 
#endif  
  }; 
  assert(false); 
  
  
 LABEL_STATE(ANIME_PARSER__AUTOMATON_STATE__START): { 
    int next_token; 
    next_token = get_next_token_type(); 
    anime_parser__automaton__aux(exception_data, this, token_env, section_list, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_EOF); 
    return 0; 
  }; 
  
  
  LABEL_STATE(section_list): { 
    int next_token; 
    for (;;) { 
      next_token = get_current_token_type(); 
      while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
#if DEBUG_PARSER >= 10 
      dputs_array(stderr_d, "NEXT TOP-LEVEL DECL: current_token = ", int_string__stack(*current_token_ref), " - token_type = ", anime_token__type_get_cstr(next_token), "(", int_string__stack(next_token), ")", "\n"); 
#endif 
      if (-1 == next_token) { next_token = get_next_token_type(); }; 
      switch (next_token) { 
      case ANIME_TOKEN_STRING_C : 
      case ANIME_TOKEN_STRING_P : 
      case ANIME_TOKEN_IDENT    : anime_parser__automaton__aux(exception_data, this, token_env, section_one, current_token_ref, retval1_ref); continue; 
      case ANIME_TOKEN_EOF      : return ANIME_TOKEN_EOF; 
      default: { 
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_IDENT, ANIME_TOKEN_STRING_P, ANIME_TOKEN_STRING_C, ANIME_TOKEN_EOF); 
	return -1; 
      }; break; 
      }; 
    }; 
    assert(false); 
    return 0; 
  }; 

  LABEL_STATE(section_one): { 
    int next_token; 
    //next_token = get_current_token_type(); 
    const int section_token = *current_token_ref; 
    next_token = get_next_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OPENBRACE); 
    const int openbrace_token = *current_token_ref; 
    next_token = get_next_token_type(); // Moving forward. 
    const int_anime_tree_t section_tree = anime_tree__open(/*anime_tree_env_t * this*/this -> anime_tree_env, /*const uint8_t tree_type*/ANIME__TREE_TYPE__SECTION); 
    anime_tree__push_uint16(this -> anime_tree_env, section_token); 
    anime_tree__push_uint16(this -> anime_tree_env, openbrace_token); 
    const int_anime_tree_t close_brace_address = anime_tree__get_top_address(this -> anime_tree_env); 
    anime_tree__push_uint16(this -> anime_tree_env, ~0); 
    const int_anime_tree_t first_child_address = anime_tree__get_top_address(this -> anime_tree_env); 
    anime_parser__automaton__aux(exception_data, this, token_env, property_list, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEBRACE); 
    const int closebrace_token = *current_token_ref; 
    anime_tree__write_uint16(this -> anime_tree_env, close_brace_address, closebrace_token); 
    anime_tree__close(this -> anime_tree_env, section_tree, first_child_address); 
    next_token = get_next_token_type(); 
    return 0; 
  }; 

  LABEL_STATE(property_list): { 
    int next_token; 
    for (;;) { 
      next_token = get_current_token_type(); 
      while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
#if DEBUG_PARSER >= 10 
      dputs_array(stderr_d, "[property_list]: current_token = ", int_string__stack(*current_token_ref), " - token_type = ", anime_token__type_get_cstr(next_token), "(", int_string__stack(next_token), ")", "\n"); 
#endif 
      if (-1 == next_token) { next_token = get_next_token_type(); }; 
      switch (next_token) { 
      case ANIME_TOKEN_CLOSEBRACE: return 0; break; 
      case ANIME_TOKEN_STRING_C  : 
      case ANIME_TOKEN_STRING_P  : 
      case ANIME_TOKEN_IDENT     : anime_parser__automaton__aux(exception_data, this, token_env, property_one             , current_token_ref, retval1_ref); continue; 
      default: { 
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_IDENT, ANIME_TOKEN_STRING_P, ANIME_TOKEN_STRING_C, ANIME_TOKEN_CLOSEBRACE); 
	return -1; 
      }; break; 
      }; 
    }; 
    assert(false); 
    return 0; 
  }; 

  LABEL_STATE(property_one): { 
    int next_token; 
    enum { id_max = 12 }; 
    int id_type[id_max]; 
    int id_value[id_max]; 
    int id_nb = 0; 
    next_token = get_current_token_type(); 
    { int break_for = false; for (;!break_for;) { 
      switch (next_token) { 
      case ANIME_TOKEN_AFFECTATION: break_for = true; break;  
      case ANIME_TOKEN_OPENBRACE  : break_for = true; break;  
      case ANIME_TOKEN_STRING_C   : 
      case ANIME_TOKEN_STRING_P   : 
      case ANIME_TOKEN_IDENT      : SYNTAX__EXCEPTION__ASSERT(id_nb < id_max,"Too many idents"); id_type[id_nb] = next_token; id_value[id_nb] = *current_token_ref; id_nb++; next_token = get_next_token_type(); continue; 
      default: { 
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_IDENT, ANIME_TOKEN_STRING_P, ANIME_TOKEN_STRING_C); 
	return -1; 
      }; break; 
      }; 
    }; };  
#if DEBUG_PARSER >= 50 
      dputs_array(stderr_d, "id_nb = ", int_string__stack(id_nb), "\n"); 
#endif 
    SYNTAX__EXCEPTION__ASSERT(id_nb > 0,"Not enough idents"); 
    if (ANIME_TOKEN_AFFECTATION == next_token) { 
#if DEBUG_PARSER >= 10 
      dputs_array(stderr_d, "(ANIME_TOKEN_AFFECTATION == next_token): current_token = ", int_string__stack(*current_token_ref), " - token_type = ", anime_token__type_get_cstr(next_token), "(", int_string__stack(next_token), ")", "\n"); 
#endif 
      const int assign_token = *current_token_ref; 
      const int_anime_tree_t assign_tree = anime_tree__open(/*anime_tree_env_t * this*/this -> anime_tree_env, /*const uint8_t tree_type*/ANIME__TREE_TYPE__PROPERTY); 
      for (int i = 0; i < id_nb; i++) { 
	anime_tree__push_uint16(this -> anime_tree_env, id_value[i]); 
      }; 
      anime_tree__push_uint16(this -> anime_tree_env, assign_token); 
      const int_anime_tree_t first_child_address = anime_tree__get_top_address(this -> anime_tree_env); 
      next_token = get_next_token_type(); // Moving forward. 
      anime_parser__automaton__aux(exception_data, this, token_env, property_value, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      anime_tree__close(this -> anime_tree_env, assign_tree, first_child_address); 
      next_token = get_next_token_type(); 
    } 
    else if (ANIME_TOKEN_OPENBRACE == next_token) { 
#if DEBUG_PARSER >= 10 
      dputs_array(stderr_d, "(ANIME_TOKEN_OPENBRACE == next_token): current_token = ", int_string__stack(*current_token_ref), " - token_type = ", anime_token__type_get_cstr(next_token), "(", int_string__stack(next_token), ")", "\n"); 
#endif 
      const int openbrace_token = *current_token_ref; 
      const int_anime_tree_t subsection_tree = anime_tree__open(/*anime_tree_env_t * this*/this -> anime_tree_env, /*const uint8_t tree_type*/ANIME__TREE_TYPE__SUBSECTION); 
      for (int i = 0; i < id_nb; i++) { 
	anime_tree__push_uint16(this -> anime_tree_env, id_value[i]); 
      }; 
      anime_tree__push_uint16(this -> anime_tree_env, openbrace_token); 
      const int_anime_tree_t close_brace_address = anime_tree__get_top_address(this -> anime_tree_env); 
      anime_tree__push_uint16(this -> anime_tree_env, ~0); 
      const int_anime_tree_t first_child_address = anime_tree__get_top_address(this -> anime_tree_env); 
      next_token = get_next_token_type(); // Moving forward. 
      anime_parser__automaton__aux(exception_data, this, token_env, property_list, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEBRACE); 
      const int closebrace_token = *current_token_ref; 
      anime_tree__write_uint16(this -> anime_tree_env, close_brace_address, closebrace_token); 
      anime_tree__close(this -> anime_tree_env, subsection_tree, first_child_address); 
      next_token = get_next_token_type(); 
    } 
    else { 
      SYNTAX__EXCEPTION__ASSERT(false,"Something got wrong."); 
    }; 
    
    return 0; 
  }; 

  LABEL_STATE(property_value): { 
    int next_token; 
    next_token = get_current_token_type(); 
    for (;;) { // We can have a a list of values, using commas. 
      if (ANIME_TOKEN_PTVIRG    == next_token) { return 0; }; 
      if (ANIME_TOKEN_OPENBRACE == next_token) { 
	anime_parser__automaton__aux(exception_data, this, token_env, property_value_braced, current_token_ref, retval1_ref); 
      } 
      else { 
	anime_parser__automaton__aux(exception_data, this, token_env, expression, current_token_ref, retval1_ref); 
      }; 
      next_token = get_current_token_type(); 
      if (ANIME_TOKEN_VIRGULE == next_token) { next_token = get_next_token_type(); continue; }; 
      return 0; 
    }; 
    return 0; 
  }; 

  LABEL_STATE(property_value_braced): { 
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OPENBRACE); 
    const int openbrace_token = *current_token_ref; 
    const int_anime_tree_t property_value_braced_tree = anime_tree__open(/*anime_tree_env_t * this*/this -> anime_tree_env, /*const uint8_t tree_type*/ANIME__TREE_TYPE__PROPERTY_BRACED); 
    anime_tree__push_uint16(this -> anime_tree_env, openbrace_token); 
    const int_anime_tree_t close_brace_address = anime_tree__get_top_address(this -> anime_tree_env); 
    anime_tree__push_uint16(this -> anime_tree_env, ~0); 
    const int_anime_tree_t first_child_address = anime_tree__get_top_address(this -> anime_tree_env); 
    next_token = get_next_token_type(); // Moving forward. 
    anime_parser__automaton__aux(exception_data, this, token_env, property_list, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEBRACE); 
    const int closebrace_token = *current_token_ref; 
    anime_tree__write_uint16(this -> anime_tree_env, close_brace_address, closebrace_token); 
    anime_tree__close(this -> anime_tree_env, property_value_braced_tree, first_child_address); 
    next_token = get_next_token_type(); 
    return 0; 
  }; 

  LABEL_STATE(expression): { 
    expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
    return expr_tree; 
  }; 




 LABEL_STATE(expr): { 
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
    int8_t current_lalr_state = 0; 
    int16_t current_symbol = get_current_token_type(); 
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
#define DROP_OPERATOR(x) { assert(operator__nb > 0); operator__nb--; }; 
#define DROP_ARITY(x)    { assert(   arity__nb > 0);    arity__nb--; }; 
#define DROP_MASTER(x)   { assert(  master__nb > 0);   master__nb--; }; 
#define DROP_RULE_IDX(x) { assert(rule_idx__nb > 0); rule_idx__nb--; }; 
#define DROP_RULE_POS(x) { assert(rule_pos__nb > 0); rule_pos__nb--; }; 
#define INC_ARITY()      { assert(   arity__nb > 0); arity__array[arity__nb]++; }; 
#define OUTPUT_TREE_PUSH(token_root,arity,new_tree) { assert(output_token_tree_stack__nb < output_token_tree_stack__size); output_token_tree_stack__arity[output_token_tree_stack__nb] = (arity); output_token_tree_stack__array[output_token_tree_stack__nb] = (token_root); (new_tree) = output_token_tree_stack__nb; output_token_tree_stack__nb++; }; 
#define EXPR_CASE_GOTO(id) case id: goto glue(label__expr_state,id); break;  
#define EXPR_LABEL_STATE(id) glue(label__expr_state,id) 
    PUSH_PATH(11); 
    for (;;) { 
#if DEBUG_PARSER >= 2
  dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", " - current_lalr_state: ", int_string__stack(current_lalr_state), " - current_token: ", int_string__stack(*current_token_ref), " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", "\n"); 
#endif 
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(stderr__fileno, int_string__stack(path__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
#endif 
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "\t", "OUTPUTS: [ "); for (int i = 0; i < outputs__nb; i++) { dputs_array(stderr__fileno, int_string__stack(outputs__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
#endif 
      switch (current_lalr_state) { 
	EXPR_CASE_GOTO(0);  // RL: S → . S   _   S | ... 
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
      assert(false); 
      
    EXPR_LABEL_STATE(0): { 
	//if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
	//if (int_member_huh(current_symbol, ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL)) { 
	if (int_member_huh(current_symbol, ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL, ANIME_TOKEN_NULL_PTR, ANIME_TOKEN_IDENT)) { 
	  //RL: Constant value. 
	  //const int16_t new_tree = anime_parser_chunk_env__push1(this -> expr_tree_env, current_symbol, *current_token_ref); 
	  //const int16_t new_tree = *current_token_ref; 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(*current_token_ref,/*arity*/~0,new_tree); 
	  
	  PUSH_OUTPUT(new_tree); 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 1; // goto 
	  continue; 
	}; 
	if (int_member_huh(current_symbol, ANIME_TOKEN_LOGICAL_NOT, ANIME_TOKEN_IPLUS, ANIME_TOKEN_IMOINS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_RMOINS)) { 
	  // RL: Prefix unary operator. 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(1); 
	  PUSH_PATH(1); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(6); // RL: Where we will go when the sub expression will be reduced. 
	  current_lalr_state = 0; // RL: Right now, go to there. 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	  PUSH_PATH(1); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(7); // RL: Where we will go when the sub expression will be reduced. 
	  current_lalr_state = 0; // RL: Right now, go to there. 
	  current_symbol = get_next_token_type(); 
	  continue;
	}; 
#if 0 
	if (ANIME_TOKEN_IDENT == current_symbol) { 
	  // RL: Here, we have two possibilities: (i) an ident evaluation; or (ii) a function call. So we do a LA (look-ahead) to choose. 
	  // RL: But, first, we gonna need the ident value anyway. 
	  const int16_t new_tree = anime_expr_tree__push0(this -> expr_tree_env, current_symbol, *current_token_ref); 
	  PUSH_OUTPUT(new_tree); 
	  current_symbol = get_next_token_type(); 
	  if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	    // RL: That's a function call. 
#if 0 
	    int ident_subtree; 
	    POP_OUTPUT(ident_subtree); 
	    const int16_t new_tree = anime_expr_tree__push1(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, -1, ident_subtree); 
	    PUSH_OUTPUT(new_subtree); 
#endif 
	    PUSH_PATH(1); // RL: Where we will go back after having built the tree. 
	    //current_symbol = -1; 
	    current_lalr_state = 8; 
	    continue;
	  }; 
	  
	  // RL: That's an ident evaluation. 
	  { 
	    //PUSH_PATH(current_lalr_state); 
	    //PUSH_PATH(1); 
	    PUSH_OUTPUT(new_tree); 
	    current_symbol = get_current_token_type(); // -1; 
	    current_lalr_state = 1; 
	    continue; 
	  }; 
 
	  assert(false); 
	}; 
#endif 
	
	if (ANIME_TOKEN_LAMBDA == current_symbol) { 
#if 1 
	  SYNTAX__EXCEPTION__ASSERT(false,"Lambda expression not implemented."); 
#else  
	  const int lambda_decl_expr = anime_parser__automaton__aux(exception_data, this, token_env, expr_lambda, current_token_ref, retval1_ref);
	  current_symbol = get_current_token_type(); ; 
	  //const int16_t new_tree = anime_expr_tree__push0(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__LAMBDA, lambda_decl); 
	  const int16_t new_tree = lambda_decl_expr; 
	  PUSH_OUTPUT(new_tree); 
	  current_lalr_state = 1; 
	  continue; 
#endif 
	}; 

	if (ANIME_TOKEN__SYNTAX_MASTER__BASE <= current_symbol && current_symbol < ANIME_TOKEN__SYNTAX_MASTER__TOP) { 
	  PUSH_PATH(1); // RL: Where we will go after having reduced the custom syntax. 
	  current_lalr_state = 16; // RL: Right now, go to there. 
	  continue;
	}; 
	
	
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL, ANIME_TOKEN_IDENT, ANIME_TOKEN_LOGICAL_NOT, ANIME_TOKEN_IPLUS, ANIME_TOKEN_IMOINS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_RMOINS, ANIME_TOKEN_OPENPAR, ANIME_TOKEN_LAMBDA, ANIME_TOKEN_SYNTAX_MASTER); 
	
	// RL: TODO XXX FIXME: Do we need to here have an 'S' case? 
	
	dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", " - current_lalr_state: ", int_string__stack(current_lalr_state), " - current_token: ", int_string__stack(*current_token_ref), " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", "\n"); 
	dputs_array(stderr__fileno, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(stderr__fileno, int_string__stack(path__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
	assert(false); 
      };  
      
      
      
      
      
      
    EXPR_LABEL_STATE(1): { 
	// RL: We have read one expression. Now we will read the operator applied to that left expression. 
	// RL: We try to order them by priority. 
	// RL: TODO XXX FIXME: Do we need a priority stack? 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 

#if 0 	// RL: That could be a quick end. 
	//if (ANIME_TOKEN_EOF == current_symbol) { 
	if (ANIME_TOKEN_PTVIRG == current_symbol) { 
	  // RL: Nothing to be read left. 
	  // RL: We just an 'S' expression; so that looks good. 
	  //     However, we might be nested in other expression, expecting something to be read. 
	  //assert(1 == outputs__nb); 
	  //POP_OUTPUT(expr_tree); 
	  //current_symbol = -1; 
	  //current_lalr_state = 11; 
	  POP_PATH(current_lalr_state); 
	  continue; 
	}; 
#endif 
	
	const int infix_binary_operator_huh = int_member_huh(current_symbol, ANIME_TOKEN_AFFECTATION, ANIME_TOKEN_AFFECTATION_SIMPLE, ANIME_TOKEN_AFFECTATION_IADD, ANIME_TOKEN_AFFECTATION_RADD, ANIME_TOKEN_AFFECTATION_ISUB, ANIME_TOKEN_AFFECTATION_RSUB, ANIME_TOKEN_AFFECTATION_IMULT, ANIME_TOKEN_AFFECTATION_RMULT, ANIME_TOKEN_AFFECTATION_IDIV, ANIME_TOKEN_AFFECTATION_RDIV, ANIME_TOKEN_AFFECTATION_IMOD, ANIME_TOKEN_AFFECTATION_L_AND, ANIME_TOKEN_AFFECTATION_L_OR, ANIME_TOKEN_AFFECTATION_L_XOR, ANIME_TOKEN_AFFECTATION_B_AND, ANIME_TOKEN_AFFECTATION_B_OR, ANIME_TOKEN_AFFECTATION_B_XOR, ANIME_TOKEN_AFFECTATION_B_RSHIFT, ANIME_TOKEN_AFFECTATION_B_LSHIFT, ANIME_TOKEN_LOGICAL_OR, ANIME_TOKEN_LOGICAL_AND, ANIME_TOKEN_LOGICAL_XOR, ANIME_TOKEN_BITWISE_OR, ANIME_TOKEN_BITWISE_AND, ANIME_TOKEN_BITWISE_XOR, ANIME_TOKEN_BITWISE_SHIFT_LEFT, ANIME_TOKEN_BITWISE_SHIFT_RIGHT, ANIME_TOKEN_EQUAL, ANIME_TOKEN_DIFF, ANIME_TOKEN_INF, ANIME_TOKEN_SUP, ANIME_TOKEN_INFEQ, ANIME_TOKEN_SUPEQ, ANIME_TOKEN_IPLUS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_IMINUS, ANIME_TOKEN_RMINUS, ANIME_TOKEN_IMULT, ANIME_TOKEN_RMULT, ANIME_TOKEN_IDIV, ANIME_TOKEN_RDIV, ANIME_TOKEN_POINT, ANIME_TOKEN_FLECHE); 
	
	// RL: The default behavior is to shift. 
	//     However, this is an undesirable behavior to handle priorities: 
	//        " 1 * 2 + 3 " 
	//     In such case, we should not shift, but reduce. 
	//     In order to implement that, we have just to compare priorities: 
	//       if priority(current_operator) < priority(previous_operator) then reduce else shift 
	//     
	if (infix_binary_operator_huh) { 
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
	    //PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the next 'S' tree. 
	    PUSH_PATH(12); // RL: Where we will go when the expression will be reduced. 
	    //current_symbol = -1; 
	    current_symbol = get_next_token_type(); 
	    current_lalr_state = 0; 
	    continue; 
	  }; 
	}; 
	
	if (ANIME_TOKEN_OPENBRACKET == current_symbol) { 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(2); 
	  //PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the next 'S' tree. 
	  PUSH_PATH(13); // RL: Where we will go when the expression will be reduced. 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 0; 
	  continue; 
	}; 
	
	if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	  // RL: Then it's a function call. 
	  PUSH_PATH(1); // RL: Where we will go back after having built the tree. 
	  current_lalr_state = 8; // RL: Arg parsing. 
	  continue;
	}; 
	
	if (ANIME_TOKEN_HUH == current_symbol) { 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(3); 
	  PUSH_PATH(14); // RL: Where we will go when the expression will be reduced. 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 0; 
	  continue; 
	}; 
	
	//if (int_member_huh(current_symbol, ANIME_TOKEN_INC, ANIME_TOKEN_DEC)) { 
	if (int_member_array_nb(current_symbol, anime_parser__postfix_operators__nb, anime_parser__postfix_operators)) { 
	  // RL: Postfix unary operator. 
#if 1 
	  int subtree; 
	  POP_OUTPUT(subtree); 
	  const int operator_token = *current_token_ref; 
	  const int operator = current_symbol; 
	  //const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendant*/subtree); 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(*current_token_ref,1,new_tree); // By connexity, subtree should be at the top. 
	  PUSH_OUTPUT(new_tree); 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 1; 
#else 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_ARITY(1); 
	  PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(6); // RL: Where we will go when the expression will be reduced. 
	  current_symbol = -1; 
	  current_lalr_state = 0; 
#endif 
	  continue; 
	}; 

	// RL: Anything that is not expected triggers a reduction. 
	POP_PATH(current_lalr_state); 
	continue; 
	
	assert(false); 
      }; 
      
      






    EXPR_LABEL_STATE(6): { 
	// RL: PREFIX 
	// RL: A unary symbol was read, and a tree was built and is on the ouput stack. 
	// RL: So, we have to get that tree on the stack, make a new tree, and push it onto the stack. 
	// RL: After that, we should backtrack by one. 
	int subtree; 
	POP_OUTPUT(subtree); 
	int operator_token; 
	POP_OUTPUT(operator_token); 
	int operator; 
	POP_OPERATOR(operator); 
	DROP_ARITY(); 
	//const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendant*/subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(operator_token,1,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	POP_PATH(current_lalr_state); 
	continue; 
      }; 
      
    EXPR_LABEL_STATE(7): { 
	// RL: A '(' and a 'S' were read. Now we expect a ')'. 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_CLOSEPAR); 
	// RL: So, we do not touch the tree on the stack. 
	// RL: Now, we should backtrack by one. 
	POP_PATH(current_lalr_state); 
	//current_symbol = -1; 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 

    EXPR_LABEL_STATE(8): { // RL: funcall: S → ident . ( ... 
	// RL: Here, we expect a comma-separated list of expressions, that could be empty. 
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_OPENPAR); 
	current_symbol = get_next_token_type(); 
	if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
#if 1
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  //const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, /*fun_subtree*/ident_subtree, /*arg_list*/-1); 
	  int16_t new_tree; 
	  //OUTPUT_TREE_PUSH(*current_token_ref,0,new_tree); // CLOSEPAR 
	  OUTPUT_TREE_PUSH(ident_subtree,0,new_tree); // By connexity, subtree should be at the top. 
	  PUSH_OUTPUT(new_tree); 
#else 
	  // RL: The funcall_subtree is already on the stack. 
#endif 
	  POP_PATH(current_lalr_state); 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	
	// RL: Now we expect a list of arguments. 
	PUSH_OPERATOR(ANIME_TOKEN_VIRGULE); 
	PUSH_ARITY(0); 
	PUSH_PATH(9); // After having reducing 
	current_lalr_state = 0; // Current next step 
	//current_symbol = -1; 
	//current_symbol = get_next_token_type(); 
	continue;
      }; 
      
    EXPR_LABEL_STATE(9): { // RL: arg_list: S . , S OR ')' 
	// RL: OK. We've just read one 'S'. Now we expect a ')' or a ','. Anything else is an error. 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	  DROP_OPERATOR(); // Current operator should be ANIME_TOKEN_VIRGULE 
	  DROP_ARITY();    // Current arity of ANIME_TOKEN_VIRGULE, so should be zero. 

	  int arg_subtree; 
	  POP_OUTPUT(arg_subtree); 
#if 1 
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  //const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, /*fun_subtree*/ident_subtree, /*arg_list*/arg_subtree); 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(ident_subtree,1,new_tree); // By connexity, subtree should be at the top. 
	  PUSH_OUTPUT(new_tree); 
#else 
	  int funcall_subtree; 
	  POP_OUTPUT(funcall_subtree); 
	  anime_expr_tree__add_subtree(this -> expr_tree_env, funcall_subtree, arg_subtree); 
	  PUSH_OUTPUT(funcall_tree); 
#endif 
	  POP_PATH(current_lalr_state); 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	
	if (current_symbol == ANIME_TOKEN_VIRGULE) { 
	  INC_ARITY();            // Top operator is ANIME_TOKEN_VIRGULE. 
	  PUSH_PATH(10);          // After having reducing 
	  current_lalr_state = 0; // Current next step 
	  current_symbol = -1;    // Current symbol got read. 
	  continue; 
	}; 
	
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_VIRGULE,ANIME_TOKEN_CLOSEPAR); 
      
	assert(false); 
      }; 



    EXPR_LABEL_STATE(10): { // RL: arg_list with two or more items (at least one comma read): S . , S OR ) 
	// RL: OK, we've just read one 'S'. Before that, we read a ',', and before that we read a 'S'. 
	//     So, now, we have to merge 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	
	if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	  DROP_OPERATOR(); // Top operator is ANIME_TOKEN_VIRGULE. 
	  //DROP_ARITY(); 
	  int current_arity; 
	  POP_ARITY(current_arity); 
	  
#if 1 
	  // By connectivity, all the subtrees are already on the output tree stack. 
	  for (int i = 0; i < current_arity; i++) { 
	    int arg_subtree; 
	    POP_OUTPUT(arg_subtree); 
	  }; 
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(ident_subtree,current_arity,new_tree); // By connexity, subtree should be at the top. 
#else 
	  int arg_subtree; 
	  POP_OUTPUT(arg_subtree); 
	  int arglist_subtree; 
	  POP_OUTPUT(arglist_subtree); 
	  const int16_t new_arglist_subtree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__COMMA_LIST, /*arglist_subtree*/arglist_subtree, /*arg_subtree*/arg_subtree); 
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, /*fun_subtree*/ident_subtree, /*arg_list*/new_arglist_subtree); 
#endif 
	  PUSH_OUTPUT(new_tree); 
	  // -- 
	  POP_PATH(current_lalr_state); // Going to the state after having reduced. 
	  current_symbol = -1; // Current symbol got read. 
	  continue; 
	}; 
	
	if (current_symbol == ANIME_TOKEN_VIRGULE) { 
#if 1 
	  INC_ARITY();            // Top operator is ANIME_TOKEN_VIRGULE. 
#else 
	  int arg_subtree; 
	  POP_OUTPUT(arg_subtree); 
	  int arglist_subtree; 
	  POP_OUTPUT(arglist_subtree); 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__COMMA_LIST, /*arglist_subtree*/arglist_subtree, /*arg_subtree*/arg_subtree); 
	  PUSH_OUTPUT(new_tree); 
#endif 
	  PUSH_PATH(10);          // After having reducing 
	  current_lalr_state = 0; // Current next step 
	  current_symbol = -1; 
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
	//const int16_t new_tree = anime_parser_chunk_env__push3(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendants1*/left_subtree, /*descendants2*/right_subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(operator_token,2,new_tree); // By connexity, subtree should be at the top. 
	
	PUSH_OUTPUT(new_tree); 
	// -- 
	//POP_PATH(current_lalr_state); 
	current_lalr_state = 1; 
	continue; 
      }; 


    EXPR_LABEL_STATE(13): { // RL: S →   S [  S . ] 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	
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
	//const int16_t new_tree = anime_parser_chunk_env__push3(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendants1*/left_subtree, /*descendants2*/right_subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(operator_token,2,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	// -- 
	//POP_PATH(current_lalr_state); 
	current_lalr_state = 1; 
	continue; 
      }; 


    EXPR_LABEL_STATE(14): { // RL: S →   S ?  S . : S  
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_DEUXPOINTS); 
	current_symbol = get_next_token_type(); // RL: Eating the token. 
	PUSH_PATH(15); // RL: Where we will go after having reduced. 
	current_lalr_state = 0; 
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
	//const int16_t new_tree = anime_parser_chunk_env__push4(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendants1*/left_subtree, middle_subtree, /*descendants2*/right_subtree); 
	int16_t new_tree; 
	OUTPUT_TREE_PUSH(operator_token,2,new_tree); // By connexity, subtree should be at the top. 
	PUSH_OUTPUT(new_tree); 
	current_lalr_state = 1; 
	continue; 
      }; 

    EXPR_LABEL_STATE(16): { // RL: S →   . SYNTAX_MASTER 
#if 0 
	dputs_array(stderr__fileno, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(stderr__fileno, int_string__stack(path__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
#endif 

	const int master_token_type_id = current_symbol; 
	const int master_index         = master_token_type_id - ANIME_TOKEN__SYNTAX_MASTER__BASE; 
	const int root_rule_index      = this -> custom_syntax_root__array[master_index]; 
#if 0 
	dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", 
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
	current_lalr_state = 17; 
	continue; 
      }; 
	
    EXPR_LABEL_STATE(17): { // RL: S →   . SYNTAX_MASTER // SHIFT 
	//const int master_token_type_id = current_symbol; 
	const int master_index =   master__array[  master__nb - 1]; 
	const int rule_index   = rule_idx__array[rule_idx__nb - 1]; 
	const int rule_len     = this -> custom_syntax_rules__array[rule_index][2]; 
	const int rule_pos     = rule_pos__array[rule_pos__nb - 1]; 
	const int expected_thg = rule_pos >= rule_len ? -1 : this -> custom_syntax_rules__array[rule_index][3 + rule_pos]; 
	//const int node_id      = this -> custom_syntax_rules__array[rule_index][1]; 
#if 0 
	dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", 
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
		    " - CUSTOM_SYNTAX_NODE__BASE: ", int_string__stack(ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE), 
		    " - CUSTOM_SYNTAX_NODE__TOP: ", int_string__stack(ANIME_PARSER__CUSTOM_SYNTAX_NODE__TOP), 
		    " - CUSTOM_SYNTAX_RULE__TOP: ", int_string__stack(ANIME_PARSER__CUSTOM_SYNTAX_RULE__TOP), 
		    "\n"); 
#endif 
	if (rule_len == 0) { 
	  const int tree_type    = this -> custom_syntax_trees__array[rule_index][0]; 
	  const int subtrees_len = this -> custom_syntax_trees__array[rule_index][1]; 
	  //current_symbol = node_id; 
	  if (0 == tree_type) { 
	    PUSH_OUTPUT(-1); 
	    DROP_RULE_POS(); 
	    DROP_RULE_IDX(); 
	    POP_PATH(current_lalr_state); 
	    continue; 
	  }; 
	  if (0 == subtrees_len) { 
	    //const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/tree_type); 
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
	    subtrees[i] = this -> custom_syntax_trees__array[rule_index][2 + i]; 
	  }; 
	  //const int16_t new_tree = anime_parser_chunk_env__push_array(this -> expr_tree_env, /*type*/tree_type, subtrees_len, subtrees); 
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
	  const int tree_type    = this -> custom_syntax_trees__array[rule_index][0]; 
	  const int subtrees_len = this -> custom_syntax_trees__array[rule_index][1]; 
	  if (0 == tree_type) { 
	    if (0 == subtrees_len) { 
	      PUSH_OUTPUT(-1); 
	      DROP_RULE_POS(); 
	      DROP_RULE_IDX(); 
	      POP_PATH(current_lalr_state); 
	      continue; 
	    }; 
	    assert(1 == subtrees_len); 
	    const int item_index = this -> custom_syntax_trees__array[rule_index][2]; 
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
	    //const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/tree_type); 
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
	  int item_index = this -> custom_syntax_trees__array[rule_index][2 + j]; 
	  for (int i = 0; i < rule_len; i++) { 
	    POP_OUTPUT(one_subtree); 
	    if (rule_len - i - 1 != item_index) continue; 
	    subtrees[j] = one_subtree; 
	    j--; 
	    item_index = this -> custom_syntax_trees__array[rule_index][2 + j]; 
	  }; 
	  assert(j == -1); 
	  //const int16_t new_tree = anime_parser_chunk_env__push_array(this -> expr_tree_env, /*type*/tree_type, subtrees_len, subtrees); 
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
	  current_lalr_state = 0; 
	  continue; 
	}; 
	if (current_symbol < 0) { current_symbol = get_next_token_type(); }; 
	if (expected_thg < ANIME_TOKEN__SYNTAX_KEYWORD__TOP) { 
	  SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, expected_thg); 
	  //DROP_RULE_POS(); 
	  //PUSH_RULE_POS(rule_pos+1); 
	  //const int16_t new_tree = anime_parser_chunk_env__push1(this -> expr_tree_env, current_symbol, *current_token_ref); 
	  //const int16_t new_tree = *current_token_ref; 
	  // RL: TODO XXX FIXME: Likely, this does not work. 
	  int16_t new_tree; 
	  OUTPUT_TREE_PUSH(*current_token_ref,-1,new_tree); // By connexity, subtree should be at the top. 
	  PUSH_OUTPUT(new_tree); 
	  rule_pos__array[rule_pos__nb - 1]++; 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	if (expected_thg >= ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE) { 
	  assert(false); 
	  PUSH_PATH(17); 
	  PUSH_RULE_IDX(expected_thg); 
	  PUSH_RULE_POS(0); 
	  continue; 
	}; 
	if (expected_thg >= ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE) { 
#if 0 
	  dputs_array(stderr__fileno, "HHHHHHHH---------------------------------------------------------------------------------------------------ERE\n"); 
#endif 
	  // RL: Here, we have to code the union. 
	  // RL: What would be great would be to code back-tracking. 
	  //     It would not be that awful are rules are LL(1)-like, it's just more convenient to write the same rule a second time with a minor variant 
	  //     than to factor out ourself the 'premier' set. 
	  // RL: Obviously a better approach would be to code all the alived rules; and filter them while reading. 
	  // RL: For the moment, it will be the strong-LL(1) approach, not very user-friendly, but which works and with a low complexity. 
	  const int matching_rule_id = anime_parser__custom_syntax__rule_lookup(this, /*node_id*/expected_thg, /*token_i*/current_symbol); 
	  if (matching_rule_id < 0) { SYNTAX__EXPECTING_NOT_THIS_TOKEN(current_symbol); }; 
	  PUSH_PATH(17); 
	  PUSH_RULE_IDX(matching_rule_id - ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE); 
	  rule_pos__array[rule_pos__nb - 1]++; 
	  PUSH_RULE_POS(0); 
	  continue; 
	}; 
	
	
	assert(false); 
	
	PUSH_PATH(17); // RL: Where we will go after having reduced. 
	current_lalr_state = 17; 
	continue; 
      }; 
	



      assert(false); 
    }; // for (;;) 
    
    
    // HERE WE ARE! 
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "output_token_tree_stack__nb = ", int_string__stack(output_token_tree_stack__nb), "\n" ); 
  dputs_array(stderr__fileno, "output_token_tree_stack__array[0] = ", int_string__stack(output_token_tree_stack__array[0]), "\n" ); 
  dputs_array(stderr__fileno, "output_token_tree_stack__arity[0] = ", int_string__stack(output_token_tree_stack__arity[0]), "\n" ); 
#endif 


    POP_OUTPUT(expr_tree); 
    
    // OK, now the tree is postfix-ly stored in the output tree stack. 
    // Now, we want to reverse, to store it prefix-ly. 
    uint16_t reverse_tree__array[output_token_tree_stack__nb]; 
    uint8_t  reverse_tree__arity[output_token_tree_stack__nb]; 
    uint8_t  reverse_tree__nb = 0; 
#define REVERSE_TREE_PUSH(node,arity) { assert(reverse_tree__nb < output_token_tree_stack__nb); reverse_tree__array[reverse_tree__nb] = (node); reverse_tree__arity[reverse_tree__nb] = (arity); reverse_tree__nb++; }; 
    { 
      // We need to traverse the tree until the child #1 is found — then iterate. 
      enum { max_depth = INT8_MAX - 3 }; 
      uint16_t current_tree_path[max_depth]; 
      uint8_t  how_many_children_processed[max_depth]; 
      uint8_t current_reverse_index = output_token_tree_stack__nb - 1; // The root. 
      assert(current_reverse_index >= 0); 
      current_tree_path[0] = current_reverse_index; 
      current_reverse_index --; 
      how_many_children_processed[0] = 0; 
      uint8_t path_len = 1; 
      // First, we have to find the deepest & rightmost element, and push it onto the reverse stack. 
      for (;;) { 
	if (0 == path_len) { break; }; 
	const uint16_t current_node  = current_tree_path[path_len-1]; 
	const uint8_t  current_arity = output_token_tree_stack__arity[current_node]; 
	const uint16_t current_token = output_token_tree_stack__array[current_node]; 
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "current_node  = ", int_string__stack(current_node), "\n" ); 
  dputs_array(stderr__fileno, "current_arity = ", int_string__stack(current_arity), "\n" ); 
  dputs_array(stderr__fileno, "~current_arity = ", int_string__stack((uint8_t)~current_arity), "\n" ); 
  dputs_array(stderr__fileno, "current_token = ", int_string__stack(current_token), "\n" ); 
#endif 
#if 0 
	dprintf(stderr_d, "\t" "\t" "current_token   = %d" "\n", current_token); 
#endif 
	if (0 == (uint8_t)~current_arity) { /* just found a leaf */ goto please_reduce; }; 
	if (how_many_children_processed[path_len-1] == current_arity) { /* current node got completed */ goto please_reduce; }; 
	goto please_recurse_into_next_child; 

please_reduce: {
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "reverse_tree__nb = ", int_string__stack(reverse_tree__nb), "\n" ); 
  dputs_array(stderr__fileno, "reverse_tree__array[0] = ", int_string__stack(reverse_tree__array[0]), "\n" ); 
  dputs_array(stderr__fileno, "reverse_tree__arity[0] = ", int_string__stack(reverse_tree__arity[0]), "\n" ); 
#endif 
	  REVERSE_TREE_PUSH(current_token,current_arity); 
#if 0 
  dputs_array(stderr__fileno, "reverse_tree__nb = ", int_string__stack(reverse_tree__nb), "\n" ); 
	dprintf(stderr_d, "\t" "\t" "reverse_tree__array[%d]   = %d" "\n", reverse_tree__nb-1, reverse_tree__array[reverse_tree__nb-1]); 
#endif 
	  for (;;) { 
	    path_len--; 
	    if (0 == path_len) { break; }; 
	    how_many_children_processed[path_len-1]++; 
	    if (how_many_children_processed[path_len-1] == output_token_tree_stack__arity[current_tree_path[path_len-1]]) { 
	      REVERSE_TREE_PUSH(output_token_tree_stack__array[current_tree_path[path_len-1]],output_token_tree_stack__arity[current_tree_path[path_len-1]]); 
	      continue; 
	    }; 
	    break; 
	  }; 
	  if (0 == path_len) { break; }; 
	  goto please_recurse_into_next_child; 
	}; 
	
please_recurse_into_next_child: 
	path_len++; 
	assert(current_reverse_index >= 0); 
	current_tree_path[path_len-1] = current_reverse_index; 
	current_reverse_index --; 
	how_many_children_processed[path_len-1] = 0; 
	continue; 
      }; 
    }; 


#if 0
    for (int i = 0; i < reverse_tree__nb; i++) { 
      dprintf(stderr_d, "\t" "\t" "reverse_tree__array[%d]   = %d" "\n", i, reverse_tree__array[i]); 
    }; 
#endif 
    
    // DONE — We have a fully reversed tree — pushing it now. 
    { 
      // We have to traverse the tree. So, no choice, we need to keep track of where we are. 
      enum { max_depth = INT8_MAX - 3 }; 
      uint16_t current_tree_path[max_depth]; 
      uint8_t  how_many_children_processed[max_depth]; 
      uint8_t  reverse_tree__i = reverse_tree__nb-1; 
      int_anime_tree_t current_tree[max_depth]; 
      int_anime_tree_t first_child_address[max_depth]; 
      assert(reverse_tree__i >= 0); 
      current_tree_path[0] = reverse_tree__i; 
      //reverse_tree__i --; 
      how_many_children_processed[0] = 0; 
      uint8_t path_len = 1; 
      for (;;) { 
	if (reverse_tree__i == (uint8_t)~0) { break; }; 
	const uint8_t          current_arity = reverse_tree__arity[reverse_tree__i]; 
	const uint16_t         current_token = reverse_tree__array[reverse_tree__i]; 
	current_tree[path_len-1] = anime_tree__open(/*anime_tree_env_t * this*/this -> anime_tree_env, /*const uint8_t tree_type*/ANIME__TREE_TYPE__EXPR); 
	anime_tree__push_uint16(this -> anime_tree_env, current_token); 
#if 0 
	dprintf(stderr_d, "\t" "\t" "reverse_tree__nb = %d" "\n", reverse_tree__nb); 
	dprintf(stderr_d, "\t" "\t" "reverse_tree__i = %d" "\n", reverse_tree__i); 
	dprintf(stderr_d, "\t" "\t" "current_token   = %d" "\n", current_token); 
#endif 
	first_child_address[path_len-1] = anime_tree__get_top_address(this -> anime_tree_env); 
	
	if (0 == (uint8_t)~current_arity) { /* just found a leaf */ goto please_reduce2; }; 
	if (how_many_children_processed[path_len-1] == current_arity) { /* current node got completed */ goto please_reduce2; }; 
	goto please_recurse_into_next_child2; 
	
      please_reduce2: {
	  anime_tree__close(this -> anime_tree_env, current_tree[path_len-1], first_child_address[path_len-1]); 
	  for (;;) { 
	    path_len--; 
	    if (0 == path_len) { break; }; 
	    how_many_children_processed[path_len-1]++; 
	    if (how_many_children_processed[path_len-1] == reverse_tree__arity[current_tree_path[path_len-1]]) { 
	      anime_tree__close(this -> anime_tree_env, current_tree[path_len-1], first_child_address[path_len-1]); 
	      continue; 
	    }; 
	    break; 
	  }; 
	  if (0 == path_len) { break; }; 
	  goto please_recurse_into_next_child2; 
	}; 
	
      please_recurse_into_next_child2: 
	path_len++; 
	assert(reverse_tree__i >= 0); 
	current_tree_path[path_len-1] = reverse_tree__i; 
	reverse_tree__i --; 
	how_many_children_processed[path_len-1] = 0; 
	continue; 
      }; 
	
	
      expr_tree = current_tree[0]; 
    };
    
    
    // RL: TODO XXX FIXME: Do we need that? What's the invariant? What's the convention? 
    return expr_tree; 
  }; // LABEL_STATE(expr) 
  





















#if 0   
 LABEL_STATE(decl_constante): { 
    //ANIME_TOKEN_IDENT token_equal_or_assign expr_constante ANIME_TOKEN_PTVIRG ;
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CONST); 
    do { 
      next_token = get_next_token_type(); 
    } while (next_token == ANIME_TOKEN_CONST); 
    for (;;) { 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
      const int ident_token = *current_token_ref; 
      next_token = get_next_token_type(); 
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_EQUAL, ANIME_TOKEN_AFFECTATION, ANIME_TOKEN_AFFECTATION_SIMPLE, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS); 
      next_token = get_next_token_type(); 
      expr_tree  = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      anime_parser_chunk_env__push(this -> decl_toplevel, ANIME_DECL_TOPLEVEL_LIST__TYPE__CONSTANTE, ident_token, expr_tree); 
      next_token = get_next_token_type(); 
      if (next_token != ANIME_TOKEN_IDENT) { break; }; 
    }; 
    return 0; 
  }; 



 LABEL_STATE(decl_type__top_level): { 
    //ANIME_TOKEN_IDENT token_equal_or_assign type_expr ANIME_TOKEN_PTVIRG ;
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_TYPE); 
    do { 
      next_token = get_next_token_type(); 
    } while (next_token == ANIME_TOKEN_TYPE); 
    for (;;) { 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
      const int ident_token = *current_token_ref; 
      next_token = get_next_token_type(); 
      if (next_token == ANIME_TOKEN_VIRGULE) { 
	EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Defining the same underlying type with multiple names does not make much sense. If you actually want to do that, please break down that definition and that gonna be accepted."); 
      }; 
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_EQUAL, ANIME_TOKEN_AFFECTATION, ANIME_TOKEN_AFFECTATION_SIMPLE, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS); 
      next_token = get_next_token_type(); 
      type_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      anime_parser_chunk_env__push(this -> decl_toplevel, ANIME_DECL_TOPLEVEL_LIST__TYPE__TYPE, ident_token, type_expr_tree); 
      next_token = get_next_token_type(); 
      if (next_token != ANIME_TOKEN_IDENT) { break; }; 
    }; 
    return 0; 
  }; 



 LABEL_STATE(decl_variable__top_level): { 
    //ANIME_TOKEN_IDENT token_equal_or_assign type_expr ANIME_TOKEN_PTVIRG ;
    int next_token; 
    int ident_list_nb = 0; 
    int ident_list_array[decl__arg_ident_list__size]; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_VAR); 
    do { 
      next_token = get_next_token_type(); 
    } while (next_token == ANIME_TOKEN_VAR); 
    for (;;) { 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
      ident_list_nb = 1; 
      ident_list_array[0] = *current_token_ref; 
      next_token = get_next_token_type(); 
      if (next_token == ANIME_TOKEN_VIRGULE) { 
	for (;;) { 
	  do { next_token = get_next_token_type(); } while (next_token == ANIME_TOKEN_VIRGULE); 
	  SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
	  if (ident_list_nb == decl__arg_ident_list__size) { 
	    EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Declaring too many variables at the same time - I can handle at most ", int_string__stack(decl__arg_ident_list__size), " in one declaration. Please break down that declaration (or recompile the parser with a larger stack)."); 
	  }; 
	  ident_list_array[ident_list_nb] = *current_token_ref; 
	  ident_list_nb++; 
	  next_token = get_next_token_type(); 
	  if (next_token != ANIME_TOKEN_VIRGULE) { break; }; 
	}; 
      };
      
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_PTVIRG, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS); 
      if (next_token != ANIME_TOKEN_PTVIRG) { 
	next_token     = get_next_token_type(); 
	type_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
	next_token     = get_current_token_type(); 
      } 
      else { 
	type_expr_tree = -1; 
      }; 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 

      int * ident_token_ptr = ident_list_array + ident_list_nb; 
      for (int i = 0; i < ident_list_nb; i++) { 
	ident_token_ptr--; 
	anime_parser_chunk_env__push(this -> decl_toplevel, ANIME_DECL_TOPLEVEL_LIST__TYPE__VARIABLE, *ident_token_ptr, type_expr_tree); 
      }; 
      
      next_token = get_next_token_type(); 
      if (next_token != ANIME_TOKEN_IDENT) { break; }; 
    }; 
    return 0; 
  }; 



 LABEL_STATE(expr): { 
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
    const int8_t path__size = 63; // RL: This represents the nestedness of an expression. If an expression is more nested than that, then we wouldn't be able to parse it. 
    int8_t path__array[path__size]; 
    int8_t path__nb = 0; 
    const int8_t outputs__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
    int16_t outputs__array[outputs__size]; 
    int8_t outputs__nb = 0; 
    // RL: Extra stacks, as the automaton could be simplified in adding variables instead of extending all these into states. 
    const int8_t operator__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
    int8_t operator__array[operator__size]; 
    int8_t operator__nb = 0; 
    const int8_t arity__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
    int8_t arity__array[arity__size]; 
    int8_t arity__nb = 0; 
    const int8_t master__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
    int8_t master__array[master__size]; 
    int8_t master__nb = 0; 
    const int8_t rule_idx__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
    int8_t rule_idx__array[rule_idx__size]; 
    int8_t rule_idx__nb = 0; 
    const int8_t rule_pos__size = path__size; // RL: They should be the same as it would not make any sense otherwise. 
    int8_t rule_pos__array[rule_pos__size]; 
    int8_t rule_pos__nb = 0; 
    int8_t current_lalr_state = 0; 
    int16_t current_symbol = get_current_token_type(); 
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
#define DROP_OPERATOR(x) { assert(operator__nb > 0); operator__nb--; }; 
#define DROP_ARITY(x)    { assert(   arity__nb > 0);    arity__nb--; }; 
#define DROP_MASTER(x)   { assert(  master__nb > 0);   master__nb--; }; 
#define DROP_RULE_IDX(x) { assert(rule_idx__nb > 0); rule_idx__nb--; }; 
#define DROP_RULE_POS(x) { assert(rule_pos__nb > 0); rule_pos__nb--; }; 
#define EXPR_CASE_GOTO(id) case id: goto glue(label__expr_state,id); break;  
#define EXPR_LABEL_STATE(id) glue(label__expr_state,id) 
    PUSH_PATH(11); 
    for (;;) { 
#if DEBUG_PARSER >= 2
  dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", " - current_lalr_state: ", int_string__stack(current_lalr_state), " - current_token: ", int_string__stack(*current_token_ref), " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", "\n"); 
#endif 
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(stderr__fileno, int_string__stack(path__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
#endif 
#if DEBUG_PARSER >= 3 
  dputs_array(stderr__fileno, "\t", "OUTPUTS: [ "); for (int i = 0; i < outputs__nb; i++) { dputs_array(stderr__fileno, int_string__stack(outputs__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
#endif 
      switch (current_lalr_state) {
	EXPR_CASE_GOTO(0);  // RL: S → . S   _   S | ...  
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
      assert(false); 
      
    EXPR_LABEL_STATE(0): { 
	//if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	if (-1 == current_symbol) { current_symbol = get_next_token_type(); }; 
	//if (int_member_huh(current_symbol, ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL)) { 
	if (int_member_huh(current_symbol, ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL, ANIME_TOKEN_NULL_PTR, ANIME_TOKEN_IDENT)) { 
	  //RL: Constant value. 
	  const int16_t new_tree = anime_parser_chunk_env__push1(this -> expr_tree_env, current_symbol, *current_token_ref); 
	  //const int16_t new_tree = *current_token_ref; 

	  PUSH_OUTPUT(new_tree); 
	  //PUSH_PATH(current_lalr_state); 
	  current_symbol = get_next_token_type(); //-1; 
	  current_lalr_state = 1; 
	  continue;
	}; 
	if (int_member_huh(current_symbol, ANIME_TOKEN_LOGICAL_NOT, ANIME_TOKEN_IPLUS, ANIME_TOKEN_IMOINS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_RMOINS)) { 
	  // RL: Prefix unary operator. 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(1); 
	  //PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(1); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(6); // RL: Where we will go when the expression will be reduced. 
	  current_symbol = get_next_token_type(); //-1; 
	  current_lalr_state = 0; 
	  continue; 
	}; 
	if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	  //PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(1); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(7); // RL: Where we will go when the expression will be reduced. 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); //-1; 
	  current_lalr_state = 0; 
	  continue;
	}; 
#if 0 
	if (ANIME_TOKEN_IDENT == current_symbol) { 
	  // RL: Here, we have two possibilities: (i) an ident evaluation; or (ii) a function call. So we do a LA (look-ahead) to choose. 
	  // RL: But, first, we gonna need the ident value anyway. 
	  const int16_t new_tree = anime_expr_tree__push0(this -> expr_tree_env, current_symbol, *current_token_ref); 
	  PUSH_OUTPUT(new_tree); 
	  current_symbol = get_next_token_type(); 
	  if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	    // RL: That's a function call. 
#if 0 
	    int ident_subtree; 
	    POP_OUTPUT(ident_subtree); 
	    const int16_t new_tree = anime_expr_tree__push1(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, -1, ident_subtree); 
	    PUSH_OUTPUT(new_subtree); 
#endif 
	    PUSH_PATH(1); // RL: Where we will go back after having built the tree. 
	    //current_symbol = -1; 
	    current_lalr_state = 8; 
	    continue;
	  }; 
	  
	  // RL: That's an ident evaluation. 
	  { 
	    //PUSH_PATH(current_lalr_state); 
	    //PUSH_PATH(1); 
	    PUSH_OUTPUT(new_tree); 
	    current_symbol = get_current_token_type(); // -1; 
	    current_lalr_state = 1; 
	    continue; 
	  }; 
 
	  assert(false); 
	}; 
#endif 
	
	if (ANIME_TOKEN_LAMBDA == current_symbol) { 
	  const int lambda_decl_expr = anime_parser__automaton__aux(exception_data, this, token_env, expr_lambda, current_token_ref, retval1_ref);
	  current_symbol = get_current_token_type(); ; 
	  //const int16_t new_tree = anime_expr_tree__push0(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__LAMBDA, lambda_decl); 
	  const int16_t new_tree = lambda_decl_expr; 
	  PUSH_OUTPUT(new_tree); 
	  current_lalr_state = 1; 
	  continue; 
	}; 

	if (ANIME_TOKEN__SYNTAX_MASTER__BASE <= current_symbol && current_symbol < ANIME_TOKEN__SYNTAX_MASTER__TOP) { 
	  PUSH_PATH(1); // RL: Where we will go after having reduced the custom syntax. 
	  current_lalr_state = 16; 
	  continue;
	}; 
	
	
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_TRUE, ANIME_TOKEN_FALSE, ANIME_TOKEN_ENTIER, ANIME_TOKEN_REEL__VIRG, ANIME_TOKEN_REEL__DOT, ANIME_TOKEN_REEL__E, ANIME_TOKEN_CHAINE_C, ANIME_TOKEN_CHAINE_P, ANIME_TOKEN_NIL, ANIME_TOKEN_IDENT, ANIME_TOKEN_LOGICAL_NOT, ANIME_TOKEN_IPLUS, ANIME_TOKEN_IMOINS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_RMOINS, ANIME_TOKEN_OPENPAR, ANIME_TOKEN_LAMBDA, ANIME_TOKEN_SYNTAX_MASTER); 
	
	// RL: TODO XXX FIXME: Do we need to here have an 'S' case? 
	
	dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", " - current_lalr_state: ", int_string__stack(current_lalr_state), " - current_token: ", int_string__stack(*current_token_ref), " - current_symbol: ", current_symbol >= 0 && current_symbol < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(current_symbol) : "_", "(", int_string__stack(current_symbol), ")", "\n"); 
	dputs_array(stderr__fileno, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(stderr__fileno, int_string__stack(path__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
	assert(false); 
      };  
      
      




    EXPR_LABEL_STATE(1): { 
	// RL: We have read one expression. Now we will read the operator applied to that left expression. 
	// RL: We try to here order them by priority. 
	// RL: TODO XXX FIXME: Do we need a priority stack? 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 

#if 0 	// RL: That could be a quick end. 
	//if (ANIME_TOKEN_EOF == current_symbol) { 
	if (ANIME_TOKEN_PTVIRG == current_symbol) { 
	  // RL: Nothing to be read left. 
	  // RL: We just an 'S' expression; so that looks good. 
	  //     However, we might be nested in other expression, expecting something to be read. 
	  //assert(1 == outputs__nb); 
	  //POP_OUTPUT(expr_tree); 
	  //current_symbol = -1; 
	  //current_lalr_state = 11; 
	  POP_PATH(current_lalr_state); 
	  continue; 
	}; 
#endif 
	
	const int infix_binary_operator_huh = int_member_huh(current_symbol, ANIME_TOKEN_AFFECTATION, ANIME_TOKEN_AFFECTATION_SIMPLE, ANIME_TOKEN_AFFECTATION_IADD, ANIME_TOKEN_AFFECTATION_RADD, ANIME_TOKEN_AFFECTATION_ISUB, ANIME_TOKEN_AFFECTATION_RSUB, ANIME_TOKEN_AFFECTATION_IMULT, ANIME_TOKEN_AFFECTATION_RMULT, ANIME_TOKEN_AFFECTATION_IDIV, ANIME_TOKEN_AFFECTATION_RDIV, ANIME_TOKEN_AFFECTATION_IMOD, ANIME_TOKEN_AFFECTATION_L_AND, ANIME_TOKEN_AFFECTATION_L_OR, ANIME_TOKEN_AFFECTATION_L_XOR, ANIME_TOKEN_AFFECTATION_B_AND, ANIME_TOKEN_AFFECTATION_B_OR, ANIME_TOKEN_AFFECTATION_B_XOR, ANIME_TOKEN_AFFECTATION_B_RSHIFT, ANIME_TOKEN_AFFECTATION_B_LSHIFT, ANIME_TOKEN_LOGICAL_OR, ANIME_TOKEN_LOGICAL_AND, ANIME_TOKEN_LOGICAL_XOR, ANIME_TOKEN_BITWISE_OR, ANIME_TOKEN_BITWISE_AND, ANIME_TOKEN_BITWISE_XOR, ANIME_TOKEN_BITWISE_SHIFT_LEFT, ANIME_TOKEN_BITWISE_SHIFT_RIGHT, ANIME_TOKEN_EQUAL, ANIME_TOKEN_DIFF, ANIME_TOKEN_INF, ANIME_TOKEN_SUP, ANIME_TOKEN_INFEQ, ANIME_TOKEN_SUPEQ, ANIME_TOKEN_IPLUS, ANIME_TOKEN_RPLUS, ANIME_TOKEN_IMINUS, ANIME_TOKEN_RMINUS, ANIME_TOKEN_IMULT, ANIME_TOKEN_RMULT, ANIME_TOKEN_IDIV, ANIME_TOKEN_RDIV, ANIME_TOKEN_POINT, ANIME_TOKEN_FLECHE); 
	
	// RL: The default behavior is to shift. 
	//     However, this is an undesirable behavior to handle priorities: 
	//        " 1 * 2 + 3 " 
	//     In this case, we should not shift, but reduce. 
	//     In order to implement that, we have just to compare priorities: 
	//       if priority(current_operator) < priority(previous_operator) then reduce else shift 
	//     
	if (infix_binary_operator_huh) { 
	  int reduce_huh = false; 
	  if (operator__nb > 0) { 
	    const int previous_operator = operator__array[operator__nb-1]; 
	    reduce_huh = (previous_operator >= current_symbol); // RL: Property of the token-types: first the lowest priority, last the highest priority. 
	  }; 
	  if (reduce_huh) { 
	    POP_PATH(current_lalr_state); 
	    continue; 
	  } 
	  else {  
	    PUSH_OPERATOR(current_symbol); 
	    PUSH_OUTPUT(*current_token_ref); 
	    PUSH_ARITY(2); 
	    //PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the next 'S' tree. 
	    PUSH_PATH(12); // RL: Where we will go when the expression will be reduced. 
	    //current_symbol = -1; 
	    current_symbol = get_next_token_type(); 
	    current_lalr_state = 0; 
	    continue; 
	  }; 
	}; 
	
	if (ANIME_TOKEN_OPENBRACKET == current_symbol) { 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(2); 
	  //PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the next 'S' tree. 
	  PUSH_PATH(13); // RL: Where we will go when the expression will be reduced. 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 0; 
	  continue; 
	}; 
	
	if (ANIME_TOKEN_OPENPAR == current_symbol) { 
	  // RL: Then it's a function call. 
	  PUSH_PATH(1); // RL: Where we will go back after having built the tree. 
	  current_lalr_state = 8; // RL: Arg parsing. 
	  continue;
	}; 
	
	if (ANIME_TOKEN_HUH == current_symbol) { 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_OUTPUT(*current_token_ref); 
	  PUSH_ARITY(3); 
	  PUSH_PATH(14); // RL: Where we will go when the expression will be reduced. 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 0; 
	  continue; 
	}; 
	
	//if (int_member_huh(current_symbol, ANIME_TOKEN_INC, ANIME_TOKEN_DEC)) { 
	if (int_member_array_nb(current_symbol, anime_parser__postfix_operators__nb, anime_parser__postfix_operators)) { 
	  // RL: Postfix unary operator. 
#if 1 
	  int subtree; 
	  POP_OUTPUT(subtree); 
	  const int operator_token = *current_token_ref; 
	  const int operator = current_symbol; 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendant*/subtree); 
	  PUSH_OUTPUT(new_tree); 
	  current_symbol = get_next_token_type(); 
	  current_lalr_state = 1; 
#else 
	  PUSH_OPERATOR(current_symbol); 
	  PUSH_ARITY(1); 
	  PUSH_PATH(current_lalr_state); // RL: Where we will go after having built the unary tree. 
	  PUSH_PATH(6); // RL: Where we will go when the expression will be reduced. 
	  current_symbol = -1; 
	  current_lalr_state = 0; 
#endif 
	  continue; 
	}; 

	// RL: Anything that is not expected triggers a reduction. 
	POP_PATH(current_lalr_state); 
	continue; 
	
	assert(false); 
      }; 
      
      






    EXPR_LABEL_STATE(6): { 
	// RL: PREFIX 
	// RL: A unary symbol was read, and a tree was built and is on the ouput stack. 
	// RL: So, we have to get that tree on the stack, make a new tree, and push it onto the stack. 
	// RL: After that, we should backtrack by one. 
	int subtree; 
	POP_OUTPUT(subtree); 
	int operator_token; 
	POP_OUTPUT(operator_token); 
	int operator; 
	POP_OPERATOR(operator); 
	DROP_ARITY(); 
	const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendant*/subtree); 
	PUSH_OUTPUT(new_tree); 
	POP_PATH(current_lalr_state); 
	continue; 
      }; 
      
    EXPR_LABEL_STATE(7): { 
	// RL: A '(' and a 'S' were read. Now we expect a ')'. 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_CLOSEPAR); 
	// RL: So, we do not touch the tree on the stack. 
	// RL: Now, we should backtrack by one. 
	POP_PATH(current_lalr_state); 
	//current_symbol = -1; 
	current_symbol = get_next_token_type(); 
	continue; 
      }; 

    EXPR_LABEL_STATE(8): { // RL: funcall: S → ident . ( ... 
	// RL: Here, we expect a comma-separated list of expressions, that could be empty. 
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_OPENPAR); 
	current_symbol = get_next_token_type(); 
	if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
#if 1
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, /*fun_subtree*/ident_subtree, /*arg_list*/-1); 
	  PUSH_OUTPUT(new_tree); 
#else 
	  // RL: The funcall_subtree is already on the stack. 
#endif 
	  POP_PATH(current_lalr_state); 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	
	// RL: Now we expect a list of arguments. 
	PUSH_OPERATOR(ANIME_TOKEN_VIRGULE); 
	PUSH_ARITY(INT8_MAX); 
	PUSH_PATH(9); 
	current_lalr_state = 0; 
	//current_symbol = -1; 
	//current_symbol = get_next_token_type(); 
	continue;
      }; 
      
    EXPR_LABEL_STATE(9): { // RL: arg_list: S . , S OR ) 
	// RL: OK. We've just read one 'S'. Now we expect a ')' or a ','. Anything else is an error. 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	  DROP_OPERATOR(); 
	  DROP_ARITY(); 

	  int arg_subtree; 
	  POP_OUTPUT(arg_subtree); 
#if 1 
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, /*fun_subtree*/ident_subtree, /*arg_list*/arg_subtree); 
	  PUSH_OUTPUT(new_tree); 
#else 
	  int funcall_subtree; 
	  POP_OUTPUT(funcall_subtree); 
	  anime_expr_tree__add_subtree(this -> expr_tree_env, funcall_subtree, arg_subtree); 
	  PUSH_OUTPUT(funcall_tree); 
#endif 
	  POP_PATH(current_lalr_state); 
	  //current_symbol = -1; 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	
	if (current_symbol == ANIME_TOKEN_VIRGULE) { 
	  PUSH_PATH(10); 
	  current_lalr_state = 0; 
	  current_symbol = -1; 
	  continue;
	}; 
	
	SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(current_symbol,ANIME_TOKEN_VIRGULE,ANIME_TOKEN_CLOSEPAR); 
      
	assert(false); 
      }; 



    EXPR_LABEL_STATE(10): { // RL: arg_list with two or more items (at least one comma read): S . , S OR ) 
	// RL: OK, we've just read one 'S'. Before that, we read a ',', and before that we read a 'S'. 
	//     So, now, we have to merge 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	
	if (current_symbol == ANIME_TOKEN_CLOSEPAR) { 
	  DROP_OPERATOR(); 
	  DROP_ARITY(); 

	  int arg_subtree; 
	  POP_OUTPUT(arg_subtree); 
	  int arglist_subtree; 
	  POP_OUTPUT(arglist_subtree); 
	  const int16_t new_arglist_subtree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__COMMA_LIST, /*arglist_subtree*/arglist_subtree, /*arg_subtree*/arg_subtree); 
	  int ident_subtree; 
	  POP_OUTPUT(ident_subtree); 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__FUNCALL, /*fun_subtree*/ident_subtree, /*arg_list*/new_arglist_subtree); 
	  PUSH_OUTPUT(new_tree); 
	  // -- 
	  POP_PATH(current_lalr_state); 
	  current_symbol = -1; 
	  continue; 
	}; 
	
	if (current_symbol == ANIME_TOKEN_VIRGULE) { 
	  int arg_subtree; 
	  POP_OUTPUT(arg_subtree); 
	  int arglist_subtree; 
	  POP_OUTPUT(arglist_subtree); 
	  const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__COMMA_LIST, /*arglist_subtree*/arglist_subtree, /*arg_subtree*/arg_subtree); 
	  PUSH_OUTPUT(new_tree); 
	  // -- 
	  PUSH_PATH(10); 
	  current_lalr_state = 0; 
	  current_symbol = -1; 
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
	const int16_t new_tree = anime_parser_chunk_env__push3(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendants1*/left_subtree, /*descendants2*/right_subtree); 
	PUSH_OUTPUT(new_tree); 
	// -- 
	//POP_PATH(current_lalr_state); 
	current_lalr_state = 1; 
	continue; 
      }; 


    EXPR_LABEL_STATE(13): { // RL: S →   S [  S . ] 
	if (-1 == current_symbol) { current_symbol = yyanimelex(); }; 
	
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
	const int16_t new_tree = anime_parser_chunk_env__push3(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendants1*/left_subtree, /*descendants2*/right_subtree); 
	PUSH_OUTPUT(new_tree); 
	// -- 
	//POP_PATH(current_lalr_state); 
	current_lalr_state = 1; 
	continue; 
      }; 


    EXPR_LABEL_STATE(14): { // RL: S →   S ?  S . : S  
	SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, ANIME_TOKEN_DEUXPOINTS); 
	current_symbol = get_next_token_type(); // RL: Eating the token. 
	PUSH_PATH(15); // RL: Where we will go when reducing. 
	current_lalr_state = 0; 
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
	const int16_t new_tree = anime_parser_chunk_env__push4(this -> expr_tree_env, /*type*/operator, /*value*/operator_token, /*descendants1*/left_subtree, middle_subtree, /*descendants2*/right_subtree); 
	PUSH_OUTPUT(new_tree); 
	current_lalr_state = 1; 
	continue; 
      }; 

    EXPR_LABEL_STATE(16): { // RL: S →   . SYNTAX_MASTER 
#if 0 
	dputs_array(stderr__fileno, "\t", "PATH: [ "); for (int i = 0; i < path__nb; i++) { dputs_array(stderr__fileno, int_string__stack(path__array[i]), " -> "); }; dputs_array(stderr__fileno, " ]", "\n" ); 
#endif 

	const int master_token_type_id = current_symbol; 
	const int master_index         = master_token_type_id - ANIME_TOKEN__SYNTAX_MASTER__BASE; 
	const int root_rule_index      = this -> custom_syntax_root__array[master_index]; 
#if 0 
	dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", 
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
	current_lalr_state = 17; 
	continue; 
      }; 
	
    EXPR_LABEL_STATE(17): { // RL: S →   . SYNTAX_MASTER // SHIFT 
	//const int master_token_type_id = current_symbol; 
	const int master_index =   master__array[  master__nb - 1]; 
	const int rule_index   = rule_idx__array[rule_idx__nb - 1]; 
	const int rule_len     = this -> custom_syntax_rules__array[rule_index][2]; 
	const int rule_pos     = rule_pos__array[rule_pos__nb - 1]; 
	const int expected_thg = rule_pos >= rule_len ? -1 : this -> custom_syntax_rules__array[rule_index][3 + rule_pos]; 
	//const int node_id      = this -> custom_syntax_rules__array[rule_index][1]; 
#if 0 
	dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", 
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
		    " - CUSTOM_SYNTAX_NODE__BASE: ", int_string__stack(ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE), 
		    " - CUSTOM_SYNTAX_NODE__TOP: ", int_string__stack(ANIME_PARSER__CUSTOM_SYNTAX_NODE__TOP), 
		    " - CUSTOM_SYNTAX_RULE__TOP: ", int_string__stack(ANIME_PARSER__CUSTOM_SYNTAX_RULE__TOP), 
		    "\n"); 
#endif 
	if (rule_len == 0) { 
	  const int tree_type    = this -> custom_syntax_trees__array[rule_index][0]; 
	  const int subtrees_len = this -> custom_syntax_trees__array[rule_index][1]; 
	  //current_symbol = node_id; 
	  if (0 == tree_type) { 
	    PUSH_OUTPUT(-1); 
	    DROP_RULE_POS(); 
	    DROP_RULE_IDX(); 
	    POP_PATH(current_lalr_state); 
	    continue; 
	  }; 
	  if (0 == subtrees_len) { 
	    const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/tree_type); 
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
	    subtrees[i] = this -> custom_syntax_trees__array[rule_index][2 + i]; 
	  }; 
	  const int16_t new_tree = anime_parser_chunk_env__push_array(this -> expr_tree_env, /*type*/tree_type, subtrees_len, subtrees); 
	  PUSH_OUTPUT(new_tree); 
	  DROP_RULE_POS(); 
	  DROP_RULE_IDX(); 
	  POP_PATH(current_lalr_state); 
	  continue; 
	}; 
	//if (expected_thg < 0) { 
	if (rule_pos >= rule_len) { 
	  const int tree_type    = this -> custom_syntax_trees__array[rule_index][0]; 
	  const int subtrees_len = this -> custom_syntax_trees__array[rule_index][1]; 
	  if (0 == tree_type) { 
	    if (0 == subtrees_len) { 
	      PUSH_OUTPUT(-1); 
	      DROP_RULE_POS(); 
	      DROP_RULE_IDX(); 
	      POP_PATH(current_lalr_state); 
	      continue; 
	    }; 
	    assert(1 == subtrees_len); 
	    const int item_index = this -> custom_syntax_trees__array[rule_index][2]; 
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
	    const int16_t new_tree = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/tree_type); 
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
	  int item_index = this -> custom_syntax_trees__array[rule_index][2 + j]; 
	  for (int i = 0; i < rule_len; i++) { 
	    POP_OUTPUT(one_subtree); 
	    if (rule_len - i - 1 != item_index) continue; 
	    subtrees[j] = one_subtree; 
	    j--; 
	    item_index = this -> custom_syntax_trees__array[rule_index][2 + j]; 
	  }; 
	  assert(j == -1); 
	  const int16_t new_tree = anime_parser_chunk_env__push_array(this -> expr_tree_env, /*type*/tree_type, subtrees_len, subtrees); 
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
	  current_lalr_state = 0; 
	  continue; 
	}; 
	if (current_symbol < 0) { current_symbol = get_next_token_type(); }; 
	if (expected_thg < ANIME_TOKEN__SYNTAX_KEYWORD__TOP) { 
	  SYNTAX__EXPECTING_THIS_TOKEN(current_symbol, expected_thg); 
	  //DROP_RULE_POS(); 
	  //PUSH_RULE_POS(rule_pos+1); 
	  const int16_t new_tree = anime_parser_chunk_env__push1(this -> expr_tree_env, current_symbol, *current_token_ref); 
	  //const int16_t new_tree = *current_token_ref; 
	  PUSH_OUTPUT(new_tree); 
	  rule_pos__array[rule_pos__nb - 1]++; 
	  current_symbol = get_next_token_type(); 
	  continue; 
	}; 
	if (expected_thg >= ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE) { 
	  assert(false); 
	  PUSH_PATH(17); 
	  PUSH_RULE_IDX(expected_thg); 
	  PUSH_RULE_POS(0); 
	  continue; 
	}; 
	if (expected_thg >= ANIME_PARSER__CUSTOM_SYNTAX_NODE__BASE) { 
#if 0 
	  dputs_array(stderr__fileno, "HHHHHHHH---------------------------------------------------------------------------------------------------ERE\n"); 
#endif 
	  // RL: Here, we have to code the union. 
	  // RL: What would be great would be to code back-tracking. 
	  //     It would not be that awful are rules are LL(1)-like, it's just more convenient to write the same rule a second time with a minor variant 
	  //     than to factor out ourself the 'premier' set. 
	  // RL: Obviously a better approach would be to code all the alived rules; and filter them while reading. 
	  // RL: For the moment, it will be the strong-LL(1) approach, not very user-friendly, but which works and with a low complexity. 
	  const int matching_rule_id = anime_parser__custom_syntax__rule_lookup(this, /*node_id*/expected_thg, /*token_i*/current_symbol); 
	  if (matching_rule_id < 0) { SYNTAX__EXPECTING_NOT_THIS_TOKEN(current_symbol); }; 
	  PUSH_PATH(17); 
	  PUSH_RULE_IDX(matching_rule_id - ANIME_PARSER__CUSTOM_SYNTAX_RULE__BASE); 
	  rule_pos__array[rule_pos__nb - 1]++; 
	  PUSH_RULE_POS(0); 
	  continue; 
	}; 
	
	
	assert(false); 
	
	PUSH_PATH(17); // RL: Where we will go when reducing. 
	current_lalr_state = 17; 
	continue; 
      }; 
	



      assert(false); 
    }; // for (;;) 
    
    // RL: TODO XXX FIXME: Do we need that? What's the invariant? What's the convention? 
    POP_OUTPUT(expr_tree); 
    return expr_tree; 
  }; // LABEL_STATE(expr) 











 LABEL_STATE(type_expr): { 
#if 0 
  type__top_level: TOKEN_BOOLEAN | TOKEN_INTEGER | expr TOKEN_SUBRANGE expr | TOKEN_REAL | TOKEN_STRING | pointer__top_level | array__top_level | record__top_level | nom ;
  pointer__top_level: TOKEN_PTR type__top_level ;
  array__top_level: 
    TOKEN_ARRAY TOKEN_OPENBRACKET expr                     TOKEN_CLOSEBRACKET TOKEN_OF type__top_level 
      | TOKEN_ARRAY TOKEN_OPENBRACKET expr TOKEN_SUBRANGE expr TOKEN_CLOSEBRACKET TOKEN_OF type__top_level 
      ;
  record__top_level: TOKEN_RECORD liste_decl_champ__top_level TOKEN_END ; 
  liste_decl_champ__top_level: liste_decl_champ__top_level decl_champ__top_level | ;
  decl_champ__top_level: TOKEN_IDENT TOKEN_DEUXPOINTS type__top_level TOKEN_PTVIRG ;
#endif 

    int next_token; 
    for (;;) { 
      next_token = get_current_token_type(); 
      if (int_member_huh(next_token, ANIME_TOKEN_BOOLEAN, ANIME_TOKEN_VARIANT, ANIME_TOKEN_INTEGER, ANIME_TOKEN_FLOAT, ANIME_TOKEN_STRING, ANIME_TOKEN_IDENT)) { 
	type_expr_tree = anime_parser_chunk_env__push1(this -> type_tree_env, /*type*/next_token, /*value*/*current_token_ref); 
	next_token = get_next_token_type(); 
	return type_expr_tree; 
      }; 
      
      if (next_token == ANIME_TOKEN_ENTIER) { 
	// RL: That could be an integer range. 
	const int left_token = *current_token_ref; 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_SUBRANGE); 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_ENTIER); 
	const int right_token = *current_token_ref; 
	type_expr_tree = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__SUBRANGE_CONST, /*value*/left_token, right_token); 
	next_token = get_next_token_type(); 
	return type_expr_tree; 
      }; 

      if (next_token == ANIME_TOKEN_OPENBRACKET) { 
	// RL: This a complex range. Expressions are allowed. 
	next_token = get_next_token_type(); 
	const int left_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
	next_token = get_current_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_SUBRANGE); 
	next_token = get_next_token_type(); 
	const int right_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
	next_token = get_current_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_CLOSEBRACKET); 
	type_expr_tree = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__SUBRANGE_EXPR, /*value*/left_expr_tree,/*descendants*/right_expr_tree); 
	next_token = get_next_token_type(); 
	return type_expr_tree; 
      }; 

      
      if (next_token == ANIME_TOKEN_ARRAY) { 
	int expr1; 
	int expr2; 
	int subtype; 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_OPENBRACKET); 
	next_token = get_next_token_type(); 
	expr1 = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
	next_token = get_current_token_type(); 
	if (next_token == ANIME_TOKEN_SUBRANGE) { 
	  next_token = get_next_token_type(); 
	  expr2 = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
	  next_token = get_current_token_type(); 
	} 
	else { 
	  expr2 = -1; 
	}; 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_CLOSEBRACKET); 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_OF); 
	next_token = get_next_token_type(); 
	subtype = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
	next_token = get_current_token_type(); 
	type_expr_tree = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARRAY, /*descendants*/ expr1, expr2, subtype); 
	return type_expr_tree; 
      }; 
      
      if (next_token == ANIME_TOKEN_RECORD) { 
	next_token = get_next_token_type(); 
	//const int fields = anime_parser__automaton__aux(exception_data, this, token_env, record_fields, current_token_ref, retval1_ref); 
	const int fields_nb = anime_parser__automaton__aux(exception_data, this, token_env, record_fields, current_token_ref, retval1_ref); 
	next_token = get_current_token_type(); 
	assert(next_token == ANIME_TOKEN_END); 
	//type_expr_tree = anime_parser_chunk_env__push1(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD, /*value*/fields); 
	type_expr_tree = anime_parser_chunk_env__push1(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD, /*value*/fields_nb); 
	next_token = yyanimelex(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token, ANIME_TOKEN_PTVIRG); 
	return type_expr_tree; 
      }; 
      
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_ARRAY, ANIME_TOKEN_RECORD, ANIME_TOKEN_OPENBRACKET, ANIME_TOKEN_SUBRANGE, ANIME_TOKEN_BOOLEAN, ANIME_TOKEN_VARIANT, ANIME_TOKEN_INTEGER, ANIME_TOKEN_FLOAT, ANIME_TOKEN_IDENT); 
    }; 
    assert(false); 
    return 0; 

  
    return type_expr_tree; 
  }; // LABEL_STATE(type_expr) 
  
  













 LABEL_STATE(record_fields): { 
#if 0 
  record__top_level:           TOKEN_RECORD liste_decl_champ__top_level TOKEN_END ; 
  liste_decl_champ__top_level:              liste_decl_champ__top_level decl_champ__top_level | ;
  decl_champ__top_level:       TOKEN_IDENT TOKEN_DEUXPOINTS type__top_level TOKEN_PTVIRG ;
#endif 
    int next_token; 
    int ident_list_nb = 0; 
    int ident_list_array[decl__arg_ident_list__size]; 

    next_token = get_current_token_type(); 
    for (;;) { 
      if (next_token == ANIME_TOKEN_END) { 
#if 1
	return 0; 
#else 
	//type_expr_tree = -1; 
	type_expr_tree = anime_parser_chunk_env__push0(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD_FIELD_NIL); 
	return type_expr_tree; 
#endif 
      }; 
      
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
      ident_list_nb = 1; 
      ident_list_array[0] = *current_token_ref; 
      next_token = get_next_token_type(); 
      if (next_token == ANIME_TOKEN_VIRGULE) { 
	for (;;) { 
	  do { next_token = get_next_token_type(); } while (next_token == ANIME_TOKEN_VIRGULE); 
	  SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
	  if (ident_list_nb == decl__arg_ident_list__size) { 
	    EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Declaring too many variables at the same time - I can handle at most ", int_string__stack(decl__arg_ident_list__size), " in one declaration. Please break down that declaration (or recompile the parser with a larger stack)."); 
	  }; 
	  ident_list_array[ident_list_nb] = *current_token_ref; 
	  ident_list_nb++; 
	  next_token = get_next_token_type(); 
	  if (next_token != ANIME_TOKEN_VIRGULE) { break; }; 
	}; 
      }; 
      
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS); 
      next_token = get_next_token_type(); 
      const int field_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
      next_token = get_next_token_type(); 
      //const int fields_tail = anime_parser__automaton__aux(exception_data, this, token_env, record_fields, current_token_ref, retval1_ref); 
      const int fields_tail_nb = anime_parser__automaton__aux(exception_data, this, token_env, record_fields, current_token_ref, retval1_ref); 
      
      //int fields_list = fields_tail; 
      int fields_list_nb = fields_tail_nb; 
      int * ident_token_ptr = ident_list_array + ident_list_nb; 
      for (int i = 0; i < ident_list_nb; i++) { 
	ident_token_ptr--; 
	//fields_list = anime_type_tree__push2(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD_FIELD_CONS, /*value*/*ident_token_ptr,/*descendant1*/field_type, fields_list); 
	//fields_list = anime_type_tree__push2(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD_FIELD_CONS, /*value*/*ident_token_ptr,/*descendant1*/field_type); 
	//fields_list = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD_FIELD_CONS, /*value*/*ident_token_ptr,/*descendant1*/field_type); 
	anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__RECORD_FIELD_CONS, /*value*/*ident_token_ptr,/*descendant1*/field_type); 
	fields_list_nb ++; 
      }; 
      //return fields_list; 
      return fields_list_nb; 
    }; 
    
    assert(false); 
    return 0; 
    
    return type_expr_tree; 
  }; // LABEL_STATE(record_fields) 
  
  



 LABEL_STATE(decl_procedure): { 
    //ANIME_TOKEN_IDENT OPENPAR arg_list CLOSEPAR retval_type? PTVIRG? localvar? begin ;
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_PROCEDURE, ANIME_TOKEN_FUNCTION); 
    do { 
      next_token = get_next_token_type(); 
    } while (int_member_huh(next_token, ANIME_TOKEN_PROCEDURE, ANIME_TOKEN_FUNCTION)); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
    const int ident_token = *current_token_ref; 
    next_token = get_next_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OPENPAR); 
    const int arg_list = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEPAR); 
    next_token = get_next_token_type(); 
    int retval_type; 
    if (int_member_huh(next_token, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS)) { 
      next_token = get_next_token_type(); 
      retval_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
    } 
    else { 
      retval_type = -1; 
    }; 
    while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
    int localvar_ref = -1; 
    int localvar_nb;
    if (next_token == ANIME_TOKEN_VAR) { 
      localvar_ref = anime_parser__automaton__aux(exception_data, this, token_env, decl__local_var, current_token_ref, &localvar_nb); 
      next_token = get_current_token_type(); 
    } 
    else {
      localvar_nb = 0; 
    }; 
    
    while (next_token == ANIME_TOKEN_PTVIRG) { 
      next_token = get_next_token_type(); 
    }; 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_BEGIN); 
    int inst_nb;
    const int inst_ref = anime_parser__automaton__aux(exception_data, this, token_env, instructions__begin, current_token_ref, &inst_nb); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_END); 
    
    const int funproc_type_expr_tree = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__FUNPROC, /*descendant1*/arg_list, retval_type); 
    //const int funproc_decl = anime_decl_toplevel_list__push__funproc(this -> decl_toplevel, /*ident*/ident_token, /*typing_expr*/funproc_type_expr_tree, /*localvar_nb*/localvar_nb, /*localvar_ref*/localvar_ref, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 
    const int funproc_decl = anime_parser_chunk_env__push(this -> decl_toplevel, ANIME_DECL_TOPLEVEL_LIST__TYPE__FUNPROC, /*ident*/ident_token, /*typing_expr*/funproc_type_expr_tree, /*localvar_nb*/localvar_nb, /*localvar_ref*/localvar_ref, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 

    
    next_token = get_next_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
    return funproc_decl; 
  }; // LABEL_STATE(decl_procedure) 




  
  
  
 LABEL_STATE(expr_lambda): { 
    //ANIME_TOKEN_IDENT OPENPAR arg_list CLOSEPAR retval_type? PTVIRG? localvar? begin ;
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_LAMBDA); 
    do { next_token = get_next_token_type(); } while (next_token == ANIME_TOKEN_LAMBDA); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OPENPAR); 
    const int arg_list = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEPAR); 
    next_token = get_next_token_type(); 
    
    int retval_type; 
    if (int_member_huh(next_token, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS)) { 
      do { next_token = get_next_token_type(); } while (int_member_huh(next_token, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS)); 
      //next_token = get_next_token_type(); 
      retval_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
    } 
    else { 
      retval_type = -1; 
    }; 
    
    while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
    int localvar_ref; 
    int localvar_nb;
    if (next_token == ANIME_TOKEN_VAR) { 
      localvar_ref = anime_parser__automaton__aux(exception_data, this, token_env, decl__local_var, current_token_ref, &localvar_nb); 
      next_token = get_current_token_type(); 
    } 
    else {
      localvar_nb = 0; 
      localvar_ref = -1; 
    }; 
    
    while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_BEGIN); 
    int inst_nb; 
    const int inst_ref = anime_parser__automaton__aux(exception_data, this, token_env, instructions__begin, current_token_ref, &inst_nb); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_END); 
    
    //const int lambda_type_expr_tree = anime_type_tree__push2(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__FUNPROC, /*descendant1*/arg_list, retval_type); 
    const int lambda_type_expr_tree = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__FUNPROC, /*descendant1*/arg_list, retval_type); 
    // RL: TODO XXX FIXME: Is it top-level? It's definitely not in the spirit? Then... Expr? 
    //const int lambda_decl = anime_decl_toplevel_list__push__lambda(this -> decl_toplevel, /*typing_expr*/lambda_type_expr_tree, /*localvar_nb*/localvar_nb, /*localvar_ref*/localvar_ref, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 
    //const int lambda_decl_expr = anime_expr_tree__push3(this -> expr_tree_env, ANIME_EXPR_TREE__TYPE__LAMBDA, -1, lambda_type_expr_tree, localvar_ref, inst_ref); 
    const int lambda_decl_expr = anime_parser_chunk_env__push(this -> expr_tree_env, /*type*/ANIME_EXPR_TREE__TYPE__LAMBDA, /*lambda_type_expr_tree*/lambda_type_expr_tree, /*localvar_ref*/localvar_ref, /*inst_ref*/inst_ref); 
    
    next_token = get_next_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
    return lambda_decl_expr; 
  }; // LABEL_STATE(decl_procedure) 




  
  
  
 LABEL_STATE(decl_methode): { 
    //ANIME_TOKEN_IDENT of type_expr OPENPAR arg_list CLOSEPAR retval_type? PTVIRG? localvar? begin ;
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_METHODE); 
    do { 
      next_token = get_next_token_type(); 
    } while (next_token == ANIME_TOKEN_METHODE); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
    const int ident_token = *current_token_ref; 
    next_token = get_next_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OF); 
    next_token = get_next_token_type(); 
    const int of_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OPENPAR); 
    const int arg_list = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEPAR); 
    next_token = get_next_token_type(); 
    int retval_type; 
    if (int_member_huh(next_token, ANIME_TOKEN_DEUXPOINTS, ANIME_TOKEN_AS)) { 
      next_token = get_next_token_type(); 
      retval_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
    } 
    else { 
      retval_type = -1; 
    }; 
    while (next_token == ANIME_TOKEN_PTVIRG) { 
      next_token = get_next_token_type(); 
    }; 
    int localvar_ref = -1; 
    int localvar_nb;
    if (next_token == ANIME_TOKEN_VAR) { 
      localvar_ref = anime_parser__automaton__aux(exception_data, this, token_env, decl__local_var, current_token_ref, &localvar_nb); 
      next_token = get_current_token_type(); 
    } 
    else {
      localvar_nb = 0; 
    }; 
    
    while (next_token == ANIME_TOKEN_PTVIRG) { 
      next_token = get_next_token_type(); 
    }; 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_BEGIN); 
    int inst_nb;
    const int inst_ref = anime_parser__automaton__aux(exception_data, this, token_env, instructions__begin, current_token_ref, &inst_nb); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_END); 
    
    //const int methode_type_expr_tree = anime_type_tree__push3(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__METHODE, /*descendant1*/of_type, arg_list, retval_type); 
    const int methode_type_expr_tree = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__METHODE, /*descendant1*/of_type, arg_list, retval_type); 
    //const int methode_decl = anime_decl_toplevel_list__push__method(this -> decl_toplevel, /*ident*/ident_token, /*of_type*/of_type,/*typing_expr*/methode_type_expr_tree, /*localvar_nb*/localvar_nb, /*localvar_ref*/localvar_ref, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 
    const int methode_decl = anime_parser_chunk_env__push(this -> decl_toplevel, ANIME_DECL_TOPLEVEL_LIST__TYPE__METHOD, /*ident*/ident_token, /*of_type*/of_type,/*typing_expr*/methode_type_expr_tree, /*localvar_nb*/localvar_nb, /*localvar_ref*/localvar_ref, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 

    
    next_token = get_next_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
    return methode_decl; 
  }; // LABEL_STATE(decl_methode) 
  
  
  
  
  
  
  
 LABEL_STATE(decl_main): { 
    //ANIME_TOKEN_IDENT of type_expr OPENPAR arg_list CLOSEPAR retval_type? PTVIRG? localvar? begin ;
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_BEGIN); 
    int inst_nb; // = rand(); // = INT_MIN;
    const int inst_ref = anime_parser__automaton__aux(exception_data, this, token_env, instructions__begin, current_token_ref, &inst_nb); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_END); 
    
    //const int main_decl = anime_decl_toplevel_list__push__mainproc(this -> decl_toplevel, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 
    const int main_decl = anime_parser_chunk_env__push(this -> decl_toplevel, ANIME_DECL_TOPLEVEL_LIST__TYPE__MAINPROC, /*inst_nb*/inst_nb, /*inst_ref*/inst_ref); 

    
    next_token = get_next_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    //next_token = get_next_token_type(); 
      
    return main_decl; 
  }; // LABEL_STATE(decl_main) 
  




 LABEL_STATE(decl__arg_list): { 
    // OPENPAR  CLOSEPAR 
    // OPENPAR arg0 CLOSEPAR 
    // OPENPAR arg0 [; arg_i]+ CLOSEPAR 
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_OPENPAR); 
    
#if 1
    next_token = get_next_token_type(); 
    if (next_token == ANIME_TOKEN_CLOSEPAR) { return -1; }; 
    //next_token = get_next_token_type(); 
    *retval1_ref = 0; // args_nb 
    const int arg_list = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list__inner, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_CLOSEPAR); 
#else 
    int arg_list = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 

    next_token = get_next_token_type(); 
    for (;;) { 
      if (next_token == ANIME_TOKEN_CLOSEPAR) { break; }; 
      
      //SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_IDENT, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF, ANIME_TOKEN_BYVAL); 
      const int arg_one = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_one, current_token_ref, retval1_ref); 
      //arg_list = anime_type_tree__push2(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__CONS, /*descendants*/arg_list, arg_one); 
      arg_list = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__CONS, /*descendants*/arg_list, arg_one); 
      next_token = get_current_token_type(); 
      if (next_token == ANIME_TOKEN_CLOSEPAR) { break; }; 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      do { 
	next_token = get_next_token_type(); 
      } while (next_token == ANIME_TOKEN_PTVIRG); 
    }; // for (;;)  
#endif 
      
    return arg_list; 
  }; // LABEL_STATE(decl__arg_list) 




 LABEL_STATE(decl__arg_list__inner): { 
    int next_token; 
    //const int arg_list_empty = -1; 
    //const int arg_list_empty = anime_type_tree__push0(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL, /*value*/-1); 
    // [var|byref|byval] ident (, ident)* : <type> 
    int byref = false; 
    int ident_list_nb = 0; 
    int ident_list_array[decl__arg_ident_list__size]; 
    //SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_IDENT, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF, ANIME_TOKEN_BYVAL); 
    
    next_token = get_current_token_type(); 
    if (next_token == ANIME_TOKEN_CLOSEPAR) { 
      //const int arg_list_empty = -1; 
      //const int arg_list_empty = anime_type_tree__push0(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 
      //const int arg_list_empty = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 
      const int arg_list_empty = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL, /*args_nb*/*retval1_ref); 
//#ifdef DEBUG_PARSER 
#if 0
      dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", " - current_token: ", int_string__stack(*current_token_ref), " - next_token: ", next_token >= 0 && next_token < ANIME_TOKEN_TYPE_COUNT ? anime_token__type_get_cstr(next_token) : "_", "(", int_string__stack(next_token), ")", " - arg_list_empty: ", int_string__stack(arg_list_empty), "\n"); 
#endif 
      //assert(false); 
      return arg_list_empty; 
    }; 
    
    if (int_member_huh(next_token, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF)) { 
      byref = true; 
      do { 
	next_token = get_next_token_type(); 
      } while (int_member_huh(next_token, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF)); 
    } 
    else if (next_token == ANIME_TOKEN_BYVAL) { 
      do { 
	next_token = get_next_token_type(); // RL: Skip 
      } while (next_token == ANIME_TOKEN_BYVAL); 
    }; 
    
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
    
    ident_list_nb = 1; 
    ident_list_array[0] = *current_token_ref; 
    next_token = get_next_token_type(); 
    if (next_token == ANIME_TOKEN_VIRGULE) { 
      for (;;) { 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
	if (ident_list_nb == decl__arg_ident_list__size) { 
	  EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Declaring too many variables at the same time - I can handle at most ", int_string__stack(decl__arg_ident_list__size), " in one declaration. Please break down that declaration (or recompile the parser with a larger stack)."); 
	}; 
	ident_list_array[ident_list_nb] = *current_token_ref; 
	ident_list_nb++; 
	next_token = get_next_token_type(); 
	if (next_token != ANIME_TOKEN_VIRGULE) { break; }; 
      }; 
    }; 
    
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_DEUXPOINTS); 
    
    next_token = get_next_token_type(); 
    const int arg_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 


    
#if 1
    while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
    //const int arg_tail = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list__inner, current_token_ref, retval1_ref); 
    //anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list__inner, current_token_ref, retval1_ref); 
    //const int arg_head = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list__inner, current_token_ref, retval1_ref); 
    *retval1_ref += ident_list_nb; 
    const int arg_head = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list__inner, current_token_ref, retval1_ref); 
#else 
    int arg_tail; 
    if (next_token == ANIME_TOKEN_PTVIRG) { 
      arg_tail = anime_parser__automaton__aux(exception_data, this, token_env, decl__arg_list__inner, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
    }
    else { 
#if 0 
      arg_tail = -1; 
#else 
      ///const int arg_list_empty = anime_type_tree__push0(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 
      const int arg_list_empty = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 
      arg_tail = arg_list_empty; 
#endif 
    }; 
#endif 



    //int arg_head; // = -1;
    //int arg_list = arg_tail; 
    //int * ident_token_ptr = ident_list_array + ident_list_nb; 
    int * ident_token_ptr = ident_list_array; // + ident_list_nb; 
    //int arg_one[ident_list_nb]; 
    for (int i = 0; i < ident_list_nb; i++) { 
      //ident_token_ptr--; 
      //arg_list = anime_type_tree__push3(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__CONS, /*value*/*ident_token_ptr,/*descendant1*/byref, arg_type, arg_list); 
      //arg_list = anime_type_tree__push3(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, arg_type); 
      //arg_list = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, arg_type); 
      //const int arg_one = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, arg_type); 
      //arg_one[i] = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, /*arg_type*/-1); 
      //arg_one[i] = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, /*arg_type*/arg_type); 
      anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, /*arg_type*/arg_type); 
      //if (i == 0) { arg_head = arg_one; }; 
      ident_token_ptr++; 
    }; 




#if 0 
    for (int i = 0; i < ident_list_nb; i++) { 
      anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/arg_one[i], /*field_name_cstr*/"type_expr", /*field_value*/arg_type); 
    };
#endif  
    
    //return arg_list; 
    return arg_head; 
    //return arg_one[0]; 
  }; // LABEL_STATE(decl__arg_list__inner) 
  
  
  
#if 0   
 LABEL_STATE(decl__arg_one): { 
    // [var|byref|byval] ident (, ident)* : <type> 
    int next_token; 
    int byref = false; 
    int ident_list_nb = 0; 
    int ident_list_array[decl__arg_ident_list__size]; 
    //SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_IDENT, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF, ANIME_TOKEN_BYVAL); 
    
    next_token = get_current_token_type(); 
    if (int_member_huh(next_token, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF)) { 
      byref = true; 
      do { 
	next_token = get_next_token_type(); 
      } while (int_member_huh(next_token, ANIME_TOKEN_VAR, ANIME_TOKEN_BYREF)); 
    } 
    else if (next_token == ANIME_TOKEN_BYVAL) { 
      do { 
	next_token = get_next_token_type(); // RL: Skip 
      } while (next_token == ANIME_TOKEN_BYVAL); 
    }; 

    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
    
    ident_list_nb = 1; 
    ident_list_array[0] = *current_token_ref; 
    next_token = get_next_token_type(); 
    if (next_token == ANIME_TOKEN_VIRGULE) { 
      for (;;) { 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
	if (ident_list_nb == decl__arg_ident_list__size) { 
	  EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Declaring too many variables at the same time - I can handle at most ", int_string__stack(decl__arg_ident_list__size), " in one declaration. Please break down that declaration (or recompile the parser with a larger stack)."); 
	}; 
	ident_list_array[ident_list_nb] = *current_token_ref; 
	ident_list_nb++; 
	next_token = get_next_token_type(); 
	if (next_token != ANIME_TOKEN_VIRGULE) { break; }; 
      }; 
    };  
    
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_DEUXPOINTS); 
    
    next_token = get_next_token_type(); 
    const int arg_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 

    if (1 == ident_list_nb) { 
      //const int arg_one = anime_type_tree__push2(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/ident_list_array[0],/*descendant1*/byref, arg_type); 
      const int arg_one = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/ident_list_array[0],/*descendant1*/byref, arg_type); 
      return arg_one; 
    }; 
    //int arg_list = anime_type_tree__push0(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 
    int arg_list = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__NIL); 
    int * ident_token_ptr = ident_list_array + ident_list_nb; 
    for (int i = 0; i < ident_list_nb; i++) { 
      ident_token_ptr--; 
      //const int arg_one = anime_type_tree__push2(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, arg_type); 
      const int arg_one = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__ONE, /*value*/*ident_token_ptr,/*descendant1*/byref, arg_type); 
      //arg_list = anime_type_tree__push1(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__CONS, /*value*/arg_one,/*descendant1*/arg_list); 
      arg_list = anime_parser_chunk_env__push(this -> type_tree_env, /*type*/ANIME_TYPE_TREE__TYPE__ARG_LIST__CONS, /*value*/arg_one,/*descendant1*/arg_list); 
    }; 

    //next_token = get_current_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    return arg_list; 
  }; // LABEL_STATE(decl__arg_one) 
#endif 
  











 LABEL_STATE(decl__local_var__one): { 
    // ident_list : type ; 
    int next_token; 
    int ident_list_nb = 0; 
    int ident_list_array[decl__arg_ident_list__size]; 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
    
    ident_list_nb = 1; 
    ident_list_array[0] = *current_token_ref; 
    next_token = get_next_token_type(); 
    if (next_token == ANIME_TOKEN_VIRGULE) { 
      for (;;) { 
	next_token = get_next_token_type(); 
	SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
	if (ident_list_nb == decl__arg_ident_list__size) { 
	  EXCEPTION__RAISE(__FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Declaring too many variables at the same time - I can handle at most ", int_string__stack(decl__arg_ident_list__size), " in one declaration. Please break down that declaration (or recompile the parser with a larger stack)."); 
	}; 
	ident_list_array[ident_list_nb] = *current_token_ref; 
	ident_list_nb++; 
	next_token = get_next_token_type(); 
	if (next_token != ANIME_TOKEN_VIRGULE) { break; }; 
      }; 
    }; 
    
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_DEUXPOINTS); 
    
    next_token = get_next_token_type(); 
    const int localvar_type = anime_parser__automaton__aux(exception_data, this, token_env, type_expr, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
#if 0     
    if (1 == ident_list_nb) { 
      //const int localvar_one = anime_decl_local_list__push2(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__ONE, /*value*/ident_list_array[0],/*descendant1*/localvar_type); 
      const int localvar_one = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__ONE, /*value*/ident_list_array[0],/*descendant1*/localvar_type); 
      return localvar_one; 
    }; 
#endif 
    //int localvar_list = anime_decl_local_list__push0(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__NIL); 
    //int localvar_list = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__NIL); 
    //int * ident_token_ptr = ident_list_array + ident_list_nb; 
    int * ident_token_ptr = ident_list_array; // + ident_list_nb; 
    //int ref_to_the_first_item_on_the_stack = -1; 
    int lvar_list = *retval1_ref; // -1; 
    for (int i = 0; i < ident_list_nb; i++) { 
      //ident_token_ptr--; 
      //const int localvar_one = anime_decl_local_list__push2(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__ONE, /*value*/*ident_token_ptr,/*descendant1*/localvar_type); 
      //const int localvar_one = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__ONE, /*value*/*ident_token_ptr,/*descendant1*/localvar_type); 
      //const int current_ref_to_the_first_item_on_the_stack = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__ONE, /*value*/*ident_token_ptr,/*descendant1*/localvar_type); 
      lvar_list = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__VARIABLE, /*value*/*ident_token_ptr,/*descendant1*/localvar_type, lvar_list); 
#if 0 
      if (ref_to_the_first_item_on_the_stack < 0) { 
	ref_to_the_first_item_on_the_stack = current_ref_to_the_first_item_on_the_stack; 
      }; 
#endif 

      //localvar_list = anime_decl_local_list__push2(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__CONS, /*value*/localvar_one,/*descendant1*/localvar_list); 
      //localvar_list = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__CONS, /*value*/localvar_one,/*descendant1*/localvar_list); 
      ident_token_ptr++; 
    }; 
    //return localvar_list; 
    //*retval1_ref = ident_list_nb; 
    //return ref_to_the_first_item_on_the_stack; 
    return lvar_list; 
  }; // LABEL_STATE(decl__local_var__one) 
  
  
  
 LABEL_STATE(decl__local_var): { 
    // VAR (ident_list : type ;) + 
    // RL: I need to return the address of the first item or the last item on the stack, and the number of items. 
    int next_token; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_VAR); 
    next_token = get_next_token_type(); 
    while (next_token == ANIME_TOKEN_VAR) { next_token = get_next_token_type(); }; 
    
    //int localvar_list = anime_decl_local_list__push0(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__NIL); 
    //int localvar_list = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__NIL); 
    //int localvar_tail = -1; 
    //int localvar_nb = 0; 
    //int ref_to_the_first_item_on_the_stack = -1; 
    int lvar_list = -1; 
    for (;;) { 
      //const int localvar_one = anime_parser__automaton__aux(exception_data, this, token_env, decl__local_var__one, current_token_ref, retval1_ref); 
      //const int current_ref_to_the_first_item_on_the_stack = anime_parser__automaton__aux(exception_data, this, token_env, decl__local_var__one, current_token_ref, retval1_ref); 
      lvar_list = anime_parser__automaton__aux(exception_data, this, token_env, decl__local_var__one, current_token_ref, &lvar_list); 
#if 0 
      localvar_nb += *retval1_ref; 
      if (ref_to_the_first_item_on_the_stack < 0) { 
	ref_to_the_first_item_on_the_stack = current_ref_to_the_first_item_on_the_stack; 
      }; 
#endif 
      
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
      //localvar_list = anime_decl_local_list__push2(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__CONS, /*value*/localvar_one,/*descendant1*/localvar_list); 
      //localvar_list = anime_parser_chunk_env__push(this -> decl_local, /*type*/ANIME_DECL_LOCAL_LIST__TYPE__LOCALVAR__CONS, /*value*/localvar_one,/*descendant1*/localvar_list); 
      
      next_token = get_next_token_type(); 
      if (next_token != ANIME_TOKEN_IDENT) { break; }; 
    }; 
    
    //return localvar_list; 
    //*retval1_ref = localvar_nb; 
    //return ref_to_the_first_item_on_the_stack; 
    return lvar_list; 
  }; // LABEL_STATE(decl__local_var) 
  
  
  
#if 0 
//#ifdef DEBUG_PARSER 
  dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">: ", "[", anime_parser_automaton_state__cstr[state], "]", " - current_token: ", int_string__stack(*current_token_ref), " - next_token: ", anime_token__type_get_cstr(next_token), "(", int_string__stack(next_token), ")", "\n"); 
#endif 

 LABEL_STATE(instructions__begin): { 
    // (instructions_one ; ) * 
    int next_token; 
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_BEGIN); 
    
#if 1
    //const int begin_ref = this -> inst_list_env -> memory__array_nb; 
    next_token = get_next_token_type();
    int inst_list_head = -1; 
    for (;;) { 
      //do { next_token = get_next_token_type(); } while (next_token == ANIME_TOKEN_PTVIRG); 
      while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
      if (next_token == ANIME_TOKEN_END) { 
#if 1 
	return inst_list_head; 
#else 
	*retval1_ref = this -> inst_list_env -> memory__array_nb; 
	return begin_ref; 
#endif 
      }; 
      //if (next_token == ANIME_TOKEN_EOF) { break; }; 
      
      //const int instruction_one = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
      inst_list_head = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, &inst_list_head); 
      
      next_token = get_current_token_type(); 
      //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_PTVIRG,ANIME_TOKEN_END,ANIME_TOKEN_UNTIL); 
      
      //instructions_list = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__LIST__CONS, /*value1*/instruction_one, /*value2*/instructions_list); 
    }; 
    assert(false); 
    return -1; 
#else 
    int instructions_list = anime_inst_list__push0(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__LIST__NIL); 
    for (;;) { 
      next_token = get_next_token_type(); 
      while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
      if (next_token == ANIME_TOKEN_END) { break; }; 
      //if (next_token == ANIME_TOKEN_EOF) { break; }; 
      
      const int instruction_one = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
      
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
      instructions_list = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__LIST__CONS, /*value1*/instruction_one, /*value2*/instructions_list); 
    }; 
    return instructions_list; 
#endif 
  }; // LABEL_STATE(instructions__begin) 
  
  
 LABEL_STATE(instructions__expr): { 
    // GRAMMAR: expr ; 
    int next_token; 
    // RL: Issue here: there can be a lambda in the expr, therefore instructions could be pushed onto the instructions stack. 
    //     Thus, we have to push the instruction first. And then we rewrite it. 
    const int instruction_expr = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__EXPR, /*value1:expr_tree*/-1, /*inst_list_head*/*retval1_ref); 

    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
    next_token = get_current_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_PTVIRG,ANIME_TOKEN_END,ANIME_TOKEN_UNTIL); 
    //const int instruction_expr = anime_inst_list__push1(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__EXPR, /*value1*/expr_tree); 
    //const int instruction_expr = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__EXPR, /*value1*/expr_tree); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_expr, /*field_name_cstr*/"expr_tree", /*field_value*/expr_tree); 
    //next_token = get_next_token_type(); 
    return instruction_expr; 
  }; // LABEL_STATE(instructions__expr) 
  
  
 LABEL_STATE(instructions__one): { 
#if 0 
instruction:
| begin    -> direct_descendants_nb (direct descendants, not nested) 
| ifnoelse -> EXPR + if_true_direct_descendants_nb 
| ifelse   -> EXPR + if_true_direct_descendants_nb + if_false_direct_descendants_nb 
| when     -> EXPR + if_true_direct_descendants_nb 
| unless   -> EXPR + if_false_direct_descendants_nb 
| while    -> EXPR + if_true_direct_descendants_nb 
| for      -> EXPR + EXPR + if_true_direct_descendants_nb 
| repeat   -> EXPR + direct_descendants_nb 
#endif 
    int next_token; 
    
    next_token = get_current_token_type(); 
    while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 

    int next_state; 
    switch (next_token) { 
    case ANIME_TOKEN_BEGIN : next_state = instructions__begin;  break; 
    case ANIME_TOKEN_IF    : next_state = instructions__if;     break; 
    case ANIME_TOKEN_WHEN  : next_state = instructions__when;   break; 
    case ANIME_TOKEN_UNLESS: next_state = instructions__unless; break; 
    case ANIME_TOKEN_WHILE : next_state = instructions__while;  break; 
    case ANIME_TOKEN_FOR   : next_state = instructions__for;    break; 
    case ANIME_TOKEN_REPEAT: next_state = instructions__repeat; break; 
    default                  : next_state = instructions__expr;   break; 
      //SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_BEGIN, ANIME_TOKEN_IF, ANIME_TOKEN_WHEN, ANIME_TOKEN_UNLESS, ANIME_TOKEN_WHILE, ANIME_TOKEN_FOR, ANIME_TOKEN_REPEAT); 
    }; 

    const int instruction_one = anime_parser__automaton__aux(exception_data, this, token_env, next_state, current_token_ref, retval1_ref); 
    if (next_state == instructions__begin) { 
      // RL: Otherwise, the current token points to 'END', and for an instruction, it is expected to have everything eaten - a semi-colon is expected. 
      next_token = get_next_token_type(); 
    }; 
    
    return instruction_one; 
  }; // LABEL_STATE(instructions__one) 
  
  
  
 LABEL_STATE(instructions__if): { 
    // IF expr THEN inst 
    // IF expr THEN inst ELSE inst 
    int next_token; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IF); 
    
    // RL: Issue here: there can be a lambda in the expr, therefore instructions could be pushed onto the instructions stack. 
    //     Thus, we have to push the instruction first. And then we rewrite it. 
    const int instruction_if = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__IF_ELSE, /*value1*/-1, /*instruction_if_true*/-1, /*instruction_if_false*/-1, /*inst_list_head*/*retval1_ref); 

    next_token = get_next_token_type(); 
    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 

    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_if, /*field_name_cstr*/"test_expr_tree", /*field_value*/expr_tree); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_THEN); 
    
    //const int instruction_if = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__IF_ELSE, /*value1*/expr_tree, /*instruction_if_true*/-1, /*instruction_if_false*/-1); 

    next_token = get_next_token_type(); 
    *retval1_ref = -1; 
    const int instruction_if_true = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 

    next_token = get_current_token_type(); 
    while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 

    //anime_parser_chunk_env__set_field_value(this -> inst_list_env, /*chunk_offset*/instruction_if, /*field_i*/2, /*field_value*/instruction_if_true); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_if, /*field_name_cstr*/"inst_if_true", /*field_value*/instruction_if_true); 
    
    if (next_token != ANIME_TOKEN_ELSE) { 
      //const int instruction_if = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__IF_NO_ELSE, /*value1*/expr_tree, /*value2*/instruction_if_true); 
      //const int instruction_if = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__IF_NO_ELSE, /*value1*/expr_tree, /*value2*/instruction_if_true); 
      return instruction_if; 
    }; 
    
    next_token = get_next_token_type(); 
    *retval1_ref = -1; 
    const int instruction_if_false = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    //const int instruction_if = anime_inst_list__push3(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__IF_ELSE, /*value1*/expr_tree, /*value2*/instruction_if_true, /*value3*/instruction_if_false); 
    //const int instruction_if = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__IF_ELSE, /*value1*/expr_tree, /*value2*/instruction_if_true, /*value3*/instruction_if_false); 
    //anime_parser_chunk_env__set_field_value(this -> inst_list_env, /*chunk_offset*/instruction_if, /*field_i*/3, /*field_value*/instruction_if_false); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_if, /*field_name_cstr*/"inst_if_false", /*field_value*/instruction_if_false); 

    return instruction_if; 
  }; // LABEL_STATE(instructions__if) 
  
  




 LABEL_STATE(instructions__when): { 
    // WHEN expr THEN|DO inst 
    int next_token; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_WHEN); 

    // RL: Issue here: there can be a lambda in the expr, therefore instructions could be pushed onto the instructions stack. 
    //     Thus, we have to push the instruction first. And then we rewrite it. 
    const int instruction_when = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHEN, /*value1:expr_tree*/-1, /*instruction_when_true*/-1, /*inst_list_head*/*retval1_ref); 

    next_token = get_next_token_type(); 
    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 

    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_when, /*field_name_cstr*/"test_expr_tree", /*field_value*/expr_tree); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_THEN,ANIME_TOKEN_DO); 
    next_token = get_next_token_type(); 
    
    //const int instruction_when = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHEN, /*value1*/expr_tree, /*instruction_when_true*/-1); 

    *retval1_ref = -1; 
    const int instruction_when_true = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    //const int instruction_when = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHEN, /*value1*/expr_tree, /*value2*/instruction_when_true); 
    //const int instruction_when = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHEN, /*value1*/expr_tree, /*value2*/instruction_when_true); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_when, /*field_name_cstr*/"inst_if_true", /*field_value*/instruction_when_true); 

    return instruction_when; 
  }; // LABEL_STATE(instructions__when) 
  
  


 LABEL_STATE(instructions__unless): { 
    // UNLESS expr DO inst 
    int next_token; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_UNLESS); 

    // RL: Issue here: there can be a lambda in the expr, therefore instructions could be pushed onto the instructions stack. 
    //     Thus, we have to push the instruction first. And then we rewrite it. 
    const int instruction_unless = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__UNLESS, /*value1:expr_tree*/-1, /*value2: instruction_unless_false*/-1, /*inst_list_head*/*retval1_ref); 

    next_token = get_next_token_type(); 
    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_DO); 
    
    //const int instruction_unless = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__UNLESS, /*value1*/expr_tree, /*value2: instruction_unless_false*/-1); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_unless, /*field_name_cstr*/"test_expr_tree", /*field_value*/expr_tree); 
    
    next_token = get_next_token_type(); 
    *retval1_ref = -1; 
    const int instruction_unless_false = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    //const int instruction_unless = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__UNLESS, /*value1*/expr_tree, /*value2*/instruction_unless_false); 
    //const int instruction_unless = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__UNLESS, /*value1*/expr_tree, /*value2*/instruction_unless_false); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_unless, /*field_name_cstr*/"inst_if_false", /*field_value*/instruction_unless_false); 

    return instruction_unless; 
  }; // LABEL_STATE(instructions__unless) 
  
  
  
 LABEL_STATE(instructions__while): { 
    // WHILE expr DO inst 
    int next_token; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_WHILE); 
    
    next_token = get_next_token_type(); 
    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_DO); 

    const int instruction_while = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHILE, /*value1*/expr_tree, /*value2: instruction_while_true*/-1, /*inst_list_head*/*retval1_ref); 

    next_token = get_next_token_type(); 
    *retval1_ref = -1; 
    const int instruction_while_true = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    //const int instruction_while = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHILE, /*value1*/expr_tree, /*value2*/instruction_while_true); 
    //const int instruction_while = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__WHILE, /*value1*/expr_tree, /*value2*/instruction_while_true); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_while, /*field_name_cstr*/"inst_if_true", /*field_value*/instruction_while_true); 

    return instruction_while; 
  }; // LABEL_STATE(instructions__while) 
  
  
  
 LABEL_STATE(instructions__repeat): { 
    // REPEAT inst* UNTIL expr 
    int next_token; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_REPEAT); 
    
#if 1 
    //const int begin_ref = this -> inst_list_env -> memory__array_nb; 

    // RL: Issue here: there can be a lambda in the expr, therefore instructions could be pushed onto the instructions stack. 
    //     Thus, we have to push the instruction first. And then we rewrite it. 
    const int instruction_repeat = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__REPEAT, /*value1*/-1, /*value2*/-1, /*inst_list_head*/*retval1_ref); 

    //int dfs_inst_nb = 0; 
    int inst_list_head = -1; 
    next_token = get_next_token_type(); 
    //int end_ref; 
    for (;;) { 
      //do { next_token = get_next_token_type(); } while (next_token == ANIME_TOKEN_PTVIRG); 
      while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
      if (next_token == ANIME_TOKEN_UNTIL) { 
	//end_ref = this -> inst_list_env -> memory__array_nb; 
	//return begin_ref; 
	break; 
      }; 
      //const int instruction_one = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
      inst_list_head = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, &inst_list_head); 
      
      //dfs_inst_nb++; 
      
      next_token = get_current_token_type(); 
      //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_PTVIRG,ANIME_TOKEN_UNTIL); 
    };

    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_UNTIL); 
    
    next_token = get_next_token_type(); 
    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    //SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_PTVIRG,ANIME_TOKEN_END,ANIME_TOKEN_UNTIL); 
    
    //const int instruction_repeat = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__REPEAT, /*value1*/expr_tree, /*value2*/begin_ref); 
    //const int instruction_repeat = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__REPEAT, /*value1*/expr_tree, /*value2*/begin_ref); 

    //return instruction_repeat; 

    //const int end_ref = this -> inst_list_env -> memory__array_nb; 

    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_repeat, /*field_name*/"test_expr_tree", /*field_value*/expr_tree); 
    //anime_parser_chunk_env__set_field_value(this -> inst_list_env, /*chunk_offset*/instruction_repeat, /*field_i*/2, /*field_value*/dfs_inst_nb); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_repeat, /*field_name*/"inst", /*field_value*/inst_list_head); 
    //anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_repeat, /*field_name*/"inst_list_head", /*field_value*/inst_list_head); 

    return instruction_repeat; 
#else 
    int instructions_list = anime_inst_list__push0(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__LIST__NIL); 
    for (;;) { 
      next_token = get_next_token_type(); 
      while (next_token == ANIME_TOKEN_PTVIRG) { next_token = get_next_token_type(); }; 
      if (next_token == ANIME_TOKEN_UNTIL) { break; }; 
      
      const int instruction_one = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
      
      next_token = get_current_token_type(); 
      SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
      
      instructions_list = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__LIST__CONS, /*value1*/instruction_one, /*value2*/instructions_list); 
    }; 
    
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_UNTIL); 
    
    next_token = get_next_token_type(); 
    const int expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    const int instruction_repeat = anime_inst_list__push2(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__REPEAT, /*value1*/expr_tree, /*value2*/instructions_list); 
    return instruction_repeat; 
#endif 
  }; // LABEL_STATE(instructions__repeat) 
  



 LABEL_STATE(instructions__for): { 
    // FOR ident = expr to expr [step expr] DO inst 
    // FOR ident = expr downto expr [step expr] DO inst 
    int next_token; 
    int downto = false; 

    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_FOR); 

    next_token = get_next_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_IDENT); 
    const int ident_token = *current_token_ref; 
    
    next_token = get_next_token_type(); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token,ANIME_TOKEN_AFFECTATION, ANIME_TOKEN_AFFECTATION_SIMPLE); 
    
    // RL: Issue here: there can be a lambda in the expr, therefore instructions could be pushed onto the instructions stack. 
    //     Thus, we have to push the instruction first. And then we rewrite it. 
    const int instruction_for = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__FOR, /*value1*/ident_token, /*init_expr_tree*/-1, /*downto*/false, /*final_expr_tree*/-1, /*step_expr_tree*/-1, /*instruction_for_true*/-1, /*inst_list_head*/*retval1_ref); 
    
    next_token = get_next_token_type(); 
    const int init_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 

    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_for, /*field_name_cstr*/"init_expr", /*field_value*/init_expr_tree); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_TO, ANIME_TOKEN_DOWNTO); 
    
    if (next_token == ANIME_TOKEN_DOWNTO) { 
      downto = true; 
    }; 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_for, /*field_name_cstr*/"downto_huh", /*field_value*/downto); 
    
    next_token = get_next_token_type(); 
    const int final_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 

    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_for, /*field_name_cstr*/"final_expr", /*field_value*/final_expr_tree); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_ONE_OF_THESE_TOKENS(next_token, ANIME_TOKEN_DO, ANIME_TOKEN_STEP); 
    
    int step_expr_tree = -1; 
    if (next_token == ANIME_TOKEN_STEP) { 
      next_token = get_next_token_type(); 
      step_expr_tree = anime_parser__automaton__aux(exception_data, this, token_env, expr, current_token_ref, retval1_ref); 
      next_token = get_current_token_type(); 
      anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_for, /*field_name_cstr*/"step_expr", /*field_value*/step_expr_tree); 
    }; 
    
    assert(next_token == ANIME_TOKEN_DO); 
    
    //const int instruction_for = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__FOR, /*value1*/ident_token, init_expr_tree, downto, final_expr_tree, step_expr_tree, /*instruction_for_true*/-1); 
    
    
    next_token = get_next_token_type(); 
    *retval1_ref = -1; 
    const int instruction_for_true = anime_parser__automaton__aux(exception_data, this, token_env, instructions__one, current_token_ref, retval1_ref); 
    
    next_token = get_current_token_type(); 
    SYNTAX__EXPECTING_THIS_TOKEN(next_token,ANIME_TOKEN_PTVIRG); 
    
    //const int instruction_for = anime_inst_list__push6(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__FOR, /*value1*/ident_token, init_expr_tree, downto, final_expr_tree, step_expr_tree, /*value2*/instruction_for_true); 
    //const int instruction_for = anime_parser_chunk_env__push(this -> inst_list_env, /*type*/ANIME_INST_LIST__TYPE__FOR, /*value1*/ident_token, init_expr_tree, downto, final_expr_tree, step_expr_tree, /*value2*/instruction_for_true); 
    anime_parser_chunk_env__set_field_value_by_name(this -> inst_list_env, /*chunk_offset*/instruction_for, /*field_name_cstr*/"inst_if_true", /*field_value*/instruction_for_true); 
    
    return instruction_for; 
  }; // LABEL_STATE(instructions__for) 
  
  
  
  
  
  
  
#endif 
  
  assert(false); 
  
  return -1; 
}; 




#if 0 
static int anime_parser__parenthesis[] = { 
  ANIME_TOKEN_BEGIN,       ANIME_TOKEN_END, 
  ANIME_TOKEN_OPENPAR,     ANIME_TOKEN_CLOSEPAR, 
  ANIME_TOKEN_OPENBRACKET, ANIME_TOKEN_CLOSEBRACKET, 
  ANIME_TOKEN_REPEAT,      ANIME_TOKEN_UNTIL, 
  ANIME_TOKEN_RECORD,      ANIME_TOKEN_END 
}; 
enum { anime_parser__parenthesis__size = ARRAY_SIZE(anime_parser__parenthesis) }; 
#else 
static int anime_parser__parenthesis__opening[] = { 
  ANIME_TOKEN_BEGIN,       
  ANIME_TOKEN_OPENPAR, 
  ANIME_TOKEN_OPENBRACKET, 
  ANIME_TOKEN_REPEAT, 
  ANIME_TOKEN_RECORD, 
  ANIME_TOKEN_OPENBRACE 
}; 
enum { anime_parser__parenthesis__opening__size = ARRAY_SIZE(anime_parser__parenthesis__opening) }; 

static int anime_parser__parenthesis__closing[] = { 
  ANIME_TOKEN_END, 
  ANIME_TOKEN_CLOSEPAR, 
  ANIME_TOKEN_CLOSEBRACKET, 
  ANIME_TOKEN_UNTIL, 
  ANIME_TOKEN_END, 
  ANIME_TOKEN_CLOSEBRACE 
}; 
enum { anime_parser__parenthesis__closing__size = ARRAY_SIZE(anime_parser__parenthesis__closing) }; 

static void assert_compile__dakjdds438sd(void) { 
  ASSERT_COMPILE(anime_parser__parenthesis__opening__size == anime_parser__parenthesis__closing__size); 
}; 
#endif

enum { anime_parser__parenthesis__stack_size = 48 }; // RL: Nestedness. 

extern int anime_parser__parenthesis__check(const anime_token_env_t * token_env) { 
  int paren_stack[anime_parser__parenthesis__stack_size]; 
  int paren_nb = 0; 
  const int token_nb = anime_token__get_count(token_env); 
  for (int token_i = 0; token_i < token_nb; token_i++) { 
    const int token_type = anime_token__get_type(token_env, token_i); 
    if (int_member_array(token_type, anime_parser__parenthesis__opening)) { 
      if (paren_nb >= anime_parser__parenthesis__stack_size) { 
	const char * srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); 
	const char * srcval_cstr = anime_token__get_srcval_cstr(token_env, token_i); 
	const int line1 = anime_token__get_line1(token_env, token_i); 
	const int column0 = anime_token__get_column0(token_env, token_i); 
	dputs_array(stderr__fileno, 
#ifdef DEBUG_PARSER 
		    "{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:token ", anime_token__type_get_cstr(token_type), "(", int_string__stack(token_type),")", "}:", 
#endif 
		    srcfile_cstr, ":", int_string__stack(line1), ":", int_string__stack(column0), ": ", "Nestedness is too large for the stack parser. Please un-nest your program or recompile the parser with a larger stack (opening token '", srcval_cstr, "')", ".", "\n"); 
	return (INT_MIN | token_i); 
      }; 
      paren_stack[paren_nb] = token_i; 
      paren_nb++; 
      continue; 
    }; 
    if (int_member_array(token_type, anime_parser__parenthesis__closing)) { 
      int closing_paren_i = 0; while (token_type != anime_parser__parenthesis__closing[closing_paren_i]) { closing_paren_i++; }; 
      const int expected_opening_type = anime_parser__parenthesis__opening[closing_paren_i]; 
      if (paren_nb <= 0) { 
	const char * srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); 
	const char * srcval_cstr = anime_token__get_srcval_cstr(token_env, token_i); 
	const int line1 = anime_token__get_line1(token_env, token_i); 
	const int column0 = anime_token__get_column0(token_env, token_i); 
	dputs_array(stderr__fileno, 
#ifdef DEBUG_PARSER 
"{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:token ", anime_token__type_get_cstr(token_type), "(", int_string__stack(token_type),")", "}:", 
#endif 
		    srcfile_cstr, ":", int_string__stack(line1), ":", int_string__stack(column0), ": ", "Token '", srcval_cstr, "' is a closing token and does not have any matching opening token; there should be a ", anime_token__type_get_cstr(expected_opening_type), " token before this one.", "\n"); 
	return (INT_MIN | token_i); 
      }; 
      paren_nb--; 
      const int opening_token_i = paren_stack[paren_nb]; 
      const int actual_opening_type = anime_token__get_type(token_env, opening_token_i); 
      int opening_paren_i = 0; while (actual_opening_type != anime_parser__parenthesis__opening[opening_paren_i]) { opening_paren_i++; }; 
//#ifdef DEBUG_PARSER 
#if 0 
      dputs_array(stderr__fileno, "{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:token ", int_string__stack(opening_token_i), ": ", anime_token__type_get_cstr(actual_opening_type), "(", int_string__stack(actual_opening_type),")", "}:", "'opening_paren_i' = ", int_string__stack(opening_paren_i), "\n");
#endif 
      const int expected_closing_type = anime_parser__parenthesis__closing[opening_paren_i]; 
      //if (actual_opening_type != expected_opening_type) { 
      if (token_type != expected_closing_type) { 
	const char * opening_srcfile_cstr = anime_token__get_srcfile_cstr(token_env, opening_token_i); 
	const char * opening_srcval_cstr = anime_token__get_srcval_cstr(token_env, opening_token_i); 
	const int opening_line1 = anime_token__get_line1(token_env, opening_token_i); 
	const int opening_column0 = anime_token__get_column0(token_env, opening_token_i); 
	const char * closing_srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); 
	const char * closing_srcval_cstr = anime_token__get_srcval_cstr(token_env, token_i); 
	const int closing_line1 = anime_token__get_line1(token_env, token_i); 
	const int closing_column0 = anime_token__get_column0(token_env, token_i); 
	dputs_array(stderr__fileno, 
#ifdef DEBUG_PARSER 
"{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:token ", anime_token__type_get_cstr(token_type), "(", int_string__stack(token_type),")", "}:", 
#endif 
		    opening_srcfile_cstr, ":", int_string__stack(opening_line1), ":", int_string__stack(opening_column0), ": ", "Opening token '", opening_srcval_cstr, "' and closing token '", closing_srcval_cstr, "' (", (opening_srcfile_cstr == closing_srcfile_cstr ? "" : closing_srcfile_cstr), ":", int_string__stack(closing_line1), ":", int_string__stack(closing_column0), ") do not match. The closing token should have been a ", anime_token__type_get_cstr(expected_closing_type), ".", "\n"); 
	return (INT_MIN | token_i); 
      }; 
      
      continue; 
    }; 
  }; 
  
  if (paren_nb == 0) { return 0; }; 
  
  
   dputs_array(stderr__fileno, 
#ifdef DEBUG_PARSER 
	      "{", __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">", "}:", 
#endif
	      "There are ", int_string__stack(paren_nb), " opening tokens without any matching closing tokens:", "\n"); 
  for (int i = 0; i < paren_nb; i++) { 
    const int token_i = paren_stack[i]; 
    const int token_type = anime_token__get_type(token_env, token_i); 
    int opening_paren_i = 0; while (token_type != anime_parser__parenthesis__opening[opening_paren_i]) { opening_paren_i++; }; 
    const int expected_closing_type = anime_parser__parenthesis__closing[opening_paren_i]; 
    const char * opening_srcfile_cstr = anime_token__get_srcfile_cstr(token_env, token_i); 
    const char * opening_srcval_cstr = anime_token__get_srcval_cstr(token_env, token_i); 
    const int opening_line1 = anime_token__get_line1(token_env, token_i); 
    const int opening_column0 = anime_token__get_column0(token_env, token_i); 
    dputs_array(stderr__fileno, "\t", opening_srcfile_cstr, ":", int_string__stack(opening_line1), ":", int_string__stack(opening_column0), ": ", "Opening token '", opening_srcval_cstr, "' needs a ", anime_token__type_get_cstr(expected_closing_type), " closing token.", "\n"); 
  }; 
  return (INT_MIN | *paren_stack); 
}; 
 
 

extern int anime_parser__automaton(anime_parser_env_t * this, const anime_token_env_t * token_env); 


enum { anime_parser__automaton__exception_data_size = sizeof(sigjmp_buf) + (1 << 9) }; 
int anime_parser__automaton(anime_parser_env_t * this, const anime_token_env_t * token_env) { 
  int current_token = -1; 
  int retval1; 
  char exception_data[anime_parser__automaton__exception_data_size]; 
  *((int16_t*) exception_data + 0) = sizeof(exception_data); 
  *((int16_t*) exception_data + 2) = sizeof(sigjmp_buf); 
  sigjmp_buf * setjmp_env_ptr = (sigjmp_buf *) (exception_data + 4); 
  const int setjmp_value = sigsetjmp(*setjmp_env_ptr, 0); 
  if (0 == setjmp_value) { 
    this -> anime_tree_env -> filled_huh = -11; 
    const int last_topdecl_chunk_offset = anime_parser__automaton__aux(exception_data, this, token_env, ANIME_PARSER__AUTOMATON_STATE__START, /*current_token_ref*/&current_token, /*retval1_ref*/&retval1); 
    this -> anime_tree_env -> filled_huh = 1; 
    return last_topdecl_chunk_offset; 
  } 
  else { 
    // RL: An exception was raised. 
    // RL: Basically, syntax error. 
    //dputs_array(stderr__fileno, __FILE__ ":" STRINGIFY(__LINE__) ":<",__func__, ">:", "[", anime_parser_automaton_state__cstr[state], "]: ", "Unexpected token ", int_string__stack(next_token), " - I was expecting a name to identify the currently being defined constant value.", "\n"); return -1; 
    const char * msg = (const char *) (exception_data + 4 + sizeof(sigjmp_buf)); 
    dputs(stderr__fileno, msg); 
    dput_eol(stderr__fileno); 
    return setjmp_value; 
  }; 
  return -1; 
}; 














