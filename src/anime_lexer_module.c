#include "anime_global.h"
#include "anime.h"
#include "anime_type.h"
#include "anime_lexer_module.h"


//#include "anime_lexer_module_token_type.ci"
#include "anime_lexer_module_automata.ci"
#include "anime_lexer_module_print.ci"







// =================================================================================================== 
// LEXING / TOKENIZATION 

#define ANIME_LEXER__VALIDATE(one_line_start,one_line_next) {		\
    one_line_start__col0 += (one_line_next - one_line_start);		\
    one_line_start = one_line_next;					\
  }; 

#define ANIME_LEXER__PUSH_BACK(one_line_start,one_line_next,push_back_nb) { one_line_next -= (push_back_nb); assert(one_line_start <= one_line_next); }; 

int_anime_error_t anime__lexer__fill_from_fd(anime_t * this, const int input_fd) { 
  LOCAL_ALLOCA__DECLARE(int16_t,1 << 14); 
  int_anime_error_t * error_id_r = &(this -> error_id); 
  const uint16_t error_size = this -> error_size; 
  char * error_str = this -> error_str; 
  if (0     >   input_fd) { *error_id_r = ANIME__LEXER__BAD_INPUT_FD    ; snprintf(error_str, error_size, "bad input fd."); return *error_id_r; }; 
  const int stdlog_d = this -> stdlog_d; 
  // Error management 
  const char * input_filename_cstr = NULL;
  int srcval_len;
  char * srcval_rstr;
  int offset0       = 0; 
  int line1         = 1; 
  int line1_offset0 = 0; 
  int c; 
  int error_var__recognized_token_type; 
  goto label__body; 
  
#define GOTO_LABEL_ERROR(__error_label__) { srcval_len = one_line_next - one_line_start; srcval_rstr = one_line + one_line_start; goto __error_label__; }

 label__error__error_while_reading_the_input_stream: { 
    return ANIME__TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM; 
  }; 

 label__error__line_too_large: {
    return ANIME__LEXER__LINE_TOO_LARGE; 
  };
  
 error_label__error_while_reading_the_input_stream: {
    *error_id_r = ANIME__TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM; 
    char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
    snprintf(error_str, error_size, "%s:%d:%d: There was an error while reading the input stream (read char = %X [%c]): '%s'", input_filename_cstr, line1, offset0 - line1_offset0, c, c, srcval_cstr); 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
 error_label__token_matches_no_pattern: { 
    *error_id_r = ANIME__TOKEN_PARSER__TOKEN_MATCHES_NO_PATTERN; 
    char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
    snprintf(error_str, error_size, "%s:%d:%d: Failure to recognize this input as a token: '%s'", input_filename_cstr, line1, offset0 - line1_offset0, srcval_cstr); 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__error_token: { 
    *error_id_r = ANIME__TOKEN_PARSER__ERROR_TOKEN; 
    char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
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
    char * srcval_cstr = LOCAL_ALLOCA(srcval_len+1); bcopy(srcval_rstr, srcval_cstr, srcval_len);  srcval_cstr[srcval_len] = '\0'; 
    snprintf(error_str, error_size, "%s:%d:%d: Token stack overflow (this problem could be overcome in recompiling me with a bigger size for the token stack): '%s'", input_filename_cstr, line1, offset0 - line1_offset0, srcval_cstr); 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
#if 0 
    if (this -> stdlog_d > 0) { anime__lexeme__print_all(this, this -> stdlog_d); };     
#endif 
    return *error_id_r; 
  }; 

 label__body: { 
    int      recognizing_automaton_index; 
    int      current_prefix_total_length; 
    int      current_prefix_length_recognized; 
    const int16_t lexer_automata_states__sizeof = (sizeof(int8_t)) * anime_token_automata__size; 
    int8_t * lexer_automata_states = LOCAL_ALLOCA(lexer_automata_states__sizeof); 
    unsigned char one_line[ANIME_LINE_LEN_MAX]; 
    int8_t one_line_nb; 
    int8_t one_line_start; 
    int8_t one_line_next; 
    int8_t one_line_start__col0; 
  
    input_filename_cstr = anime__filename_get(this); 
      
    
    
    int token_type = -1; 
    int this_is_an_token_error_huh = false; 
    int should_be_skipped_huh = false; 
    int at_least_one_alive = -1; 
    
    // RL: INIT 
    recognizing_automaton_index = -1; 
    current_prefix_total_length = 0; 
    current_prefix_length_recognized = 0; 
    bzero(lexer_automata_states, lexer_automata_states__sizeof); 
    one_line_nb = 0; 
    one_line_start = 0; 
    one_line_next = 0; 
    one_line_start__col0 = 0; 
    goto label__lexing; 
		
    
  label__lexing__eof: { 
      *error_id_r = ANIME__OK; 
      *error_str = '\0'; 
      return *error_id_r; 
    }; 
    
  label__lexing: { 
      for (;;) { 
	for (;;) { 
	  goto label__lexing__read_one_char; label__lexing__read_one_char__ret:{}; 
	  at_least_one_alive = -1; 
	  goto label__lexing__automata_read; label__lexing__automata_read__ret:{}; 
	  if (0 > at_least_one_alive) break; 
	  if ('\n' == c) break; 
	}; 
	
	if (-1 == recognizing_automaton_index) { GOTO_LABEL_ERROR(error_label__token_matches_no_pattern); }; 
	
	token_type = -1; 
	this_is_an_token_error_huh = false; 
	should_be_skipped_huh = false; 
	goto label__lexing__a_token_was_recognized; label__lexing__a_token_was_recognized__ret:{}; 
	
	if (this_is_an_token_error_huh) { error_var__recognized_token_type = token_type; GOTO_LABEL_ERROR(error_label__error_token); }; 

	if (not(should_be_skipped_huh)) { 
 	  const int_lexeme_t token_index = anime__lexeme_stack__push(this, token_type, /*rstr*/one_line + one_line_start, /*len*/one_line_next - one_line_start, line1, one_line_start__col0, /*offset0*/line1_offset0 + one_line_start__col0); 
	  if (0 > token_index) { GOTO_LABEL_ERROR(error_label__stack_overflow); }; 
	}; 
	
	if (ANIME_TOKEN_EOF == token_type) { goto label__lexing__eof; }; 
	
	ANIME_LEXER__VALIDATE(one_line_start,one_line_next); 
	offset0 += current_prefix_length_recognized; 
	if (ANIME_TOKEN_EOL == token_type) { 
	  line1++; 
	  line1_offset0 = offset0; 
	  one_line_start__col0 = 0; 
	}; 
	recognizing_automaton_index = -1; 
	current_prefix_total_length = 0; 
	current_prefix_length_recognized = 0; 
	bzero(lexer_automata_states, lexer_automata_states__sizeof); 
	continue; 
      }; 
      assert(false); 
    };
    

    
  label__lexing__automata_read: { 
      if ('\n' == c && 1 != current_prefix_total_length) { 
	// RL: Line discipline => newline char should be part of no token, excepted TOKEN_EOL. 
	//     En conséquence, aucun automate n’a pas reconnaître EOL. 
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
      goto label__lexing__automata_read__ret;
    }; 
    

    
    
  label__lexing__a_token_was_recognized: { 
      for (;;) { 
	// RL: Something was recognized. 
	const int recognized_token_type = anime_token_automata__get_token_type(/*automata*/anime_token_automata, /*automaton_i*/recognizing_automaton_index); 
    
	// RL: First, the EOF token. 
	if (ANIME_TOKEN_EOF == recognized_token_type) { token_type = recognized_token_type; break; }; 
	  
	const int nb_chars_to_push_back = (current_prefix_total_length - current_prefix_length_recognized); 
	//anime_token_input__move_backward(input_env, nb_chars_to_push_back); 
	//one_line_next -= nb_chars_to_push_back; assert(one_line_next > one_line_start); 
	ANIME_LEXER__PUSH_BACK(one_line_start,one_line_next,nb_chars_to_push_back);
	  
	// RL: Second, the error tokens. 
	this_is_an_token_error_huh = int_member_huh(recognized_token_type,ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF,ANIME_TOKEN_STRING_C__EOL, ANIME_TOKEN_STRING_C__EOF, ANIME_TOKEN_STRING_P__EOL, ANIME_TOKEN_STRING_P__EOF,ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__LONELY_ENDING); 
	if (this_is_an_token_error_huh) { token_type = recognized_token_type; break; }; 
	  
	// RL: Third, the to-be-skipped tokens. 
	static const int to_be_skipped[] = { ANIME_TOKEN_BLANC, ANIME_TOKEN_EOF, ANIME_TOKEN_EOL, ANIME_TOKEN_COMMENT__ONE_LINE_CPP, ANIME_TOKEN_COMMENT__ONE_LINE_SCRIPT, ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE, ANIME_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF };  
	should_be_skipped_huh = int_member_array(recognized_token_type, to_be_skipped); 
	if (should_be_skipped_huh) { token_type = recognized_token_type; break; }; 

#if 1
	int master_token_type = -1; 
	int keyword_token_type = -1; 
#else
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
#endif 
	  
	// RL: Finally, the generic tokens. 
	token_type = master_token_type >= 0 ? master_token_type : keyword_token_type >= 0 ? keyword_token_type : recognized_token_type ; 
	break; 
      };
      goto label__lexing__a_token_was_recognized__ret; 
    }; 


  label__lexing__read_one_char: { 
      //*error_id_r = anime_lexer__read_one_char(input_fd, one_line, sizeof(one_line), &one_line_nb, &one_line_start, &one_line_next, &c);
      //if (ANIME__OK != *error_id) goto label__error__error_while_reading_input; 

      for (int8_t read_huh = false;;) { 
	if (read_huh) { 
	  const ssize_t read_nb = read(input_fd, one_line + one_line_next, sizeof(one_line) - one_line_next); 
	  if (-1 == read_nb) { goto label__error__error_while_reading_the_input_stream; }; 
	  if ( 0 == read_nb) { c = EOF; break; }; 
	  one_line_nb += read_nb; 
	  read_huh = false; 
	  continue; 
	}; 
	if (0 == one_line_nb) { 
	  one_line_start = 0; 
	  one_line_next  = 0; 
	  read_huh = true; 
	  continue;
	}; 
	if (one_line_next >= one_line_nb) { 
	  // RL: Rotating buffer 
	  if (0 == one_line_start) { goto label__error__line_too_large; }; 
	  bcopy(/*src*/one_line + one_line_start,/*dst*/one_line,/*len*/one_line_next - one_line_start); 
	  one_line_nb   -= one_line_start; 
	  one_line_next -= one_line_start; 
	  one_line_start = 0; 
	  read_huh = true; 
	  continue;
	};
	assert(one_line_next < one_line_nb); 
	c = one_line[one_line_next]; 
	one_line_next++; 
	break; 
      }; 

#if 0 
      if (stdlog_d > 0) dprintf(stdlog_d, "read char = %X [%c]" "\n", c, c); 
#endif 
      
      if (0 > c && c != EOF) { GOTO_LABEL_ERROR(error_label__error_while_reading_the_input_stream); }; 
      if (EOF != c) current_prefix_total_length++; 
      goto label__lexing__read_one_char__ret;
    }; 
  };
}; 


#define ANIME__TOKEN_TYPE__C
//#define ANIME__TOKEN_TYPE__TYPE_T uint8_t 
#define EXTERN extern
#include "anime_lexer_module_token_type.ci"
#undef  EXTERN
//#undef  ANIME__TOKEN_TYPE__TYPE_T
#undef  ANIME__TOKEN_TYPE__C

#define ANIME__AUTOMATA_TYPE__C
//#define ANIME__AUTOMATA_TYPE__TYPE_T int8_t 
#define EXTERN extern
#include "anime_lexer_module_automata_type.ci"
#undef  EXTERN
//#undef  ANIME__AUTOMATA_TYPE__TYPE_T
#undef  ANIME__AUTOMATA_TYPE__C




void anime__lexer__check_and_assert(void) {
  int_anime_token_type__check_and_assert(); 
  int_anime_automata_type__check_and_assert(); 
};


