#include <stdio.h>
#include <assert.h>

enum bool_t {true = (0 == 0), false = (0 != 0)};
typedef enum bool_t bool_t;
typedef bool_t bool;



#define SPACE_HUH(c) ((' ' == (c)) || ('\t' == (c)))

//#define READ() 

//static inline bool LOOK_FOR




int main(void) {
  int c;
  
  
  // la grande boucle
  for (;;) {
    
    // on skippe les espaces
    do {
      c = getchar();
      if (c == EOF) return 0;
    } while (SPACE_HUH(c));
    
    // si le caractère suivant n'est pas un #, on boucle
    if (c != '#')
      goto skip_until_end_of_line; 

    // on skippe les espaces
    do {
      c = getchar();
      if (c == EOF) return 0;
    } while (SPACE_HUH(c));
    
    // le mot suivant doit être "include"
    if (c != 'i') goto skip_until_end_of_line;
    c = getchar(); if (c != 'n') goto skip_until_end_of_line;
    c = getchar(); if (c != 'c') goto skip_until_end_of_line;
    c = getchar(); if (c != 'l') goto skip_until_end_of_line;
    c = getchar(); if (c != 'u') goto skip_until_end_of_line;
    c = getchar(); if (c != 'd') goto skip_until_end_of_line;
    c = getchar(); if (c != 'e') goto skip_until_end_of_line;
    
    // on skippe les espaces
    do {
      c = getchar();
      if (c == EOF) return -1;
    } while (SPACE_HUH(c));
    
    // le caractère suivant doit être un "
    if (c != '"') goto skip_until_end_of_line;

    // on print tant que pas EOF || '"'
    for (;;) {
      c = getchar();
      if (c == '"') break;
      if (c == EOF) return -1;
      putchar(c);
    }; 
    
    // on put un newline
    putchar('\n');
    
skip_until_end_of_line: 
    while (c != '\n') { 
      c = getchar(); 
      if (c == EOF) return 0; 
    }; 
    continue; 
    
  }; 
  
  
  assert(false);
  return -1;
}; 

