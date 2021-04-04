#ifndef ANIME_TREE_H 
#define ANIME_TREE_H 


// *** TREE_TYPE *** 
 
enum { 
  ANIME__TREE_TYPE__NULL, // invalid 
  ANIME__TREE_TYPE__SECTION, 
  ANIME__TREE_TYPE__PROPERTY, 
  ANIME__TREE_TYPE__PROPERTY_BRACED, 
  ANIME__TREE_TYPE__SUBSECTION, 
  ANIME__TREE_TYPE__EXPR, 
  ANIME__TREE_TYPE__COUNT, 
}; 

static const char * anime_tree_type__cstr[] = {
  "NULL", // invalid 
  "SECTION", 
  "PROPERTY", 
  "PROPERTY_BRACED", 
  "SUBSECTION", 
  "EXPR", 
  NULL 
};


// *** TREE_ENV *** 
 
#ifndef ANIME_TREE_ENV_T 
#define ANIME_TREE_ENV_T 
struct anime_tree_env_t; 
typedef struct anime_tree_env_t anime_tree_env_t; 
#endif 

enum { ANIME_TREE_ENV__ERROR_BUFFER_SIZE = (1 << 11) }; 

enum { anime_tree__memory__array_size__default = (1 << 13) }; 
struct anime_tree_env_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  int8_t  error_id; // 0: none; …<0: error; …>0: warning 
  char    error_str[ANIME_TREE_ENV__ERROR_BUFFER_SIZE]; 
  
  int8_t filled_huh; // 0: not done; -1: currently being filled; 1: yes, filled up 
  
  //char     string_stack[ANIME__STRING_STACK_SIZE]; 
  //uint16_t string_stack_nb; 
  
  
  uint8_t  field_bitsize;      // RL: Bit-wideness of this structure fields: 8 bits, 16 bits, 32 bits, or 64 bits. (Currently, it's statically 16.) 
  uint16_t memory__array_size; // RL: Allocated size of the array. 
  uint16_t memory__array_nb;   // RL: Bottom of the array (but top of the stack). 
  char     memory__array[];    // RL: Top of the array (but bottom of the stack). 
}; 


// RL: For storage, where data should be packed (anywhere else, 'int' is good). It ensures that a tree will fit into a 'int_anime_tree_t'. 
typedef       uint16_t           int_anime_tree_t; 
extern  const int_anime_tree_t   int_anime_tree__max; 

extern        int_anime_tree_t   anime_tree_env__sizeof  (anime_tree_env_t * this); 
extern        int_anime_tree_t   anime_tree_env__sizeof_alloc(const int memory__array_size); 
extern        void               anime_tree_env__bzero   (anime_tree_env_t * this); 
extern        anime_tree_env_t * anime_tree_env__make    (const int data_memory_size, const int stdlog_d); 
extern        anime_tree_env_t * anime_tree_env__make_b  (const int bsize, void * bvalue, int * used_size_ref, const int data_memory_size, const int stdlog_d); 
extern        anime_tree_env_t * anime_tree_env__make_r  (anime_tree_env_t * this, const int data_memory_size, const int stdlog_d); 
extern        void               anime_tree_env__delete  (anime_tree_env_t * this); 
extern        void               anime_tree_env__delete_r(anime_tree_env_t * this); 
//extern  const char             * anime_tree_env__strcopy (anime_tree_env_t * this, const char * cstr); 
extern        void               anime_tree_env__print_f (const anime_tree_env_t * this, FILE * out_stream); 
extern        void               anime_tree_env__print_d (const anime_tree_env_t * this, const int fd); 
extern        void               anime_tree_env__print_d__raw(const anime_tree_env_t * this, const int fd); 
 


// *** TREE_CHUNK *** 
//  - uint16_t: size 
//  - uint8_t : type 
//  - uint8_t : child_nb 
//  - uint8_t : shift_to_first_child 
//  - bytes   : data (not a field per se) 
// 
 
extern int_anime_tree_t anime_tree__open (anime_tree_env_t * this, const uint8_t tree_type); 
extern void             anime_tree__close(anime_tree_env_t * this, const int anime_tree, const int first_child_address); 
extern int_anime_tree_t anime_tree__get_top_address(const anime_tree_env_t * this); 
extern int              anime_tree__push_uint8 (anime_tree_env_t * this, const  uint8_t data); 
extern int              anime_tree__push_int8  (anime_tree_env_t * this, const   int8_t data); 
extern int              anime_tree__push_uint16(anime_tree_env_t * this, const uint16_t data); 
extern int              anime_tree__push_int16 (anime_tree_env_t * this, const  int16_t data); 
extern int              anime_tree__push_uint24(anime_tree_env_t * this, const uint24_t data); 
extern int              anime_tree__push_int24 (anime_tree_env_t * this, const  int24_t data); 
extern int              anime_tree__push_uint32(anime_tree_env_t * this, const uint32_t data); 
extern int              anime_tree__push_int32 (anime_tree_env_t * this, const  int32_t data); 

extern int              anime_tree__write_uint16(      anime_tree_env_t * this, const int address, const uint16_t   data  ); 
extern int              anime_tree__read_uint8  (const anime_tree_env_t * this, const int address,       uint8_t  * data_r); 
extern int              anime_tree__read_uint16 (const anime_tree_env_t * this, const int address,       uint16_t * data_r); 


extern int              anime_tree__get_filled_status(const anime_tree_env_t * this); 
extern int              anime_tree__get_tree_at(const anime_tree_env_t * this, const int tree_address, uint16_t * tree_size_r, uint8_t * type_r, uint8_t * child_nb_r, uint8_t * shift_to_first_child_r, uint16_t * data_address_r); 
 
#endif /* ANIME_TREE_H */

