#include "anime_global.h"
#include "anime.h"
#include "anime_token.h"
#include "anime_token_type.h"
#include "anime_token_input_buffering.h"
#include "anime_token_parser.h"
#include "anime_data_generation_001_from_tokens.h"




#define CHECK_IDENT(_ident_) {						\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type(token_env, token_i);		\
    srcval = anime_token__get_srcval_cstr(token_env, token_i);		\
    if (ANIME_TOKEN_IDENT != token_type) { error__expected_token_type = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type; }; \
    if (0 != strcasecmp((_ident_), srcval)) { error__expected_token_value = (_ident_); goto error_label__non_matching_token_value;  }; \
    token_i++;								\
  }; 

#define CHECK_SUGAR(_expected_token_type_) {			       \
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type(token_env, token_i);	       \
    if ((_expected_token_type_) != token_type) { error__expected_token_type = (_expected_token_type_); goto error_label__non_matching_token_type; };	       \
    token_i++;							       \
  }; 

#define LOOKAHEAD_THEN_READ_SIGN() {					\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_IMOINS == token_type) { signval = -1; token_i ++; } \
    else if (ANIME_TOKEN_RMOINS == token_type) { signval = -1; token_i ++; } \
    else { signval = 1; };						\
  };

#define READ_FLOAT() {							\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_ENTIER     == token_type) { floatval = (float) (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { floatval = (float) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { floatval = (float) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { floatval = (float) (atof(srcval)); } \
    else { error__expected_token_type = ANIME_TOKEN_REEL__DOT; goto error_label__non_matching_token_type; }; \
    if (signval < 0) floatval = -floatval;				\
    token_i++;								\
  };

#define READ_ENTIER() {							\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_ENTIER     == token_type) { intval =       (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { intval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { intval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { intval = (int) (atof(srcval)); } \
    else { error__expected_token_type = ANIME_TOKEN_ENTIER; goto error_label__non_matching_token_type; }; \
    if (signval < 0) intval = -intval;					\
    token_i++;								\
  };

#define READ_BOOLEEN() {						\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
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
    token_i++;								\
  };

#define READ_IDENT() {						   \
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i); \
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if (ANIME_TOKEN_IDENT != token_type) { error__expected_token_type = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type; }; \
    identval = srcval;						   \
    token_i++;							   \
  }; 

#define READ_STRING() {						   \
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i); \
    srcval     = anime_token__get_srcval_cstr(token_env, token_i); \
    if (ANIME_TOKEN_STRING_C != token_type) { error__expected_token_type = ANIME_TOKEN_STRING_C; goto error_label__non_matching_token_type; }; \
    strval = srcval;						   \
    token_i++;							   \
  }; 

#define LOOKAHEAD_IDENT(_ident_) {					\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    lookahead_match_huh = (ANIME_TOKEN_IDENT == token_type) && (0 == strcasecmp((_ident_), srcval)); \
  }; 

#define LOOKAHEAD_SUGAR(_expected_token_type_) {			\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    lookahead_match_huh = ((_expected_token_type_) == token_type);	\
  }; 

 


int anime_data_generation_001_from_tokens(const anime_token_env_t * token_env, anime_t * anime_data) { 
  if (NULL ==  token_env) { return ANIME__DATA_GENERATION__NULL_TOKEN_ENV ; }; 
  if (NULL == anime_data) { return ANIME__DATA_GENERATION__NULL_ANIME_DATA; }; 
  int token_i = 0; 
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
  
  anime__bzero(anime_data); 
  anime_data -> filled_huh = -1; 

  if (0 >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; 
  anime_data -> filename = anime__strcopy(anime_data, anime_token__get_srcfile_cstr(token_env, 0)); 
  
  do { 
    CHECK_IDENT("physique"); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
      CHECK_IDENT("zone"); CHECK_IDENT("de"); CHECK_IDENT("choc"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	CHECK_IDENT("longueur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> choc_longueur = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("largeur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> choc_largeur  = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("hauteur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> choc_hauteur  = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("masse"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> masse = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
    
 
    CHECK_IDENT("gameplay"); 
    CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
      CHECK_IDENT("points"    ); CHECK_IDENT("de"); CHECK_IDENT("vie"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_ENTIER(); anime_data -> vie = intval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("invincible"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_BOOLEEN(); anime_data -> invincible = boolval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("hostile"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_BOOLEEN(); anime_data -> hostile    = boolval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      
      
      
    CHECK_IDENT("graphique"); 
    CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 

      for (;;) { 
	LOOKAHEAD_IDENT("membre"); 
	if (!(lookahead_match_huh)) { break; }; 
      
	token_i++; 
	if (anime_data -> membres_nb >= anime_membres_size) { break; }; 
	READ_IDENT(); anime_data -> membres_nom[anime_data -> membres_nb] = anime__strcopy(anime_data, identval); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	  CHECK_IDENT("fils"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("image"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> membres_image[anime_data -> membres_nb] = anime__strcopy(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("largeur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> membres_largeur[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("hauteur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> membres_hauteur[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("angle"); CHECK_IDENT("max"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> membres_angle_max_y[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	anime_data -> membres_nb ++; 
      }; 

#if 0 
      fprintf(stderr, "token_type = %s" "\n", anime_token__type_get_cstr(anime_token__get_type(token_env, token_i))); 
      fprintf(stderr, "token_value = %s" "\n", anime_token__get_srcval_cstr(token_env, token_i)); 
      fprintf(stderr, "lookahead_match_huh = %s" "\n", lookahead_match_huh ? "true" : "false"); 
      fprintf(stderr, "HERE" "\n"); 
#endif 
      
    CHECK_IDENT("membres"); CHECK_IDENT("racines"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); 
    LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); 
    if (!(lookahead_match_huh)) { 
      for (;;) { 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_OPENBRACE); 
	if (!(lookahead_match_huh)) { break; }; 
	token_i++; { 
	  if (anime_data -> racines_nb >= anime_racines_size) { break; }; 
	  CHECK_IDENT("qui"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_IDENT(); anime_data -> racines_qui[anime_data -> racines_nb] = anime__strcopy(anime_data, identval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("x"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_x[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("y"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_y[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("z"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_z[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("angle"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_angle_y[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	anime_data -> racines_nb ++; 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG ); if (lookahead_match_huh) { token_i++; break; }; 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_VIRGULE); if (lookahead_match_huh) { token_i++; continue; }; 
	break; 
      }; 
    }; 
    
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      
    if (token_i < anime_token__get_count(token_env)) { goto error_too_many_tokens; }; 
      
    success_huh = true; 
    anime_data -> filled_huh = 2; 
  } while (false); 

  return success_huh ? ANIME__OK : ~0; 


error_not_enough_tokens: { 
    //const int token_count_left = anime_token__get_count(token_env) - token_i; 
    anime_data -> error_id = ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS; 
    const int error_location_len = token_i <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i - 1), anime_token__get_line1(token_env, token_i - 1), anime_token__get_column0(token_env, token_i - 1)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "End-of-file reached, while parsing not completed"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
}; 

error_too_many_tokens: { 
    const int token_count_left = anime_token__get_count(token_env) - token_i; 
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




