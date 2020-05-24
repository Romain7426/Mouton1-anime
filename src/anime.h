#ifndef ANIME_H
#define ANIME_H

/* Penser à regarder lexing.out
   Valeur de retour :
    -  0 : OK
    - -1 : filename est NULL
    - -2 : allocation ratée de mémoire
    - -3 : ouverture en écriture impossible du fichier "lexing.out"
    - -4 : ouverture en lecture de filename impossible
    - < -4 : erreur de parsing (syntaxe).
    - ...
*/
//extern const int LireAnime(const char *, CBonhomme *);
//extern int LireAnime(const char * dir, const char * filename, CBonhomme * bongarsp);


enum { anime_actions_size = 15 }; 
enum { anime_events_size  = 15 }; 
enum { anime_membres_size = 15 }; 
enum { anime_racines_size = anime_membres_size }; 
enum { ANIME_EVENTS_TOUS, ANIME_EVENTS_AUCUN, ANIME_EVENTS_CODE }; 

struct anime_t; 
typedef struct anime_t anime_t; 
struct anime_t {
  char * filename; 
  
  //physique;
  float choc_longueur;
  float choc_largeur;
  float choc_hauteur;
  float masse;
  
  //anime_tgameplay gameplay;
  int vie;
  int invincible;
  int hostile;

  char * actions_array_nom                 [anime_actions_size];
  char * actions_array_affichage           [anime_actions_size];
  char * actions_array_icone               [anime_actions_size];
  char * actions_array_gestionnaire_fichier[anime_actions_size];
  char * actions_array_gestionnaire_proc   [anime_actions_size];
  int    actions_nb;

  char * events_array_nom                    [anime_events_size]; 
  int    events_array_genere_type            [anime_events_size]; 
  char * events_array_genere_code_fichier    [anime_events_size]; 
  char * events_array_genere_code_proc       [anime_events_size]; 
  char * events_array_traitement_code_fichier[anime_events_size]; 
  char * events_array_traitement_code_proc   [anime_events_size]; 
  int    events_nb;

  //anime_tgraphique graphique;
  char * membres_nom        [anime_membres_size]; 
  char * membres_image      [anime_membres_size]; 
  float  membres_largeur    [anime_membres_size]; 
  float  membres_hauteur    [anime_membres_size]; 
  float  membres_angle_max_y[anime_membres_size]; 
  int    membres_nb; 
  
  char * racines_qui    [anime_racines_size]; 
  float  racines_x      [anime_racines_size]; 
  float  racines_y      [anime_racines_size]; 
  float  racines_z      [anime_racines_size]; 
  float  racines_angle_y[anime_racines_size]; 
  int    racines_nb; 
  
  
  
  const char * temp_code_fichier; 
  const char * temp_code_proc; 
  
  int temp_events_genere_type;
  const char * temp_events_genere_code_fichier;
  const char * temp_events_genere_code_proc; 

  const char * temp_events_par_code_fichier; 
  const char * temp_events_par_code_proc; 
  
  const char * temp_events_traitement_code_fichier; 
  const char * temp_events_traitement_code_proc; 
};

extern void      anime__print         (const anime_t * this, FILE * out_stream); 
extern anime_t * anime__make          (void);  
extern void      anime__delete        (      anime_t * this);  
extern anime_t * anime__make_from_file(const char * filename, const char * log_filename);  
extern int       anime__fill_from_file(      anime_t * this, const char * filename, const char * log_filename);  
extern void      anime__actions_push  (      anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc);  
extern void      anime__events_push   (      anime_t * this, const char * events_nom, const int events_genere_type, const char * events_genere_code_fichier, const char * events_genere_code_proc, const char * events_traitement_fichier, const char * events_traitement_proc);  
extern void      anime__membres_push  (      anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y); 
extern int       anime__membres_lookup(const anime_t * this, const char * nom); 
extern void      anime__racines_push  (      anime_t * this, const char * qui, const float x, const float y, const float z, const float angle_y); 






#endif /* ANIME_H */
