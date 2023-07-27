#include "anime_global.h"
#include "anime.h"
#include "anime_token.h"
#include "anime_token_type.h"
#include "anime_token_input_buffering.h"
#include "anime_token_parser.h"
#include "anime_tree.h"
#include "anime_data_generation_002_from_trees.h"



int anime_data_generation_002_from_trees(const anime_tree_env_t * tree_env, const anime_token_env_t * token_env, anime_t * anime_data, const int stduser_d) { 
  if (NULL ==   tree_env) { return ANIME__DATA_GENERATION__NULL_TREE_ENV  ; }; 
  if (NULL ==  token_env) { return ANIME__DATA_GENERATION__NULL_TOKEN_ENV ; }; 
  if (NULL == anime_data) { return ANIME__DATA_GENERATION__NULL_ANIME_DATA; }; 
  if (   0 ==   tree_env -> filled_huh) { return ANIME__DATA_GENERATION__TREE_ENV__EMPTY       ; }; 
  if (  -1 ==   tree_env -> filled_huh) { return ANIME__DATA_GENERATION__TREE_ENV__BEING_FILLED; }; 
  if (   1 !=   tree_env -> filled_huh) { return ANIME__DATA_GENERATION__TREE_ENV__NOT_FILLED  ; }; 
  
  anime__bzero(anime_data); 
  anime_data -> filled_huh = -1; 
  
  if (0 >= tree_env -> memory__array_nb) { goto error_not_enough_trees; }; 

  int error_id; 
  
  uint16_t tree_size; 
  uint8_t  tree_type; 
  uint8_t  expected_tree_type; 
  uint8_t  child_nb; 
  uint8_t  shift_to_first_child;
  uint16_t data_address; 
  
  uint16_t current_tree = 0; 

  uint16_t section_physique_tree  = ~0; 
  uint16_t section_gameplay_tree  = ~0; 
  uint16_t section_graphique_tree = ~0; 
  int8_t   section_physique_tree_nb  = 0; 
  int8_t   section_gameplay_tree_nb  = 0; 
  int8_t   section_graphique_tree_nb = 0; 
  int8_t   section_unknown_tree_nb   = 0; 



  // *** Gathering section data *** 
  { 
  for (;;) { 
    //dprintf(stderr_d, "current_tree = %d" "\n", current_tree); 
    if (current_tree >= tree_env -> memory__array_nb) { break; }; 
    
    error_id = anime_tree__get_tree_at(tree_env, current_tree, &tree_size, &tree_type, &child_nb, &shift_to_first_child, &data_address); 
    
    if (ANIME__TREE__WRONG_ADDRESS == error_id) { goto error_wrong_tree_address; }; 
    if (ANIME__OK                  != error_id) { goto error_unhandled_error   ; }; 
    
#if 0 
    dprintf(stderr_d, "\t" "tree_size            = %d" "\n", tree_size); 
    dprintf(stderr_d, "\t" "tree_type            = %d" "\n", tree_type); 
    dprintf(stderr_d, "\t" "child_nb             = %d" "\n", child_nb); 
    dprintf(stderr_d, "\t" "shift_to_first_child = %d" "\n", shift_to_first_child); 
    dprintf(stderr_d, "\t" "data_address         = %d" "\n", data_address); 
#endif 
    
    if (ANIME__TREE_TYPE__SECTION != tree_type) { expected_tree_type = ANIME__TREE_TYPE__SECTION; goto error_wrong_tree_type; }; 
    uint16_t section_name_token = 0; 
    error_id = anime_tree__read_uint16(tree_env, data_address, &section_name_token); 
    if (ANIME__TREE__WRONG_ADDRESS == error_id) { goto error_wrong_tree_address; }; 
    if (ANIME__OK                  != error_id) { goto error_unhandled_error   ; }; 
    const char * section_name_token_srcval = anime_token__get_srcval_cstr(token_env, section_name_token); 
    //dprintf(stderr_d, "section_name_token_srcval = %s" "\n", section_name_token_srcval); 
    
    if (0 == strcasecmp(section_name_token_srcval, "physique")) { 
      if (0 == section_physique_tree_nb) section_physique_tree = current_tree; 
      section_physique_tree_nb++; 
      if (section_physique_tree_nb > 1) { 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Extraneous 'physique' section"); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
      }; 
    } 
    else if (0 == strcasecmp(section_name_token_srcval, "gameplay")) { 
      if (0 == section_gameplay_tree_nb) section_gameplay_tree = current_tree; 
      section_gameplay_tree_nb++; 
      if (section_gameplay_tree_nb > 1) { 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Extraneous 'gameplay' section"); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
      }; 
    } 
    else if (0 == strcasecmp(section_name_token_srcval, "graphique")) { 
      if (0 == section_graphique_tree_nb) section_graphique_tree = current_tree; 
      section_graphique_tree_nb++; 
      if (section_graphique_tree_nb > 1) { 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Extraneous 'graphique' section"); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
      }; 
    } 
    else { 
      section_unknown_tree_nb++; 
      if (section_unknown_tree_nb > 0) { 
	const int error_location_len = section_name_token <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, section_name_token - 1), anime_token__get_line1(token_env, section_name_token - 1), anime_token__get_column0(token_env, section_name_token - 1)); 
	const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
	snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Unknown '%s' section", section_name_token_srcval); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
	if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
      }; 
    }; 

    current_tree += tree_size; 
  }; 
  
  if (0 == section_physique_tree_nb ) { goto error_missing_section_physique ; }; 
  if (0 == section_gameplay_tree_nb ) { goto error_missing_section_gameplay ; }; 
  if (0 == section_graphique_tree_nb) { goto error_missing_section_graphique; }; 
  
  if (1 < section_physique_tree_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There are %d 'physique' sections — only the first one will be used, following ones got discarded.", section_physique_tree_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  
  if (1 < section_gameplay_tree_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There are %d 'gameplay' sections — only the first one will be used, following ones got discarded.", section_gameplay_tree_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  
  if (1 < section_graphique_tree_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There are %d 'graphique' sections — only the first one will be used, following ones got discarded.", section_graphique_tree_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  
  if (0 < section_unknown_tree_nb) { 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "There are %d unknown sections — They all got discarded.", section_unknown_tree_nb); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", anime_data -> error_str); }; 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
  };  
  };
  

  // *** PROCESSING 'PHYSIQUE' SECTION *** 
  do { 
    assert(section_physique_tree != (int_anime_tree_t)~0); 

    current_tree = section_physique_tree; 
    error_id = anime_tree__get_tree_at(tree_env, current_tree, &tree_size, &tree_type, &child_nb, &shift_to_first_child, &data_address); 
    if (ANIME__TREE__WRONG_ADDRESS == error_id) { goto error_wrong_tree_address; }; 
    if (ANIME__OK                  != error_id) { goto error_unhandled_error   ; }; 
    
#if 0 
    dprintf(stderr_d, "\t" "tree_size            = %d" "\n", tree_size); 
    dprintf(stderr_d, "\t" "tree_type            = %d" "\n", tree_type); 
    dprintf(stderr_d, "\t" "child_nb             = %d" "\n", child_nb); 
    dprintf(stderr_d, "\t" "shift_to_first_child = %d" "\n", shift_to_first_child); 
    dprintf(stderr_d, "\t" "data_address         = %d" "\n", data_address); 
#endif 
    
    const int fils_nb = child_nb; 
    if (0 == fils_nb) break; 
    //uint16_t fils_address[child_nb]; // For some unknown reasons, VLAs make «-fstack-protector» fail. 
    uint16_t * fils_address = alloca((sizeof(*fils_address)) * child_nb); 
    fils_address[0] = current_tree + shift_to_first_child; 
    for (int i = 0; i < fils_nb - 1; i++) { 
      uint16_t fils_size; 
      anime_tree__read_uint16(tree_env, fils_address[i], &fils_size); 
      fils_address[i+1] = fils_address[i] + fils_size; 
    }; 
#if 0 
    for (int i = 0; i < fils_nb; i++) { 
      dprintf(stderr_d, "\t" "fils_address[%d] = %d" "\n", i, fils_address[i]); 
    }; 
#endif 
#if 0 
    for (int i = 0; i < fils_nb; i++) { 
      uint8_t fils_type; 
      anime_tree__read_uint8(tree_env, fils_address[i] + sizeof(uint16_t), &fils_type); 
      dprintf(stderr_d, "\t" "fils_type[%d] = %s(%d)" "\n", i, anime_tree_type__cstr[fils_type], fils_type); 
    }; 
#endif
    int fils_i = 0; 
    for (;;) { 
      if (fils_i >= fils_nb) { break; }; 
      
      current_tree = fils_address[fils_i];
      error_id = anime_tree__get_tree_at(tree_env, current_tree, &tree_size, &tree_type, &child_nb, &shift_to_first_child, &data_address); 
      if (ANIME__TREE__WRONG_ADDRESS == error_id) { goto error_wrong_tree_address; }; 
      if (ANIME__OK                  != error_id) { goto error_unhandled_error   ; }; 
      
#if 1 
      dprintf(stderr_d, "\t" "tree_size            = %d" "\n", tree_size); 
      dprintf(stderr_d, "\t" "tree_type            = %d" "\n", tree_type); 
      dprintf(stderr_d, "\t" "child_nb             = %d" "\n", child_nb); 
      dprintf(stderr_d, "\t" "shift_to_first_child = %d" "\n", shift_to_first_child); 
      dprintf(stderr_d, "\t" "data_address         = %d" "\n", data_address); 
#endif 
      
      const int node_field_bytes = shift_to_first_child - (data_address - current_tree); 
#if 1 
      dprintf(stderr_d, "\t" "node_field_bytes     = %d" "\n", node_field_bytes); 
#endif 

      uint16_t property_token; 
      anime_tree__read_uint16(tree_env, data_address, &property_token); 
      const char * property_srcval = anime_token__get_srcval_cstr(token_env, property_token); 
      dprintf(stderr_d, "property_srcval = %s" "\n", property_srcval); 

      if (0 == strcasecmp(property_srcval, "masse")) { 
	assert(4 == node_field_bytes); 
	uint16_t assign_token; 
	anime_tree__read_uint16(tree_env, data_address + 2, &assign_token); 
	const uint8_t assign_token_type = anime_token__get_type(token_env, assign_token); 
	assert(ANIME_TOKEN_AFFECTATION == assign_token_type); 
	assert(1 ==  child_nb); 
	

	current_tree = fils_address[fils_i] + shift_to_first_child; 
	error_id = anime_tree__get_tree_at(tree_env, current_tree, &tree_size, &tree_type, &child_nb, &shift_to_first_child, &data_address); 
	if (ANIME__TREE__WRONG_ADDRESS == error_id) { goto error_wrong_tree_address; }; 
	if (ANIME__OK                  != error_id) { goto error_unhandled_error   ; }; 
	
#if 1
	dprintf(stderr_d, "\t" "\t" "tree_size            = %d" "\n", tree_size); 
	dprintf(stderr_d, "\t" "\t" "tree_type            = %d" "\n", tree_type); 
	dprintf(stderr_d, "\t" "\t" "child_nb             = %d" "\n", child_nb); 
	dprintf(stderr_d, "\t" "\t" "shift_to_first_child = %d" "\n", shift_to_first_child); 
	dprintf(stderr_d, "\t" "\t" "data_address         = %d" "\n", data_address); 
#endif 
	assert(ANIME__TREE_TYPE__EXPR == tree_type); 
	assert(0 == child_nb); 
	assert(shift_to_first_child == tree_size); 
	const int node_field_bytes = shift_to_first_child - (data_address - current_tree); 
#if 1 
	dprintf(stderr_d, "\t" "\t" "node_field_bytes     = %d" "\n", node_field_bytes); 
#endif 
	assert(node_field_bytes == 2); 
	uint16_t value_token; 
	anime_tree__read_uint16(tree_env, data_address, &value_token); 
	const uint8_t value_token_type   = anime_token__get_type(token_env, value_token); 
	const char *  value_token_srcval = anime_token__get_srcval_cstr(token_env, value_token); 
#if 1 
	dprintf(stderr_d, "\t" "\t" "value_token          = %d" "\n", value_token); 
	dprintf(stderr_d, "\t" "\t" "value_token_type     = %d" "\n", value_token_type); 
	dprintf(stderr_d, "\t" "\t" "value_token_srcval   = %s" "\n", value_token_srcval); 
#endif 
	const float floatval = atof(value_token_srcval); 
	
	anime_data -> masse = floatval; 
	      
	fils_i++; 
	continue; 
      }; 
      
      
      
      
      fils_i++; 
      
    }; 
    
    
    
    
    
    
  } while (false); 
  
  
  // *** PROCESSING 'GAMEPLAY' SECTION *** 
  { 
    assert(section_gameplay_tree != (int_anime_tree_t)~0); 
  }; 
  
  
  // *** PROCESSING 'GRAPHIQUE' SECTION *** 
  { 
    assert(section_graphique_tree != (int_anime_tree_t)~0); 
  }; 


  
  
  
  
  
  
  
  anime_data -> filled_huh = 1; 
  return ANIME__OK; 


 error_missing_section_physique: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_PHYSIQUE_SECTION; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Missing 'physique' section"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   
  
 error_missing_section_gameplay: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_GAMEPLAY_SECTION; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Missing 'gameplay' section"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   
  
 error_missing_section_graphique: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__MISSING_GRAPHIQUE_SECTION; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Missing 'graphique' section"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };   
  
 error_not_enough_trees: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__NOT_ENOUGH_TREES; 
#if 0
    const int error_location_len = token_i <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i - 1), anime_token__get_line1(token_env, token_i - 1), anime_token__get_column0(token_env, token_i - 1)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "End-of-file reached, while parsing not completed"); 
#else 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "End-of-file reached, while data generation not completed"); 
#endif 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  }; 
  
 error_wrong_tree_address: { 
    anime_data -> error_id = ANIME__TREE__WRONG_ADDRESS; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Wrong tree address: Malformed tree"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  }; 
  
 error_unhandled_error: { 
    anime_data -> error_id = error_id; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Unhandled error: %d", error_id); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  }; 

 error_wrong_tree_type: { 
    anime_data -> error_id = ANIME__DATA_GENERATION__TREE__WRONG_TREE_TYPE; 
    snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "Wrong tree type: expecting %s — got %s", anime_tree_type__cstr[expected_tree_type], anime_tree_type__cstr[tree_type]); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  }; 
  
  
}; 








#if 0 
#define CHECK_IDENT(_ident_) {						\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type(token_env, token_i);		\
    srcval = anime_token__get_srcval_cstr(token_env, token_i);		\
    if (ANIME_TOKEN_IDENT != token_type) { error__expected_token_type = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type; }; \
    if (0 != strcasecmp((_ident_), srcval)) { error__expected_token_value = (_ident_); goto error_label__non_matching_token_value;  }; \
    token_i++;								\
  }; 

#define CHECK_SUGAR(_expected_token_type_) {			       \
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type(token_env, token_i);	       \
    if ((_expected_token_type_) != token_type) { error__expected_token_type = (_expected_token_type_); goto error_label__non_matching_token_type; };	       \
    token_i++;							       \
  }; 

#define LOOKAHEAD_THEN_READ_SIGN() {					\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_IMOINS == token_type) { signval = -1; token_i ++; } \
    else if (ANIME_TOKEN_RMOINS == token_type) { signval = -1; token_i ++; } \
    else { signval = 1; };						\
  };

#define READ_FLOAT() {							\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_ENTIER     == token_type) { floatval = (float) (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { floatval = (float) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { floatval = (float) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { floatval = (float) (atof(srcval)); } \
    else { error__expected_token_type = ANIME_TOKEN_REEL__DOT; goto error_label__non_matching_token_type; }; \
    if (signval < 0) floatval = -floatval;				\
    token_i++;								\
  };

#define READ_ENTIER() {							\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_ENTIER     == token_type) { intval =       (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { intval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { intval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { intval = (int) (atof(srcval)); } \
    else { error__expected_token_type = ANIME_TOKEN_ENTIER; goto error_label__non_matching_token_type; }; \
    if (signval < 0) intval = -intval;					\
    token_i++;								\
  };

#define READ_BOOLEEN() {						\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if      (ANIME_TOKEN_TRUE       == token_type) { boolval =                 true; } \
    else if (ANIME_TOKEN_FALSE      == token_type) { boolval =                false; } \
    else if (ANIME_TOKEN_ENTIER     == token_type) { boolval =       (atoi(srcval)); } \
    else if (ANIME_TOKEN_REEL__VIRG == token_type) { boolval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__DOT  == token_type) { boolval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_REEL__E    == token_type) { boolval = (int) (atof(srcval)); } \
    else if (ANIME_TOKEN_IDENT      == token_type) {			\
      if      ((0 == strcasecmp("vrai", srcval)) || (0 == strcasecmp("true" , srcval))) { boolval =  true; } \
      else if ((0 == strcasecmp("faux", srcval)) || (0 == strcasecmp("false", srcval))) { boolval = false; } \
      else { goto error_label__expecting_boolean; };			\
    }									\
    else { goto error_label__expecting_boolean; };			\
    token_i++;								\
  };

#define READ_IDENT() {						   \
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i); \
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    if (ANIME_TOKEN_IDENT != token_type) { error__expected_token_type = ANIME_TOKEN_IDENT; goto error_label__non_matching_token_type; }; \
    identval = srcval;						   \
    token_i++;							   \
  }; 

#define READ_STRING() {						   \
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i); \
    srcval     = anime_token__get_srcval_cstr(token_env, token_i); \
    if (ANIME_TOKEN_STRING_C != token_type) { error__expected_token_type = ANIME_TOKEN_STRING_C; goto error_label__non_matching_token_type; }; \
    strval = srcval;						   \
    token_i++;							   \
  }; 

#define LOOKAHEAD_IDENT(_ident_) {					\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    srcval     = anime_token__get_srcval_cstr(token_env, token_i);	\
    lookahead_match_huh = (ANIME_TOKEN_IDENT == token_type) && (0 == strcasecmp((_ident_), srcval)); \
  }; 

#define LOOKAHEAD_SUGAR(_expected_token_type_) {			\
    if (token_i >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; \
    token_type = anime_token__get_type       (token_env, token_i);	\
    lookahead_match_huh = ((_expected_token_type_) == token_type);	\
  }; 

 


int anime_data_generation_002_from_trees(const anime_tree_env_t * tree_env, anime_t * anime_data) { 
  if (NULL ==  token_env) { return ANIME__DATA_GENERATION__NULL_TOKEN_ENV ; }; 
  if (NULL == anime_data) { return ANIME__DATA_GENERATION__NULL_ANIME_DATA; }; 
  int token_i = 0; 
  int token_type; 
  int success_huh = false; 
  const char * srcval; 
  int signval = 1; 
  float floatval; 
  int intval; 
  int boolval; 
  const char * identval; 
  const char * strval; 
  int lookahead_match_huh = false; 
  int error__expected_token_type; 
  const char * error__expected_token_value; 
  
  anime__bzero(anime_data); 
  anime_data -> filled_huh = -1; 

  if (0 >= anime_token__get_count(token_env)) { goto error_not_enough_tokens; }; 
  anime_data -> filename = anime__strcopy(anime_data, anime_token__get_srcfile_cstr(token_env, 0)); 
  
  do { 
    CHECK_IDENT("physique"); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
      CHECK_IDENT("zone"); CHECK_IDENT("de"); CHECK_IDENT("choc"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	CHECK_IDENT("longueur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> choc_longueur = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("largeur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> choc_largeur  = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	CHECK_IDENT("hauteur" ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> choc_hauteur  = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("masse"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> masse = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
    
 
    CHECK_IDENT("gameplay"); 
    CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
      CHECK_IDENT("points"    ); CHECK_IDENT("de"); CHECK_IDENT("vie"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_ENTIER(); anime_data -> vie = intval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("invincible"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_BOOLEEN(); anime_data -> invincible = boolval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
      CHECK_IDENT("hostile"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_BOOLEEN(); anime_data -> hostile    = boolval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      
      
      
    CHECK_IDENT("graphique"); 
    CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 

      for (;;) { 
	LOOKAHEAD_IDENT("membre"); 
	if (!(lookahead_match_huh)) { break; }; 
      
	token_i++; 
	if (anime_data -> membres_nb >= anime_membres_size) { break; }; 
	READ_IDENT(); anime_data -> membres_nom[anime_data -> membres_nb] = anime__strcopy(anime_data, identval); CHECK_SUGAR(ANIME_TOKEN_OPENBRACE); { 
	  CHECK_IDENT("fils"   ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("image"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_STRING(); anime_data -> membres_image[anime_data -> membres_nb] = anime__strcopy(anime_data, strval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("largeur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> membres_largeur[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("hauteur"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> membres_hauteur[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("angle"); CHECK_IDENT("max"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> membres_angle_max_y[anime_data -> membres_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	anime_data -> membres_nb ++; 
      }; 

#if 0 
      fprintf(stderr, "token_type = %s" "\n", anime_token__type_get_cstr(anime_token__get_type(token_env, token_i))); 
      fprintf(stderr, "token_value = %s" "\n", anime_token__get_srcval_cstr(token_env, token_i)); 
      fprintf(stderr, "lookahead_match_huh = %s" "\n", lookahead_match_huh ? "true" : "false"); 
      fprintf(stderr, "HERE" "\n"); 
#endif 
      
    CHECK_IDENT("membres"); CHECK_IDENT("racines"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); 
    LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG); 
    if (!(lookahead_match_huh)) { 
      for (;;) { 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_OPENBRACE); 
	if (!(lookahead_match_huh)) { break; }; 
	token_i++; { 
	  if (anime_data -> racines_nb >= anime_racines_size) { break; }; 
	  CHECK_IDENT("qui"  ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); READ_IDENT(); anime_data -> racines_qui[anime_data -> racines_nb] = anime__strcopy(anime_data, identval); CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("x"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_x[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("y"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_y[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("z"    ); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_z[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	  CHECK_IDENT("angle"); CHECK_IDENT("y"); CHECK_SUGAR(ANIME_TOKEN_AFFECTATION); LOOKAHEAD_THEN_READ_SIGN(); READ_FLOAT(); anime_data -> racines_angle_y[anime_data -> racines_nb] = floatval; CHECK_SUGAR(ANIME_TOKEN_PTVIRG); 
	}; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
	anime_data -> racines_nb ++; 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_PTVIRG ); if (lookahead_match_huh) { token_i++; break; }; 
	LOOKAHEAD_SUGAR(ANIME_TOKEN_VIRGULE); if (lookahead_match_huh) { token_i++; continue; }; 
	break; 
      }; 
    }; 
    
    }; CHECK_SUGAR(ANIME_TOKEN_CLOSEBRACE); 
      
    if (token_i < anime_token__get_count(token_env)) { goto error_too_many_tokens; }; 
      
    success_huh = true; 
    anime_data -> filled_huh = 2; 
  } while (false); 

  return success_huh ? ANIME__OK : ~0; 


error_not_enough_tokens: { 
    //const int token_count_left = anime_token__get_count(token_env) - token_i; 
    anime_data -> error_id = ANIME__DATA_GENERATION__NOT_ENOUGH_TOKENS; 
    const int error_location_len = token_i <= 0 ? 0 : snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i - 1), anime_token__get_line1(token_env, token_i - 1), anime_token__get_column0(token_env, token_i - 1)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "End-of-file reached, while parsing not completed"); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
}; 

error_too_many_tokens: { 
    const int token_count_left = anime_token__get_count(token_env) - token_i; 
    anime_data -> error_id = ANIME__DATA_GENERATION__TOO_MANY_TOKENS;   
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Parsing done, but still non-read tokens (%d too many tokens)", token_count_left); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
}; 

error_label__expecting_boolean:  {
    const char * error__expected_token_type_cstr = "BOOLEAN"; 
    const char * error__got_token_type_cstr      = anime_token__type_get_cstr(token_type); 
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };

error_label__non_matching_token_type: {
    const char * error__expected_token_type_cstr = anime_token__type_get_cstr(error__expected_token_type); 
    const char * error__got_token_type_cstr      = anime_token__type_get_cstr(                token_type); 
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };

error_label__non_matching_token_value: {
    anime_data -> error_id = ANIME__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE; 
    const int error_location_len = snprintf(anime_data -> error_str, ANIME__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", anime_token__get_srcfile_cstr(token_env, token_i), anime_token__get_line1(token_env, token_i), anime_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(ANIME__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(anime_data -> error_str + error_location_written_len, ANIME__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token value — Expecting: '%s' ; Got: '%s'", error__expected_token_value, srcval); 
    if (anime_data -> stdlog_d > 0) { dprintf(anime_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, anime_data -> error_str); }; 
    return anime_data -> error_id; 
  };


}; 

#endif 



