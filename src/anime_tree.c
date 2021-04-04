#include "anime_global.h"
#include "anime.h"
#include "anime_tree.h"

#define DEBUG 1 

enum { INT_ANIME_TREE_TOP = sizeof(int_anime_tree_t) == 1 ? UINT8_MAX : sizeof(int_anime_tree_t) == 2 ? UINT16_MAX : sizeof(int_anime_tree_t) == 4 ? UINT32_MAX : sizeof(int_anime_tree_t) == 8 ? UINT64_MAX : -1 }; 
enum { INT_ANIME_TREE_MAX = INT_ANIME_TREE_TOP - 1 }; // The top value («~0») is used as an invalid value. 
 
const int_anime_tree_t int_anime_tree_max = INT_ANIME_TREE_MAX; 


int_anime_tree_t anime_tree_env__sizeof(anime_tree_env_t * this) { 
  return sizeof(*this) + this -> memory__array_size; 
}; 

int_anime_tree_t anime_tree_env__sizeof_alloc(const int memory__array_size) { 
  return sizeof(anime_tree_env_t) + memory__array_size; 
}; 

void anime_tree_env__bzero(anime_tree_env_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  const int stdlog_d = this -> stdlog_d; 
  const int mem_size = this -> memory__array_size; 
  bzero(this, sizeof(*this) + mem_size); 
  this -> memory__array_size = mem_size; 
  this -> malloced_flag = malloced_flag; 
  this -> stdlog_d = stdlog_d; 
};  

anime_tree_env_t * anime_tree_env__make_r(anime_tree_env_t * this, const int data_memory_size, const int stdlog_d) { 
  const int memory__array_size = data_memory_size > 0 ? data_memory_size : anime_tree__memory__array_size__default; 
  bzero(this, sizeof(*this) + memory__array_size); 
  this -> stdlog_d = stdlog_d; 
  //this -> string_stack[0] = '\0'; 
  //this -> string_stack_nb++; 
  this -> field_bitsize = 16; 
  this -> memory__array_size = memory__array_size; 
  return this; 
}; 

anime_tree_env_t * anime_tree_env__make_b(const int bsize, void * bvalue, int * used_size_ref, const int data_memory_size, const int stdlog_d) { 
  const int memory__array_size = data_memory_size > 0 ? data_memory_size : anime_tree__memory__array_size__default; 
  anime_tree_env_t * this = (anime_tree_env_t *) bvalue; 
  if (bsize < (int)(sizeof(*this) + memory__array_size)) return NULL; 
  if (NULL != used_size_ref) *used_size_ref = (sizeof(*this) + memory__array_size); 
  return anime_tree_env__make_r(this, data_memory_size, stdlog_d); 
}; 
 
anime_tree_env_t * anime_tree_env__make(const int data_memory_size, const int stdlog_d) { 
  const int memory__array_size = data_memory_size > 0 ? data_memory_size : anime_tree__memory__array_size__default; 
  anime_tree_env_t * this = (anime_tree_env_t *) malloc(sizeof(anime_tree_env_t) + memory__array_size); 
  anime_tree_env__make_r(this, data_memory_size, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
}; 

void anime_tree_env__delete_r(anime_tree_env_t * this) {
  anime_tree_env__bzero(this); 
}; 

void anime_tree_env__delete(anime_tree_env_t * this) {
  const int malloced_flag = this -> malloced_flag; 
  anime_tree_env__delete_r(this); 
  if (1 == malloced_flag) { 
    free(this); 
  }; 
}; 

void anime_tree_env__print_f(const anime_tree_env_t * this, FILE * out_stream) { 
  anime_tree_env__print_d(this, fileno(out_stream)); 
}; 

 
void anime_tree_env__print_d__raw(const anime_tree_env_t * this, const int fd) { 
  if (NULL == this) { dprintf(fd, "ANIME_TREE_ENV is NULL" "\n"); return; }; 
  
  dprintf(fd, "struct anime_tree_env_t { " "\n"); 
  dprintf(fd, "  uint8_t malloced_flag = %d; // 0 if not, 1 if yes." "\n", this -> malloced_flag); 
  
  dprintf(fd, "  int stdlog_d = %d; // Foreign — we don't own it; valid only if 'stdlog_d > 0'" "\n", this -> stdlog_d);  
  
  dprintf(fd, "  int8_t  error_id = %d; // 0: none; …<0: error; …>0: warning" "\n", this -> error_id);   
  dprintf(fd, "  char    error_str[%d];" "\n", (int) ARRAY_LEN(this -> error_str));   
  
  dprintf(fd, "  int8_t filled_huh = %d; // 0: not done; -1: currently being filled; 1: yes, filled up" "\n", this -> filled_huh);   
  
  //char     string_stack[ANIME__STRING_STACK_SIZE]; 
  //uint16_t string_stack_nb; 
  
  
  dprintf(fd, "  uint8_t  field_bitsize = %d;      // RL: Bit-wideness of this structure fields: 8 bits, 16 bits, 32 bits, or 64 bits. (Currently, it's statically 16.)" "\n", this -> field_bitsize);   
  dprintf(fd, "  uint16_t memory__array_size = %d; // RL: Allocated size of the array." "\n", this -> memory__array_size);   
  dprintf(fd, "  uint16_t memory__array_nb = %d;   // RL: Bottom of the array (but top of the stack)." "\n", this -> memory__array_nb);   
  const int nb_bytes = MAX(0,MIN(8,this -> memory__array_nb)); 
  dprintf(fd, "  char     memory__array[] = { %X, %X, %X, %X, %X, %X, %X, %X, … };    // RL: Top of the array (but bottom of the stack)." "\n", 
	  nb_bytes >= 1 ? this -> memory__array[0] : 0xFF, 
	  nb_bytes >= 2 ? this -> memory__array[1] : 0xFF, 
	  nb_bytes >= 3 ? this -> memory__array[2] : 0xFF, 
	  nb_bytes >= 4 ? this -> memory__array[3] : 0xFF, 
	  nb_bytes >= 5 ? this -> memory__array[4] : 0xFF, 
	  nb_bytes >= 6 ? this -> memory__array[5] : 0xFF, 
	  nb_bytes >= 7 ? this -> memory__array[6] : 0xFF, 
	  nb_bytes >= 8 ? this -> memory__array[7] : 0xFF 
	  );   
  dprintf(fd, "};" "\n"); 
}; 

void anime_tree_env__print_d(const anime_tree_env_t * this, const int fd) { 
  dprintf(fd, "ANIME_TREE_ENV" "\n"); 
}; 



// *** TREE_CHUNK *** 
//  - uint16_t: size 
//  - uint8_t : type 
//  - uint8_t : child_nb 
//  - uint8_t : shift_to_first_child 
//  - bytes   : data (not a field per se) 

int_anime_tree_t anime_tree__open(anime_tree_env_t * this, const uint8_t tree_type) { 
  if (this -> memory__array_nb + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t) >=  this -> memory__array_size) return ~0; 
  const int anime_tree = this -> memory__array_nb; 
#if 1 || DEBUG >= 10 
  dprintf(stderr_d, "OPEN at %d" "\n", anime_tree); 
#endif
  /* uint16_t: size                 */ *((uint16_t *) (this -> memory__array + anime_tree)) = ~0; // Being filled. 
  /* uint8_t : type                 */ *((uint8_t  *) (this -> memory__array + anime_tree + sizeof(uint16_t))) = tree_type; 
  /* uint8_t : child_nb             */ *((uint8_t  *) (this -> memory__array + anime_tree + sizeof(uint16_t) + sizeof(uint8_t))) = ~0; // Being filled. 
  /* uint8_t : shift_to_first_child */ *((uint8_t  *) (this -> memory__array + anime_tree + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t))) = ~0; // Being filled. 
  /* bytes   : data (not a field per se) */ this -> memory__array_nb += sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t); 
  return anime_tree; 
}; 

int_anime_tree_t anime_tree__get_top_address(const anime_tree_env_t * this) { 
  return this -> memory__array_nb; 
}; 

void anime_tree__close(anime_tree_env_t * this, const int anime_tree, const int first_child_address) { 
  const int chunk_size = this -> memory__array_nb - anime_tree; 
  const int shift_to_first_child = first_child_address - anime_tree; 
  char * p = this -> memory__array + anime_tree; 
  *((uint16_t *) p) = chunk_size; 
  int fils_nb = 0; 
  int fils_id = first_child_address; 
  for (;;) { 
    if (fils_id >= this -> memory__array_nb) { break; }; 
    fils_nb ++; 
    char * q = this -> memory__array + fils_id; 
    const int sz = *((uint16_t *) (q)); 
    fils_id += sz; 
  }; 
  *((uint8_t *) (p + sizeof(uint16_t) + sizeof(uint8_t))) = fils_nb; 
  *((uint8_t *) (p + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t))) = shift_to_first_child; 
#if DEBUG >= 100 
  dprintf(stderr_d, "\t" "chunk_size           = %d" "\n", chunk_size); 
  dprintf(stderr_d, "\t" "chunk_size           = %d" "\n", *((uint16_t *) p)); 
  dprintf(stderr_d, "\t" "chunk_size @0        = %d" "\n", *((uint16_t *) (this -> memory__array))); 
  dprintf(stderr_d, "\t" "fils_nb              = %d" "\n", fils_nb); 
  dprintf(stderr_d, "\t" "shift_to_first_child = %d" "\n", shift_to_first_child); 
#endif
#if DEBUG >= 10 
  dprintf(stderr_d, "CLOSE at %d" "\n", anime_tree); 
#endif
}; 

int anime_tree__push_uint8(anime_tree_env_t * this, const uint8_t data) { 
  if (this -> memory__array_nb + sizeof(uint8_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  *((uint8_t *) (this -> memory__array + this -> memory__array_nb)) = data; 
  this -> memory__array_nb += sizeof(uint8_t); 
  return ANIME__OK; 
}; 

int anime_tree__read_uint8(const anime_tree_env_t * this, const int address, uint8_t * data_r) {
  if (address < 0) { return ANIME__TREE__WRONG_ADDRESS; }; 
  if (address + sizeof(uint8_t) > (this -> memory__array_nb)) { return ANIME__TREE__WRONG_ADDRESS; }; 
  *data_r = *((const uint8_t *) (this -> memory__array + address)); 
  return ANIME__OK; 
};

int anime_tree__push_int8(anime_tree_env_t * this, const int8_t data) { 
  if (this -> memory__array_nb + sizeof(int8_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  *((int8_t *) (this -> memory__array + this -> memory__array_nb)) = data; 
  this -> memory__array_nb += sizeof(int8_t); 
  return ANIME__OK; 
}; 

int anime_tree__push_uint16(anime_tree_env_t * this, const uint16_t data) { 
  if (this -> memory__array_nb + sizeof(uint16_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  *((uint16_t *) (this -> memory__array + this -> memory__array_nb)) = data; 
  this -> memory__array_nb += sizeof(uint16_t); 
  return ANIME__OK; 
}; 

int anime_tree__write_uint16(anime_tree_env_t * this, const int address, const uint16_t data) { 
#if DEBUG >= 50 
  dprintf(stderr_d, "WRITE at %d = %d" "\n", address, data); 
#endif
  if (address < 0) { return ANIME__TREE__WRONG_ADDRESS; }; 
  if (address + sizeof(uint16_t) > (this -> memory__array_nb)) { return ANIME__TREE__WRONG_ADDRESS; }; 
  *((uint16_t *) (this -> memory__array + address)) = data; 
  return ANIME__OK; 
};
  
int anime_tree__read_uint16(const anime_tree_env_t * this, const int address, uint16_t * data_r) {
  if (address < 0) { return ANIME__TREE__WRONG_ADDRESS; }; 
  if (address + sizeof(uint16_t) > (this -> memory__array_nb)) { return ANIME__TREE__WRONG_ADDRESS; }; 
  *data_r = *((const uint16_t *) (this -> memory__array + address)); 
  return ANIME__OK; 
};


int anime_tree__push_int16(anime_tree_env_t * this, const int16_t data) { 
  if (this -> memory__array_nb + sizeof(uint16_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  *((uint16_t *) (this -> memory__array + this -> memory__array_nb)) = data; 
  this -> memory__array_nb += sizeof(uint16_t); 
  return ANIME__OK; 
}; 

int anime_tree__push_uint24(anime_tree_env_t * this, const uint24_t data) { 
  if (this -> memory__array_nb + 3*sizeof(uint8_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  uint8_t * p = this -> memory__array + this -> memory__array_nb; 
  *(p + 0) = (data >>  0) & 0xFF; 
  *(p + 1) = (data >>  8) & 0xFF; 
  *(p + 2) = (data >> 16) & 0xFF; 
  this -> memory__array_nb += 3*sizeof(uint8_t); 
  return ANIME__OK; 
}; 

int anime_tree__push_int24(anime_tree_env_t * this, const int24_t data) { 
  if (this -> memory__array_nb + 3*sizeof(int8_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  int8_t * p = this -> memory__array + this -> memory__array_nb; 
  *(p + 0) = (data >>  0) & 0xFF; 
  *(p + 1) = (data >>  8) & 0xFF; 
  *(p + 2) = (data >> 16) & 0xFF; 
  this -> memory__array_nb += 3*sizeof(int8_t); 
  return ANIME__OK; 
}; 

int anime_tree__push_uint32(anime_tree_env_t * this, const uint32_t data) { 
  if (this -> memory__array_nb + sizeof(uint32_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  *((uint32_t *) (this -> memory__array + this -> memory__array_nb)) = data; 
  this -> memory__array_nb += sizeof(uint32_t); 
  return ANIME__OK; 
}; 

int anime_tree__push_int32(anime_tree_env_t * this, const int32_t data) { 
  if (this -> memory__array_nb + sizeof(int32_t) >=  this -> memory__array_size) return ANIME__TREE__NO_SPACE_LEFT; 
  *((int32_t *) (this -> memory__array + this -> memory__array_nb)) = data; 
  this -> memory__array_nb += sizeof(int32_t); 
  return ANIME__OK; 
}; 


// ****************************************************** 
 
int anime_tree__get_filled_status(const anime_tree_env_t * this) { 
  if (NULL == this) { return -2; }; 
  return this -> filled_huh; 
}; 

int anime_tree__get_tree_at(const anime_tree_env_t * this, const int tree_address, uint16_t * tree_size_r, uint8_t * type_r, uint8_t * child_nb_r, uint8_t * shift_to_first_child_r, uint16_t * data_address_r) { 
  *data_address_r = tree_address + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t); 
  if (*data_address_r > this -> memory__array_nb) return ANIME__TREE__WRONG_ADDRESS; 
  const char * p = this -> memory__array + tree_address;  
  *tree_size_r            = *((const uint16_t *) (p)); 
  *type_r                 = *((const uint8_t  *) (p + sizeof(uint16_t))); 
  *child_nb_r             = *((const uint8_t  *) (p + sizeof(uint16_t) + sizeof(uint8_t)));  
  *shift_to_first_child_r = *((const uint8_t  *) (p + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t))); 
  return ANIME__OK; 
}; 




















