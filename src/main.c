#include "anime_global.h"
#include "anime.h"
#include "main.h"

#include "main_stdlog_buffering.ci" 
#include "main_subr.ci"
#include "main_options.ci"

//struct a_t { char u; char aa[]; }; // RL: sizeof(struct a_t) = 1 



int main(const int argc, const char * argv[]) { 
  int_anime_error_t error_id; 
  char error_str[ANIME__ERROR_BUFFER_SIZE]; 
  const char * input_file_name = NULL; 
  int input_file_fd = -1;
  int stduser_d = -1; 
  //anime_t a_anime[1]; 
  //dprintf(stderr_d, "sizeof(anime_t) = %lu" "\n", (unsigned long int) sizeof(anime_t)); 
  anime_t * a_anime = NULL; 
  goto label__body; 


 label__exit: { 
    //anime__delete_r(a_anime); 
    if (NULL != a_anime) anime__delete_b(a_anime); 
    if (stduser_d > 2) { close(stduser_d); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "Exit value = [ %d ] %s " "\n", error_id, int_anime_error__get_cstr(error_id)); }; 
    if (stdlog_d > 0) { main__stdlog_close(stdlog_d); }; 
    return error_id; 
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
    snprintf(error_str, ANIME__ERROR_BUFFER_SIZE, "First arg is null"); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 
  
 label__error__first_arg_is_empty: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, ANIME__ERROR_BUFFER_SIZE, "First arg is empty"); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 

 label__error__cannot_open_input_file: { 
    error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    snprintf(error_str, ANIME__ERROR_BUFFER_SIZE, "Cannot open input file: %s", input_file_name); 
    if (stderr_d > 0) { dprintf(stderr_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    goto label__exit; 
  }; 

label__error__anime_buffer_is_too_small: { 
    if (stderr_d > 0) dprintf(stderr_d, "%s" "\n", "anime_buffer is too small"); 
    goto label__exit; 
  }; 

 label__error__cannot_parse_input_file: { 
    if (stderr_d > 0) dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
    goto label__exit; 
  }; 
  
 label__body: { 
    //fprintf(stderr, "anime_token_env__sizeof = %d" "\n", (int) (anime_token_env__sizeof)); 
    //main__stdlog_init(); 
    enum { main__stdlog__buffer_bytesize = INT16_MAX }; 
    char main__stdlog__buffer[main__stdlog__buffer_bytesize]; 
    main__stdlog_init(main__stdlog__buffer, main__stdlog__buffer_bytesize); 
    main_arg_print(argc, argv, stdlog_d); 
    srandomdev(); 
    main_time_print(stdlog_d); 
    int_buffered_outstream__error__check_and_assert(); 
    anime__check_and_assert(/*debug_print_huh*/false, /*stderr_d*/stderr_d); 

    // PARSING ARGUMENT OPTIONS/FLAGS 
    { 
      if (!program_options__parse(argc, argv)) { goto label__error__options_parsing_failed; }; 
      
      error_id = program_options__run(argc, argv, /*stdprint_d*/stdout_d, /*stduser_d*/stderr_d, /*stdlog_d*/stdlog_d); 
      if (ANIME__OK != error_id) { goto label__error__options_running_failed; }; 
      
      //dprintf(stderr_d, "program_options__stdlog_new_output = %s" "\n", program_options__stdlog_new_output); 
      if (program_options__stdlog_new_output != NULL) { 
	//main__stdlog_reopen(program_options__stdlog_new_output); 
	main__stdlog_reopen(stdlog_d, program_options__stdlog_new_output, main__stdlog__buffer, main__stdlog__buffer_bytesize); 
      }; 
      
      stduser_d = stderr_d; 
      if (program_options[PROGRAM_OPTIONS_INDEX__QUIET] > 0) { stduser_d = -1; }; 
      if (program_options__stduser_new_output != NULL) { main__stderr_open(&stduser_d, program_options__stduser_new_output); }; 
    }; 
    
    assert(program_options__plain__nb > 0); // RLE: This should have been caught beforehand. 
  
    // PLAIN ARGUMENTS - TESTING THE FIRST AS INPUT FILE (others ignored) 
    // Other arguments are considered as fields to be printed. 
    input_file_name = NULL; 
    input_file_fd = -1; 
    { 
      const int arg_i = program_options__plain[0]; 
      const char * s = argv[arg_i];
      if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_name = %s" "\n", __func__, s); }; 
      for (;;) { 
	if (NULL ==  s) { goto label__error__first_arg_is_null; }; 
	if ('\0' == *s) { goto label__error__first_arg_is_empty; }; 
	input_file_name = "<stdin>";  
	input_file_fd   = stdin_d;
	if ('-' == *s && '\0' == *(s+1)) break; 
	if (0 == strcasecmp(s, "stdin")) break; 
	input_file_name = s; 
	input_file_fd   = open(input_file_name, O_RDONLY); 
	if (0 > input_file_fd) { goto label__error__cannot_open_input_file; }; 
	break; 
      }; 
      if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_fd   = %d" "\n", __func__, input_file_fd  ); }; 
    }; 
  
  
#if 0 
    dprintf(stderr_d, "ANIME__MAIN__CANNOT_OPEN_INPUT_FILE = %d [ %s ]" "\n", ANIME__MAIN__CANNOT_OPEN_INPUT_FILE, int_anime_error__get_cstr(ANIME__MAIN__CANNOT_OPEN_INPUT_FILE));
    dprintf(stderr_d, "ANIME__OK = %d [ %s ]" "\n", ANIME__OK, int_anime_error__get_cstr(ANIME__OK));
#endif 

    // PARSING INPUT FILE 
    char a_anime_buffer[anime_bytesize]; 
    { 
      //anime__make_r(a_anime, stdlog_d); 
      a_anime = anime__make_b(a_anime_buffer, (sizeof(a_anime_buffer)), /*anime_buffer_bytesize_used_r*/NULL, stdlog_d); 
      if (NULL == a_anime) { goto label__error__anime_buffer_is_too_small; } 

      
      error_id = anime__fill_from_file(a_anime, input_file_name, input_file_fd, stduser_d); 
      if (error_id != ANIME__OK) { goto label__error__cannot_parse_input_file; }; 
      
      if (input_file_fd != stdin_d) { close(input_file_fd); }; 
      input_file_fd = -1; 
      
      if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "OK" "\n", a_anime -> filename); 

      if (program_options[PROGRAM_OPTIONS_INDEX__PRINT] > 0) { anime__print_d(a_anime, stdout_d); }; 
    }; 
    
    
    // PARSING FOLLOWING ARGUMENTS AS FIELDS TO BE PRINTED 
    {    
      for (int i = 1; i < program_options__plain__nb; i++) { 
	const int arg_i = program_options__plain[i]; 
	const char * field = argv[arg_i]; 
	error_id = anime__print_field_value_by_name(a_anime, field, /*stdprint_d*/stdout_d, /*stduser_d*/stduser_d, &a_anime -> error_id, a_anime -> error_size, a_anime -> error_str); 
	if (error_id == ANIME__OK) { continue; }; 
	if (stduser_d > 0) { dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); }; 
	continue; 
      }; 
    }; 

    // BYE 
    goto label__exit; 
  }; 

}; 



