#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include "anime.h"
#include "anime.global.h"
//#include "anime.parser.tab.h"


anime_t * anime__make(void) {  
  MALLOC_BZERO(anime_t,this); 
  return this; 
};  

void anime__delete(anime_t * this) {  
  for (int i = 0; i < this -> racines_nb; i++) { 
    free(this -> racines_qui[i]); 
  }; 
 
  for (int i = 0; i < this -> membres_nb; i++) { 
    free(this -> membres_nom[i]); 
    free(this -> membres_image[i]); 
  }; 
  
  for (int i = 0; i < this -> events_nb; i++) { 
    free(this -> events_array_nom[i]); 
    free(this -> events_array_genere_code_fichier[i]); 
    free(this -> events_array_genere_code_proc[i]); 
    free(this -> events_array_traitement_code_fichier[i]); 
    free(this -> events_array_traitement_code_proc[i]); 
  }; 

  for (int i = 0; i < this -> events_nb; i++) { 
    free(this -> actions_array_nom[i]); 
    free(this -> actions_array_affichage[i]);
    free(this -> actions_array_icone[i]);
    free(this -> actions_array_gestionnaire_fichier[i]);
    free(this -> actions_array_gestionnaire_proc[i]);
  }; 
  
  free(this -> filename); 
  
  free(this); 
};  

anime_t * anime__make_from_file(const char * filename, const char * log_filename) {  
  MALLOC_BZERO(anime_t,this); 
  const int retval = anime__fill_from_file(this, filename, log_filename); 
  if (retval < 0) { 
    free(this); 
    return NULL; 
  }; 
  return this; 
};  

void anime__actions_push(anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc) {  
  assert(this -> actions_nb < anime_actions_size); 
  const int i = this -> actions_nb; 
  this -> actions_array_nom[i] = strcopy(nom); 
  this -> actions_array_affichage[i] = strcopy(affichage); 
  this -> actions_array_icone[i] = strcopy(icone); 
  this -> actions_array_gestionnaire_fichier[i] = strcopy(gestionnaire_fichier); 
  this -> actions_array_gestionnaire_proc[i] = strcopy(gestionnaire_proc); 
  this -> actions_nb++; 
};  

void anime__events_push(anime_t * this, const char * events_nom, const int events_genere_type, const char * events_genere_code_fichier, const char * events_genere_code_proc, const char * events_traitement_fichier, const char * events_traitement_proc) {  
  assert(this -> events_nb < anime_events_size); 
  const int i = this -> events_nb; 
  this -> events_array_nom[i] = strcopy(events_nom); 
  this -> events_array_genere_type[i] = events_genere_type; 
  this -> events_array_genere_code_fichier[i] = strcopy(events_genere_code_fichier); 
  this -> events_array_genere_code_proc[i] = strcopy(events_genere_code_proc); 
  this -> events_array_traitement_code_fichier[i] = strcopy(events_traitement_fichier); 
  this -> events_array_traitement_code_proc[i] = strcopy(events_traitement_proc); 
  this -> events_nb++; 
};  

void anime__membres_push(anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y) {  
  assert(this -> membres_nb < anime_membres_size); 
  const int i = this -> membres_nb; 
  this -> membres_nom[i] = strcopy(nom); 
  this -> membres_image[i] = strcopy(image); 
  this -> membres_largeur[i] = largeur; 
  this -> membres_hauteur[i] = hauteur; 
  this -> membres_angle_max_y[i] = angle_max_y; 
  this -> membres_nb++; 
};  

int anime__membres_lookup(const anime_t * this, const char * nom) {  
  for (int i = 0; i < this -> membres_nb; i++) { 
    if (0 == strcmp(nom, this -> membres_nom[i])) return i; 
  }; 
  return -1; 
};  
 
void anime__racines_push(anime_t * this, const char * qui, const float x, const float y, const float z, const float angle_y) {  
  assert(this -> racines_nb < anime_racines_size); 
  const int i = this -> racines_nb; 
  this -> racines_qui[i] = strcopy(qui); 
  this -> racines_x[i] = x; 
  this -> racines_y[i] = y; 
  this -> racines_z[i] = z; 
  this -> racines_angle_y[i] = angle_y; 
  this -> racines_nb++; 
};  

void anime__print(const anime_t * this, FILE * out_stream) { 
  //fprintf(out_stream, "filename = '%s'" "\n", NULL); 
  fprintf(out_stream, "filename = '%s'" "\n", this -> filename); 

  fprintf(out_stream, " " "\n"); 

  fprintf(out_stream, "physique { " "\n"); 
  fprintf(out_stream, "\t" "choc_longueur = %f" "\n", this -> choc_longueur); 
  fprintf(out_stream, "\t" "choc_largeur  = %f" "\n", this -> choc_largeur); 
  fprintf(out_stream, "\t" "choc_hauteur  = %f" "\n", this -> choc_hauteur); 
  fprintf(out_stream, "\t" "masse         = %f" "\n", this -> masse); 
  fprintf(out_stream, "}; " "\n"); 

  fprintf(out_stream, " " "\n"); 

  fprintf(out_stream, "gameplay { " "\n"); 
  fprintf(out_stream, "\t" "vie        = %d" "\n", this -> vie); 
  fprintf(out_stream, "\t" "invincible = %d" "\n", this -> invincible); 
  fprintf(out_stream, "\t" "hostile    = %d" "\n", this -> hostile); 
  fprintf(out_stream, "}; " "\n"); 

  fprintf(out_stream, " " "\n"); 
  


  fprintf(out_stream, "graphique { " "\n"); 
  fprintf(out_stream, "\t" " " "\n"); 
  fprintf(out_stream, "\t" "racines[%d] =  " "\n", this -> racines_nb); 
  for (int i = 0; i < this -> racines_nb; i++) { 
    fprintf(out_stream, "\t" "\t" "{ qui = %s \t\t ; x := %f ; y := %f ; z := %f ; angle y := %f ;}," "\n", this -> racines_qui[i], this -> racines_x[i], this -> racines_y[i], this -> racines_z[i], this -> racines_angle_y[i]); 
  }; 
  fprintf(out_stream, "\t" "; " "\n"); 

  fprintf(out_stream, "\t" " " "\n"); 

  fprintf(out_stream, "\t" "membres[%d] =  " "\n", this -> membres_nb); 
  for (int i = 0; i < this -> membres_nb; i++) { 
    fprintf(out_stream, "\t" "\t" "{ nom = %s \t\t ; image := %s \t\t ; largeur := %f ; hauteur := %f ; angle y max := %f ;}," "\n", this -> membres_nom[i], this -> membres_image[i], this -> membres_largeur[i], this -> membres_hauteur[i], this -> membres_angle_max_y[i]); 
  }; 
  fprintf(out_stream, "\t" "; " "\n"); 

  fprintf(out_stream, "}; " "\n"); 

  fprintf(out_stream, " " "\n"); 


  
  
}; 











#define SUFF_ANIME_OUT ".lexing.out"

//anime_t * anime__fill_from_file(anime_t * this, const char * filename, const char * log_filename) {  
int anime__fill_from_file(anime_t * this, const char * filename, const char * log_filename) {  
  if (filename == NULL) { anime_err("Erreur: impossible 'filename' est le pointeur NULL.\n"); return -1; }; 
  
  this -> filename = strcopy(filename); 
  
  // log file 
  if (NULL == log_filename) { 
    char anime_log[strlen(filename) + strlen(SUFF_ANIME_OUT) + 1];
    strcat(strcpy(anime_log, filename), SUFF_ANIME_OUT);
    //message("On essaye d'ouvrir en lecture le fichier '%s'.", anime_log);
    yyanimeout = fopen(anime_log, "wb");
    if (yyanimeout == NULL) {
      anime_err("Erreur: impossible d'ouvrir en écriture le fichier \"%s\".\n", anime_log);
      return -2;
    };
  } 
  else {
    message("On essaye d'ouvrir en écriture le fichier '%s'." "\n", log_filename);
    yyanimeout = fopen(log_filename, "wb");
    if (yyanimeout == NULL) {
      anime_err("Erreur: impossible d'ouvrir en écriture le fichier \"%s\".\n", log_filename);
      return -3;
    }; 
  };
  
  //yyanimein
  FILE * entrin = NULL;
  { 
#if 0 
    char anime_fullpath[strlen(filename) + strlen(dir) + 1];
    anime_fullpath = strcat(strcpy(anime_fullpath, dir), filename);
#else 
    const char * anime_fullpath = filename; 
#endif 
    entrin = fopen(anime_fullpath, "rb");
    if (entrin == NULL) {
      anime_err("Erreur : impossible d'ouvrir en lecture le fichier \"%s\".\n", filename);
      (void) fclose(yyanimeout);
      return -4;
    }; 
  }; 

  anime_restart_lexer();
  yyanimerestart(entrin);
  anime_parser_reset();

  /* L'analyse elle meme. */
  int res; 
  yyanime_global_objet_being_filled_up_while_parsing = this; 
#if 1
  res = yyanimeparse();
#else
  res = 0;
#endif

  fprintf(yyanimeout, "\n" "\n"  "---------------------------------------"  "\n" "\n"); 

  //* On match. */
  switch (res) {
  case 0:  (void) fprintf(yyanimeout, "Analyse réussie !!!\n"); break; 
  default: (void) fprintf(yyanimeout, "Analyse ratée...\n");    break; 
  }; 
  
  if (0 == res) { 
    fprintf(yyanimeout, "\n\n" "==============================================================================" "\n" "\n"); 
    anime__print(this, yyanimeout);   
  }; 
  
  //* On ferme les flux. */
  (void) fclose(yyanimeout); 
  (void) fclose(yyanimein);
  
  return (0 == res) ? 0 : -5; 
}; 
























#if 0
#define ANIME_OUT ".lexing.out"
//const int LireAnime(const char * filename, CBonhomme * bongarsp) {
int LireAnime(const char * dir, const char * filename, CBonhomme * bongarsp) {
  int res;
  FILE *in;

  if (filename == NULL) {
    return -1;
  }

  char * fout;
  
  fout = (char *) malloc((strlen(LOGDIR) + strlen(filename) + 1 + strlen(ANIME_OUT) + 1) * sizeof(char));

  if (fout == NULL) {
    return -2;
  }

  (void) strcat(strcat(strcpy(fout, LOGDIR), filename), ANIME_OUT);
#if 0
  anime_err("fout = %s\n", fout);
  yyanimeout = fopen(fout, "wb");
  assert(yyanimeout != NULL);
  assert(false);
#endif

  yyanimeout = fopen(fout, "wb");
  if (yyanimeout == NULL) {
    //(void) printf("Erreur: impossible d'ouvrir le fichier \"%s\".", fout);
    return -3;
  }

  (void) fprintf(yyanimeout, "Initialisation du fichier \"%s\" de sortie réussie !\n", fout);

  filename = STRCAT2_(dir, filename);
  in = fopen(filename, "rb");
  if (in == NULL) {
    (void) fprintf(yyanimeout, "Erreur : impossible d'ouvrir le fichier \"%s\".\nFin de l'analyse.\n", filename);
    fclose(yyanimeout);
    free(fout);
    return -4;
  }
  
  (void) fprintf(yyanimeout, "Ouverture en lecture du fichier \"%s\" réussie.\nDébut de l'analyse du fichier.\n\n", filename);

  anime_restart_lexer();
  yyanimerestart(in);
  anime_parser_reset();

  bongars = bongarsp;

  res = yyanimeparse();

  (void) fprintf(yyanimeout, "\n\n\nRésultat de l'analyse : %d\n", res);
  (void) fprintf(yyanimeout, "\t=> %s\n", res ? "Analyse ratée..." : "Analyse réussie !!!");
  

  
  fclose(yyanimein);
  fclose(yyanimeout); 
  free(fout);
  
  switch (res) {
  case 0:   return 0;
  default:  return -4 + res;
  }; 
  
};

#endif 
