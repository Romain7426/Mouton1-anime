#include "anime_inc.hi"
#include "anime.h"
#include "anime_module.h"
#include "anime_type.h"
#include "anime_lexer_module.h"
#include "anime_syntax_module.h"
#include "anime_generation_module.h"

#include "anime_module_type.hi"

#include "anime_module_type.ci"
#include "anime_module_string.ci" 
#include "anime_module_subr.ci" 
//#include "anime_module_error.ci" 
#include "anime_module_print.ci" 
#include "anime_module_print_field.ci" 
#include "anime_module_consistency.ci" 
#include "anime_module_dump_and_restore.ci"
#include "anime_module_lexeme.ci"
#include "anime_module_divers.ci"
#include "anime_module_endian_swap.ci"




#if 0
// FRA <RL>
// Ce module est le point d'entrée du programme. 
// Il est le coordonnateur entre les sous-modules. 
// Lui-même ne calcule rien. 
// Les autres modules sont le traitement pendant que il est la commande. 
// 
// anime_module.h est vide puisque: 
//  - Il n'est le sous-module d'aucun module. 
//    Donc il n'exporte aucune fonction à un sur-module. 
//  - Il n'exporte que les fonctions exportées dans la bibliothèque, 
//    c'est-à-dire celles déclarées dans anime.h. 
// 
// Pour les sous-modules, les fonctions exportées par les sous-modules sont les 
// fonctions utilisées par le module coordinateur. 
// 
// Les sous-modules: 
//  - anime_lexer_module.c 
//  - anime_syntax_module.c 
//  - anime_generation_module.c 
// 
// Le sous-module anime_lexer_module.c procède à l'analyse lexicale:
//  - celui-là recompose le fichier de description (une suite de caractères) 
//    en unités lexicales (lexèmes, tokens), c'est-à-dire manipulable 
//    par l'analyseur de structure. 
// 
// Le sous-module anime_syntax_module.c procède à l'analyse syntaxique:
//  - Celui-là vérifie la structure du fichier de description.
//    Celui-ci est-il correctement structuré? 
//    Celui-ci est-il correctement écrit? 
//  - Techniquement, du fait des expressions infixes pouvant avoir un nombre arbitraire 
//    de sous-expressions, il s'agit de la partie la plus complexe. 
//     * Interdire les sous-expressions réduirait considérablement la complexité. 
//     * Pour analyser les sous-expressions, il est nécessaire d'avoir un automate d'analyse. 
//     * En l'espèce, l'automate d'analyse ne contient que deux états. 
//       (Voire la fonction <anime__syntax_expr__sous_expression_huh()>.) 
//       (Il s'agit d'un automate LR(0) qui regarde le caractère sur le ruban pour 
//        décider de la transition - c'est donc un automate LALR(0).) 
// 
// 
// Le sous-module anime_generation_module.c procède à l'évaluation et au remplissage de la structure de données:
//  - Rien à ajouter. 
// 
// Chaque sous-module est composé de sous-fichiers.
// Chacun sont directement inclus dans le sous-module:
//  - Les fichiers hi et les fichier ci.
// 
// Également, il existe le module "main.c" pour le programmen indépendant 
// d'analyse et de vérification d'un fichier de description. 
// Ce module est indépendant de la bibliothèque: 
//  - Celui-là n'inclut que le fichier anime.h. 
//  - Après la compilation, il est lié à la bibliothèque anime.a. 
// 
// Aussi, il y a le fichier "anime_global.h". 
// Celui-ci contient des définitions communes internes à la bibliothèque. 
// Il devrait pas etre inclu par main. 
// (Il pourrait être renommé "anime_common_def.h"? Ou "anime_common_headers.h"?) 
// Il ne devrait pas y avoir de "anime_global.c".
//
// Enfin, il y a les bibliothèques communes: lib*.ci.
#endif 




int_anime_error_t anime__fill_from_file(anime_t * this, const char * filepathname, const int stduser_d) { 
  const int fd = open(filepathname, O_RDONLY); 
  if (0 > fd) return ANIME__CANNOT_OPEN_INPUT_FILE; 
  return anime__fill_from_fd(this, filepathname, fd, stduser_d); 
};


int_anime_error_t anime__fill_from_buffer(anime_t * this, const char * input_name, const char * buffer, const int16_t buffer_bytesize, const int stduser_d) { 
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
  goto label__body; 

  int16_t error_sub__line = -1;
  //label__error__sub: {
 label__error__cannot_make_pipe: { 
    this -> error_id = ANIME__CANNOT_MAKE_PIPE; 
    *this -> error_str = '\0'; 
    DISPLAY_TRACE(this -> stdlog_d, this -> error_id); 
    return this -> error_id; 
  }; 

 label__pipe_buffer_size_ok: { 
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    int buffer_pipe[2]; // RL: [0] is output (read end), [1] is input (write end) 
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    if (-1 == pipe(buffer_pipe)) { error_sub__line = __LINE__ ; goto label__error__cannot_make_pipe; }; 
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    write(buffer_pipe[1], buffer, buffer_bytesize); 
    close(buffer_pipe[1]);
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    this -> error_id = anime__fill_from_fd(this, input_name, buffer_pipe[0], stduser_d); 
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    close(buffer_pipe[0]);
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    return this -> error_id;
  }; 

 label__pipe_buffer_size_is_too_small: { 
#define DEBUG_TRACE 1
#ifdef DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    const int my_buffer_fd = buffer_to_fd__open(buffer, buffer_bytesize); 
#ifdef DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    if (0 > my_buffer_fd) { error_sub__line = __LINE__ ; goto label__error__cannot_make_pipe; }; 
#ifdef DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    this -> error_id = anime__fill_from_fd(this, input_name, my_buffer_fd, stduser_d); 
#ifdef DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    buffer_to_fd__close(my_buffer_fd); 
#ifdef DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
    return this -> error_id;
#undef DEBUG_TRACE 
  }; 
  
 label__body: {   
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "{" __FILE__ ":%d:<%s()>}: -- DEBUG: %d " "%s" "\n", __LINE__, __func__, __LINE__, ""); dputs(STDERR_FILENO, trace); }; 
#endif
#if DEBUG_TRACE
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "PIPEBUFFERSIZE: %lld" "\n", (long long int) PIPEBUFFERSIZE); dputs(STDERR_FILENO, trace); }; 
    { char trace[INT8_MAX]; snprintf(trace, sizeof(trace), "buffer_bytesize: %lld" "\n", (long long int) buffer_bytesize); dputs(STDERR_FILENO, trace); }; 
#endif
    if (UINTMAX_C(PIPEBUFFERSIZE) >= (uintmax_t)buffer_bytesize) goto label__pipe_buffer_size_ok; 
    goto label__pipe_buffer_size_is_too_small; 
  }; 
}; 





int_anime_error_t anime__fill_from_fd(anime_t * this, const char * input_name, const int input_fd, const int stduser_d) { 
  int_anime_error_t error_id; 
  goto label__body; 

  int16_t error_sub__line = -1;
 label__error__sub: { 
    DISPLAY_TRACE(this -> stdlog_d, error_id); 
    return error_id; 
  }; 
  
 
 label__body: { 
    this -> filename = anime__string_stack__push_lookup(this, input_name); 

    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[LEXEMES]" "\n"); }; 
    error_id = anime__lexer__fill_from_fd(this, input_fd); 
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
#if 1
    // Cette fonction n'est pas rapide. 
    if (this -> stdlog_d > 0) { anime__lexeme__print_all(this, this -> stdlog_d); }; 
#endif 
    
#if 0
    return ANIME__ERROR_GENERIC;
#else
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[STRUCTURE]" "\n"); }; 
    error_id = anime__syntax__structure_check_and_fill(this, /*stdwarning_d*/stduser_d, /*stderror_d*/stduser_d); 
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Reconstruction de la structure: réalisée" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Cohérence de la structure: vérifiée" "\n"); }; 
    if (this -> stdlog_d > 0) { anime__syntax__print(this, this -> stdlog_d); }; 

    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[EXPRESSIONS -> SYNTAXE]" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Pour commencer, nous devons déterminer l'arité des symboles d'addition et de soustraction (unaire ou binaire?)." "\n"); }; 
    error_id = anime__syntax_expr__arity__compute(this);
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Arités calculées" "\n"); }; 
    error_id = anime__syntax_expr__check_syntax(this); 
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Chaque expression est correctement écrite." "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> ." "\n"); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[NOM DES CHAMPS]" "\n"); }; 
    error_id = anime__generation__field_names__compute(this); 
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Noms des champs: calculés" "\n"); }; 
    
    this -> filled_huh = 2; // RL: À supprimer. 
    error_id = anime__post_syntax__consistency_check(this, stduser_d); 
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Absence d’incohérence entre les noms des champs: vérifiée" "\n"); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[VALEURS DES CHAMPS]" "\n"); }; 
    error_id = anime__generation__field_values__compute(this); 
    if (error_id != ANIME__OK) { error_sub__line = __LINE__; goto label__error__sub; }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "---> Valeurs des champs: calculées" "\n"); }; 
    
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "===============================================================================" "\n"); }; 
    if (this -> stdlog_d > 0) { dputs(this -> stdlog_d, "[TERMINÉ]" "\n"); }; 
    if (this -> stdlog_d > 0) { anime__print_d(this, this -> stdlog_d); }; 
    
    return ANIME__OK; 
#endif
  };   
  
}; 


void anime__check_and_assert(const int8_t debug_print_huh, const int stddebug_d) { 
  if (ANIME_BYTESIZE < anime_bytesize_actual) { 
    if (debug_print_huh) { 
      dprintf(stddebug_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s>()>}: anime_bytesize: %d" "\n",  __func__, (int) ANIME_BYTESIZE); 
      dprintf(stddebug_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s>()>}: anime_bytesize_actual: %d" "\n",  __func__, (int) anime_bytesize_actual); 
    }; 
    assert(false); 
  }; 

  assert(ANIME_LINE_LEN_MAX == ANIME_LINE_LEN_MAX__compiled_value); 

  assert(ANIME_VERSION_MAJOR == ANIME_VERSION_MAJOR__compiled_value); 
  assert(ANIME_VERSION_MINOR <= ANIME_VERSION_MINOR__compiled_value); 
  //assert(ANIME_VERSION_REVISION <= ANIME_VERSION_REVISION__compiled_value); 
  

  int_buffered_outstream__error__check_and_assert(); 
  int_buffer_to_fd__error__check_and_assert(); 
  
  int_anime_error__check_and_assert();   
  anime__lexer__check_and_assert(); 
  anime__syntax__check_and_assert(); 
  anime__generation__check_and_assert(); 
}; 



#define ANIME__ERROR__C
#define EXTERN extern
#include "anime_module_error.ci"
#undef  EXTERN
#undef  ANIME__ERROR__C

#define BUFFERED_OUTSTREAM__C 
#define BUFFERED_OUTSTREAM__MAX 8 
#define EXTERN extern
#include "lib__07__buffered_outstream.ci"
#undef  EXTERN
#undef  BUFFERED_OUTSTREAM__MAX
#undef  BUFFERED_OUTSTREAM__C 

#define BUFFER_TO_FD__C 
#define BUFFER_TO_FD__MAX 8 
#define EXTERN extern
#include "lib__11__buffer_to_fd.ci"
#undef  EXTERN
#undef  BUFFER_TO_FD__MAX 
#undef  BUFFER_TO_FD__C 
