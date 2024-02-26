#ifndef ANIME_TOKEN_H
#define ANIME_TOKEN_H

// *********************** TOKEN ENV *********************** 

#ifndef ANIME_TOKEN_ENV_T 
#define ANIME_TOKEN_ENV_T 
struct         anime_token_env_t; 
typedef struct anime_token_env_t   anime_token_env_t; 
#endif 
extern  const  int32_t             anime_token_env__sizeof; 
extern         anime_token_env_t * anime_token_env__make    (const int stdlog_d); 
extern         anime_token_env_t * anime_token_env__make_b  (const int bsize, void * bvalue, int * used_size_ref, const int stdlog_d); 
extern         anime_token_env_t * anime_token_env__make_r  (anime_token_env_t * this, const int stdlog_d); 
extern         void                anime_token_env__delete  (anime_token_env_t * this); 
extern         void                anime_token_env__delete_r(anime_token_env_t * this); 
extern  const  char              * anime_token_env__strcopy (anime_token_env_t * this, const char * cstr); 

extern         int                 anime_token__parser__stdlog(const anime_token_env_t * this); 



// *********************** TOKEN *********************** 

typedef       uint16_t          int_anime_token_t; 
extern  const int_anime_token_t int_anime_token_max; // RL: For storage, where data should be packed (anywhere else, 'int' is good). It ensures that a token will fit into a 'int_anime_token_type_t'. 
enum { ANIME_TOKEN_I_INVALID = UINT16_MAX }; 
extern  const int_anime_token_t ANIME_TOKEN_I_INVALID__compiled_value; 
enum { ANIME_TOKEN_I_BOF = UINT16_MAX - 1 }; 
extern  const int_anime_token_t ANIME_TOKEN_I_BOF__compiled_value; 
static void anime_token__check_and_assert(void) {
  assert(ANIME_TOKEN_I_INVALID == ANIME_TOKEN_I_INVALID__compiled_value); 
  assert(ANIME_TOKEN_I_BOF     == ANIME_TOKEN_I_BOF__compiled_value); 
}; 

extern int anime_token__push(anime_token_env_t * this, const int srcval_len, const char * srcval_rstr, const int token_type, const char * srcfile, const int offset0, const int line1, const int column0); 

extern const char * anime_token__get_srcval_cstr (const anime_token_env_t * this, const int token_idx); 
extern       int    anime_token__get_type        (const anime_token_env_t * this, const int token_idx); 
extern const char * anime_token__get_srcfile_cstr(const anime_token_env_t * this, const int token_idx); 
extern       int    anime_token__get_offset0     (const anime_token_env_t * this, const int token_idx); 
extern       int    anime_token__get_line1       (const anime_token_env_t * this, const int token_idx); 
extern       int    anime_token__get_column0     (const anime_token_env_t * this, const int token_idx); 
extern       int    anime_token__get_count       (const anime_token_env_t * this); 
extern       int    anime_token__get_size        (const anime_token_env_t * this); 

extern       void   anime_token__syntax_filtering__adjust_type(anime_token_env_t * this, const int token_idx, const int adjusted_type); 

extern void anime_token__print_stats     (const int filedes, const anime_token_env_t * this); 
extern void anime_token__print_one_token (const int filedes, const anime_token_env_t * this, const int token_i); 
extern void anime_token__print_nb_tokens (const int filedes, const anime_token_env_t * this, const int token_nb); 
extern void anime_token__print_all_tokens(const int filedes, const anime_token_env_t * this); 

extern int anime_token__dump_raw   (const int filedes, const anime_token_env_t * this); 
extern int anime_token__restore_raw(const int filedes,       anime_token_env_t * this); 

extern       int      anime_token__master_push_cstr(      anime_token_env_t * this, const char * ident_cstr); 
extern       int      anime_token__master_push_pstr(      anime_token_env_t * this, const int    ident_pstr); 
extern       int      anime_token__master_count    (const anime_token_env_t * this); 
extern const int    * anime_token__master_len      (const anime_token_env_t * this); 
extern const char * * anime_token__master_cstr     (const anime_token_env_t * this); 

extern       int      anime_token__syntax_keyword_push_cstr(      anime_token_env_t * this, const char * ident_cstr); 
extern       int      anime_token__syntax_keyword_push_pstr(      anime_token_env_t * this, const int    ident_pstr); 
extern       int      anime_token__syntax_keyword_count    (const anime_token_env_t * this); 
extern const int    * anime_token__syntax_keyword_len      (const anime_token_env_t * this); 
extern const char * * anime_token__syntax_keyword_cstr     (const anime_token_env_t * this); 

#endif /* ANIME_TOKEN_H */
