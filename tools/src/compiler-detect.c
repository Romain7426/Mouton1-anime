#include <unistd.h>

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

#define CHAR_TO_DIGIT(__c__) (						\
			      ((__c__) >= '0' && (__c__) <= '9') ? (__c__) - '0' : \
			      ((__c__) >= 'A' && (__c__) <= 'F') ? (__c__) - 'A' + 10 : \
			      ((__c__) >= 'a' && (__c__) <= 'f') ? (__c__) - 'a' + 10 : \
			      '?')

enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 
 

static int write_long_long_int(long long int n) { 
  char * p; 
  p = buffer + BUF_SIZE; 
  p--; 
  *p = '\0';
  p--; 
  for (;;) { 
    *p = '0' + (n % 10); 
    n = n / 10; 
    if (0 == n) break; 
    if (p == buffer) { return ~0; }; 
    p--; 
  };   
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(STDOUT_FILENO, p, len); 
  return 0; 
}; 

static int write_long_int(int n) { 
  char * p; 
  p = buffer + BUF_SIZE; 
  p--; 
  *p = '\0';
  p--; 
  for (;;) { 
    *p = '0' + (n % 10); 
    n = n / 10; 
    if (0 == n) break; 
    if (p == buffer) { return ~0; }; 
    p--; 
  };   
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(STDOUT_FILENO, p, len); 
  return 0; 
}; 

static int write_string(const char * cstr) { 
  if (NULL == cstr) { 
    static const char s[] = "NULL"; 
    write(STDOUT_FILENO, s, sizeof(s) - 1); 
    return sizeof(s) - 1; 
  }; 
  
  const char * p = cstr; 
  for (;;) { if (*p == '\0') break; p++; }; 
  const int len = p - cstr; 
  write(STDOUT_FILENO, cstr, len); 
  return len; 
}; 

static int write_string_ln(const char * cstr) { 
  if (NULL == cstr) { 
    static const char s[] = "NULL" "\n"; 
    write(STDOUT_FILENO, s, sizeof(s) - 1); 
    return sizeof(s); 
  }; 
  
  const char * p = cstr; 
  for (;;) { if (*p == '\0') break; p++; }; 
  const int len = p - cstr; 
  write(STDOUT_FILENO, cstr, len); 
  write(STDOUT_FILENO, "\n", 1); 
  return len + 1; 
}; 

static int write_eol(void) { 
  write(STDOUT_FILENO, "\n", 1); 
  return 1; 
}; 



#define STRINGIFYX(s) #s
#define STRINGIFY(s) STRINGIFYX(s) 
#define WRITE_MACRO_VALUE_STRING2(__m__) {		\
    static const char s[] = #__m__;			\
    write(STDOUT_FILENO, s, sizeof(s) - 1);		\
    write(STDOUT_FILENO, " = ", 3);			\
    static const char t[] = STRINGIFY(__m__);		\
    write(STDOUT_FILENO, t, sizeof(t) - 1);		\
    write(STDOUT_FILENO, "\n", 1);			\
  }; 


#define WRITE_MACRO_VALUE         WRITE_MACRO_VALUE_STRING2 
#define WRITE_MACRO_VALUE_STRING  WRITE_MACRO_VALUE_STRING2
#define WRITE_MACRO_VALUE_DOUBLE  WRITE_MACRO_VALUE_STRING2




static void print_compiler(void); 




int main(const int argc, const char * argv[]) { 
  // echo "" | gcc -E -dM - 

#if defined(__PCC__) 
  write_string_ln("pcc"); 
  return 0; 
#endif 

#ifdef __clang__ 
  write_string_ln("clang"); 
  return 0; 
#endif

#ifdef __TINYC__ 
  write_string_ln("tcc"); 
  return 0; 
#endif

#if defined(__BORLANDC__)
  write_string_ln("borlandc"); 
  return 0; 
#endif


#if defined(__COMO__)
  write_string_ln("como"); 
  return 0; 
#endif

#if defined(_CRAYC)
  write_string_ln(""); 
  return 0; 
#endif

#if defined(__MINGW32__)
  write_string_ln(""); 
  return 0; 
#endif

#if defined(__CYGWIN__)
  write_string_ln(""); 
  return 0; 
#endif

#if defined(__DECC) 
  write_string_ln(""); 
  return 0; 
#endif
#if defined(__DECCXX)
  write_string_ln(""); 
  return 0; 
#endif
#if defined(__DECC_VER)
  write_string_ln(""); 
  return 0; 
#endif

#if defined(VAXC)
  write_string_ln("vaxc"); 
  return 0; 
#endif
#if defined(__VAXC)
  write_string_ln("vaxc"); 
  return 0; 
#endif

#if defined(__DCC__) 
  write_string_ln("dcc"); 
  return 0; 
#endif

#if defined(__DMC__)
  write_string_ln("dmc"); 
  return 0; 
#endif

#if defined(__SC__) 
  write_string_ln("sc"); 
  return 0; 
#endif

#if defined(__ZTC__)
  write_string_ln("ztc"); 
  return 0; 
#endif

#if defined(__HP_aCC)
  write_string_ln("hp_acc"); 
  return 0; 
#endif
#if defined(__HP_cc)
  write_string_ln("hp_cc"); 
  return 0; 
#endif
#if defined(__hpux)
  write_string_ln("hpux"); 
  return 0; 
#endif

#if defined(__INTEL_COMPILER)
  write_string_ln("icc"); 
  return 0; 
#endif
#if defined(__ICC)
  write_string_ln("icc"); 
  return 0; 
#endif

#if defined(__KCC)
  write_string_ln("kcc"); 
  return 0; 
#endif
#if defined(__KCC_VERSION)
  write_string_ln("kcc"); 
  return 0; 
#endif

#if defined(sgi) 
  write_string_ln("sgi"); 
  return 0; 
#endif
#if defined(__sgi) 
  write_string_ln("sgi"); 
  return 0; 
#endif

#if defined(__MRC__)
  write_string_ln("mrc"); 
  return 0; 
#endif

#if defined(MPW_C) 
  write_string_ln("mpw_c"); 
  return 0; 
#endif
#if defined(MPW_CPLUS)
  write_string_ln("mpw_cplus"); 
  return 0; 
#endif

#if defined(__MWERKS__)
  write_string_ln("mwerks"); 
  return 0; 
#endif

#if defined(__CC_NORCROFT)
  write_string_ln("norcroft"); 
  return 0; 
#endif

#if defined(_SCO_DS)
  write_string_ln("sco"); 
  return 0; 
#endif
#if defined(__SCO_VERSION__)
  write_string_ln("sco"); 
  return 0; 
#endif

#if defined(__SUNPRO_C)
  write_string_ln("sunpro_c"); 
  return 0; 
#endif
#if defined(__SUNPRO_CC)
  write_string_ln("sunpro_cc"); 
  return 0; 
#endif

#if defined(__TenDRA__)
  write_string_ln("tendra"); 
  return 0; 
#endif

#if defined(__USLC__)
  write_string_ln("uslc"); 
  return 0; 
#endif

#if defined(_MSC_VER)
  write_string_ln("msc"); 
  return 0; 
#endif

#if defined(__WATCOMC__)
  write_string_ln("watcomc"); 
  return 0; 
#endif

#if defined(__xlC__)
  write_string_ln("xlc"); 
  return 0; 
#endif

#if defined(__IBMC__) 
  write_string_ln("ibmc"); 
  return 0; 
#endif
#if defined(__IBMCPP__)
  write_string_ln("ibmcpp"); 
  return 0; 
#endif

#if defined(_AIX) 
  write_string_ln("aix"); 
  return 0; 
#endif
  
#if defined(__GNUC__)
  write_string_ln("gcc"); 
  return 0; 
#endif
  
  write_string_ln("unknown"); 
  return 0; 
}; 


