#ifndef ANIME_LEXER_H
#define ANIME_LEXER_H


#include "anime_lexer_module_token_type.hi"


extern int_anime_error_t anime_lexer__run(anime_lexer_env_t * lexer_env, anime_token_input_env_t * input_env, const int input_i, int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str); 



#endif /* ANIME_LEXER_H */
