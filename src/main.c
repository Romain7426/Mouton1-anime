#include "anime_global.h"
#include "anime.h"
#include "main.h"

#include "main_stdlog_buffering.ci" 
#include "main_subr.ci"
#include "main_options.ci"

//struct a_t { char u; char aa[]; }; // RL: sizeof(struct a_t) = 1 

// amalgamated 


// RL: OBJECTIFS: 
//  -- ldd ne retourne aucune dépendance. (On compilerait donc avec libc; et avec crt0; --static) /usr/lib/libc.a /usr/lib/crt0.o  [ À titre d’exemple, lire les commandes issues par «pcc -v». ] 
//  -- KISS: keep it short and simple 
//  -- no malloc 
//   


// RLE: Modèle: commande + traitement + log 
//  -- Commande   = user => TTY (+ ligne de commande) 
//  -- Traitement = data => PIPE (+ fichiers) 
//  -- Log        = log dans un fichier (éventuellement sur le terminal) 
// 
// -- TTY  = stdtty_in_d  + stdtty_out_d 
// -- PIPE = stdpipe_in_d + stdpipe_out_d 
// -- LOG  = stdlog_d 
// 
// -- USER = stduser_out_d + stduser_in_d 
// -- DATA = stddata_out_d + stddata_in_d 
// -- LOG  = stdlog_d 
// 

int main(const int argc, const char * argv[]) { 
  int stdlog_d = -1; 
  const int stderr_d = STDERR_FILENO; 
  int stdtty_in_d  = -1; 
  int stdtty_out_d = -1; 
  int stdpipe_in_d  = -1; 
  int stdpipe_out_d = -1; 
  int stduser_in_d  = -1; 
  int stduser_out_d = -1; // RLE: Différent de stderr, car, avec l’option --quiet, on peut vouloir faire taire le logiciel. Et avoir stderr_d vivant permet de contourner stduser en cas de besoin. 
  int stddata_in_d  = -1; 
  int stddata_out_d = -1; 
  int_anime_error_t error_id; 
  enum { MAIN__ERROR_BUFFER_SIZE = 2048 }; 
  char error_str[MAIN__ERROR_BUFFER_SIZE]; 
  const char * input_file_name = NULL; 
  anime_t * a_anime = NULL; 
  goto label__body; 


 label__exit: { 
    if (NULL != a_anime) anime__delete_b(a_anime); 
    if (stdlog_d > 0) { dprintf(stdlog_d, "Exit value = [ %d ] %s " "\n", error_id, int_anime_error__get_cstr(error_id)); }; 
    if (stdlog_d > 0) { main__stdlog_close(stdlog_d, /*flush_huh*/true); }; 
    return error_id; 
  }; 
  
 label__error__generic: { 
    goto label__exit; 
  }; 
  
 label__error__options_parsing_failed: { 
    const char err_str[] = "Error while parsing options" "\n"; 
    enum { err_str_len = ARRAY_LEN(err_str) - 1 }; 
    if (stderr_d > 0) { write(stderr_d, err_str, err_str_len); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s", __func__, err_str); }; 
    error_id = ANIME__MAIN__OPTIONS__PARSING_ERROR; 
    goto label__exit; 
  }; 
  
 label__error__options_running_failed: { 
    goto label__exit; 
  }; 
  
 label__error__first_arg_is_null: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, MAIN__ERROR_BUFFER_SIZE, "First arg is null"); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 
  
 label__error__first_arg_is_empty: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, MAIN__ERROR_BUFFER_SIZE, "First arg is empty"); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 

 label__error__stdin_is_tty: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, MAIN__ERROR_BUFFER_SIZE, "stdin is tty - I refuse to read data from a tty."); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 
  
 label__error__cannot_open_input_file: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, MAIN__ERROR_BUFFER_SIZE, "Cannot open input file: %s", input_file_name); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 

label__error__anime_buffer_is_too_small: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    strlcpy(error_str, "anime_buffer is too small", MAIN__ERROR_BUFFER_SIZE); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 

 label__error__cannot_parse_input_file: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, MAIN__ERROR_BUFFER_SIZE, "<%s>: " "%s[%d]: " "%s: %s" "\n", anime__filename_get(a_anime), error_id > 0 ? "Warning" : "Error", error_id, int_anime_error__get_cstr(error_id), anime__error_cstr_get(a_anime)); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 
  
 label__body: { 
    srandomdev(); 
    endianness__check_and_assert(); 
    int_buffered_outstream__error__check_and_assert(); 
    int_buffer_to_fd__error__check_and_assert(); 
    anime__check_and_assert(/*debug_print_huh*/true, /*stderr_d*/stderr_d); 
    assert(isatty(stderr_d)); 

    // STDLOG, STDTTY, STDPIPE, STDUSER, STDDATA  
    enum { main__stdlog__buffer_bytesize = INT16_MAX }; 
    char main__stdlog__buffer[main__stdlog__buffer_bytesize]; 
    { 
      stdlog_d = main__stdlog_init(main__stdlog__buffer, main__stdlog__buffer_bytesize); 
      
      stduser_in_d  = stdtty_in_d  = isatty(STDIN_FILENO)  ? STDIN_FILENO  : open("/dev/tty", O_RDONLY); 
      stduser_out_d = stdtty_out_d = isatty(STDOUT_FILENO) ? STDOUT_FILENO : open("/dev/tty", O_WRONLY); 
    
      stddata_in_d  = stdpipe_in_d  = isatty(STDIN_FILENO)  ? -1 : STDIN_FILENO; 
      stddata_out_d = stdpipe_out_d = isatty(STDOUT_FILENO) ? -1 : STDOUT_FILENO; 
    }; 
    
    main_arg_print(argc, argv, stdlog_d); 
    main_time_print(stdlog_d); 
    
    // PARSING ARGUMENT OPTIONS/FLAGS 
    { 
      if (!program_options__parse(argc, argv)) { goto label__error__options_parsing_failed; }; 
      
      error_id = program_options__run(argc, argv, /*stdprint_d*/stduser_out_d, /*stduser_out_d*/stduser_out_d, /*stdlog_d*/stdlog_d); 
      if (ANIME__OK != error_id) { goto label__error__options_running_failed; }; 
      
      //dprintf(stderr_d, "program_options__stdlog_new_output = %s" "\n", program_options__stdlog_new_output); 
      if (program_options__stdlog_new_output != NULL) { 
	main__stdlog_reopen(&stdlog_d, program_options__stdlog_new_output, main__stdlog__buffer, main__stdlog__buffer_bytesize); 
      }; 
      
      if (program_options[PROGRAM_OPTIONS_INDEX__QUIET] > 0) { stduser_out_d = -1; }; 
      if (program_options__stduser_new_output != NULL) { main__stduser_open(&stduser_out_d, program_options__stduser_new_output); }; 
    }; 
    
    assert(program_options__plain__nb > 0); // RLE: This should have been caught beforehand. 
    
    // PLAIN ARGUMENTS - FIRST PLAIN ARG IS INPUT FILE 
    // (Other arguments are considered as fields to be printed.) 
    input_file_name = NULL; 
    stddata_in_d = -1; 
    { 
      const int arg_i = program_options__plain[0]; 
      const char * s = argv[arg_i];
      if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_name = %s" "\n", __func__, s); }; 
      for (;;) { 
	if (NULL ==  s) { goto label__error__first_arg_is_null; }; 
	if ('\0' == *s) { goto label__error__first_arg_is_empty; }; 
	if ('-' == *s && '\0' == *(s+1)) goto label__input_is_stdin; 
	if (0 == strcasecmp(s, "stdin")) goto label__input_is_stdin; 
	input_file_name = s; 
	stddata_in_d    = open(input_file_name, O_RDONLY); 
	if (0 > stddata_in_d) { goto label__error__cannot_open_input_file; }; 
	break; 
	
      label__input_is_stdin: { 
	  if (isatty(STDIN_FILENO)) goto label__error__stdin_is_tty; 
	  input_file_name = "<stdin>"; 
	  stddata_in_d    = STDIN_FILENO; 
	  break; 
	}; 
      }; 
      if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "stddata_in_d   = %d" "\n", __func__, stddata_in_d  ); }; 
    }; 
    
    assert(0 <= stddata_in_d); 
    
#if 0 
    dprintf(stderr_d, "ANIME__MAIN__CANNOT_OPEN_INPUT_FILE = %d [ %s ]" "\n", ANIME__MAIN__CANNOT_OPEN_INPUT_FILE, int_anime_error__get_cstr(ANIME__MAIN__CANNOT_OPEN_INPUT_FILE));
    dprintf(stderr_d, "ANIME__OK = %d [ %s ]" "\n", ANIME__OK, int_anime_error__get_cstr(ANIME__OK));
#endif 

    // ALLOCATING MEMORY 
    char a_anime_buffer[ANIME_BYTESIZE]; 
    a_anime = anime__make_b(a_anime_buffer, (sizeof(a_anime_buffer)), /*anime_buffer_bytesize_used_r*/NULL, stdlog_d); 
    if (NULL == a_anime) { goto label__error__anime_buffer_is_too_small; } 
    
    // PARSING INPUT FILE 
    if (program_options[PROGRAM_OPTIONS_INDEX__RESTORE] > 0) { 
      error_id = anime__restore_from_fd(a_anime, stddata_in_d); 
      if (0 > error_id) goto label__error__generic; 
    }
    else { 
      error_id = anime__fill_from_fd(a_anime, input_file_name, stddata_in_d, stduser_out_d); 
      if (error_id != ANIME__OK) { goto label__error__cannot_parse_input_file; }; 
      close(stddata_in_d); 
      stddata_in_d = -1; 
      if (stduser_out_d > 0) dprintf(stduser_out_d, "<%s>: " "OK" "\n", anime__filename_get(a_anime)); 
    }; 
    
    // PRINT? 
    if (program_options[PROGRAM_OPTIONS_INDEX__PRINT] > 0) { 
      if (stduser_out_d > 0) anime__print_d(a_anime, stduser_out_d); 
    }; 
    
    
    // FOLLOWING ARGUMENTS ARE FIELDS TO BE PRINTED 
    { 
      for (int i = 1; i < program_options__plain__nb; i++) { 
	const int arg_i = program_options__plain[i]; 
	const char * field = argv[arg_i]; 
	error_id = anime__print_field_value_by_name(a_anime, field, /*stdprint_d*/stderr_d, /*stduser_out_d*/stduser_out_d, &error_id, MAIN__ERROR_BUFFER_SIZE, error_str); 
	if (error_id == ANIME__OK) { continue; }; 
	if (stduser_out_d > 0) { dprintf(stduser_out_d, "<%s>: " "%s[%d]: " "%s" "\n", anime__filename_get(a_anime), error_id > 0 ? "Warning" : "Error", error_id, error_str); }; 
	continue; 
      }; 
    }; 
    
    // DUMP?
    if (program_options[PROGRAM_OPTIONS_INDEX__DUMP] > 0) { 
      error_id = anime__dump_to_fd(a_anime, stddata_out_d); 
      if (0 > error_id) goto label__error__generic; 
    }; 
    
    // BYE 
    goto label__exit; 
  }; 

}; 



