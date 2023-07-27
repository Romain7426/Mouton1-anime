#include "anime_global.h"
#include "anime.h"
#include "anime_token_type.h"
#include "anime_token.h"
#include "anime_token_automata.h"
#include "anime_token_input_buffering.h"
#include "anime_token_parser.h"

//#define VLA__YES
//#define ALLOCA__YES
#define LOCAL_ALLOCA__YES

#define LOCAL_ALLOCA__DECLARE(LOCAL_ALLOCA_SIZEOF)			\
  enum { LOCAL_ALLOCA__BYTE_SIZE = (LOCAL_ALLOCA_SIZEOF) }; char local_alloca__mem[LOCAL_ALLOCA__BYTE_SIZE]; int16_t local_alloca__left = LOCAL_ALLOCA__BYTE_SIZE; int16_t local_alloca__used = 0; int16_t local_alloca__requested; 

#define LOCAL_ALLOCA(REQUESTED_SIZEOF)					\
  (local_alloca__requested = (REQUESTED_SIZEOF), (local_alloca__requested > local_alloca__left ? NULL : (local_alloca__left -= local_alloca__requested, local_alloca__used += local_alloca__requested,  local_alloca__mem + local_alloca__used - local_alloca__requested))) 

// =================================================================================================== 
// LEXING / TOKENIZATION 

int_anime_error_t anime_token__parser(anime_token_env_t * token_env, anime_token_input_env_t * input_env, const int input_i, int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str) { 
  LOCAL_ALLOCA__DECLARE(1 << 14); 
  if (NULL == error_id_r) { return ANIME__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = ANIME__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  if (NULL ==  input_env) { *error_id_r = ANIME__NULL_INPUT_ENV         ; snprintf(error_str, error_size, "input_env argument is null."); return *error_id_r; }; 
  if (NULL ==  token_env) { *error_id_r = ANIME__NULL_TOKEN_ENV         ; snprintf(error_str, error_size, "token_env argument is null."); return *error_id_r; }; 
  const int stdlog_d = anime_token__parser__stdlog(token_env); 
  
  int      recognizing_automaton_index; 
  int      current_prefix_total_length; 
  int      current_prefix_length_recognized; 
#ifdef VLA__YES
  int8_t   lexer_automata_states[anime_token_automata__size]; // VLA makes «-fstack-protector» fails. 
  //enum { lexer_automata_states__sizeof = sizeof(lexer_automata_states) }; 
  const int16_t lexer_automata_states__sizeof = sizeof(lexer_automata_states); 
#elif defined ALLOCA__YES
  //enum { lexer_automata_states__sizeof = (sizeof(int8_t)) * anime_token_automata__size }; 
  const int16_t lexer_automata_states__sizeof = (sizeof(int8_t)) * anime_token_automata__size; 
  int8_t * lexer_automata_states = alloca(lexer_automata_states__sizeof); 
#elif defined LOCAL_ALLOCA__YES
  const int16_t lexer_automata_states__sizeof = (sizeof(int8_t)) * anime_token_automata__size; 
  int8_t * lexer_automata_states = LOCAL_ALLOCA(lexer_automata_states__sizeof); 
#endif 
  //int8_t   lexer_automata_states[255]; 
  
  const char * input_filename_cstr = anime_token_input__get_filename_cstr(input_env); 
  
  int offset0 = 0; 
  int line1 = 1; 
  int line1_offset0 = 0; 
  
  int c; 
  int error_var__recognized_token_type; 
  
  recognizing_automaton_index = -1; 
  current_prefix_total_length = 0; 
  current_prefix_length_recognized = 0; 
  bzero(lexer_automata_states, lexer_automata_states__sizeof); 
  
  for (;;) { 
    c = anime_token_input__getc(input_env); 
#if 0 
    if (stdlog_d > 0) dprintf(stdlog_d, "read char = %X [%c]" "\n", c, c); 
#endif 
    if (0 > c && c != EOF) { goto error_label__error_while_reading_the_input_stream; }; 
    if (EOF != c) current_prefix_total_length++; 
    
    int at_least_one_alive = -1; 
    if ('\n' == c && 1 != current_prefix_total_length) { 
      // RL: Line discipline => newline char should be part of no token, except TOKEN_EOL. 
      at_least_one_alive = -1; 
    }
    else { 
      // Moving forward each automata. 
      for (int i = 0; i < anime_token_automata__size; i++) { 
	lexer_automata_states[i] = anime_token_automata__read_symbol(anime_token_automata, i, lexer_automata_states[i], c); 
      }; 
      
      // Is there one in a final state? 
      for (int i = 0; i < anime_token_automata__size; i++) { 
	if (ANIME_TOKEN_AUTOMATA__FINAL_STATE_BASE > lexer_automata_states[i]) continue; 
	recognizing_automaton_index = i; 
	current_prefix_length_recognized = current_prefix_total_length; 
	break; 
      }; 
      
      // Is there at least one automaton still alive? 
      for (int i = 0; i < anime_token_automata__size; i++) { 
	if (0 > lexer_automata_states[i]) continue; 
	at_least_one_alive = i; 
	break; 
      }; 
    }; 
    
    if (at_least_one_alive >= 0) { 
      if ('\n' != c) { 
	continue; 
      }; 
    }; 
    
    
    if (-1 == recognizing_automaton_index) { goto error_label__token_matches_no_pattern; }; 
    
    // RL: Something was recognized. 
    const int recognized_token_type = anime_token_automata__get_token_type(/*automata*/anime_token_automata, /*automaton_i*/recognizing_automaton_index); 
    
    // RL: First, the EOF token. 
    if (ANIME_TOKEN_EOF == recognized_token_type) { 
      // Pushing an EOF Token. 
      const int    token_type    = recognized_token_type ; 
      const char * srcval_rstr   = anime_token_input__get_srcval_rstr(input_env); 
      const int    srcval_len    = anime_token_input__get_srcval_len (input_env); 
      const int    input_line1   = anime_token_input__get_line1(input_env); 
      const int    input_column0 = anime_token_input__get_column0(input_env); 
      const int    token_index   = anime_token__push(token_env, srcval_len, srcval_rstr, token_type, input_filename_cstr, offset0, input_line1, input_column0); 
      if (0 > token_index) { goto error_label__stack_overflow; }; 
      *error_id_r = ANIME__OK; 
      *error_str = '\0'; 
      return *error_id_r; 
    }; 
    
    const int nb_chars_to_push_back = (current_prefix_total_length - current_prefix_length_recognized); 
    anime_token_input__move_backward(input_env, nb_chars_to_push_back); 
    
    // RL: Second, the error tokens. 
    if (int_member_huh(recognized_token_type,ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF,ANIME_TOKEN_STRING_C__EOL, ANIME_TOKEN_STRING_C__EOF, ANIME_TOKEN_STRING_P__EOL, ANIME_TOKEN_STRING_P__EOF,ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__LONELY_ENDING)) { error_var__recognized_token_type = recognized_token_type; goto error_label__error_token; }; 
    
    // RL: Third, the to-be-skipped tokens. 
    static const int to_be_skipped[] = { ANIME_TOKEN_BLANC, ANIME_TOKEN_EOF, ANIME_TOKEN_EOL, ANIME_TOKEN_COMMENT__ONE_LINE_CPP, ANIME_TOKEN_COMMENT__ONE_LINE_SCRIPT, ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE, ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF };  
    const int should_be_skipped_huh = int_member_array(recognized_token_type, to_be_skipped); 
    if (should_be_skipped_huh) { 
      offset0 += current_prefix_length_recognized; 
      if (ANIME_TOKEN_EOL == recognized_token_type) { 
	line1++; 
	line1_offset0 = offset0; 
      }; 
      anime_token_input__validate(input_env); 
      recognizing_automaton_index = -1; 
      current_prefix_total_length = 0; 
      current_prefix_length_recognized = 0; 
      bzero(lexer_automata_states, lexer_automata_states__sizeof); 
      continue; 
    }; 
    
    // RL: Fourth, the user-defined tokens. 
    int master_token_type = -1; 
    if (ANIME_TOKEN_SYNTAX_MASTER == recognized_token_type) { 
      const int      master__nb   = anime_token__master_count(token_env); 
      const int  *   master__len  = anime_token__master_len  (token_env); 
      const char * * master__cstr = anime_token__master_cstr (token_env); 
      master_token_type  = anime_token_automaton__get__master(master__nb, master__len, master__cstr, current_prefix_length_recognized); 
      master_token_type += ANIME_TOKEN__SYNTAX_MASTER__BASE; 
    }; 
    
    int keyword_token_type = -1; 
    if (ANIME_TOKEN_SYNTAX_KEYWORD == recognized_token_type) { 
      const int      keyword__nb   = anime_token__syntax_keyword_count(token_env); 
      const int  *   keyword__len  = anime_token__syntax_keyword_len  (token_env); 
      const char * * keyword__cstr = anime_token__syntax_keyword_cstr (token_env); 
      keyword_token_type  = anime_token_automaton__get__master(keyword__nb, keyword__len, keyword__cstr, current_prefix_length_recognized); 
      keyword_token_type += ANIME_TOKEN__SYNTAX_KEYWORD__BASE; 
    }; 
    
    
    // RL: Finally, the generic tokens. 
    const int    token_type    = master_token_type >= 0 ? master_token_type : keyword_token_type >= 0 ? keyword_token_type : recognized_token_type ; 
    const char * srcval_rstr   = anime_token_input__get_srcval_rstr(input_env); 
    const int    srcval_len    = anime_token_input__get_srcval_len (input_env); 
    const int    input_line1   = anime_token_input__get_line1(input_env); 
    const int    input_column0 = anime_token_input__get_column0(input_env); 
    const int    token_index   = anime_token__push(token_env, srcval_len, srcval_rstr, token_type, input_filename_cstr, offset0, input_line1, input_column0); 
    if (0 > token_index) { goto error_label__stack_overflow; }; 
    anime_token_input__validate(input_env); 
    offset0 += current_prefix_length_recognized; 
    recognizing_automaton_index = -1; 
    current_prefix_total_length = 0; 
    current_prefix_length_recognized = 0; 
    bzero(lexer_automata_states, lexer_automata_states__sizeof); 
    continue; 
  }; 
  

  error_label__error_while_reading_the_input_stream: {
      *error_id_r = ANIME__TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM; 
      const char * srcval_rstr    = anime_token_input__get_srcval_rstr(input_env); 
      const int    srcval_len     = anime_token_input__get_srcval_len (input_env); 
#ifdef VLA__YES
      char srcval_cstr[srcval_len+1]; bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#elif defined ALLOCA__YES
      char * srcval_cstr = alloca(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#elif defined LOCAL_ALLOCA__YES
      char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#endif 
      snprintf(error_str, error_size, "%s:%d:%d: There was an error while reading the input stream (read char = %X [%c]): '%s'", input_filename_cstr, line1, offset0 - line1_offset0, c, c, srcval_cstr); 
      if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
      return *error_id_r; 
    }; 
  
  error_label__token_matches_no_pattern: { 
      *error_id_r = ANIME__TOKEN_PARSER__TOKEN_MATCHES_NO_PATTERN; 
      const char * srcval_rstr    = anime_token_input__get_srcval_rstr(input_env); 
      const int    srcval_len     = anime_token_input__get_srcval_len (input_env); 
#ifdef VLA__YES
      char srcval_cstr[srcval_len+1]; bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0';  
#elif defined ALLOCA__YES
     char * srcval_cstr = alloca(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#elif defined LOCAL_ALLOCA__YES
      char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#endif 
      snprintf(error_str, error_size, "%s:%d:%d: Failure to recognize this input as a token: '%s'", input_filename_cstr, line1, offset0 - line1_offset0, srcval_cstr); 
      if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
      return *error_id_r; 
    }; 

 error_label__error_token: { 
    *error_id_r = ANIME__TOKEN_PARSER__ERROR_TOKEN; 
    const char * srcval_rstr    = anime_token_input__get_srcval_rstr(input_env); 
    const int    srcval_len     = anime_token_input__get_srcval_len (input_env); 
#ifdef VLA__YES
    char srcval_cstr[srcval_len+1]; bcopy(srcval_rstr, srcval_cstr, srcval_len); srcval_cstr[srcval_len] = '\0'; 
#elif defined ALLOCA__YES
    char * srcval_cstr = alloca(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len); srcval_cstr[srcval_len] = '\0'; 
#elif defined LOCAL_ALLOCA__YES
      char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#endif 
    for (int i = 0; i < srcval_len; i++) { if ('\n' != srcval_cstr[i]) continue; srcval_cstr[i] = '\0'; break; }; 
    const char * msg; 
    switch (error_var__recognized_token_type) { 
    default: msg = "<\?\?\?>"; break; 
    case ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF          : msg = "A starting multi-lines C-like comment (this kind of comment: /* .... */) was started, but was not closed"; break; 
    case ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__LONELY_ENDING: msg = "A multi-lines C-like comment (this kind of comment: /* .... */) ending symbol was found (this: \"*/\"), but it does not have any starting symbol matching (this: \"/*\")"; break;
    case ANIME_TOKEN_STRING_C__EOL                              : msg = "A C-string (this kind of string: \" .... \") was started, but contains a raw newline; please use the escape char '\\n' to input newline characters in a C-string"; break; 
    case ANIME_TOKEN_STRING_C__EOF                              : msg = "A C-string (this kind of string: \" .... \") was started, but was not closed"; break; 
    case ANIME_TOKEN_STRING_P__EOL                              : msg = "A P-string (this kind of string: \' .... \') was started, but contains a raw newline; please use the escape char '\\n' to input newline characters in a P-string (or use \"newline\": \"'Hello' + newline + 'world'\")"; break; 
    case ANIME_TOKEN_STRING_P__EOF                              : msg = "A P-string (this kind of string: \' .... \') was started, but was not closed"; break;  
    }; 
    snprintf(error_str, error_size, "%s:%d:%d: %s: '%s'", input_filename_cstr, line1, offset0 - line1_offset0, msg, srcval_cstr); 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_overflow: { 
    *error_id_r = ANIME__TOKEN_PARSER__STACK_OVERFLOW; 
    const char * srcval_rstr    = anime_token_input__get_srcval_rstr(input_env); 
    const int    srcval_len     = anime_token_input__get_srcval_len (input_env); 
#ifdef VLA__YES
    char srcval_cstr[srcval_len+1]; bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#elif defined ALLOCA__YES
    char * srcval_cstr = alloca(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#elif defined LOCAL_ALLOCA__YES
      char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
#endif 
    snprintf(error_str, error_size, "%s:%d:%d: Token stack overflow (this problem could be overcome in recompiling me with a bigger size for the token stack): '%s'", input_filename_cstr, line1, offset0 - line1_offset0, srcval_cstr); 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
}; 


