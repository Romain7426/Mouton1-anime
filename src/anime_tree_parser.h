#ifndef ANIME_TREE_PARSER_H
#define ANIME_TREE_PARSER_H

#ifndef ANIME_PARSER_ENV_T 
#define ANIME_PARSER_ENV_T 
struct anime_parser_env_t; 
typedef struct anime_parser_env_t anime_parser_env_t; 
#endif 
extern const int32_t anime_parser_env__sizeof; 

extern anime_parser_env_t * anime_parser_env__make(const int stdlog_d); 
extern void anime_parser_env__delete(anime_parser_env_t * this); 

// Built 'tree_env' belongs to parser_env. 
extern const anime_tree_env_t * anime_parser_env__get_tree_env(const anime_parser_env_t * this); 

extern int anime_parser__parenthesis__check(const anime_token_env_t * token_env); 
extern int anime_parser__automaton(anime_parser_env_t * this, const anime_token_env_t * token_env); 

extern void anime_parser__print_all   (const int filedes, const anime_parser_env_t * this); 
extern void anime_parser__print_stats (const int filedes, const anime_parser_env_t * this); 
extern void anime_parser__print_pretty(const int filedes, const anime_token_env_t * token_env, const anime_parser_env_t * this); 
 
 
#endif /* ANIME_TREE_PARSER_H */

