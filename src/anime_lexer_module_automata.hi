#ifndef ANIME_TOKEN_AUTOMATA_H
#define ANIME_TOKEN_AUTOMATA_H


enum { ANIME_TOKEN_AUTOMATA__TYPE__NULL, ANIME_TOKEN_AUTOMATA__TYPE__STRING, ANIME_TOKEN_AUTOMATA__TYPE__FUNCTION, ANIME_TOKEN_AUTOMATA__TYPE__MASTER, ANIME_TOKEN_AUTOMATA__TYPE__SYNTAX_KEYWORD }; 

#ifndef ANIME_TOKEN_AUTOMATA_T 
#define ANIME_TOKEN_AUTOMATA_T 
struct anime_token_automata_t; 
typedef struct anime_token_automata_t anime_token_automata_t; 
#endif  
struct anime_token_automata_t { uint8_t token_type; int8_t automata_type; int8_t value1; const char * value_ptr1; const void * automata; }; 
extern anime_token_automata_t anime_token_automata[]; 
extern const uint8_t anime_token_automata__size; 
 
enum {  ANIME_TOKEN_AUTOMATA__FINAL_STATE_BASE = (1 << 6) }; //(INT8_MAX >> 1) }; 
#define ANIME_TOKEN_AUTOMATA__STATE_FINAL_HUH(s) ((s) >= ANIME_TOKEN_AUTOMATA__FINAL_STATE_BASE)

extern  int8_t anime_token_automata__read_symbol   (const anime_token_automata_t * automata, const uint8_t automaton_i, const int8_t current_state, const int16_t char_to_be_read); 

extern uint8_t anime_token_automata__get_token_type(const anime_token_automata_t * automata, const uint8_t automaton_i); 

extern void    anime_token_automata__set_master(anime_token_automata_t * automata, const anime_token_env_t * token_env); 

extern int8_t  anime_token_automaton__get__master(const int master__nb, const int master__len[], const char * master__array[], const int8_t current_state0); 






#endif /* ANIME_TOKEN_AUTOMATA_H */
