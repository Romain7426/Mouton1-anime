#include "lib.ci"

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
  write_string_ln(STDOUT_FILENO, "pcc"); 
  return 0; 
#endif 

#ifdef __clang__ 
  write_string_ln(STDOUT_FILENO, "clang"); 
  return 0; 
#endif

#ifdef __TINYC__ 
  write_string_ln(STDOUT_FILENO, "tcc"); 
  return 0; 
#endif

#if defined(__BORLANDC__)
  write_string_ln(STDOUT_FILENO, "borlandc"); 
  return 0; 
#endif


#if defined(__COMO__)
  write_string_ln(STDOUT_FILENO, "como"); 
  return 0; 
#endif

#if defined(_CRAYC)
  write_string_ln(STDOUT_FILENO, ""); 
  return 0; 
#endif

#if defined(__MINGW32__)
  write_string_ln(STDOUT_FILENO, ""); 
  return 0; 
#endif

#if defined(__CYGWIN__)
  write_string_ln(STDOUT_FILENO, ""); 
  return 0; 
#endif

#if defined(__DECC) 
  write_string_ln(STDOUT_FILENO, ""); 
  return 0; 
#endif
#if defined(__DECCXX)
  write_string_ln(STDOUT_FILENO, ""); 
  return 0; 
#endif
#if defined(__DECC_VER)
  write_string_ln(STDOUT_FILENO, ""); 
  return 0; 
#endif

#if defined(VAXC)
  write_string_ln(STDOUT_FILENO, "vaxc"); 
  return 0; 
#endif
#if defined(__VAXC)
  write_string_ln(STDOUT_FILENO, "vaxc"); 
  return 0; 
#endif

#if defined(__DCC__) 
  write_string_ln(STDOUT_FILENO, "dcc"); 
  return 0; 
#endif

#if defined(__DMC__)
  write_string_ln(STDOUT_FILENO, "dmc"); 
  return 0; 
#endif

#if defined(__SC__) 
  write_string_ln(STDOUT_FILENO, "sc"); 
  return 0; 
#endif

#if defined(__ZTC__)
  write_string_ln(STDOUT_FILENO, "ztc"); 
  return 0; 
#endif

#if defined(__HP_aCC)
  write_string_ln(STDOUT_FILENO, "hp_acc"); 
  return 0; 
#endif
#if defined(__HP_cc)
  write_string_ln(STDOUT_FILENO, "hp_cc"); 
  return 0; 
#endif
#if defined(__hpux)
  write_string_ln(STDOUT_FILENO, "hpux"); 
  return 0; 
#endif

#if defined(__INTEL_COMPILER)
  write_string_ln(STDOUT_FILENO, "icc"); 
  return 0; 
#endif
#if defined(__ICC)
  write_string_ln(STDOUT_FILENO, "icc"); 
  return 0; 
#endif

#if defined(__KCC)
  write_string_ln(STDOUT_FILENO, "kcc"); 
  return 0; 
#endif
#if defined(__KCC_VERSION)
  write_string_ln(STDOUT_FILENO, "kcc"); 
  return 0; 
#endif

#if defined(sgi) 
  write_string_ln(STDOUT_FILENO, "sgi"); 
  return 0; 
#endif
#if defined(__sgi) 
  write_string_ln(STDOUT_FILENO, "sgi"); 
  return 0; 
#endif

#if defined(__MRC__)
  write_string_ln(STDOUT_FILENO, "mrc"); 
  return 0; 
#endif

#if defined(MPW_C) 
  write_string_ln(STDOUT_FILENO, "mpw_c"); 
  return 0; 
#endif
#if defined(MPW_CPLUS)
  write_string_ln(STDOUT_FILENO, "mpw_cplus"); 
  return 0; 
#endif

#if defined(__MWERKS__)
  write_string_ln(STDOUT_FILENO, "mwerks"); 
  return 0; 
#endif

#if defined(__CC_NORCROFT)
  write_string_ln(STDOUT_FILENO, "norcroft"); 
  return 0; 
#endif

#if defined(_SCO_DS)
  write_string_ln(STDOUT_FILENO, "sco"); 
  return 0; 
#endif
#if defined(__SCO_VERSION__)
  write_string_ln(STDOUT_FILENO, "sco"); 
  return 0; 
#endif

#if defined(__SUNPRO_C)
  write_string_ln(STDOUT_FILENO, "sunpro_c"); 
  return 0; 
#endif
#if defined(__SUNPRO_CC)
  write_string_ln(STDOUT_FILENO, "sunpro_cc"); 
  return 0; 
#endif

#if defined(__TenDRA__)
  write_string_ln(STDOUT_FILENO, "tendra"); 
  return 0; 
#endif

#if defined(__USLC__)
  write_string_ln(STDOUT_FILENO, "uslc"); 
  return 0; 
#endif

#if defined(_MSC_VER)
  write_string_ln(STDOUT_FILENO, "msc"); 
  return 0; 
#endif

#if defined(__WATCOMC__)
  write_string_ln(STDOUT_FILENO, "watcomc"); 
  return 0; 
#endif

#if defined(__xlC__)
  write_string_ln(STDOUT_FILENO, "xlc"); 
  return 0; 
#endif

#if defined(__IBMC__) 
  write_string_ln(STDOUT_FILENO, "ibmc"); 
  return 0; 
#endif
#if defined(__IBMCPP__)
  write_string_ln(STDOUT_FILENO, "ibmcpp"); 
  return 0; 
#endif

#if defined(_AIX) 
  write_string_ln(STDOUT_FILENO, "aix"); 
  return 0; 
#endif
  
#if defined(__GNUC__)
  write_string_ln(STDOUT_FILENO, "gcc"); 
  return 0; 
#endif
  
  write_string_ln(STDOUT_FILENO, "unknown"); 
  return 0; 
}; 


