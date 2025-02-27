#ifndef ANIME_LEXER_MODULE_H
#define ANIME_LEXER_MODULE_H

#include "anime_lexer_module_token_type.hi"


extern int_anime_error_t anime__lexer__fill_from_fd(anime_t * this, const int input_fd); 

extern void anime__lexeme__print_all(const anime_t * this, const int stdout_d); 

extern void anime__lexer__check_and_assert(void); 

#endif /* ANIME_LEXER_MODULE_H */
