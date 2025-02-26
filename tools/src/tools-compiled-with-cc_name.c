#include "lib.ci"



#define WRITE_MACRO_VALUE_STRING2(__m__) {		\
    static const char s[] = #__m__;			\
    write(STDOUT_FILENO, s, sizeof(s) - 1);		\
    write(STDOUT_FILENO, " = ", 3);			\
    static const char t[] = STRINGIFY(__m__);		\
    write(STDOUT_FILENO, t, sizeof(t) - 1);		\
    write(STDOUT_FILENO, "\n", 1);			\
  }; 
 
#define WRITE_MACRO_VALUE_STRING3(__m__) {		\
    static const char t[] = STRINGIFY(__m__);		\
    write(STDOUT_FILENO, t, sizeof(t) - 1);		\
    write(STDOUT_FILENO, "\n", 1);			\
  }; 
 
// man 2 getrlimit 
// int getrlimit(int resource, struct rlimit *rlp); 
// 
//           struct rlimit {
//                   rlim_t  rlim_cur;       /* current (soft) limit */
//                   rlim_t  rlim_max;       /* hard limit */
//           };
// 
// «hard limit» -> defined by root — cannot be changed by user. 
// «soft limit» -> value used by softwares — default value defined by root, can be changed by user (always lower than «hard limit») 
// 
// => These information are per process. 

extern char **environ;

int main(const int argc, const char * argv[]) { 
#ifdef CC
  WRITE_MACRO_VALUE_STRING3(CC); 
  return 0; 
#else
  { 
    int i = -1; 
    char * env_i = NULL;
    int found_huh = false; 
    for (;;) { 
      i++; 
      env_i = environ[i]; 
      if (NULL == env_i) break; 
      found_huh = bytecompare_prefix("CC=", 3, env_i, cstrlen(env_i), 3); 
      if (!found_huh) continue; 
      write_string(STDOUT_FILENO, env_i+3); 
      return 0; 
    }; 
    return -1; 
  }; 
#endif 
}; 


