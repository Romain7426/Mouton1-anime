#include "anime_global.h"
#include "anime.h"
#include "main.h"

#include "main_options.ci"

#include <signal.h> 


static int stdlog_d = -1; 
static int stdlog_pipe[2] = {-1, -1}; // RL: [0] is output (read end), [1] is input (write end) 
static int stdlog_post_pipe_d = -1; 
 
static void main__stdlog_init(void) { 
  //stdlog_d = 2; return;
  
  //fprintf(stderr, "fcntl(3, F_GETFL) = %d" "\n", fcntl(3, F_GETFL)); 
  //if (-1 != fcntl(3, F_GETFL) && errno == EBADF) { 
  if (-1 != fcntl(3, F_GETFL)) { 
    stdlog_d = 3; 
  } 
  else { 
    //stdlog_d = open("/dev/tty", O_WRONLY);  
    stdlog_d = open("/dev/null", O_WRONLY);  
  }; 
}; 

static void (*former_handler)(int) = NULL; 
static char handler_buffer[INT16_MAX]; 
static int16_t handler_buffer_nb = 0; 
static void handler_buffer_flush(void) { 
  write(stdlog_post_pipe_d, handler_buffer, handler_buffer_nb); 
  handler_buffer_nb = 0; 
}; 
static void handler(int sig) { 
  // RL: Nous appelons write(2) qui génère des SIGIO. 
  // Donc nous devons désactiver le mask, et réinstaller le former_handler. 
  
  sigset_t sigset[1]; 
  sigemptyset(sigset);
  sigaddset(sigset, SIGIO);
  signal(SIGIO, former_handler); 
  sigprocmask(SIG_UNBLOCK, sigset, NULL); 
  goto label__body;

  label__exit: { 
    signal(SIGIO, handler); 
    return; 
  }; 
  
  label__body: { 
#if 1 
    //{ if (NULL == former_handler) { write(2, "former_handler is NULL\n", sizeof("former_handler is NULL\n")); } else { write(2, "former_handler is NOT NULL\n", sizeof("former_handler is NOT NULL\n"));}; }; 
    //const ssize_t read_nb = read(stdlog_pipe[0], handler_buffer, sizeof(handler_buffer)); 
    const ssize_t read_nb = read(stdlog_pipe[0], handler_buffer + handler_buffer_nb, sizeof(handler_buffer) - handler_buffer_nb); 
    if (0 < read_nb) { 
      handler_buffer_nb += read_nb; 
      if (sizeof(handler_buffer) == handler_buffer_nb) { 
	write(stdlog_post_pipe_d, handler_buffer, handler_buffer_nb); 
	handler_buffer_nb = 0; 
      }; 
      //write(2, "SIGIO reçu\n", sizeof("SIGIO reçu\n")); 
      //write(2, handler_buffer, read_nb); 
      goto label__exit; 
    }; 
#endif 
    if (NULL == former_handler) goto label__exit; 
    former_handler(sig); 
    goto label__exit; 
  }; 
}; 

static void main__stdlog_reopen(const char * filename) { 
  if (NULL ==  filename) return; 
  if ('\0' == *filename) return; 
  int new_fd; 
  if      (0 == strcasecmp("stdout", filename)) { new_fd = stdout_d; } 
  else if (0 == strcasecmp("stderr", filename)) { new_fd = stderr_d; } 
  else { 
    if (0 == strcasecmp("stdnull", filename)) { filename = "/dev/null"; }; 
    new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600); 
    if (new_fd < 0) return; 
    fcntl(new_fd, F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    write(new_fd, "NEW_FD works!\n", sizeof("NEW_FD works!\n")); 
  }; 
  close(stdlog_d); 
#if 1
  if (-1 == pipe(stdlog_pipe)) { 
    stdlog_pipe[0] = -1; 
    stdlog_pipe[1] = -1; 
    stdlog_d = new_fd; 
  } 
  else { 
    stdlog_post_pipe_d = new_fd; 
    former_handler = signal(SIGIO, handler); 
#if 0 
    assert(SIG_ERR != former_handler); 
    signal(SIGIO, former_handler); 
    signal(SIGIO, SIG_DFL); 
    signal(SIGIO, SIG_IGN); 
#endif 
#if 0 
#elif 0 
    fcntl(stdlog_pipe[1], F_SETOWN, getpid()); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[1], F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
#elif 1 
    fcntl(stdlog_pipe[0], F_SETOWN, getpid()); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[0], F_SETFL, O_NONBLOCK); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[0], F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[0], F_SETFL, O_ASYNC | O_NONBLOCK); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
#else 
    fcntl(stdlog_pipe[0], F_SETOWN, 0); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[1], F_SETOWN, 0); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[0], F_SETOWN, getpid()); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[1], F_SETOWN, getpid()); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[0], F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[1], F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non.  
    fcntl(stdlog_pipe[0], F_SETOWN, getpid()); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
    fcntl(stdlog_pipe[0], F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
#endif 
    for (int i = 0; i < 1; i++) { 
      write(2, "0: ", sizeof("0: "));
      write(stdlog_pipe[1], "++++++++++++++++", 16); 
      fcntl(stdlog_pipe[0], F_SETFL, O_ASYNC); // RL: J’avais espoir que cette commande ajoute un buffer… Mais non. 
      write(2, "1: ", sizeof("1: "));
      write(stdlog_pipe[1], "++++++++++++++++", 16); 
      write(stdlog_pipe[1], "++++++++++++++++", 16); 
      write(stdlog_pipe[1], "++++++++++++++++", 16); 
    }; 
    write(new_fd, "Completed\n", sizeof("Completed\n")); 
#if 1 
    //dup2(stdlog_pipe[0], new_fd); 
    //dup2(new_fd, stdlog_pipe[0]); 
#else 
    close(stdlog_pipe[0]); 
    stdlog_pipe[0] = new_fd; 
#endif
    write(stdlog_pipe[1], "%%%%", 4);
    stdlog_d = stdlog_pipe[1]; 
    write(new_fd, "NEW_FD works BIS!\n", sizeof("NEW_FD works BIS!\n")); 
    write(stdlog_d, "Pipe works!\n", sizeof("Pipe works!\n")); 
    for (int i = 0; i < 1; i++) { 
      write(stdlog_d, "+", 1);
    }; 
  };
#else 
  stdlog_d = new_fd; 
#endif 
}; 

static void main__stderr_open(int * stduser_d_r, const char * filename) { 
  if (NULL ==  filename) return; 
  if ('\0' == *filename) return; 
  if (0 == strcasecmp("stdout",  filename)) { *stduser_d_r = stdout_d; return; }; 
  if (0 == strcasecmp("stderr",  filename)) { *stduser_d_r = stderr_d; return; }; 
  if (0 == strcasecmp("stdnull", filename)) { filename = "/dev/null"; }; 
  int new_fd; 
  new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600); 
  if (new_fd < 0) return; 
  *stduser_d_r = new_fd; 
}; 



//struct a_t { char u; char aa[]; }; // RL: sizeof(struct a_t) = 1 


int main(const int argc, const char * argv[]) { 
  int_anime_error_t error_id; 
  goto label__body; 


 label__exit: { 
    if (stdlog_d > 0) { dprintf(stdlog_d, "Exit value = [ %d ] %s " "\n", error_id, int_anime_error__get_cstr(error_id)); }; 
    handler_buffer_flush(); 
    return error_id; 
  }; 

 label__body: { 
    //fprintf(stderr, "anime_token_env__sizeof = %d" "\n", (int) (anime_token_env__sizeof)); 
    main__stdlog_init(); 
    main_arg_print(argc, argv, stdlog_d); 
    srandomdev(); 
  
    { 
      enum { STRFTIME_BUFFER_SIZE = 64 }; 
      char strftime_buffer[STRFTIME_BUFFER_SIZE]; 
      const time_t clock = time(NULL); 
      struct tm timeptr[1]; 
    
      bzero(timeptr, sizeof(timeptr));
      gmtime_r(&clock, timeptr); 
      strftime(strftime_buffer, sizeof(strftime_buffer), "TZ=%Z %Y_%m_%d-%Hh%Mm%Ss %A", timeptr); 
      strftime_buffer[STRFTIME_BUFFER_SIZE-1] = '\0';
      if (stdlog_d > 0) dprintf(stdlog_d, "%s" "\n", strftime_buffer); 
 
      bzero(timeptr, sizeof(timeptr));
      localtime_r(&clock, timeptr); 
      strftime(strftime_buffer, sizeof(strftime_buffer), "TZ=%Z %Y_%m_%d-%Hh%Mm%Ss %A", timeptr); 
      strftime_buffer[STRFTIME_BUFFER_SIZE-1] = '\0'; 
      if (stdlog_d > 0) dprintf(stdlog_d, "%s" "\n", strftime_buffer); 
    }; 
  
    if (!program_options__parse(argc, argv)) { 
      const char err_str[] = "Error while parsing options" "\n"; 
      enum { err_str_len = ARRAY_LEN(err_str) - 1 }; 
      write(stderr_d, err_str, err_str_len); 
      if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s", __func__, err_str); }; 
      error_id = ANIME__MAIN__OPTIONS__PARSING_ERROR; 
      goto label__exit; 
    }; 
  
    char error_str[ANIME__ERROR_BUFFER_SIZE]; 
    error_id = program_options__run(argc, argv, /*stdprint_d*/stdout_d, /*stduser_d*/stderr_d, /*stdlog_d*/stdlog_d); 
    if (ANIME__OK != error_id) { goto label__exit; }; 
  
    //dprintf(stderr_d, "program_options__stdlog_new_output = %s" "\n", program_options__stdlog_new_output); 
    if (program_options__stdlog_new_output != NULL) { 
      main__stdlog_reopen(program_options__stdlog_new_output); 
    }; 
  
    int stduser_d = stderr_d; 
    if (program_options[PROGRAM_OPTIONS_INDEX__QUIET] > 0) { 
      stduser_d = -1; 
    }; 
    if (program_options__stduser_new_output != NULL) { 
      main__stderr_open(&stduser_d, program_options__stduser_new_output); 
    }; 
  
    assert(program_options__plain__nb > 0); 
  
    int          input_file_fd   = stdin_d;
    const char * input_file_name = "<stdin>";  
    for (;;) { 
      const int arg_i = program_options__plain[0]; 
      const char * s = argv[arg_i];
      if ('-' == *s && '\0' == *(s+1)) break; 
      if (0 == strcasecmp(s, "stdin")) break; 
      input_file_name = s; 
      input_file_fd   = open(input_file_name, O_RDONLY); 
      if (0 > input_file_fd) { 
	error_id = ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
	snprintf(error_str, ANIME__ERROR_BUFFER_SIZE, "Cannot open input file: %s", input_file_name); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
	if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
	goto label__exit; 
      }; 
      break; 
    }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_name = %s" "\n", __func__, input_file_name); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_fd   = %d" "\n", __func__, input_file_fd  ); }; 
  
  
#if 0 
    dprintf(stderr_d, "ANIME__MAIN__CANNOT_OPEN_INPUT_FILE = %d [ %s ]" "\n", ANIME__MAIN__CANNOT_OPEN_INPUT_FILE, int_anime_error__get_cstr(ANIME__MAIN__CANNOT_OPEN_INPUT_FILE));
    dprintf(stderr_d, "ANIME__OK = %d [ %s ]" "\n", ANIME__MAIN__CANNOT_OPEN_INPUT_FILE, int_anime_error__get_cstr(ANIME__OK));
#endif 
  
    do { 
      anime_t a_anime[1]; 
      anime__make_r(a_anime, stdlog_d); 
      //anime__print_d(a_anime, stduser_d); 
    
      error_id = anime__fill_from_file(a_anime, input_file_name, input_file_fd, stduser_d); 
      if (error_id != ANIME__OK) { 
	if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
	break; 
      }; 
    
      if (program_options[PROGRAM_OPTIONS_INDEX__PRINT] > 0) { 
	anime__print_d(a_anime, stdout_d); 
      }; 
    
  
      for (int i = 1; i < program_options__plain__nb; i++) { 
	const int arg_i = program_options__plain[i]; 
	error_id = anime__print_field_value_by_name(a_anime, argv[arg_i], /*stdprint_d*/stdout_d, /*stduser_d*/stduser_d, &a_anime -> error_id, a_anime -> error_size, a_anime -> error_str); 
	if (error_id != ANIME__OK) { 
	  if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
	}; 
      }; 
    
      if (error_id == ANIME__OK) { 
	if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "OK" "\n", a_anime -> filename); 
	break; 
      }; 
    } while (false); 
  
    if (input_file_fd != stdin_d) { 
      close(input_file_fd); 
    }; 
  
    if (stduser_d > 2) { 
      close(stduser_d); 
    }; 
  
    goto label__exit; 
  }; 


}; 








#if 0 
int main_old001(const int argc, const char * argv[]) { 
  //fprintf(stderr, "anime_token_env__sizeof = %d" "\n", (int) (anime_token_env__sizeof)); 
  main__init_stdlog(); 
  main_arg_print(argc, argv, stdlog_d); 
  srandomdev(); 
  
  { 
    enum { STRFTIME_BUFFER_SIZE = 64 }; 
    char strftime_buffer[STRFTIME_BUFFER_SIZE]; 
    const time_t clock = time(NULL); 
    struct tm timeptr[1]; 
    
    bzero(timeptr, sizeof(timeptr));
    gmtime_r(&clock, timeptr); 
    strftime(strftime_buffer, sizeof(strftime_buffer), "TZ=%Z %Y_%m_%d-%Hh%Mm%Ss %A", timeptr); 
    strftime_buffer[STRFTIME_BUFFER_SIZE-1] = '\0';
    if (stdlog_d > 0) dprintf(stdlog_d, "%s" "\n", strftime_buffer); 
 
    bzero(timeptr, sizeof(timeptr));
    localtime_r(&clock, timeptr); 
    strftime(strftime_buffer, sizeof(strftime_buffer), "TZ=%Z %Y_%m_%d-%Hh%Mm%Ss %A", timeptr); 
    strftime_buffer[STRFTIME_BUFFER_SIZE-1] = '\0';
    if (stdlog_d > 0) dprintf(stdlog_d, "%s" "\n", strftime_buffer); 
  }; 
  
  
  if (1 == argc) { 
    main__usage(argc, argv); 
    return ANIME__MAIN__NO_ARG; 
  }; 
  
  if (2 > argc) { 
    main__usage(argc, argv); 
    return ANIME__MAIN__TOO_MANY_ARGS; 
  }; 

  if ('-' == *argv[1] && '\0' != *(argv[1]+1)) { 
    main__usage(argc, argv); 
    return ANIME__MAIN__BAD_ARG; 
  }; 

  int          input_file_fd   = stdin_d;
  const char * input_file_name = "<stdin>";  
  do {
    if ('-' == *argv[1] && '\0' == *(argv[1]+1)) break; 
    input_file_name = argv[1]; 
    input_file_fd = open(input_file_name, O_RDONLY); 
    if (0 > input_file_fd) {
      fprintf(stderr, "Cannot open input file: %s" "\n", input_file_name, "\n"); 
      return ANIME__MAIN__CANNOT_OPEN_INPUT_FILE; 
    }; 
  } while (false); 
  dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_name = %s" "\n", __func__, input_file_name); 
  
  
  
  int error_id = ANIME__OK;   
  do { 
    anime_t a_anime[1]; 
    int alright_huh; 
    anime__make_r  (a_anime, stdlog_d); 
    //anime__print_d (a_anime, stdout_d); 
    
#if 1
    do { 
      anime_token_input_env_t   *  input_env; 
      anime_token_env_t   *  token_env; 
      //anime_parser_env_t  * parser_env; 
      //anime_t * this; 
      
      //this = NULL; 
      //this = anime_make(); 
      input_env  = anime_token_input_env__make(stdlog_d); 
      token_env  = anime_token_env__make(stdlog_d);  
      //parser_env = anime_parser_env__make(); 

        const int input_i = anime_token_input__stack_push__filedes(input_env, input_file_fd, input_file_name); 
	assert(input_i >= 0); 
  
	const int allright_huh = anime_token__parser(input_env, input_i, token_env); 
	if (not(allright_huh)) { dputs_array(stderr_d, "Something got wrong.\n"); break; }; 
	
	anime_token__print_all_tokens(stdlog_d, token_env); fflush(NULL); 

#if 0 
	error_id = anime_data_generation_001_from_tokens(token_env, a_anime); 
	//dprintf(stdlog_d, "error_id: %d" "\n", error_id); 
	if (error_id != ANIME__OK) { 
	  dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
	  break; 
	}; 
#elif 0 
	error_id = anime_parser__parenthesis__check(token_env); 
	//dprintf(stdlog_d, "error_id: %d" "\n", error_id); 
	if (0 == error_id) { dprintf(stderr_d, "parenthesis_check: OK" "\n"); }; 
	if (error_id != 0) { 
	  dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, "anime_parser__parenthesis__check"); 
	  break; 
	}; 
	
	anime_parser_env_t * parser_env; 
	parser_env = anime_parser_env__make(stdlog_d); 
	error_id = anime_parser__automaton(parser_env, token_env); 
	if (0 <= error_id) { dprintf(stderr_d, "tree_building: OK (%d)" "\n", error_id); }; 
	if (error_id < 0) { 
	  dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, "parser"); 
	  break; 
	}; 
	
	const anime_tree_env_t * tree_env = anime_parser_env__get_tree_env(parser_env); 
	
	anime_tree_env__print_d__raw(tree_env, stderr_d); 


	error_id = anime_data_generation_002_from_trees(tree_env, token_env, a_anime, stderr_d); 
	//dprintf(stdlog_d, "error_id: %d" "\n", error_id); 
	if (error_id != ANIME__OK) { 
	  dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
	  break; 
	}; 
	
#elif 1 

	//dprintf(stdlog_d, "ANIME__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS = %d" "\n", ANIME__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS); exit(0); 
	//dprintf(stdlog_d, "ANIME__DATA_GENERATION__TOO_MANY_TOKENS = %d" "\n", ANIME__DATA_GENERATION__TOO_MANY_TOKENS); exit(0); 
	//dprintf(stdlog_d, "ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1 = %d" "\n", ANIME__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1); exit(0); 
	
	error_id = anime_data_generation_003_from_syntax_filtering(token_env, a_anime, stderr_d); 
	//dprintf(stdlog_d, "error_id: %d" "\n", error_id); 
	if (error_id != ANIME__OK) { 
	  dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
	  break; 
	}; 
	
#else 
	assert(false); 
#endif 
	
	
	error_id = anime__consistency_check(a_anime, stderr_d); 
	//anime__print_d(a_anime, stderr_d); 
	anime__print_d(a_anime, stdout_d); 
	if (error_id == ANIME__OK) { 
	  dprintf(stderr_d, "<%s>: " "OK" "\n", a_anime -> filename); 
	  break; 
	}; 
	
	//anime__print_d(a_anime, stderr_d); 
	dprintf(stderr_d, "<%s>: " "%s[%d]: " "%s" "\n", a_anime -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_anime -> error_str); 
	
    } while (false); 
#else     
    alright_huh = anime__fill_from_file__new(a_anime, input_file_name, input_file_fd); 
#endif 
    

#if 0 
    dprintf(stdlog_d, "STRING_STACK[ %d / %d ] = %.1f%%" "\n", a_anime -> string_stack_nb, (int) (sizeof(a_anime -> string_stack) / sizeof(*(a_anime -> string_stack))), 100.0 * ((double) a_anime -> string_stack_nb) / ((double) (sizeof(a_anime -> string_stack) / sizeof(*(a_anime -> string_stack)))));  
#endif 
#if 0  
    fprintf(stderr, "LEXER_STACK[ %d / %d ] = %.1f%%" "\n", a_anime -> lexer_stack_nb, sizeof(a_anime -> lexer_stack) / sizeof(*(a_anime -> lexer_stack)), 100.0 * ((double) a_anime -> lexer_stack_nb) / ((double) (sizeof(a_anime -> lexer_stack) / sizeof(*(a_anime -> lexer_stack)))));  
#endif 
    
    anime__delete_r(a_anime); 
  } while (false); 
  
  
  if (input_file_fd != stdin_d) { 
    close(input_file_fd); 
  }; 
  
  
#if 0 
  fprintf(stderr, "Hello World!" "\n"); 
  fprintf(stderr, "%d" "\n", INT8_MIN); 
  fprintf(stderr, "%d" "\n", ~(INT8_MAX)); 
  fprintf(stderr, "%d" "\n", ANIME__STRCOPY); 
#endif 
  
  //return ANIME__MAIN__OK; 
  return error_id; 
}; 
#endif 
