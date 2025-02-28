#ifndef ANIME_DATA_GENERATION_004_FROM_SYNTAX_FILTERING_H 
#define ANIME_DATA_GENERATION_004_FROM_SYNTAX_FILTERING_H 
 
 
extern int_anime_error_t anime__syntax__structure_check_and_fill(anime_t * anime_data, const int stdwarning_d, const int stderror_d); 

extern int_anime_error_t anime__syntax_expr__arity__compute(anime_t * this); 

extern int_anime_error_t anime__syntax_expr__check_syntax(const anime_t * this); 

extern void anime__syntax__print(const anime_t * anime_data, const int stdprint_d);  

extern void anime__syntax__check_and_assert(void); 
 
#endif 
 
