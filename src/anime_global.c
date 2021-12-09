#include "anime_global.h"



static struct anime_t * yyanime_global_objet_being_filled_up_while_parsing = NULL;

#if 1 
//extern char * anime_strcopy(const char * cstr) { 
static char * anime_strcopy(const char * cstr) { 
  if (cstr == NULL) return NULL; 
  //const int cstr_len = strlen(cstr); 
  const char * p = cstr; while (*p) p++; 
  const int cstr_len = p - cstr; 
  const int byte_size = (cstr_len+1) * (sizeof(char)); 
  char * copy_cstr = malloc(byte_size); 
  //return strcpy(copy_cstr, cstr); 
  //bcopy(cstr, copy_cstr, byte_size); 
  char * q = copy_cstr; 
  p = cstr; 
  for (;;) { *q = *p; if (!*p) break; q++; p++; }; 
  return copy_cstr; 
}; 
#else 
//extern char * strcopy(const char * str); 
static char * strcopy(const char * cstr) { 
  if (cstr == NULL) return NULL; 
  //const int cstr_len = strlen(cstr); 
  const char * p = cstr; while (*p) p++; 
  const int cstr_len = p - cstr; 
  const int byte_size = (cstr_len+1) * (sizeof(char)); 
  char * copy_cstr = malloc(byte_size); 
  //return strcpy(copy_cstr, cstr); 
  //bcopy(cstr, copy_cstr, byte_size); 
  char * q = copy_cstr; 
  p = cstr; 
  while (p) { *q = *p; q++; p++; }; 
  return copy_cstr; 
}; 
#endif 



#if 0 

/* On définit toutes fonctions d'allocations de mémoire. */
liste *liste_vide(void) {
  return (liste*) NULL;
}

liste *mp(void *contenu, liste *l) {
  liste *temp;

  temp = (liste*) malloc(1 * sizeof(struct liste));
  if (temp == NULL) {
    return temp;
  }

  temp->contenu = contenu;
  temp->suivant = l;
  return temp;
}

void raz(liste* *l) {
  liste *temp;
  temp = *l;
  while (temp != NULL) {
    *l = temp->suivant;
    free(temp);
    temp = *l;
  }
}



tvecteur* new_vecteur(void) {
  return (tvecteur*) malloc(1 * sizeof(union tvecteur));
}
 
void del_vecteur(tvecteur* *v) {
  free(*v);
}


anime_taction *anime_new_action(void) {
  return (anime_taction*) malloc(1 * sizeof(struct anime_taction));
}

void anime_del_action(anime_taction *a) {
  free(a);
}


anime_sgenere* anime_new_sgenere(void) {
  return (anime_sgenere*) malloc(1 * sizeof(struct anime_sgenere));
}

void anime_del_sgenere(anime_sgenere *s) {
  free(s);
}

  
anime_tevent* anime_new_event(void) {
  return (anime_tevent*) malloc(1 * sizeof(struct anime_tevent));
}

void anime_del_event(anime_tevent *e) {
  free(e);
}


anime_tfils* anime_new_fils(void) {
  return (anime_tfils*) malloc(1 * sizeof(struct anime_tfils));
}

void anime_del_fils(anime_tfils *f) {
  free(f);
}


anime_tmembre* anime_new_membre(void) {
  return (anime_tmembre*) malloc(1 * sizeof(struct anime_tmembre));
}

void anime_del_membre(anime_tmembre *m) {
  free(m);
}



anime_tcode *anime_new_code(void) {
  return (anime_tcode*) malloc(1 * sizeof(struct anime_tcode));  
}
void anime_del_code(anime_tcode **c) {
  free(*c);
  *c = NULL;
}






#endif 
