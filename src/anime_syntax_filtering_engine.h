#ifndef ANIME_TOKEN_SYNTAX_FILTERING_ENGINE_H 
#define ANIME_TOKEN_SYNTAX_FILTERING_ENGINE_H 

#ifndef ANIME_SYNTAX_FILTERING_T 
#define ANIME_SYNTAX_FILTERING_T
struct anime_syntax_filtering_t; 
typedef struct anime_syntax_filtering_t anime_syntax_filtering_t; 
#endif /* ANIME_SYNTAX_FILTERING_T */

extern const int32_t                    anime_syntax_filtering__sizeof; 
extern       anime_syntax_filtering_t * anime_syntax_filtering__make     (const int stdlog_d); 
extern       anime_syntax_filtering_t * anime_syntax_filtering__make_b   (const int bsize, void * bvalue, int * used_size_ref, const int stdlog_d); 
extern       anime_syntax_filtering_t * anime_syntax_filtering__make_r   (      anime_syntax_filtering_t * this, const int stdlog_d); 
extern       void                       anime_syntax_filtering__bzero    (      anime_syntax_filtering_t * this); 
extern       void                       anime_syntax_filtering__delete   (      anime_syntax_filtering_t * this); 
extern       void                       anime_syntax_filtering__delete_r (      anime_syntax_filtering_t * this); 
extern       int_anime_error_t          anime_syntax_filtering__error_id (const anime_syntax_filtering_t * this); 
extern const char                     * anime_syntax_filtering__error_str(const anime_syntax_filtering_t * this); 
extern const char                     * anime_syntax_filtering__strcopy  (      anime_syntax_filtering_t * this, const char * cstr); 

extern int_anime_error_t anime_syntax_filtering__switch_to_lalr_mode    (      anime_syntax_filtering_t * this); 
extern int               anime_syntax_filtering__lalr_mode_completed_huh(const anime_syntax_filtering_t * this); 
extern int               anime_syntax_filtering__lalr_mode_read_all_huh (const anime_syntax_filtering_t * this); 

extern int_anime_error_t anime_syntax_filtering__get_current_token    (anime_syntax_filtering_t * this,       anime_token_env_t * token_env, int_anime_token_t * token_i_r); 
extern int_anime_error_t anime_syntax_filtering__get_next_token       (anime_syntax_filtering_t * this,       anime_token_env_t * token_env, int_anime_token_t * token_i_r); 
extern int_anime_error_t anime_syntax_filtering__skip_to_closing_paren(anime_syntax_filtering_t * this, const anime_token_env_t * token_env, int_anime_token_t * token_i_r); 
#define                  anime_syntax_filtering__move_to_next_token    anime_syntax_filtering__get_next_token 


#endif /* ANIME_TOKEN_SYNTAX_FILTERING_ENGINE_H */
