#ifndef ANIME_TYPE_H 
#define ANIME_TYPE_H 

enum { ANIME_ACTIONS_SIZE = 15 }; 
enum { ANIME_EVENTS_SIZE  = 15 }; 
enum { ANIME_MEMBRES_SIZE = 15 }; 
enum { ANIME_RACINES_SIZE = ANIME_MEMBRES_SIZE }; 
enum { ANIME_EVENTS_TOUS, ANIME_EVENTS_AUCUN, ANIME_EVENTS_CODE }; 

enum { ANIME__EXPRESSION_NESTEDNESS_MAX = 16 }; 
extern const uint8_t ANIME__EXPRESSION_NESTEDNESS_MAX__compiled_value; 

// Length in tokens (it means we cannot analyze expressions longer than that). 
enum { ANIME__LONGEST_INFIX_EXPRESSION = 64 }; // 2^6 = 64 — therefore, it means roughly a six-height tree (on average). 
extern const uint8_t ANIME__LONGEST_INFIX_EXPRESSION__compiled_value; 

enum { ANIME__ERROR_BUFFER_SIZE = (1 << 11) }; 
enum { ANIME__STRING_STACK_SIZE = (1 << 12) }; 
enum { ANIME__LEXEME_STACK_SIZE = (1 << 10) }; 
enum { ANIME__LEXEME_VALUE_STACK_SIZE = (1 << 12) }; 

typedef int16_t int_anime_string_t; 
typedef int16_t int_lexeme_value_t; 
typedef int16_t int_lexeme_t; 

enum { ANIME__ENDIANNESS_UNSPECIFIED = 0 }; 
enum { ANIME__ENDIANNESS_LITTLE      = 1 }; 
enum { ANIME__ENDIANNESS_BIG         = 2 }; 
enum { ANIME__ENDIANNESS_NATIVE      = 3 }; 


struct anime_t { 
  // RL: Chunks data 
  uint32_t this_bytesize; // RL: Toujours en little endian. 
  int8_t   this_typename_bytesize; 
  char     this_typename[16]; 
  uint8_t  version_major; 
  uint8_t  version_minor; 
  uint8_t  version_revision; 
  uint8_t  endianness_flag; 

  // RL: Anime data 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  int     stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  int8_t filled_huh; // Values: 
  // 0: not done 
  //-1; currently being filled
  // 1: yes and checked and consistent; 
  // 2; yes, but unchecked; 
  // 3: yes and checked, but has breaking unconsistencies; 
  // 4: yes and checked, but has non-breaking unconsistencies; 
  
  int_anime_error_t error_id; // 0: none; …<0: error; …>0: warning 
  char              error_str[ANIME__ERROR_BUFFER_SIZE]; 
  uint16_t          error_size; 
  
  char     string_stack[ANIME__STRING_STACK_SIZE]; 
  uint16_t string_stack_nb; 
  
  int_anime_string_t copyright;   
  int_anime_string_t filename; 
  
  char               lexeme_value_stack[ANIME__LEXEME_VALUE_STACK_SIZE];
  int_lexeme_value_t lexeme_value_stack__size; 
  int_lexeme_value_t lexeme_value_stack__nb; 
  
  int8_t             lexeme_stack__type   [ANIME__LEXEME_STACK_SIZE]; 
  int16_t            lexeme_stack__line1  [ANIME__LEXEME_STACK_SIZE]; 
  int8_t             lexeme_stack__col0   [ANIME__LEXEME_STACK_SIZE]; 
  int16_t            lexeme_stack__offset0[ANIME__LEXEME_STACK_SIZE]; 
  int8_t             lexeme_stack__len    [ANIME__LEXEME_STACK_SIZE]; 
  int_lexeme_value_t lexeme_stack__value  [ANIME__LEXEME_STACK_SIZE]; 
  int_lexeme_t       lexeme_stack__size; 
  int_lexeme_t       lexeme_stack__nb; 


  

  float choc_longueur;
  float choc_largeur;
  float choc_hauteur;
  float masse;
  
  int16_t vie;
  int8_t  invincible;
  int8_t  hostile;
  
  int_anime_string_t actions_array_nom                 [ANIME_ACTIONS_SIZE];
  int_anime_string_t actions_array_affichage           [ANIME_ACTIONS_SIZE];
  int_anime_string_t actions_array_icone               [ANIME_ACTIONS_SIZE];
  int_anime_string_t actions_array_gestionnaire_fichier[ANIME_ACTIONS_SIZE];
  int_anime_string_t actions_array_gestionnaire_proc   [ANIME_ACTIONS_SIZE];
  int8_t             actions_size;
  int8_t             actions_nb;
  
  int_anime_string_t events_array_nom                    [ANIME_EVENTS_SIZE]; 
  int8_t             events_array_genere_type            [ANIME_EVENTS_SIZE]; 
  int_anime_string_t events_array_genere_code_fichier    [ANIME_EVENTS_SIZE]; 
  int_anime_string_t events_array_genere_code_proc       [ANIME_EVENTS_SIZE]; 
  int_anime_string_t events_array_traitement_code_fichier[ANIME_EVENTS_SIZE]; 
  int_anime_string_t events_array_traitement_code_proc   [ANIME_EVENTS_SIZE]; 
  int8_t             events_size;
  int8_t             events_nb;
  
  int_anime_string_t membres_nom        [ANIME_MEMBRES_SIZE]; 
  int_anime_string_t membres_image      [ANIME_MEMBRES_SIZE]; 
  float              membres_largeur    [ANIME_MEMBRES_SIZE]; 
  float              membres_hauteur    [ANIME_MEMBRES_SIZE]; 
  float              membres_angle_max_y[ANIME_MEMBRES_SIZE]; 
  int8_t             membres_size; 
  int8_t             membres_nb; 
  
  int_anime_string_t racines_qui    [ANIME_RACINES_SIZE]; 
  float              racines_x      [ANIME_RACINES_SIZE]; 
  float              racines_y      [ANIME_RACINES_SIZE]; 
  float              racines_z      [ANIME_RACINES_SIZE]; 
  float              racines_angle_y[ANIME_RACINES_SIZE]; 
  int8_t             racines_size; 
  int8_t             racines_nb; 
  

  // LEXEME_I 
#define DECLARE_LEXEME_I_3(ident1,ident2,ident3) int_lexeme_t glue2(ident1,__lexeme_i); int_lexeme_t glue2(ident2,__lexeme_i); int_lexeme_t glue2(ident3,__lexeme_i);
#define DECLARE_LEXEME_I_4(ident1,ident2,ident3,ident4) int_lexeme_t glue2(ident1,__lexeme_i); int_lexeme_t glue2(ident2,__lexeme_i); int_lexeme_t glue2(ident3,__lexeme_i); int_lexeme_t glue2(ident4,__lexeme_i);
#define DECLARE_LEXEME_I_5_ARRAY(__array_prefix__,ident1,ident2,ident3,ident4,ident5,__array_size__) int_lexeme_t glue3(__array_prefix__,ident1,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident2,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident3,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident4,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident5,__lexeme_i)[__array_size__];
#define DECLARE_LEXEME_I_6_ARRAY(__array_prefix__,ident1,ident2,ident3,ident4,ident5,ident6,__array_size__) int_lexeme_t glue3(__array_prefix__,ident1,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident2,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident3,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident4,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident5,__lexeme_i)[__array_size__]; int_lexeme_t glue3(__array_prefix__,ident6,__lexeme_i)[__array_size__];
  
  DECLARE_LEXEME_I_4(choc_longueur,choc_largeur,choc_hauteur,masse);
  DECLARE_LEXEME_I_3(vie,invincible,hostile);   
  DECLARE_LEXEME_I_5_ARRAY(actions_array_,nom,affichage,icone,gestionnaire_fichier,gestionnaire_proc,ANIME_ACTIONS_SIZE); 
  DECLARE_LEXEME_I_6_ARRAY(events_array_,nom,genere_type,genere_code_fichier,genere_code_proc,traitement_code_fichier,traitement_code_proc,ANIME_EVENTS_SIZE); 
  DECLARE_LEXEME_I_5_ARRAY(membres_,nom,image,largeur,hauteur,angle_max_y,ANIME_MEMBRES_SIZE); 
  DECLARE_LEXEME_I_5_ARRAY(racines_,qui,x,y,z,angle_y,ANIME_RACINES_SIZE); 

  // LEXEME_LEN 
#define DECLARE_LEXEME_LEN_3(ident1,ident2,ident3) int8_t glue2(ident1,__lexeme_len); int8_t glue2(ident2,__lexeme_len); int8_t glue2(ident3,__lexeme_len);
#define DECLARE_LEXEME_LEN_4(ident1,ident2,ident3,ident4) int8_t glue2(ident1,__lexeme_len); int8_t glue2(ident2,__lexeme_len); int8_t glue2(ident3,__lexeme_len); int8_t glue2(ident4,__lexeme_len);
#define DECLARE_LEXEME_LEN_5_ARRAY(__array_prefix__,ident1,ident2,ident3,ident4,ident5,__array_size__) int8_t glue3(__array_prefix__,ident1,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident2,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident3,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident4,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident5,__lexeme_len)[__array_size__];
#define DECLARE_LEXEME_LEN_6_ARRAY(__array_prefix__,ident1,ident2,ident3,ident4,ident5,ident6,__array_size__) int8_t glue3(__array_prefix__,ident1,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident2,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident3,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident4,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident5,__lexeme_len)[__array_size__]; int8_t glue3(__array_prefix__,ident6,__lexeme_len)[__array_size__];
  
  DECLARE_LEXEME_LEN_4(choc_longueur,choc_largeur,choc_hauteur,masse);
  DECLARE_LEXEME_LEN_3(vie,invincible,hostile);   
  DECLARE_LEXEME_LEN_5_ARRAY(actions_array_,nom,affichage,icone,gestionnaire_fichier,gestionnaire_proc,ANIME_ACTIONS_SIZE); 
  DECLARE_LEXEME_LEN_6_ARRAY(events_array_,nom,genere_type,genere_code_fichier,genere_code_proc,traitement_code_fichier,traitement_code_proc,ANIME_EVENTS_SIZE); 
  DECLARE_LEXEME_LEN_5_ARRAY(membres_,nom,image,largeur,hauteur,angle_max_y,ANIME_MEMBRES_SIZE); 
  DECLARE_LEXEME_LEN_5_ARRAY(racines_,qui,x,y,z,angle_y,ANIME_RACINES_SIZE); 
  

  
#if 0   
  const char * temp_code_fichier; 
  const char * temp_code_proc; 
  
  int          temp_events_genere_type;
  const char * temp_events_genere_code_fichier;
  const char * temp_events_genere_code_proc; 
  
  const char * temp_events_par_code_fichier; 
  const char * temp_events_par_code_proc; 
  
  const char * temp_events_traitement_code_fichier; 
  const char * temp_events_traitement_code_proc; 
#endif 
}; 



extern const char *       anime__string_stack__get(const anime_t * this, const int_anime_string_t astr); 
extern int_anime_string_t anime__string_stack__push_nolookup(anime_t * this, const char * cstr); 
extern int_anime_string_t anime__string_stack__lookup(const anime_t * this, const char * cstr); 
extern int_anime_string_t anime__string_stack__push_lookup(anime_t * this, const char * cstr); 

extern int8_t anime__actions_push(anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc); 
extern int8_t anime__events_push (anime_t * this, const char * nom, const int8_t genere_type, const char * genere_code_fichier, const char * genere_code_proc, const char * traitement_fichier, const char * traitement_proc); 
extern int8_t anime__membres_push(anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y); 
extern int8_t anime__racines_push(anime_t * this, const char * qui, const float x, const float y, const float z, const float angle_y); 

extern int8_t  anime__membres_lookup(const anime_t * this, const char * nom); 



extern int_lexeme_t anime__lexeme_stack__push(anime_t * this, const int8_t type, const char * rstr, const int8_t len, const int16_t line1, const int8_t col0, const int16_t offset0); 
extern void   anime__lexeme__print_all(const anime_t * this, const int stdout_d); 
extern void   anime__lexeme__print_stats(const anime_t * this, const int8_t new_line_huh, const int filedes); 

#endif /* ANIME_TYPE_H */
