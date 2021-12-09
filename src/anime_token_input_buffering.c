#include "anime_global.h" 
#include "anime_token_input_buffering.h" 

enum { INT_ANIME_TOKEN_INPUT_STACK_TOP = sizeof(int_anime_token_input_stack_t) == 1 ? UINT8_MAX : sizeof(int_anime_token_input_stack_t) == 2 ? UINT16_MAX : sizeof(int_anime_token_input_stack_t) == 4 ? UINT32_MAX : sizeof(int_anime_token_input_stack_t) == 8 ? UINT64_MAX : 0 }; 
enum { INT_ANIME_TOKEN_INPUT_STACK_MAX = INT_ANIME_TOKEN_INPUT_STACK_TOP - 1 }; // UINT8_MAX value is kept aside as an invalid value. 
const int_anime_token_input_stack_t int_anime_token_input_stack_max = INT_ANIME_TOKEN_INPUT_STACK_MAX; 

static const char * anime_token_input__type_cstr_tab[] = {
  "NULL", 
  "RO_MEM", 
  "FILE",   // RL: Owner, as we open the file. 
  "FD",     // RL: Given, so we are not the owner, and we should not close it. 
  NULL 
}; 
 
enum { anime_token_input__type_cstr_tab__size = ARRAY_SIZE(anime_token_input__type_cstr_tab) }; 

static void assert_compile__dkushdsuf2387645kjhsdfr2(void) { 
  ASSERT_COMPILE(anime_token_input__type_cstr_tab__size == ANIME_TOKEN_INPUT__TYPE__COUNT + 1); 
}; 


const char * anime_token_input_env__strcopy(anime_token_input_env_t * this, const char * cstr) { 
  if (NULL ==  cstr) { return this -> string_stack; }; 
  if ('\0' == *cstr) { return this -> string_stack; }; 
  const int len1 = 1 + strlen(cstr); 
  if (this -> string_stack_nb + len1 > ANIME_TOKEN_INPUT__STRING_STACK_SIZE) { 
    this -> error_id = ANIME_TOKEN_INPUT__STRCOPY; 
    snprintf(this -> error_str, ANIME_TOKEN_INPUT__ERROR_BUFFER_SIZE, "Not enough space in the anime buffer to copy the string (mem needed: %d ; mem left: %d ; cstr: '%s')", len1, ANIME_TOKEN_INPUT__STRING_STACK_SIZE - this -> string_stack_nb, cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> string_stack + this -> string_stack_nb; 
  bcopy(cstr, new_str, len1); 
  this -> string_stack_nb += len1; 
  return new_str; 
}; 


anime_token_input_env_t * anime_token_input_env__make_r(anime_token_input_env_t * this, const int stdlog_d) { 
  bzero(this, sizeof(*this)); 
  this -> stdlog_d = stdlog_d; 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb++; 
  this -> stack_nb = 0; 
  return this; 
}; 
 
anime_token_input_env_t * anime_token_input_env__make_b(const int bsize, void * bvalue, const int stdlog_d, int * used_size_ref) { 
  anime_token_input_env_t * this = (anime_token_input_env_t *) bvalue; 
  if (bsize < (int)sizeof(*this)) return NULL; 
  if (NULL != used_size_ref) *used_size_ref = sizeof(*this); 
  return anime_token_input_env__make_r(this, stdlog_d); 
}; 

anime_token_input_env_t * anime_token_input_env__make(const int stdlog_d) { 
  MALLOC_BZERO(anime_token_input_env_t,this); 
  anime_token_input_env__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
}; 

void anime_token_input_env__delete_r(anime_token_input_env_t * this) { 
  assert(0 == this -> stack_nb); 
  bzero(this, sizeof(*this)); 
}; 
 
void anime_token_input_env__delete(anime_token_input_env_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  anime_token_input_env__delete_r(this); 
  if (1 == malloced_flag) { 
    free(this); 
  }; 
}; 

 

static int anime_token_input__make__alloc_and_init(anime_token_input_env_t * this, const int input_type) { 
  assert(this -> stack_nb < ANIME_TOKEN_INPUT__STACK_SIZE); 
  const int input_i = this -> stack_nb;  
  this -> stack_nb++; 
  
  this -> input_type[input_i] = input_type; 
  this -> ro_mem    [input_i] = NULL; 
  this -> ro_mem_len[input_i] = -1; 
  this -> fileno    [input_i] = -1; 
  this -> filename  [input_i] = NULL; 
  
  //anime_token_input__make__assign_buffer(this, input_i); 
  //this -> cumulated_read_nb[input_i] = 0; 
  this -> eof_huh = false; 

#if 1 
  this -> buffer0_char0[input_i] = 0; 
  INT24_PACKED_ASSIGN_UNPACKED(this -> buffer0_line1[input_i],1); 
  this -> buffer_i    [input_i] = 0; 
  this -> buffer_j    [input_i] = 0; 
#else 
  this -> token_char0  [input_i] = 0; 
  INT24_PACKED_ASSIGN_UNPACKED(this -> token_line1[input_i],1); 
  this -> token_column0[input_i] = 0; 
  this -> token_len    [input_i] = 0; 
#endif 
  
#if 0 
  this -> repl_huh = false; 
  this -> repl_prompt_cstr = NULL; 
#endif 
  
  return input_i; 
}; 
 
int anime_token_input__stack_push__filename(anime_token_input_env_t * this, const char * filename_cstr) { 
  if (NULL ==  filename_cstr) { return -1; }; 
  if ('\0' == *filename_cstr) { return -1; }; 
  const char * copied_filename_cstr = anime_token_input_env__strcopy(this, filename_cstr); 
  if (NULL == copied_filename_cstr) { return -1; }; 
  const int fileno = open(filename_cstr, O_RDONLY); 
  if (fileno < 0) { return -1; }; 
  
  const int index = anime_token_input__make__alloc_and_init(this, ANIME_TOKEN_INPUT__TYPE__FILE); 
  this -> filename[index] = copied_filename_cstr; 
  this -> fileno  [index] = fileno; 
  
  return index; 
}; 
 
int anime_token_input__stack_push__memory(anime_token_input_env_t * this, const int ro_mem_len, const char * ro_mem, const char * ro_mem_description) { 
  const char * copied_ro_mem_description = anime_token_input_env__strcopy(this, ro_mem_description); 
  if (NULL != ro_mem_description) { if (NULL == copied_ro_mem_description) { return -1; }; }; 
  const int index = anime_token_input__make__alloc_and_init(this, ANIME_TOKEN_INPUT__TYPE__RO_MEM); 
  this -> ro_mem    [index] = ro_mem; 
  this -> ro_mem_len[index] = ro_mem_len; 
  this -> filename  [index] = copied_ro_mem_description; 
  return index; 
}; 
 
int anime_token_input__stack_push__filedes(anime_token_input_env_t * this, const int fileno, const char * fd_description) { 
  const char * copied_fd_description = anime_token_input_env__strcopy(this, fd_description); 
  if (NULL != fd_description) { if (NULL == copied_fd_description) { return -1; }; }; 
  const int index = anime_token_input__make__alloc_and_init(this, ANIME_TOKEN_INPUT__TYPE__FD); 
  this -> fileno  [index] = fileno; 
  this -> filename[index] = copied_fd_description; 

#if 0   
  this -> repl_huh[index] = (1 == isatty(fileno)); 
  if (this -> repl_huh[index]) { 
    const char * repl_prompt = "> "; 
    const int    repl_promp_pstr = anime_string__push(this -> string_env, repl_prompt); 
    this -> repl_prompt_pstr[index] = repl_promp_pstr; 
    this -> repl_prompt_cstr[index] = anime_string__get_cstr(this -> string_env, repl_promp_pstr); 
  }; 
#endif 
  
  return index; 
}; 

int anime_token_input__stack_pop(anime_token_input_env_t * this) { 
  assert(this -> stack_nb > 0); 
  const int index = this -> stack_nb - 1; 
  if (ANIME_TOKEN_INPUT__TYPE__FILE == this -> input_type[index]) { 
    close(this -> fileno[index]); 
  }; 
  this -> stack_nb--; 
  return this -> stack_nb; 
}; 
 
 
 

int anime_token_input__eof_huh(anime_token_input_env_t * this) { 
  return this -> eof_huh; 
}; 


static int anime_token_input__buffer__fill(anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 

#if 1 
  assert(0 == this -> buffer_nb); 
#else 
  this -> buffer0_char0[input_i] += this -> buffer_nb; 
  {
    int line1; INT24_PACKED_READ (this -> buffer0_line1[input_i], line1); 
    line1++;   INT24_PACKED_WRITE(this -> buffer0_line1[input_i], line1); 
  }; 
  this -> buffer_i    [input_i] = 0; 
  this -> buffer_j    [input_i] = 0; 
#endif 


  switch (this -> input_type[input_i]) { 
  case ANIME_TOKEN_INPUT__TYPE__RO_MEM: goto anime_token_input__buffer__fill__state__ro_mem; break; 
  case ANIME_TOKEN_INPUT__TYPE__FILE  : goto anime_token_input__buffer__fill__state__fileno; break; 
  case ANIME_TOKEN_INPUT__TYPE__FD    : goto anime_token_input__buffer__fill__state__fileno; break; 
  }; 
  assert(false); 
  
  
  
 anime_token_input__buffer__fill__state__fileno: {
    if (this -> repl_huh) { 
      assert(false); 
    } 
    else { 
      ssize_t read_nb = -1; 
      int buffer_i = 0; 
      char c; 
      for (;;) { 
	read_nb = read(this -> fileno[input_i], &c, 1); 
	if ( 0 == read_nb) { this -> eof_huh = (0 == buffer_i); this -> buffer_nb = buffer_i; this -> buffer[buffer_i] = '\0'; return buffer_i; }; 
	if (-1 == read_nb) { this -> buffer_nb = buffer_i; return -1; }; 
	*(this -> buffer + buffer_i) = c; 
	buffer_i += read_nb; 
	if ('\n' == c) { this -> buffer_nb = buffer_i; this -> buffer[buffer_i] = '\0'; return buffer_i; }; 
	if (ANIME_TOKEN_INPUT__BUFFER_SIZE - 1 == buffer_i) { this -> buffer_nb = buffer_i; return -1; }; 
      }; 
    }; 
  }; 
  assert(false); 

 anime_token_input__buffer__fill__state__ro_mem: { 
    const int already_read    = this -> buffer0_char0[input_i]; 
    const int left_to_be_read = this -> ro_mem_len[input_i] - already_read; 
    if (0 >= left_to_be_read) { 
      this -> eof_huh = true; 
      return 0; 
    }; 
#if 1 
    const char * ro_mem     = this -> ro_mem[input_i]; 
    const int    ro_mem_len = this -> ro_mem_len[input_i]; 
    int ro_mem_i = already_read; 
    int buffer_i = 0; 
    char c; 
    for (;;) { 
      if (ro_mem_i == ro_mem_len) { this -> eof_huh = (0 == buffer_i); this -> buffer_nb = buffer_i; this -> buffer[buffer_i] = '\0'; return buffer_i; }; 
      c = ro_mem[ro_mem_i]; 
      *(this -> buffer + buffer_i) = c; 
      buffer_i ++; 
      ro_mem_i ++; 
      if ('\n' == c) { this -> buffer_nb = buffer_i; this -> buffer[buffer_i] = '\0'; return buffer_i; }; 
      if (ANIME_TOKEN_INPUT__BUFFER_SIZE - 1 == buffer_i) { this -> buffer_nb = buffer_i; return -1; }; 
    }; 
#else 
    const int bcopy_nb = MIN(ANIME_TOKEN_INPUT__BUFFER_SIZE,left_to_be_read); 
    bcopy(this -> ro_mem[input_i], this -> buffer, bcopy_nb); 
    this -> buffer_nb = bcopy_nb; 
    return bcopy_nb; 
#endif 
  }; 
  assert(false); 
  
  return -1; 
}; 

 
int anime_token_input__getc(anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
#if 0 
  { 
    dputs_array(stderr_d, __func__, "\n"); 
    dputs_array(stderr_d, "this -> buffer0_char0[input_i] = ", int_string__stack(this -> buffer0_char0[input_i]), "\n"); 
    int line1; INT24_PACKED_READ (this -> buffer0_line1[input_i], line1); 
    dputs_array(stderr_d, "this -> buffer0_line1[input_i] = ", int_string__stack(line1), "\n"); 
    dputs_array(stderr_d, "this -> buffer_i     [input_i] = ", int_string__stack(this -> buffer_i[input_i]), "\n"); 
    dputs_array(stderr_d, "this -> buffer_j     [input_i] = ", int_string__stack(this -> buffer_j[input_i]), "\n"); 
    dputs_array(stderr_d, "this -> buffer_nb    [input_i] = ", int_string__stack(this -> buffer_nb), "\n"); 
    dputs_array(stderr_d, "this -> buffer       [input_i] = "); for (int i = 0; i < this -> buffer_nb; i++) dputc(stderr_d, this -> buffer[i]); dputc(stderr_d, '\n'); 
    dputs_array(stderr_d, "this -> eof_huh      [input_i] = ", bool_string(this -> eof_huh), "\n"); 
  }; 
#elif 0 
  dputs_array(stderr_d, __func__, "\n"); 
  dputs_array(stderr_d, "this -> current_buffer0[input_i] = ", int_string__stack(this -> current_buffer0[input_i]), "\n"); 
  dputs_array(stderr_d, "this -> token_buffer0  [input_i] = ", int_string__stack(this -> token_buffer0[input_i]), "\n"); 
  dputs_array(stderr_d, "this -> buffer_nb      [input_i] = ", int_string__stack(this -> buffer_nb[input_i]), "\n"); 
  dputs_array(stderr_d, "this -> eof_huh        [input_i] = ", bool_string(this -> eof_huh[input_i]), "\n"); 
#endif 
  
  if (this -> eof_huh) { return EOF; }; 
  
  if (0 == this -> buffer_nb) { 
    anime_token_input__buffer__fill(this); 
    if (this -> eof_huh) { return EOF; }; 
  }; 
  
  assert(this -> buffer_nb > 0); 
  
  if (this -> buffer_j[input_i] == this -> buffer_nb) { 
    if (this -> buffer_i[input_i] != this -> buffer_nb) { 
      assert('\n' != this -> buffer[this -> buffer_nb - 1]); 
      //return -3; // EOF reached - won't continue until you validate the input. 
      return EOF; 
    }; 
    
    assert(this -> buffer_j[input_i] == this -> buffer_i[input_i]); 
    
    this -> buffer0_char0[input_i] += this -> buffer_nb; 
    if ('\n' == this -> buffer[this -> buffer_nb - 1]) {
      int line1; INT24_PACKED_READ (this -> buffer0_line1[input_i], line1); 
      line1++;   INT24_PACKED_WRITE(this -> buffer0_line1[input_i], line1); 
    }; 
    this -> buffer_nb = 0; 
    this -> buffer_i[input_i] = 0; 
    this -> buffer_j[input_i] = 0; 
    anime_token_input__buffer__fill(this); 
    //dprintf(stderr_d, "BUFFER: %s", this -> buffer); 
    if (this -> eof_huh) { return EOF; }; 
    assert(this -> buffer_nb > 0); 
  }; 
  
  assert(this -> buffer_j[input_i] < this -> buffer_nb); 
  //const int c = this -> buffer[this -> buffer_j[input_i]]; 
  const unsigned char c = this -> buffer[this -> buffer_j[input_i]]; 
  this -> buffer_j[input_i]++; 
  return c; 
}; 


void anime_token_input__move_backward(anime_token_input_env_t * this, const int chars_nb) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  assert(chars_nb >= 0); 
  assert(chars_nb <= this -> buffer_j[input_i]); 
  this -> buffer_j[input_i] -= chars_nb; 
  assert(this -> buffer_i[input_i] <= this -> buffer_j[input_i]); 
}; 
 
const char * anime_token_input__get_srcval_rstr(anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  return (this -> buffer) + (this -> buffer_i[input_i]); 
}; 
 
int anime_token_input__get_srcval_len(anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  return this -> buffer_j[input_i] - this -> buffer_i[input_i]; 
}; 
 
void anime_token_input__validate(anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  this -> buffer_i[input_i] = this -> buffer_j[input_i]; 
}; 







void anime_token_input__repl__turn_off(anime_token_input_env_t * this) { 
  this -> repl_huh = false; 
}; 
 
void anime_token_input__repl__turn_on(anime_token_input_env_t * this) { 
  this -> repl_huh = true; 
}; 

int anime_token_input__repl__set_prompt(anime_token_input_env_t * this, const char * prompt_cstr) { 
  if (NULL == prompt_cstr) { 
    const char * copied_prompt = anime_token_input_env__strcopy(this, ""); 
    assert(NULL != copied_prompt); 
    this -> repl_prompt_cstr = copied_prompt; 
    return ANIME_TOKEN_INPUT__OK; 
  }; 
  const char * copied_prompt = anime_token_input_env__strcopy(this, prompt_cstr); 
  if (NULL == copied_prompt) { return ANIME_TOKEN_INPUT__STRCOPY; }; 
  this -> repl_prompt_cstr = copied_prompt; 
  return ANIME_TOKEN_INPUT__OK; 
}; 

const char * anime_token_input__get_filename_cstr(const anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  return this -> filename[input_i]; 
}; 

int anime_token_input__get_token_location(const anime_token_input_env_t * this, int24_t * token_line1_ref, uint16_t * token_column0_ref, uint16_t * token_len_ref) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  //INT24_PACKED_ASSIGN_PACKED(*token_line1_ref, this -> buffer0_line1[input_i]); 
  INT24_PACKED_READ(this -> buffer0_line1[input_i],*token_line1_ref); 
  *token_column0_ref = this -> buffer_i[input_i]; 
  *token_len_ref = this -> buffer_j[input_i] - this -> buffer_i[input_i]; 
  return ANIME_TOKEN_INPUT__OK; 
}; 

int anime_token_input__get_line1(const anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  int line1; 
  //INT24_PACKED_ASSIGN_PACKED(*token_line1_ref, this -> buffer0_line1[input_i]); 
  INT24_PACKED_READ(this -> buffer0_line1[input_i],line1); 
  return line1; 
}; 

int anime_token_input__get_column0(const anime_token_input_env_t * this) { 
  assert(0 < this -> stack_nb); 
  const int input_i = this -> stack_nb - 1; 
  //dprintf(stderr_d, "BUFFER: buffer_i = %d — buffer_j = %d " "\n", this -> buffer_i[input_i], this -> buffer_j[input_i]); 
  return this -> buffer_i[input_i]; 
}; 



