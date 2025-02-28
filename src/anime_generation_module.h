#ifndef ANIME_GENERATION_MODULE_H
#define ANIME_GENERATION_MODULE_H

extern int_anime_error_t anime__generation__arity__compute(anime_t * this); 

extern int_anime_error_t anime__generation__field_names__compute(anime_t * this); 

extern int_anime_error_t anime__generation__field_values__compute(anime_t * this); 

extern void anime__generation__check_and_assert(void); 

#endif /* ANIME_GENERATION_MODULE_H */
