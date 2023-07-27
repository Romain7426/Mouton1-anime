#include "anime_global.h"
#include "anime.h"
#include "anime_token.h"
#include "anime_token_input_buffering.h"
#include "anime_token_parser.h"
//#include "anime_tree.h"
//#include "anime_tree_parser.h"
//#include "anime_data_generation_001_from_tokens.h"
//#include "anime_data_generation_002_from_trees.h"
#include "anime_data_generation_003_from_syntax_filtering.h"

const uint8_t ANIME_VERSION_MAJOR__compiled_value    = (uint8_t) ANIME_VERSION_MAJOR; 
const uint8_t ANIME_VERSION_MINOR__compiled_value    = (uint8_t) ANIME_VERSION_MINOR; 
const uint8_t ANIME_VERSION_REVISION__compiled_value = (uint8_t) ANIME_VERSION_REVISION; 

const uint8_t ANIME__EXPRESSION_NESTEDNESS_MAX__compiled_value = (uint8_t) ANIME__EXPRESSION_NESTEDNESS_MAX; 
const uint8_t ANIME__LONGEST_INFIX_EXPRESSION__compiled_value  = (uint8_t) ANIME__LONGEST_INFIX_EXPRESSION; 

#define PROGRAM_NAME "Anime (lib part of ‘Mouton1’ — whose purpose is to read anime data description files into C data structures)" 
static const char program_name[] = PROGRAM_NAME; 
enum { program_name__cstrlen = ARRAY_SIZE(program_name) - 1 }; 
#define PROGRAM_COPYRIGHT_YEAR1 "2004"
#define PROGRAM_COPYRIGHT_YEAR2 "2021"
#define PROGRAM_URL "https://github.com/Romain7426/Mouton1-anime" 

const char anime_copyright[] = 
"_Software_: " PROGRAM_NAME "\n"
"_License_: " "ISC License" "\n"
"_URL_: " PROGRAM_URL "\n"
"_Copyright years_: " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 "\n"
"" "\n"
PROGRAM_NAME "\n"
"Copyright (c) " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " " "\n"
"All rights reserved." "\n"
"" "\n"
"Redistribution and use in source and binary forms, with or without" "\n"
"modification, are permitted provided that the following conditions" "\n"
"are met:" "\n"
"1. Redistributions of source code must retain the above copyright" "\n"
"   notice, this list of conditions and the following disclaimer." "\n"
"2. Redistributions in binary form must reproduce the above copyright" "\n"
"   notice, this list of conditions and the following disclaimer in the" "\n"
"   documentation and/or other materials provided with the distribution." "\n"
"" "\n"
"THIS SOFTWARE IS PROVIDED BY THE _AUTHORS_ ``AS IS'' AND ANY EXPRESS" "\n"
"OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED" "\n"
"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE" "\n"
"DISCLAIMED. IN NO EVENT SHALL THE _AUTHORS_ BE LIABLE FOR ANY DIRECT," "\n"
"INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES" "\n"
"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR" "\n"
"SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)" "\n"
"HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT," "\n"
"STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING" "\n"
"IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE" "\n"
"POSSIBILITY OF SUCH DAMAGE." "\n" 
"" "\n" 
"NB: We do not care of what you do with this code as long as " "\n" 
"    you do not prevent us nor others from using it." "\n" 
;
enum {           anime_copyright__strlen__const_value = ARRAY_SIZE(anime_copyright) - 1 }; 
const uint16_t   anime_copyright__strlen = (uint16_t) anime_copyright__strlen__const_value; 
const char     * anime_copyright__get(void) { return anime_copyright; }; 
void             anime_copyright__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_copyright, anime_copyright__strlen__const_value); if ('\n' != *(anime_copyright + anime_copyright__strlen__const_value - 1)) write(stduser_d, "\n", 1); }; }; 

const char       anime_url[] = PROGRAM_URL; 
enum {           anime_url__strlen__const_value = ARRAY_SIZE(anime_url) - 1 }; 
const uint16_t   anime_url__strlen = anime_url__strlen__const_value; 
const char     * anime_url__get(void) { return anime_url; }; 
void             anime_url__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_url, anime_url__strlen__const_value); write(stduser_d, "\n", 1); }; }; 


#define DIGIT_TO_STRING(d) (			\
			    (d) == 0 ? "0" :	\
			    (d) == 1 ? "1" :	\
			    (d) == 2 ? "2" :	\
			    (d) == 3 ? "3" :	\
			    (d) == 4 ? "4" :	\
			    (d) == 5 ? "5" :	\
			    (d) == 6 ? "6" :	\
			    (d) == 7 ? "7" :	\
			    (d) == 8 ? "8" :	\
			    (d) == 9 ? "9" :	\
			    "?")

#define DIGIT_TO_CHAR(d) (((d) >= 0 && (d) <= 9) ? '0' + (d) : '?') 
    
const char       anime_version[] = { DIGIT_TO_CHAR(ANIME_VERSION_MAJOR), '.', DIGIT_TO_CHAR(ANIME_VERSION_MINOR), '.', DIGIT_TO_CHAR(ANIME_VERSION_REVISION), '\0' }; 
enum {           anime_version__strlen__const_value = ARRAY_SIZE(anime_version) - 1 }; 
const uint16_t   anime_version__strlen = anime_version__strlen__const_value; 
const char     * anime_version__get(void) { return anime_version; }; 
void             anime_version__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_version, anime_version__strlen__const_value); write(stduser_d, "\n", 1); }; };


const char       anime_example[] = 
#include "chaman.anime.ci"
; 
enum {           anime_example__strlen__const_value = ARRAY_SIZE(anime_example) - 1 }; 
const uint16_t   anime_example__strlen = anime_example__strlen__const_value; 
const char     * anime_example__get(void) { return anime_example; }; 
void             anime_example__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, anime_example, anime_example__strlen__const_value); write(stduser_d, "\n", 1); }; }; 




anime_t * anime__make(const int stdlog_d) {  
  MALLOC_BZERO(anime_t,this); 
  anime__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
};  

anime_t * anime__make_r(anime_t * this, const int stdlog_d) { 
  bzero(this, sizeof(*this)); 
  this -> stdlog_d = stdlog_d; 
  this -> error_size = ANIME__ERROR_BUFFER_SIZE; 
#if 0 
  this -> lexer_stack[0] = '\0'; 
  this -> lexer_stack_nb = 1; 
#endif 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb = 1; 
  this -> copyright = anime_copyright; 
  this -> membres_size = anime_membres_size; 
  this -> racines_size = anime_racines_size; 
  return this; 
};  

void anime__delete_r(anime_t * this) { 
#if 0 
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
#endif 
  
  //free(this -> filename); 
  
  const int malloced_flag = this -> malloced_flag; 
  const int error_size    = this -> error_size; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
  this -> error_size    = ANIME__ERROR_BUFFER_SIZE; //error_size; 
};  

void anime__delete(anime_t * this) { 
  anime__delete_r(this); 
  if (1 == this -> malloced_flag) { 
    free(this); 
  };
};  

void anime__bzero(anime_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  const int stdlog_d      = this -> stdlog_d; 
  const int error_size    = this -> error_size; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
  this -> stdlog_d      = stdlog_d; 
  this -> error_size    = ANIME__ERROR_BUFFER_SIZE; //error_size; 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb = 1; 
  this -> copyright = anime_copyright; 
  this -> membres_size = anime_membres_size; 
  this -> racines_size = anime_racines_size; 
};  

int_anime_error_t anime__consistency_check(anime_t * this, const int stduser_d) { 
  if (NULL == this) return ANIME__NULL_STRUCT; 
  if (   0 == this -> filled_huh) { 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime data structure empty — checking consistency meaningless — aborting."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    return ANIME__EMPTY_STRUCTURE; 
  };
  if (  -1 == this -> filled_huh) { 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime data structure only partially filled — checking consistency meaningless — aborting."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    return ANIME__FILLING_NOT_COMPLETED; 
  };
  if (   1 == this -> filled_huh) { 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime structure consistency already checked (as ok) — doing it again though."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
  } 
  else if (2 == this -> filled_huh) { } 
  else if (3 == this -> filled_huh) { 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime structure consistency already checked (as having breaking unconsistencies) — doing it again though."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
  } 
  else if (4 == this -> filled_huh) { 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime structure consistency already checked (as having non-breaking unconsistencies) — doing it again though."); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
  } 
  else { 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Unknown filled status: %d — checking consistency anyways.", this -> filled_huh); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
  };

  int breaking_inconsistencies = 0; 
  int non_breaking_inconsistencies = 0; 
  
  for (int i = 0; i < this -> membres_nb; i++) { 
    const char * m_nom = this -> membres_nom[i]; 
    int found_huh = false; 
    for (int j = 0; j < this -> racines_nb; j++) { 
      const char * r_nom = this -> racines_qui[j]; 
      if (0 == strcasecmp(m_nom, r_nom)) { found_huh = true; break; }; 
    }; 
    if (found_huh) continue; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "<Non-breaking inconsistency>: " "The member '%s' is not used (not rooted).", m_nom); 
    if (stduser_d > 0) { dprintf(stduser_d, "<%s>: " "%s" "\n", this -> filename, this -> error_str); }; 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    non_breaking_inconsistencies++; 
  };
  
  for (int i = 0; i < this -> membres_nb; i++) { 
    const char * m_nom1 = this -> membres_nom[i]; 
    int count_nb = 1; 
    for (int i2 = i+1; i2 < this -> membres_nb; i2++) { 
      const char * m_nom2 = this -> membres_nom[i2]; 
      if (0 == strcasecmp(m_nom1, m_nom2)) { count_nb++; }; 
    }; 
    if (count_nb == 1) continue; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "<Non-breaking inconsistency>: " "There %d members named '%s' (only the first one gonna be used, others will be ignored).", count_nb, m_nom1); 
    if (stduser_d > 0) { dprintf(stduser_d, "<%s>: " "%s" "\n", this -> filename, this -> error_str); }; 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    non_breaking_inconsistencies++; 
  };
  
  for (int j = 0; j < this -> racines_nb; j++) { 
    const char * r_nom = this -> racines_qui[j]; 
    int found_huh = false; 
    for (int i = 0; i < this -> membres_nb; i++) { 
      const char * m_nom = this -> membres_nom[i]; 
      if (0 == strcasecmp(m_nom, r_nom)) { found_huh = true; break; }; 
    }; 
    if (found_huh) continue; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "<Breaking inconsistency>: " "The root '%s' is referencing a missing member.", r_nom); 
    if (stduser_d > 0) { dprintf(stduser_d, "<%s>: " "%s" "\n", this -> filename, this -> error_str); }; 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    breaking_inconsistencies++; 
  };

  for (int j = 0; j < this -> racines_nb; j++) { 
    const char * r_nom1 = this -> racines_qui[j]; 
    int count_nb = 1; 
    for (int j2 = j+1; j2 < this -> racines_nb; j2++) { 
      const char * r_nom2 = this -> racines_qui[j2]; 
      if (0 == strcasecmp(r_nom1, r_nom2)) { count_nb++; }; 
    }; 
    if (count_nb == 1) continue; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "<Non-breaking inconsistency>: " "There are %d root named '%s'.", count_nb, r_nom1); 
    if (stduser_d > 0) { dprintf(stduser_d, "<%s>: " "%s" "\n", this -> filename, this -> error_str); }; 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    non_breaking_inconsistencies++; 
  };
  
  
  
  
  if (0 != breaking_inconsistencies) { 
    this -> error_id = ANIME__HAS_BREAKING_UNCONSISTENCIES; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime data struct has %d breaking consistency issues.", breaking_inconsistencies); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    this -> filled_huh = 3; 
    return this -> error_id; 
  }; 
  
  if (0 != non_breaking_inconsistencies) { 
    this -> error_id = ANIME__HAS_NON_BREAKING_UNCONSISTENCIES; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Anime data struct has %d non-breaking consistency issues.", non_breaking_inconsistencies); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, this -> error_str); }; 
    this -> filled_huh = 4; 
    return this -> error_id; 
  }; 
  
  this -> error_id = ANIME__OK; 
  this -> filled_huh = 1; 
  return this -> error_id; 
}; 


#if 0 
anime_t * anime__make_from_file(const char * filename, const char * log_filename) {  
  MALLOC_BZERO(anime_t,this); 
  const int retval = anime__fill_from_file(this, filename, log_filename); 
  if (retval < 0) { 
    free(this); 
    return NULL; 
  }; 
  return this; 
}; 
#endif 

void anime__actions_push(anime_t * this, const char * nom, const char * affichage, const char * icone, const char * gestionnaire_fichier, const char * gestionnaire_proc) {  
  assert(this -> actions_nb < anime_actions_size); 
  const int i = this -> actions_nb; 
  this -> actions_array_nom      [i] = anime__strcopy(this, nom); 
  this -> actions_array_affichage[i] = anime__strcopy(this, affichage); 
  this -> actions_array_icone    [i] = anime__strcopy(this, icone); 
  this -> actions_array_gestionnaire_fichier[i] = anime__strcopy(this, gestionnaire_fichier); 
  this -> actions_array_gestionnaire_proc   [i] = anime__strcopy(this, gestionnaire_proc); 
  this -> actions_nb++; 
};  

void anime__events_push(anime_t * this, const char * events_nom, const int events_genere_type, const char * events_genere_code_fichier, const char * events_genere_code_proc, const char * events_traitement_fichier, const char * events_traitement_proc) {  
  assert(this -> events_nb < anime_events_size); 
  const int i = this -> events_nb; 
  this -> events_array_nom[i] = anime__strcopy(this, events_nom); 
  this -> events_array_genere_type[i] = events_genere_type; 
  this -> events_array_genere_code_fichier[i] = anime__strcopy(this, events_genere_code_fichier); 
  this -> events_array_genere_code_proc[i] = anime__strcopy(this, events_genere_code_proc); 
  this -> events_array_traitement_code_fichier[i] = anime__strcopy(this, events_traitement_fichier); 
  this -> events_array_traitement_code_proc[i] = anime__strcopy(this, events_traitement_proc); 
  this -> events_nb++; 
};  

void anime__membres_push(anime_t * this, const char * nom, const char * image, const float largeur, const float hauteur, const float angle_max_y) {  
  assert(this -> membres_nb < anime_membres_size); 
  const int i = this -> membres_nb; 
  this -> membres_nom[i] = anime__strcopy(this, nom); 
  this -> membres_image[i] = anime__strcopy(this, image); 
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
  this -> racines_qui[i] = anime__strcopy(this, qui); 
  this -> racines_x[i] = x; 
  this -> racines_y[i] = y; 
  this -> racines_z[i] = z; 
  this -> racines_angle_y[i] = angle_y; 
  this -> racines_nb++; 
};  

void anime__print_f(const anime_t * this, FILE * out_stream) { 
  anime__print_d(this, fileno(out_stream)); 
}; 

void anime__print_d(const anime_t * this, const int fd) { 
  dprintf(fd, "/* filename := '%s' */" "\n", this -> filename); 
  
  dprintf(fd, " " "\n"); 

  dprintf(fd, "physique { " "\n"); 
  dprintf(fd, "  " "zone de choc := {" "\n"); 
  dprintf(fd, "  " "  " "longueur := %10f;" "\n", this -> choc_longueur); 
  dprintf(fd, "  " "  " "largeur  := %10f;" "\n", this -> choc_largeur); 
  dprintf(fd, "  " "  " "hauteur  := %10f;" "\n", this -> choc_hauteur); 
  dprintf(fd, "  " "};" "\n"); 
  dprintf(fd, "  " "masse := %10f;" "\n", this -> masse); 
  dprintf(fd, "} " "\n"); 

  dprintf(fd, " " "\n"); 

  dprintf(fd, "gameplay { " "\n"); 
  dprintf(fd, "  " "points de vie := %5d;" "\n", this -> vie); 
  dprintf(fd, "  " "invincible    :=  %s;" "\n", this -> invincible ? "vrai" : "faux"); 
  dprintf(fd, "  " "hostile       :=  %s;" "\n", this -> hostile    ? "vrai" : "faux"); 
  dprintf(fd, "} " "\n"); 

  dprintf(fd, " " "\n"); 
  


  dprintf(fd, "graphique { " "\n"); 
  dprintf(fd, "  " " " "\n"); 
  dprintf(fd, "  " "/* membres[%d / %d]: */" "\n", this -> membres_nb, this -> membres_size); 
  for (int i = 0; i < this -> membres_nb; i++) { 
    dprintf(fd, "  " "membre %15s { fils := ; image := %30s ; largeur := %10f ; hauteur := %10f ; angle max y := %10f ; }" "\n", this -> membres_nom[i], this -> membres_image[i], this -> membres_largeur[i], this -> membres_hauteur[i], this -> membres_angle_max_y[i]); 
  }; 
  dprintf(fd, "  " "\n"); 
  
  dprintf(fd, "  " "membres racines /*[%d / %d]*/ := " "\n", this -> racines_nb, this -> racines_size); 
  for (int i = 0; i < this -> racines_nb; i++) { 
    dprintf(fd, "  " "  " "{ qui := %15s ; x := %10f ; y := %10f ; z := %10f ; angle y := %10f ;}," "\n", this -> racines_qui[i], this -> racines_x[i], this -> racines_y[i], this -> racines_z[i], this -> racines_angle_y[i]); 
  }; 
  dprintf(fd, "  " "; " "\n"); 

  dprintf(fd, "  " " " "\n"); 

  dprintf(fd, "} " "\n"); 

  dprintf(fd, " " "\n"); 

}; 

void anime__print_d001(const anime_t * this, const int fd) { 
  dprintf(fd, "filename = '%s'" "\n", this -> filename); 
  
  dprintf(fd, " " "\n"); 

  dprintf(fd, "physique { " "\n"); 
  dprintf(fd, "\t" "choc_longueur = %10f" "\n", this -> choc_longueur); 
  dprintf(fd, "\t" "choc_largeur  = %10f" "\n", this -> choc_largeur); 
  dprintf(fd, "\t" "choc_hauteur  = %10f" "\n", this -> choc_hauteur); 
  dprintf(fd, "\t" "masse         = %10f" "\n", this -> masse); 
  dprintf(fd, "}; " "\n"); 

  dprintf(fd, " " "\n"); 

  dprintf(fd, "gameplay { " "\n"); 
  dprintf(fd, "\t" "vie        = %5d" "\n", this -> vie); 
  dprintf(fd, "\t" "invincible = %s" "\n", this -> invincible ? "vrai" : "faux"); 
  dprintf(fd, "\t" "hostile    = %s" "\n", this -> hostile    ? "vrai" : "faux"); 
  dprintf(fd, "}; " "\n"); 

  dprintf(fd, " " "\n"); 
  


  dprintf(fd, "graphique { " "\n"); 
  dprintf(fd, "\t" " " "\n"); 
  dprintf(fd, "\t" "membres[%d] =  " "\n", this -> membres_nb); 
  for (int i = 0; i < this -> membres_nb; i++) { 
    dprintf(fd, "\t" "\t" "{ nom = %15s ; image := %30s ; largeur := %10f ; hauteur := %10f ; angle y max := %10f ;}," "\n", this -> membres_nom[i], this -> membres_image[i], this -> membres_largeur[i], this -> membres_hauteur[i], this -> membres_angle_max_y[i]); 
  }; 
  dprintf(fd, "\t" "; " "\n"); 

  dprintf(fd, "\t" "racines[%d] =  " "\n", this -> racines_nb); 
  for (int i = 0; i < this -> racines_nb; i++) { 
    dprintf(fd, "\t" "\t" "{ qui = %15s ; x := %10f ; y := %10f ; z := %10f ; angle y := %10f ;}," "\n", this -> racines_qui[i], this -> racines_x[i], this -> racines_y[i], this -> racines_z[i], this -> racines_angle_y[i]); 
  }; 
  dprintf(fd, "\t" "; " "\n"); 

  dprintf(fd, "\t" " " "\n"); 

  dprintf(fd, "}; " "\n"); 

  dprintf(fd, " " "\n"); 

}; 



static const char * anime__strcopy_nolookup(anime_t * this, const char * str) { 
  if (NULL ==  str) { return NULL; }; 
  if ('\0' == *str) { return this -> string_stack; }; 
  const int len1 = 1 + strlen(str); 
  if (this -> string_stack_nb + len1 > ANIME__STRING_STACK_SIZE) { 
    this -> error_id = ANIME__STRCOPY; 
    snprintf(this -> error_str, ANIME__ERROR_BUFFER_SIZE, "Not enough space in the anime buffer to copy the string (mem needed: %d ; mem left: %d ; str: '%s')", len1, ANIME__STRING_STACK_SIZE - this -> string_stack_nb, str); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> string_stack + this -> string_stack_nb; 
  bcopy(str, new_str, len1); 
  this -> string_stack_nb += len1; 
  return new_str; 
}; 

static const char * anime__string_lookup(const anime_t * this, const char * cstr) { 
  if (NULL ==  cstr) { return NULL; }; 
  if ('\0' == *cstr) { return this -> string_stack; }; 
  const int cstr_len1 = 1 + strlen(cstr); 
  if (cstr_len1 >= this -> string_stack_nb) return NULL; 
  const uint16_t last_start_pos = this -> string_stack_nb - cstr_len1; 
  uint16_t pos; 
  pos = 1; 
  for (;;) { 
    if (pos > last_start_pos) return NULL; 
    if ('\0' == this -> string_stack[pos + cstr_len1] && (0 == strcmp(this -> string_stack + pos, cstr))) { return this -> string_stack + pos; }; 
    while ('\0' != this -> string_stack[pos]) pos++; 
    pos++; 
  }; 
  assert(false); 
}; 

const char * anime__strcopy(anime_t * this, const char * str) { 
  if (NULL ==  str) { return NULL; }; 
  if ('\0' == *str) { return this -> string_stack; }; 
  const char * str_lookedup = anime__string_lookup(this, str); 
  if (NULL != str_lookedup) return str_lookedup; 
  const char * new_str = anime__strcopy_nolookup(this, str); 
  return new_str; 
}; 


//#define VLA__YES
//#define ALLOCA__YES
#define LOCAL_ALLOCA__YES

#define LOCAL_ALLOCA__DECLARE(LOCAL_ALLOCA_SIZEOF)			\
  enum { LOCAL_ALLOCA__BYTE_SIZE = (LOCAL_ALLOCA_SIZEOF) }; char local_alloca__mem[LOCAL_ALLOCA__BYTE_SIZE]; uint16_t local_alloca__left = LOCAL_ALLOCA__BYTE_SIZE; uint16_t local_alloca__used = 0; uint16_t local_alloca__requested; 

#define LOCAL_ALLOCA(REQUESTED_SIZEOF)					\
  (local_alloca__requested = (REQUESTED_SIZEOF), ((local_alloca__requested > local_alloca__left) ? NULL : (local_alloca__left -= local_alloca__requested, local_alloca__used += local_alloca__requested,  local_alloca__mem + local_alloca__used - local_alloca__requested))) 

int_anime_error_t anime__fill_from_file(anime_t * this, const char * input_name, const int input_fd, const int stduser_d) { 
  LOCAL_ALLOCA__DECLARE(UINT16_MAX); 
  int_anime_error_t         error_id; 
  anime_token_input_env_t   input_env[1]; 
  //dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
#if defined VLA__YES
  char                      token_env_b[anime_token_env__sizeof]; // For some unknown reasons, VLAs make «-fstack-protector» fail. 
#elif defined ALLOCA__YES
  char                    * token_env_b = alloca(anime_token_env__sizeof); 
#elif defined LOCAL_ALLOCA__YES
  char                    * token_env_b = LOCAL_ALLOCA(anime_token_env__sizeof); 
#endif 
  anime_token_env_t       * token_env; 

#if 0
  dputs_array(stderr_d, "TOKEN_ENV_SIZEOF = ", int_string(sizeof(token_env_b)), "\n"); 
  dputs_array(stderr_d, "TOKEN_ENV_B IS NULL HUH = ", bool_string(token_env_b == NULL), "\n"); 
  dputs_array(stderr_d, "local_alloca__requested = ", int_string(local_alloca__requested), "\n"); 
  dputs_array(stderr_d, "anime_token_env__sizeof = ", int_string(anime_token_env__sizeof), "\n"); 
  dputs_array(stderr_d, "local_alloca__left = ", int_string(local_alloca__left), "\n"); 
  dputs_array(stderr_d, "local_alloca__used = ", int_string(local_alloca__used), "\n"); 
#endif 
  
  anime_token_input_env__make_r(input_env, this -> stdlog_d); 
  
  token_env = anime_token_env__make_b(anime_token_env__sizeof, token_env_b, NULL, this -> stdlog_d); 
  //dputs_array(stderr_d, "TOKEN_ENV IS NULL HUH = ", bool_string(token_env == NULL), "\n"); 
  
  this -> filename = anime__strcopy(this, input_name); 
  
  const int input_i = anime_token_input__stack_push__filedes(input_env, input_fd, input_name); 
  if (input_i < 0) { goto error_label__input_error; }; 
  
  error_id = anime_token__parser(token_env, input_env, input_i, &this -> error_id, this -> error_size, this -> error_str); 
  if (error_id != ANIME__OK) { return error_id; }; 
  
  if (this -> stdlog_d > 0) { anime_token__print_all_tokens(this -> stdlog_d, token_env); fflush(NULL); }; 
  
  error_id = anime_data_generation_003_from_syntax_filtering(token_env, this, stduser_d); 
  if (error_id != ANIME__OK) { return error_id; }; 
	
  error_id = anime__consistency_check(this, stduser_d); 
  return error_id; 
  
  
 error_label__input_error: { 
    this -> error_id = ANIME__TOKEN__INPUT__ERROR; 
    snprintf(this -> error_str, this -> error_size, "Error while initializing input buffer for tokenizing: %d", input_i); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 
  
}; 

















int_anime_error_t anime__print_field_value_by_name(const anime_t * this, const char * field_name, const int stdprint_d, const int stduser_d, int_anime_error_t * error_id_r, const uint16_t error_size, char * error_str) { 
  if (NULL == error_id_r) { return ANIME__DATA_GENERATION__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  if (NULL ==       this) { *error_id_r = ANIME__NULL_STRUCT    ; snprintf(error_str, error_size, "'this' argument is null."    ); return *error_id_r; }; 
  if (NULL == field_name) { *error_id_r = ANIME__NULL_FIELD_NAME; snprintf(error_str, error_size, "field_name argument is null."); return *error_id_r; }; 

  if      ( 0 == this -> filled_huh) { 
    snprintf(error_str, error_size, "Anime data structure empty — still printing its content though."); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Warning: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, error_str); }; 
  } 
  else if (-1 == this -> filled_huh) { 
    snprintf(error_str, error_size, "Anime data structure only partially filled — still printing its content though."); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Warning: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, error_str); }; 
  } 
  else if ( 1 == this -> filled_huh) { } 
  else if ( 2 == this -> filled_huh) { } 
  else if ( 3 == this -> filled_huh) { 
    snprintf(error_str, error_size, "Anime data structure has breaking unconsistencies."); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Info: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Info: " "%s" "\n", __func__, error_str); }; 
  } 
  else if ( 4 == this -> filled_huh) { 
    snprintf(error_str, error_size, "Anime data structure has non-breaking unconsistencies."); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Info: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Info: " "%s" "\n", __func__, error_str); }; 
  } 
  else { 
    snprintf(error_str, error_size, "Anime data structure has an unknown filling status — still printing its content though."); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Warning: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, error_str); }; 
  }; 
  

  if (0 == strncasecmp("physique" , field_name, strlen("physique")))  goto label__physique_field; 
  if (0 == strncasecmp("gameplay" , field_name, strlen("gameplay")))  goto label__gameplay_field; 
  if (0 == strncasecmp("graphique", field_name, strlen("graphique"))) goto label__graphique_field; 
  
  goto label__unknown_field; 



  
  
 label__physique_field: { 
    if ((0 == strcasecmp("physique", field_name)) || (0 == strcasecmp("physique.", field_name))) { 
      dprintf(stdprint_d, "physique.zone_de_choc.longueur = %10f " "\n", this -> choc_longueur); 
      dprintf(stdprint_d, "physique.zone_de_choc.largeur  = %10f " "\n", this -> choc_largeur ); 
      dprintf(stdprint_d, "physique.zone_de_choc.hauteur  = %10f " "\n", this -> choc_hauteur ); 
      dprintf(stdprint_d, "physique.masse = %10f " "\n", this -> masse); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    if ((0 == strcasecmp("physique.zone_de_choc", field_name)) || (0 == strcasecmp("physique.zone_de_choc.", field_name)) || 
	(0 == strcasecmp("physique.zone-de-choc", field_name)) || (0 == strcasecmp("physique.zone-de-choc.", field_name)) || 
	(0 == strcasecmp("physique.zone de choc", field_name)) || (0 == strcasecmp("physique.zone de choc.", field_name)) || 
	(0 == strcasecmp("physique.choc"        , field_name)) || (0 == strcasecmp("physique.choc."        , field_name))) { 
      dprintf(stdprint_d, "physique.zone_de_choc.longueur = %10f " "\n", this -> choc_longueur); 
      dprintf(stdprint_d, "physique.zone_de_choc.largeur  = %10f " "\n", this -> choc_largeur ); 
      dprintf(stdprint_d, "physique.zone_de_choc.hauteur  = %10f " "\n", this -> choc_hauteur ); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    };

    if ((0 == strcasecmp("physique.zone_de_choc.longueur", field_name)) || 
	(0 == strcasecmp("physique.zone-de-choc.longueur", field_name)) || 
	(0 == strcasecmp("physique.zone de choc.longueur", field_name)) || 
	(0 == strcasecmp("physique.choc.longueur"        , field_name)) || 
	(0 == strcasecmp("physique.longueur"             , field_name))) { 
      dprintf(stdprint_d, "physique.zone_de_choc.longueur = %10f " "\n", this -> choc_longueur); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    if ((0 == strcasecmp("physique.zone_de_choc.largeur", field_name)) || 
	(0 == strcasecmp("physique.zone-de-choc.largeur", field_name)) || 
	(0 == strcasecmp("physique.zone de choc.largeur", field_name)) || 
	(0 == strcasecmp("physique.choc.largeur"        , field_name)) || 
	(0 == strcasecmp("physique.largeur"             , field_name))) { 
      dprintf(stdprint_d, "physique.zone_de_choc.largeur  = %10f " "\n", this -> choc_largeur ); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    if ((0 == strcasecmp("physique.zone_de_choc.hauteur", field_name)) || 
	(0 == strcasecmp("physique.zone-de-choc.hauteur", field_name)) || 
	(0 == strcasecmp("physique.zone de choc.hauteur", field_name)) || 
	(0 == strcasecmp("physique.choc.hauteur"        , field_name)) || 
	(0 == strcasecmp("physique.hauteur"             , field_name))) { 
      dprintf(stdprint_d, "physique.zone_de_choc.hauteur  = %10f " "\n", this -> choc_hauteur ); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    if ((0 == strcasecmp("physique.masse", field_name))) { 
      dprintf(stdprint_d, "physique.masse = %10f " "\n", this -> masse); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    goto label__unknown_field; 
  }; 
  
  
 label__gameplay_field: { 
    if ((0 == strcasecmp("gameplay", field_name)) || (0 == strcasecmp("gameplay.", field_name))) { 
      dprintf(stdprint_d, "gameplay.points_de_vie = %5d " "\n", this -> vie); 
      dprintf(stdprint_d, "gameplay.invincible    = %5s " "\n", this -> invincible ? "vrai" : "faux"); 
      dprintf(stdprint_d, "gameplay.hostile       = %5s " "\n", this -> hostile    ? "vrai" : "faux"); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    if ((0 == strcasecmp("gameplay.points_de_vie", field_name)) || 
	(0 == strcasecmp("gameplay.points de vie", field_name)) || 
	(0 == strcasecmp("gameplay.points-de-vie", field_name))) { 
      dprintf(stdprint_d, "gameplay.points_de_vie = %5d " "\n", this -> vie); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 

    if ((0 == strcasecmp("gameplay.invincible", field_name))) { 
      dprintf(stdprint_d, "gameplay.invincible    = %5s " "\n", this -> invincible ? "vrai" : "faux"); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 

    if ((0 == strcasecmp("gameplay.hostile", field_name))) { 
      dprintf(stdprint_d, "gameplay.hostile       = %5s " "\n", this -> hostile    ? "vrai" : "faux"); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    goto label__unknown_field; 
  }; 
  





 label__graphique_field: { 
    if ((0 == strcasecmp("graphique", field_name)) || (0 == strcasecmp("graphique.", field_name))) { 
      dprintf(stdprint_d, "graphique.membres_nb = %d " "\n", this -> membres_nb); 
      for (int i = 0; i < this -> membres_nb; i++) { 
	dprintf(stdprint_d, "graphique.membre[%15s].fils        =      " "\n", this -> membres_nom[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].image       = %30s " "\n", this -> membres_nom[i], this -> membres_image[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].largeur     = %15f " "\n", this -> membres_nom[i], this -> membres_largeur[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].hauteur     = %15f " "\n", this -> membres_nom[i], this -> membres_hauteur[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].angle_max_y = %15f " "\n", this -> membres_nom[i], this -> membres_angle_max_y[i]); 
      }; 
      dprintf(stdprint_d, "graphique.racines_nb = %d " "\n", this -> racines_nb); 
      for (int i = 0; i < this -> racines_nb; i++) { 
	dprintf(stdprint_d, "graphique.racine[%2d].qui     = %15s " "\n", i, this -> racines_qui[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].x       = %15f " "\n", i, this -> racines_x[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].y       = %15f " "\n", i, this -> racines_y[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].z       = %15f " "\n", i, this -> racines_z[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].angle_y = %15f " "\n", i, this -> racines_angle_y[i]); 
      }; 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 

    if ((0 == strcasecmp("graphique.membre" , field_name)) || (0 == strcasecmp("graphique.membre." , field_name)) || 
	(0 == strcasecmp("graphique.membres", field_name)) || (0 == strcasecmp("graphique.membres.", field_name))) { 
      dprintf(stdprint_d, "graphique.membres_nb = %d " "\n", this -> membres_nb); 
      for (int i = 0; i < this -> membres_nb; i++) { 
	dprintf(stdprint_d, "graphique.membre[%15s].fils        =      " "\n", this -> membres_nom[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].image       = %30s " "\n", this -> membres_nom[i], this -> membres_image[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].largeur     = %15f " "\n", this -> membres_nom[i], this -> membres_largeur[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].hauteur     = %15f " "\n", this -> membres_nom[i], this -> membres_hauteur[i]); 
	dprintf(stdprint_d, "graphique.membre[%15s].angle_max_y = %15f " "\n", this -> membres_nom[i], this -> membres_angle_max_y[i]); 
      }; 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 

    if ((0 == strcasecmp("graphique.racine" , field_name)) || (0 == strcasecmp("graphique.racine." , field_name)) || 
	(0 == strcasecmp("graphique.racines", field_name)) || (0 == strcasecmp("graphique.racines.", field_name))) { 
      dprintf(stdprint_d, "graphique.racines_nb = %d " "\n", this -> racines_nb); 
      for (int i = 0; i < this -> racines_nb; i++) { 
	dprintf(stdprint_d, "graphique.racine[%2d].qui     = %15s " "\n", i, this -> racines_qui[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].x       = %15f " "\n", i, this -> racines_x[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].y       = %15f " "\n", i, this -> racines_y[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].z       = %15f " "\n", i, this -> racines_z[i]); 
	dprintf(stdprint_d, "graphique.racine[%2d].angle_y = %15f " "\n", i, this -> racines_angle_y[i]); 
      }; 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 

    if ((0 == strcasecmp("graphique.membres_nb", field_name))) { 
      dprintf(stdprint_d, "graphique.membres_nb = %d " "\n", this -> membres_nb); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 

    if ((0 == strcasecmp("graphique.racines_nb", field_name))) { 
      dprintf(stdprint_d, "graphique.racines_nb = %d " "\n", this -> racines_nb); 
      *error_id_r = ANIME__OK; 
      return *error_id_r; 
    }; 
    
    do { 
      const char * prefix = "graphique.membre["; 
      const int prefix_len = strlen(prefix); 
      if ((0 != strncasecmp(prefix, field_name, prefix_len))) break; 
      int index_len = 0; const char * p = field_name + prefix_len; 
      //dprintf(stderr_d, "p = %s" "\n", p); 
      for (;;) { if (*p == ']') break; if (*p == '\0') { index_len = -1; break; }; p++; index_len++; }; 
      //dprintf(stderr_d, "index_len = %d" "\n", index_len); 
      
      const char * short_field_name = p + 1; 
      while (isspace(*(p-1))) { p--; index_len--; }; 
      if (0 != index_len) { 
	p = field_name + prefix_len; 
	while (isspace(*p)) { p++; index_len--; }; 
      }; 
      
      if (index_len < 0) { goto label__unknown_field; }; 
      
      if (0 == index_len) { 
	if ((0 == strcasecmp("", short_field_name)) || (0 == strcasecmp(".", short_field_name))) { 
	  for (int i = 0; i < this -> membres_nb; i++) { 
	    dprintf(stdprint_d, "graphique.membre[%15s].fils        =      " "\n", this -> membres_nom[i]); 
	    dprintf(stdprint_d, "graphique.membre[%15s].image       = %30s " "\n", this -> membres_nom[i], this -> membres_image[i]); 
	    dprintf(stdprint_d, "graphique.membre[%15s].largeur     = %15f " "\n", this -> membres_nom[i], this -> membres_largeur[i]); 
	    dprintf(stdprint_d, "graphique.membre[%15s].hauteur     = %15f " "\n", this -> membres_nom[i], this -> membres_hauteur[i]); 
	    dprintf(stdprint_d, "graphique.membre[%15s].angle_max_y = %15f " "\n", this -> membres_nom[i], this -> membres_angle_max_y[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".fils", short_field_name))) { 
	  for (int i = 0; i < this -> membres_nb; i++) { 
	    dprintf(stdprint_d, "graphique.membre[%15s].fils        =      " "\n", this -> membres_nom[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".image", short_field_name))) { 
	  for (int i = 0; i < this -> membres_nb; i++) { 
	    dprintf(stdprint_d, "graphique.membre[%15s].image       = %30s " "\n", this -> membres_nom[i], this -> membres_image[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".largeur", short_field_name))) { 
	  for (int i = 0; i < this -> membres_nb; i++) { 
	    dprintf(stdprint_d, "graphique.membre[%15s].largeur     = %15f " "\n", this -> membres_nom[i], this -> membres_largeur[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".hauteur", short_field_name))) { 
	  for (int i = 0; i < this -> membres_nb; i++) { 
	    dprintf(stdprint_d, "graphique.membre[%15s].hauteur     = %15f " "\n", this -> membres_nom[i], this -> membres_hauteur[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".angle_max_y", short_field_name)) || 
	    (0 == strcasecmp(".angle-max-y", short_field_name)) || 
	    (0 == strcasecmp(".angle max y", short_field_name)) || 
	    (0 == strcasecmp(".max_angle_y", short_field_name)) || 
	    (0 == strcasecmp(".max-angle-y", short_field_name)) || 
	    (0 == strcasecmp(".max angle y", short_field_name)) || 
	    (0 == strcasecmp(".angle_y_max", short_field_name)) || 
	    (0 == strcasecmp(".angle-y-max", short_field_name)) || 
	    (0 == strcasecmp(".angle y max", short_field_name))) { 
	  for (int i = 0; i < this -> membres_nb; i++) { 
	    dprintf(stdprint_d, "graphique.membre[%15s].angle_max_y = %15f " "\n", this -> membres_nom[i], this -> membres_angle_max_y[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 

	goto label__unknown_field; 
      }; 
      
      //dprintf(stderr_d, "p = %s" "\n", p); 
      int index; 
      if (isdigit(*p)) { 
	index = 0; 
	for (int i = 0; i < index_len; i++) { 
	  const char c = *(p + i); 
	  if (!isdigit(c)) break; 
	  index = 10 * index + (c - '0'); 
	}; 
	//dprintf(stderr_d, "index = %d" "\n", index); 
	if (index >= this -> membres_nb) { goto error_label__index_out_of_bounds; }; 
      } 
      else { 
	index = ~0; 
	for (int i = 0; i < this -> membres_nb; i++) { 
	  const int len = strlen(this -> membres_nom[i]); 
	  if (len != index_len) continue; 
	  if (0 != strncasecmp(p, this -> membres_nom[i], index_len)) continue; 
	  index = i; 
	  break; 
	}; 
	//dprintf(stderr_d, "index = %d" "\n", index); 
	if (index < 0) { goto error_label__index_out_of_bounds; }; 
      };
      //dprintf(stderr_d, "index = %d" "\n", index); 
      
      
      if ((0 == strcasecmp("", short_field_name)) || (0 == strcasecmp(".", short_field_name))) { 
	dprintf(stdprint_d, "graphique.membre[%15s].fils        =      " "\n", this -> membres_nom[index]); 
	dprintf(stdprint_d, "graphique.membre[%15s].image       = %30s " "\n", this -> membres_nom[index], this -> membres_image[index]); 
	dprintf(stdprint_d, "graphique.membre[%15s].largeur     = %15f " "\n", this -> membres_nom[index], this -> membres_largeur[index]); 
	dprintf(stdprint_d, "graphique.membre[%15s].hauteur     = %15f " "\n", this -> membres_nom[index], this -> membres_hauteur[index]); 
	dprintf(stdprint_d, "graphique.membre[%15s].angle_max_y = %15f " "\n", this -> membres_nom[index], this -> membres_angle_max_y[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".fils", short_field_name))) { 
	dprintf(stdprint_d, "graphique.membre[%15s].fils        =      " "\n", this -> membres_nom[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".image", short_field_name))) { 
	dprintf(stdprint_d, "graphique.membre[%15s].image       = %30s " "\n", this -> membres_nom[index], this -> membres_image[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".largeur", short_field_name))) { 
	dprintf(stdprint_d, "graphique.membre[%15s].largeur     = %15f " "\n", this -> membres_nom[index], this -> membres_largeur[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".hauteur", short_field_name))) { 
	dprintf(stdprint_d, "graphique.membre[%15s].hauteur     = %15f " "\n", this -> membres_nom[index], this -> membres_hauteur[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".angle_max_y", short_field_name)) || 
	  (0 == strcasecmp(".angle-max-y", short_field_name)) || 
	  (0 == strcasecmp(".angle max y", short_field_name)) || 
	  (0 == strcasecmp(".max_angle_y", short_field_name)) || 
	  (0 == strcasecmp(".max-angle-y", short_field_name)) || 
	  (0 == strcasecmp(".max angle y", short_field_name)) || 
	  (0 == strcasecmp(".angle_y_max", short_field_name)) || 
	  (0 == strcasecmp(".angle-y-max", short_field_name)) || 
	  (0 == strcasecmp(".angle y max", short_field_name))) { 
	dprintf(stdprint_d, "graphique.membre[%15s].angle_max_y = %15f " "\n", this -> membres_nom[index], this -> membres_angle_max_y[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      
      goto label__unknown_field; 
    } while (false); 





    do { 
      const char * prefix = "graphique.racine["; 
      const int prefix_len = strlen(prefix); 
      if ((0 != strncasecmp(prefix, field_name, prefix_len))) break; 
      int index_len = 0; const char * p = field_name + prefix_len; 
      for (;;) { if (*p == ']') break; if (*p == '\0') { index_len = -1; break; }; p++; index_len++; }; 
      const char * short_field_name = p + 1; 
      while (isspace(*(p-1))) { p--; index_len--; }; 
      if (0 != index_len) { 
	p = field_name + prefix_len; 
	while (isspace(*p)) { p++; index_len--; }; 
      }; 

      //dprintf(stderr_d, "index_len = %d" "\n", index_len); 
      if (index_len < 0) { goto label__unknown_field; }; 

      if (0 == index_len) { 
	if ((0 == strcasecmp("", short_field_name)) || (0 == strcasecmp(".", short_field_name))) { 
	  for (int i = 0; i < this -> racines_nb; i++) { 
	    dprintf(stdprint_d, "graphique.racine[%2d].qui     = %15s " "\n", i, this -> racines_qui[i]); 
	    dprintf(stdprint_d, "graphique.racine[%2d].x       = %15f " "\n", i, this -> racines_x[i]); 
	    dprintf(stdprint_d, "graphique.racine[%2d].y       = %15f " "\n", i, this -> racines_y[i]); 
	    dprintf(stdprint_d, "graphique.racine[%2d].z       = %15f " "\n", i, this -> racines_z[i]); 
	    dprintf(stdprint_d, "graphique.racine[%2d].angle_y = %15f " "\n", i, this -> racines_angle_y[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".qui", short_field_name))) { 
	  for (int i = 0; i < this -> racines_nb; i++) { 
	    dprintf(stdprint_d, "graphique.racine[%2d].qui     = %15s " "\n", i, this -> racines_qui[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".x", short_field_name))) { 
	  for (int i = 0; i < this -> racines_nb; i++) { 
	    dprintf(stdprint_d, "graphique.racine[%2d].x       = %15f " "\n", i, this -> racines_x[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".y", short_field_name))) { 
	  for (int i = 0; i < this -> racines_nb; i++) { 
	    dprintf(stdprint_d, "graphique.racine[%2d].y       = %15f " "\n", i, this -> racines_y[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".z", short_field_name))) { 
	  for (int i = 0; i < this -> racines_nb; i++) { 
	    dprintf(stdprint_d, "graphique.racine[%2d].z       = %15f " "\n", i, this -> racines_z[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 
	if ((0 == strcasecmp(".angle_y", short_field_name)) || 
	    (0 == strcasecmp(".angle-y", short_field_name)) || 
	    (0 == strcasecmp(".angle y", short_field_name))) { 
	  for (int i = 0; i < this -> racines_nb; i++) { 
	    dprintf(stdprint_d, "graphique.racine[%2d].angle_y = %15f " "\n", i, this -> racines_angle_y[i]); 
	  }; 
	  *error_id_r = ANIME__OK; 
	  return *error_id_r; 
	}; 

	goto label__unknown_field; 
      }; 
      
      //dprintf(stderr_d, "p = %s" "\n", p); 
      int index; 
      if (isdigit(*p)) { 
	index = 0; 
	for (int i = 0; i < index_len; i++) { 
	  const char c = *(p + i); 
	  if (!isdigit(c)) break; 
	  index = 10 * index + (c - '0'); 
	}; 
	//dprintf(stderr_d, "index = %d" "\n", index); 
	if (index >= this -> racines_nb) { goto error_label__index_out_of_bounds; }; 
      } 
      else { 
	index = ~0; 
	for (int i = 0; i < this -> racines_nb; i++) { 
	  const int len = strlen(this -> racines_qui[i]); 
	  if (len != index_len) continue; 
	  if (0 != strncasecmp(p, this -> racines_qui[i], index_len)) continue; 
	  index = i; 
	  break; 
	}; 
	//dprintf(stderr_d, "index = %d" "\n", index); 
	if (index < 0) { goto error_label__index_out_of_bounds; }; 
      };
      //dprintf(stderr_d, "index = %d" "\n", index); 
      
      
      if ((0 == strcasecmp("", short_field_name)) || (0 == strcasecmp(".", short_field_name))) { 
	dprintf(stdprint_d, "graphique.racine[%2d].qui     = %15s " "\n", index, this -> racines_qui[index]); 
	dprintf(stdprint_d, "graphique.racine[%2d].x       = %15f " "\n", index, this -> racines_x[index]); 
	dprintf(stdprint_d, "graphique.racine[%2d].y       = %15f " "\n", index, this -> racines_y[index]); 
	dprintf(stdprint_d, "graphique.racine[%2d].z       = %15f " "\n", index, this -> racines_z[index]); 
	dprintf(stdprint_d, "graphique.racine[%2d].angle_y = %15f " "\n", index, this -> racines_angle_y[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".qui", short_field_name))) { 
	dprintf(stdprint_d, "graphique.racine[%2d].qui     = %15s " "\n", index, this -> racines_qui[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".x", short_field_name))) { 
	dprintf(stdprint_d, "graphique.racine[%2d].x       = %15f " "\n", index, this -> racines_x[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".y", short_field_name))) { 
	dprintf(stdprint_d, "graphique.racine[%2d].y       = %15f " "\n", index, this -> racines_y[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".z", short_field_name))) { 
	dprintf(stdprint_d, "graphique.racine[%2d].z       = %15f " "\n", index, this -> racines_z[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 
      if ((0 == strcasecmp(".angle_y", short_field_name)) || 
	  (0 == strcasecmp(".angle-y", short_field_name)) || 
	  (0 == strcasecmp(".angle y", short_field_name))) { 
	dprintf(stdprint_d, "graphique.racine[%2d].angle_y = %15f " "\n", index, this -> racines_angle_y[index]); 
	*error_id_r = ANIME__OK; 
	return *error_id_r; 
      }; 


      

      goto label__unknown_field; 
    } while (false); 



    goto label__unknown_field; 
  }; 





  

 error_label__index_out_of_bounds: { 
    //dprintf(stderr_d, "STDLOG_D = %d" "\n", this -> stdlog_d); 
    //dprintf(stderr_d, "(this -> stdlog_d  > 0) = %s" "\n", (this -> stdlog_d  > 0) ? "vrai" : "faux"); 
  
    *error_id_r = ANIME__INDEX_OF_OUT_BOUNDS; 
    snprintf(error_str, error_size, "Index out of bounds: %s", field_name); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Error: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    fflush(NULL); 
    return *error_id_r; 
  }; 
  
 label__unknown_field: { 
    *error_id_r = ANIME__UNKNOWN_FIELD; 
    snprintf(error_str, error_size, "Unknown field: %s", field_name); 
    if (stduser_d         > 0) { dprintf(stduser_d, "Warning: " "%s" "\n", error_str); }; 
    if (this -> stdlog_d  > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Warning: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
}; 



#define UUU(ident) case glue(ANIME__,ident): error_cstr = STRINGIFY(ident); break; 

const char * int_anime_error__get_cstr(const int_anime_error_t error_id) { 
  const char * error_cstr = NULL; 
  switch (error_id) { 
  UUU(OK); 
  // Unspecified 
  UUU(ERROR_GENERIC); 
  // Errors 
  UUU(STRCOPY); 
  UUU(FD_NEG); 
  UUU(FDOPEN); 
  UUU(NULL_FIELD_NAME); 
  UUU(UNKNOWN_FIELD); 
  UUU(INDEX_OF_OUT_BOUNDS);
  UUU(NULL_ERROR_ID_R); 
  UUU(ERROR_SIZE_LOWER_THAN_1); 
  UUU(NULL_INPUT_ENV); 
  UUU(NULL_TOKEN_ENV); 
  UUU(TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM); 
  UUU(TOKEN_PARSER__TOKEN_MATCHES_NO_PATTERN); 
  UUU(TOKEN_PARSER__ERROR_TOKEN); 
  UUU(TOKEN_PARSER__STACK_OVERFLOW); 
  UUU(DATA_GENERATION__NULL_SYNTAX_FILTERING); 
  UUU(DATA_GENERATION__NULL_TOKEN_ENV); 
  UUU(DATA_GENERATION__NULL_ANIME_DATA); 
  UUU(DATA_GENERATION__NULL_FLOATVAL_R); 
  UUU(DATA_GENERATION__NULL_INTVAL_R); 
  UUU(DATA_GENERATION__NULL_ERROR_ID_R); 
  UUU(DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1); 
  UUU(DATA_GENERATION__NOT_ENOUGH_TOKENS); 
  UUU(DATA_GENERATION__TOO_MANY_TOKENS); 
  UUU(DATA_GENERATION__NON_MATCHING_TOKEN_TYPE); 
  UUU(DATA_GENERATION__NON_MATCHING_TOKEN_VALUE); 
  UUU(DATA_GENERATION__NULL_TREE_ENV); 
  UUU(DATA_GENERATION__TREE_ENV__EMPTY);
  UUU(DATA_GENERATION__TREE_ENV__BEING_FILLED);
  UUU(DATA_GENERATION__TREE_ENV__NOT_FILLED);
  UUU(DATA_GENERATION__NOT_ENOUGH_TREES); 
  UUU(DATA_GENERATION__TREE__WRONG_TREE_TYPE);
  UUU(DATA_GENERATION__MISSING_PHYSIQUE_SECTION); 
  UUU(DATA_GENERATION__MISSING_GAMEPLAY_SECTION); 
  UUU(DATA_GENERATION__MISSING_GRAPHIQUE_SECTION); 
  UUU(DATA_GENERATION__STACK_OVERFLOW); 
  UUU(DATA_GENERATION__STACK_UNDERFLOW); 
  UUU(DATA_GENERATION__STACK_UNEXPECTED_TOKEN); 
  UUU(DATA_GENERATION__STACK_TOO_MANY_ITEMS); 
  UUU(DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS); 
  UUU(DATA_GENERATION__MEMBRES_OVERFLOW); 
  UUU(DATA_GENERATION__RACINES_OVERFLOW); 
  UUU(TREE__NO_SPACE_LEFT); 
  UUU(TREE__WRONG_ADDRESS); 
  UUU(SYNTAX_FILTERING__NULL_THIS); 
  UUU(SYNTAX_FILTERING__NULL_TOKEN_ENV); 
  UUU(SYNTAX_FILTERING__NULL_TOKEN_I); 
  UUU(SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_TOO_SMALL); 
  UUU(SYNTAX_FILTERING__PARENTHESIS_STACK_TOO_SMALL); 
  UUU(SYNTAX_FILTERING__MISSING_CLOSING_PARENTHESIS); 
  UUU(SYNTAX_FILTERING__MISSING_OPENING_PARENTHESIS); 
  UUU(SYNTAX_FILTERING__MISMATCHING_PARENTHESIS); 
  UUU(SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS); 
  UUU(SYNTAX_FILTERING__NOT_AN_CLOSING_PARENTHESIS); 
  UUU(SYNTAX_FILTERING__CANNOT_SKIP_TO_CLOSING_PARENTHESIS_IN_LALR_MODE); 
  UUU(SYNTAX_FILTERING__CURRENT_TOKEN_OUT_OF_BOUND); 
  UUU(SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID); 
  UUU(SYNTAX_FILTERING__CURRENT_TOKEN_IS_EOF); 
  UUU(SYNTAX_FILTERING__LAST_TOKEN_SHOULD_BE_EOF); 
  UUU(SYNTAX_FILTERING__LALR_MODE_ALREADY_SET); 
  UUU(MAIN__OPTIONS__PARSING_ERROR); 
  UUU(MAIN__OPTIONS__UNKNOWN); 
  UUU(MAIN__OPTIONS__EXIT_QUICK); 
  UUU(MAIN__CANNOT_OPEN_INPUT_FILE); 
  UUU(TOKEN__PARSER__ERROR); 
  UUU(TOKEN__INPUT__ERROR); 
  // Warnings 
  UUU(NULL_STRUCT); 
  UUU(EMPTY_STRUCTURE); 
  UUU(FILLING_NOT_COMPLETED); 
  UUU(HAS_BREAKING_UNCONSISTENCIES); 
  UUU(HAS_NON_BREAKING_UNCONSISTENCIES); 
  UUU(SYNTAX_FILTERING__TOKEN_ENV_HAS_ZERO_TOKEN); 
  };
  return error_cstr; 
}; 



const char * anime__convert_token_cstring_to_regular_string(anime_t * this, const char * cstr) { 
  if (NULL ==  cstr) return cstr; 
  if ('\0' == *cstr) return this -> string_stack; 
  const size_t len0 = strlen(cstr); 
  //char tmp[len0]; // For some unknown reasons, VLAs make «-fstack-protector» fail. 
  char * tmp = alloca(len0); 
  bcopy(cstr+1, tmp, len0-2); 
  tmp[len0-2] = '\0'; 
  return anime__strcopy(this, tmp); 
}; 
