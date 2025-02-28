#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "lib.ci"

//sc_pagesize
//SIGSEGV

// Voir aussi getrlimit_stack_soft 
// et getrlimit_stack_hard

char * top_of_stack_ptr; 
char * * bottom_of_stack_ptr_ptr; 

char sigv_huh = 0; 

sigjmp_buf longjmp_buff; 

static void handler(int sig) {
  if (SIGSEGV != sig) return; 
  //_exit(3); 
  sigv_huh = 1;
  siglongjmp(longjmp_buff, /*val*/1);
};




static int main_aux(void) { 
  char top_of_stack_aux;
  const long sc_pagesize = sysconf(_SC_PAGESIZE);
  goto label__body; 
  
  label__body: {
    signal(SIGSEGV, handler); 
    
    // Lors de la définition, cette fonction retourne toujours zéro. 
    // Lors du retour, elle renvoie la valeur prescrite par longjmp. 
    const volatile int longjmp_val = sigsetjmp(longjmp_buff, /*savemask*/0);
    
    if (0 == longjmp_val) goto label__checking_size; 
    
    goto label__print_size; 
  };
  
  label__checking_size: {
    if (((void *)top_of_stack_ptr) < ((void *)&top_of_stack_aux)) {
      // Stack grows up
      return 1;
    }
    else {
      // Stack grows down
      char * p = &top_of_stack_aux; 
      bottom_of_stack_ptr_ptr = &p; 
      for (;;) {
	*p = 1;
	p -= sc_pagesize;
	//p -= 10; 
      };
      return 2;
    };
  };
  
  label__print_size: { 
    //char * top_of_stack_ptr; 
    char * bottom_of_stack_ptr = *bottom_of_stack_ptr_ptr; 

    if (((void *)top_of_stack_ptr) < ((void *)bottom_of_stack_ptr)) {
      // Stack grows up
      write_lluint_ln(STDOUT_FILENO, bottom_of_stack_ptr - top_of_stack_ptr);
    }
    else { 
      // Stack grows down
      write_lluint_ln(STDOUT_FILENO, top_of_stack_ptr - bottom_of_stack_ptr);
    };
    return 0; 
  };

  return -1; 
};



int main(void) { 
  char top_of_stack;
  top_of_stack_ptr = &top_of_stack; 
  return main_aux(); 
};
