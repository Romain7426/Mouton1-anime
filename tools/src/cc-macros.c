#include <unistd.h>

// $ echo "" | cpp -dM 
// https://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros

#ifndef INT16_MAX
enum { INT16_MAX = (1   <<  0) + (1   <<  1) + (1   <<  2) + (1   <<  3) + (1   <<  4) + (1   <<  5) + (1   <<  6) + (1   <<  7) + 
                   (1   <<  8) + (1   <<  9) + (1   << 10) + (1   << 11) + (1   << 12) + (1   << 13) + (1   << 14) }; 
#endif

enum { BUF_SIZE = INT16_MAX }; 
static char buffer[BUF_SIZE] = {}; 
 

static int write_int(long long int n) { 
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

static int write_long_double(long double n) { 
  char * p; 
  p = buffer + BUF_SIZE; 
  p--; 
  *p = '\0';
  p--; 
  *p = '0';
  const int len = BUF_SIZE - (p - buffer) - 1; 
  write(STDOUT_FILENO, p, len); 
  return 0; 
}; 


#if 0 

#define WRITE_MACRO_VALUE(__m__) {		\
    static const char s[] = #__m__;		\
    write(STDOUT_FILENO, s, sizeof(s) - 1);	\
    write(STDOUT_FILENO, " = ", 3);		\
    write_int((__m__));				\
    write(STDOUT_FILENO, "\n", 1);		\
  }; 

#define WRITE_MACRO_VALUE_DOUBLE(__m__) {		\
    static const char s[] = #__m__;			\
    write(STDOUT_FILENO, s, sizeof(s) - 1);		\
    write(STDOUT_FILENO, " = ", 3);			\
    write_long_double((__m__));				\
    write(STDOUT_FILENO, "\n", 1);			\
  }; 

#define WRITE_MACRO_VALUE_STRING(__m__) {		\
    static const char s[] = #__m__;			\
    write(STDOUT_FILENO, s, sizeof(s) - 1);		\
    write(STDOUT_FILENO, " = ", 3);			\
    static const char t[] = __m__;			\
    write(STDOUT_FILENO, t, sizeof(t) - 1);		\
    write(STDOUT_FILENO, "\n", 1);			\
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

#else 

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

#endif 




static void print_compiler(void); 
static void print_os(void); 
static void print_platform(void); 
static void print_arch(void); 
static void print_c_standards(void); 
static void print_cpp_standards(void); 
static void print_unix_standards(void); 
static void print_c_libs(void); 
static void print_cpp_libs(void); 
static void print_misc(void); 
static void print_misc2(void); 
static void print_misc3(void); 




int main(const int argc, const char * argv[]) { 
// echo "" | gcc -E -dM - 


 print_compiler(); 
 print_os(); 
 print_platform(); 
 print_arch(); 
 print_c_standards(); 
 print_cpp_standards(); 
 print_unix_standards(); 
 print_c_libs(); 
 print_cpp_libs(); 
 print_misc(); 
 print_misc2(); 
 print_misc3(); 
 
 return 0; 
}; 



void print_compiler(void) { 
#if defined(__PCC__)
 WRITE_MACRO_VALUE(__PCC__); 
#endif

#if defined(__PCC_MINOR__)
 WRITE_MACRO_VALUE(__PCC_MINOR__); 
#endif

#if defined(__PCC_MINORMINOR__)
 WRITE_MACRO_VALUE(__PCC_MINORMINOR__); 
#endif

#if defined(__TINYC__)
 WRITE_MACRO_VALUE(__TINYC__); 
#endif




#if defined(__BORLANDC__)
 WRITE_MACRO_VALUE(__BORLANDC__); 
#endif

#if defined(__COMO__)
 WRITE_MACRO_VALUE(__COMO__); 
# endif
#if defined(__COMO_VERSION__)
 WRITE_MACRO_VALUE(__COMO_VERSION__); 
#endif

#if defined(_CRAYC)
 WRITE_MACRO_VALUE(__CRAYC__); 
#endif
#if defined(_REVISION)
 WRITE_MACRO_VALUE(_REVISION); 
#endif

#if defined(__CYGWIN__)
 WRITE_MACRO_VALUE(__CYGWIN); 
#endif

#if defined(__DECC) 
 WRITE_MACRO_VALUE(__DECC); 
#endif
#if defined(__DECCXX)
 WRITE_MACRO_VALUE(__DECCXX); 
#endif
#if defined(__DECC_VER)
 WRITE_MACRO_VALUE(__DECC_VER); 
#endif
#if defined(VAXC)
 WRITE_MACRO_VALUE(__DECC_VER); 
#endif
#if defined(__VAXC)
 WRITE_MACRO_VALUE(__VAXC); 
#endif
#if defined(__osf__) 
 WRITE_MACRO_VALUE(__osf__); 
#endif
#if defined(__LANGUAGE_C__) 
 WRITE_MACRO_VALUE(__LANGUAGE_C__); 
#endif

#if defined(__DCC__) 
 WRITE_MACRO_VALUE(__LANGUAGE_C__); 
#endif
#if defined(__VERSION_NUMBER__)
 WRITE_MACRO_VALUE(__LANGUAGE_C__); 
#endif

#if defined(__DMC__)
 WRITE_MACRO_VALUE(__DMC__); 
#endif
#if defined(__SC__) 
 WRITE_MACRO_VALUE(__SC__); 
#endif
#if defined(__ZTC__)
 WRITE_MACRO_VALUE(__ZTC__); 
#endif

#if defined(__GNUC__)
  WRITE_MACRO_VALUE(__GNUC__); 
#endif
#if defined(__GNUC_MINOR__)
  WRITE_MACRO_VALUE(__GNUC_MINOR__); 
#endif
#if defined(__GNUC_PATCHLEVEL__)
  WRITE_MACRO_VALUE(__GNUC_PATCHLEVEL__); 
#endif

#if defined(__HP_aCC)
  WRITE_MACRO_VALUE(__HP_aCC); 
#endif
#if defined(__HP_cc)
  WRITE_MACRO_VALUE(__HP_cc); 
#endif
#if defined(__hpux)
  WRITE_MACRO_VALUE(__hpux); 
#endif

#if defined(__INTEL_COMPILER)
  WRITE_MACRO_VALUE(__INTEL_COMPILER); 
#endif
#if defined(__ICC)
  WRITE_MACRO_VALUE(__ICC); 
#endif

#if defined(__KCC)
  WRITE_MACRO_VALUE(__KCC); 
#endif
#if defined(__KCC_VERSION)
  WRITE_MACRO_VALUE(__KCC_VERSION); 
#endif

#if defined(__MINGW32__)
  WRITE_MACRO_VALUE(__MINGW32__); 
#endif

#if defined(sgi) 
  WRITE_MACRO_VALUE(sgi); 
#endif
#if defined(__sgi) 
  WRITE_MACRO_VALUE(__sgi); 
#endif
#if defined(_COMPILER_VERSION)
  WRITE_MACRO_VALUE(_COMPILER_VERSION); 
#endif

#if defined(__MRC__)
  WRITE_MACRO_VALUE(__MRC__); 
#endif
#if defined(MPW_C) 
  WRITE_MACRO_VALUE(MPW_C); 
#endif
#if defined(MPW_CPLUS)
  WRITE_MACRO_VALUE(MPW_CPLUS); 
#endif

#if defined(__MWERKS__)
  WRITE_MACRO_VALUE(__MWERKS__); 
#endif

#if defined(__CC_NORCROFT)
  WRITE_MACRO_VALUE(__CC_NORCROFT); 
#endif

#if defined(_SCO_DS)
  WRITE_MACRO_VALUE(_SCO_DS); 
#endif

#if defined(__SUNPRO_C)
  WRITE_MACRO_VALUE(__SUNPRO_C); 
#endif
#if defined(__SUNPRO_CC)
  WRITE_MACRO_VALUE(__SUNPRO_CC); 
#endif

#if defined(__TenDRA__)
  WRITE_MACRO_VALUE(__TenDRA__); 
#endif

#if defined(__USLC__)
  WRITE_MACRO_VALUE(__USLC__); 
#endif
#if defined(__SCO_VERSION__)
  WRITE_MACRO_VALUE(__SCO_VERSION__); 
#endif

#if defined(_MSC_VER)
  WRITE_MACRO_VALUE(_MSC_VER); 
#endif

#if defined(__WATCOMC__)
  WRITE_MACRO_VALUE(__WATCOMC__); 
#endif

#if defined(__xlC__)
  WRITE_MACRO_VALUE(__xlC__); 
#endif
#if defined(__IBMC__) 
  WRITE_MACRO_VALUE(__IBMC__); 
#endif
#if defined(__IBMCPP__)
  WRITE_MACRO_VALUE(__IBMCPP__); 
#endif
#if defined(_AIX) 
  WRITE_MACRO_VALUE(_AIX); 
#endif
}; 



void print_os(void) { 
/*************************************************************************
 * Operating Systems
 */

#if defined(__amigaos__) 
  WRITE_MACRO_VALUE(__amigaos__); 
#endif
#if defined(AMIGA)
  WRITE_MACRO_VALUE(AMIGA); 
#endif

#if defined(_AIX) 
  WRITE_MACRO_VALUE(_AIX); 
#endif
#if defined(__TOS_AIX__) 
  WRITE_MACRO_VALUE(__TOS_AIX__); 
#endif

#if defined(__BEOS__)
  WRITE_MACRO_VALUE(__BEOS__); 
#endif

#if defined(bsdi) 
  WRITE_MACRO_VALUE(bsdi); 
#endif
#if defined(__bsdi__)
  WRITE_MACRO_VALUE(__bsdi__); 
#endif

#if defined(_UNICOS) 
  WRITE_MACRO_VALUE(_UNICOS); 
#endif
#if defined(_CRAY)
  WRITE_MACRO_VALUE(_CRAY); 
#endif

#if defined(DGUX) 
  WRITE_MACRO_VALUE(DGUX); 
#endif
#if defined(__DGUX__) 
  WRITE_MACRO_VALUE(__DGUX__); 
#endif
#if defined(__dgux__)
  WRITE_MACRO_VALUE(__dgux__); 
#endif

#if defined(__DragonFly__)
  WRITE_MACRO_VALUE(__DragonFly__); 
#endif

#if defined(__FreeBSD__)
  WRITE_MACRO_VALUE(__FreeBSD__); 
#endif

#if defined(hpux) 
  WRITE_MACRO_VALUE(hpux); 
#endif
#if defined(__hpux) 
  WRITE_MACRO_VALUE(__hpux); 
#endif
#if defined(_HPUX_SOURCE)
  WRITE_MACRO_VALUE(_HPUX_SOURCE); 
#endif

#if defined(__GNU__)
  WRITE_MACRO_VALUE(__GNU__); 
#endif

#if defined(sgi) 
  WRITE_MACRO_VALUE(sgi); 
#endif
#if defined(__sgi) 
  WRITE_MACRO_VALUE(__sgi); 
#endif
#if defined(mips) 
  WRITE_MACRO_VALUE(mips); 
#endif
#if defined(_SGI_SOURCE)
  WRITE_MACRO_VALUE(_SGI_SOURCE); 
#endif

#if defined(linux) 
  WRITE_MACRO_VALUE(linux); 
#endif
#if defined(__linux) 
  WRITE_MACRO_VALUE(__linux); 
#endif
#if defined(__linux__)
  WRITE_MACRO_VALUE(__linux__); 
#endif

#if defined(macintosh) 
  WRITE_MACRO_VALUE(macintosh); 
#endif
#if defined(Macintosh) 
  WRITE_MACRO_VALUE(Macintosh); 
#endif
#if defined(__MACOS__)
  WRITE_MACRO_VALUE(__MACOS__); 
#endif

#if defined(__MACOSX__) 
  WRITE_MACRO_VALUE(__MACOSX__); 
#endif
#if defined(__APPLE__) 
  WRITE_MACRO_VALUE(__APPLE__); 
#endif
#if defined(__MACH__)
  WRITE_MACRO_VALUE(__MACH__); 
#endif

#if defined(mpeix) 
  WRITE_MACRO_VALUE(mpeix); 
#endif
#if defined(__mpexl)
  WRITE_MACRO_VALUE(__mpexl); 
#endif

#if defined(MSDOS) 
  WRITE_MACRO_VALUE(MSDOS); 
#endif
#if defined(__MSDOS__) 
  WRITE_MACRO_VALUE(__MSDOS__); 
#endif
#if defined(_MSDOS) 
  WRITE_MACRO_VALUE(_MSDOS); 
#endif
#if defined(__DOS__)
  WRITE_MACRO_VALUE(__DOS__); 
#endif

#if defined(__NetBSD__)
  WRITE_MACRO_VALUE(__NetBSD__); 
#endif

#if defined(__OpenBSD__)
  WRITE_MACRO_VALUE(__OpenBSD__); 
#endif

#if defined(OS2) 
  WRITE_MACRO_VALUE(OS2); 
#endif
#if defined(_OS2) 
  WRITE_MACRO_VALUE(_OS2); 
#endif
#if defined(__OS2__) 
  WRITE_MACRO_VALUE(__OS2__); 
#endif
#if defined(__TOS_OS2__)
  WRITE_MACRO_VALUE(__TOS_OS2__); 
#endif

#if defined(__osf__) 
  WRITE_MACRO_VALUE(__osf__); 
#endif
#if defined(__osf) 
  WRITE_MACRO_VALUE(__osf); 
#endif

#if defined(pyr)
  WRITE_MACRO_VALUE(pyr); 
#endif

#if defined(__QNX__) 
  WRITE_MACRO_VALUE(__QNX__); 
#endif
#if defined(__QNXNTO__)
  WRITE_MACRO_VALUE(__QNXNTO__); 
#endif

#if defined(M_I386) 
  WRITE_MACRO_VALUE(M_I386); 
#endif
#if defined(M_XENIX) 
  WRITE_MACRO_VALUE(M_XENIX); 
#endif
#if defined(_SCO_C_DIALECT) 
  WRITE_MACRO_VALUE(_SCO_C_DIALECT); 
#endif

#if defined(_SEQUENT_) 
  WRITE_MACRO_VALUE(_SEQUENT_); 
#endif
#if defined(sequent)
  WRITE_MACRO_VALUE(sequent); 
#endif

#if defined(sinix)
  WRITE_MACRO_VALUE(sinix); 
#endif

#if defined(sun) 
  WRITE_MACRO_VALUE(sun); 
#endif
#if defined(__sun__) 
  WRITE_MACRO_VALUE(__sun__); 
#endif
#if defined(__SVR4) 
  WRITE_MACRO_VALUE(__SVR4); 
#endif
#if defined(__svr4__)
  WRITE_MACRO_VALUE(__svr4__); 
#endif

#if defined(ultrix) 
  WRITE_MACRO_VALUE(ultrix); 
#endif
#if defined(__ultrix) 
  WRITE_MACRO_VALUE(__ultrix); 
#endif
#if defined(__ultrix__)
  WRITE_MACRO_VALUE(__ultrix__); 
#endif

}; 



void print_platform(void) { 
/*************************************************************************
 * Platforms
 */

#if defined(VMS) 
 WRITE_MACRO_VALUE(VMS); 
#endif
#if defined(__VMS)
 WRITE_MACRO_VALUE(__VMS); 
#endif
#if defined(__VMS_VER)
 WRITE_MACRO_VALUE(__VMS_VER); 
#endif

#if defined(unix) 
 WRITE_MACRO_VALUE(unix); 
#endif
#if defined(__unix) 
 WRITE_MACRO_VALUE(__unix); 
#endif
#if defined(__unix__)
 WRITE_MACRO_VALUE(__unix__); 
#endif

#if defined(AMIGA) 
 WRITE_MACRO_VALUE(AMIGA); 
#endif

#if defined(WIN32) 
 WRITE_MACRO_VALUE(WIN32); 
#endif
#if defined(_WIN32) 
 WRITE_MACRO_VALUE(_WIN32); 
#endif
#if defined(__TOS_WIN__) 
 WRITE_MACRO_VALUE(__TOS_WIN__); 
#endif

#if defined(_BSD_SOURCE) 
 WRITE_MACRO_VALUE(_BSD_SOURCE); 
#endif
#if defined(_SYSTYPE_BSD)
 WRITE_MACRO_VALUE(_SYSTYPE_BSD); 
#endif

#if defined(__sysv__) 
 WRITE_MACRO_VALUE(__sysv__); 
#endif
#if defined(__SVR4) 
 WRITE_MACRO_VALUE(__SVR4); 
#endif
#if defined(__svr4__) 
 WRITE_MACRO_VALUE(__svr4__); 
#endif
#if defined(_SVR4_SOURCE) 
 WRITE_MACRO_VALUE(_SVR4_SOURCE); 
#endif
#if defined(_SYSTYPE_SVR4)
 WRITE_MACRO_VALUE(_SYSTYPE_SVR4); 
#endif

#if defined(UWIN)
 WRITE_MACRO_VALUE(UWIN); 
#endif

#if defined(_WINDU_SOURCE)
 WRITE_MACRO_VALUE(_WINDU_SOURCE); 
#endif

}; 

void print_arch(void) { 
#if defined(M_I386) 
  WRITE_MACRO_VALUE(M_I386); 
#endif
#ifdef __x86_64 
 WRITE_MACRO_VALUE(__x86_64); 
#endif
#ifdef __x86_64__ 
 WRITE_MACRO_VALUE(__x86_64__); 
#endif
#ifdef __amd64 
 WRITE_MACRO_VALUE(__amd64); 
#endif
#ifdef __amd64__ 
 WRITE_MACRO_VALUE(__amd64__); 
#endif

}; 


void print_c_standards(void) { 
/*************************************************************************
 * C Standards
 */
#if defined(__STDC_VERSION__)
 WRITE_MACRO_VALUE(__STDC_VERSION__); 
#endif
#if defined(__STDC__) 
 WRITE_MACRO_VALUE(__STDC__); 
#endif
#if defined(_MSC_EXTENSIONS) 
 WRITE_MACRO_VALUE(_MSC_EXTENSIONS); 
#endif
}; 

void print_cpp_standards(void) { 
/*************************************************************************
 * C++ Standards
 */
#if defined(__cplusplus)
 WRITE_MACRO_VALUE(__cplusplus); 
#endif
}; 



void print_unix_standards(void) { 
/*************************************************************************
 * Unix Standards
 */

#if defined(_POSIX_VERSION)
 WRITE_MACRO_VALUE(_POSIX_VERSION); 
#endif

#if defined(_POSIX2_C_VERSION) 
 WRITE_MACRO_VALUE(_POSIX2_C_VERSION); 
#endif

#if defined(_XOPEN_VERSION) 
 WRITE_MACRO_VALUE(_XOPEN_VERSION); 
#endif
#if defined(_XOPEN_XPG3)
 WRITE_MACRO_VALUE(_XOPEN_XPG3); 
#endif
#if defined(_XOPEN_XPG4)
 WRITE_MACRO_VALUE(_XOPEN_XPG4); 
#endif
#if defined(_XOPEN_UNIX) 
 WRITE_MACRO_VALUE(_XOPEN_UNIX); 
#endif

}; 


void print_c_libs(void) { 
/*************************************************************************
 * C Libraries
 */

#if defined(TARGET_API_MAC_CARBON)
 WRITE_MACRO_VALUE(TARGET_API_MAC_CARBON); 
#endif

#if defined(__GLIBC__)
 WRITE_MACRO_VALUE(__GLIBC__); 
#endif
#if defined(__GLIBC_MINOR__)
 WRITE_MACRO_VALUE(__GLIBC_MINOR__); 
#endif

#if defined(__GNU_LIBRARY__)
 WRITE_MACRO_VALUE(__GNU_LIBRARY__); 
#endif
#if defined(__GNU_LIBRARY_MINOR__)
 WRITE_MACRO_VALUE(__GNU_LIBRARY_MINOR__); 
#endif

#if defined(__CRTL_VER)
 WRITE_MACRO_VALUE(__CRTL_VER); 
#endif

}; 



static void print_cpp_libs(void) { 
/*************************************************************************
 * C++ Libraries
 */

#if defined(__CPPLIB_VER)
 WRITE_MACRO_VALUE(__CPPLIB_VER); 
#endif

#if defined(__GLIBCXX__)
 WRITE_MACRO_VALUE(__GLIBCXX__); 
#endif
#if defined(__GLIBCPP__)
 WRITE_MACRO_VALUE(__GLIBCPP__); 
#endif

}; 


static void print_misc(void) { 
#ifdef __SSP_STRONG__ 
 WRITE_MACRO_VALUE(__SSP_STRONG__); 
#endif
#ifdef __DBL_MIN_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MIN_EXP__); 
#endif
#ifdef __FLT_MIN__ //1.17549435e-38F
 WRITE_MACRO_VALUE(__FLT_MIN__); 
#endif
#ifdef __DEC64_DEN__ //0.000000000000001E-383DD
 WRITE_MACRO_VALUE(__DEC64_DEN__); 
#endif
#ifdef __CHAR_BIT__ 
 WRITE_MACRO_VALUE(__CHAR_BIT__); 
#endif
#ifdef __WCHAR_MAX__ 
 WRITE_MACRO_VALUE(__WCHAR_MAX__); 
#endif
#ifdef __DBL_DENORM_MIN__ //4.9406564584124654e-324
 WRITE_MACRO_VALUE(__DBL_DENORM_MIN__); 
#endif
#ifdef __FLT_EVAL_METHOD__ 
 WRITE_MACRO_VALUE(__FLT_EVAL_METHOD__); 
#endif
#ifdef __DBL_MIN_10_EXP__ //(-307)
 WRITE_MACRO_VALUE(__DBL_MIN_10_EXP__); 
#endif
#ifdef __FINITE_MATH_ONLY__ 
 WRITE_MACRO_VALUE(__FINITE_MATH_ONLY__); 
#endif
#ifdef __DEC64_MAX_EXP__ 
 WRITE_MACRO_VALUE(__DEC64_MAX_EXP__); 
#endif
#ifdef __SHRT_MAX__ 
 WRITE_MACRO_VALUE(__SHRT_MAX__); 
#endif
#ifdef __LDBL_MAX__ //1.18973149535723176502e+4932L
 WRITE_MACRO_VALUE_DOUBLE(__LDBL_MAX__); 
#endif
#ifdef __UINTMAX_TYPE__ //long long unsigned int
 WRITE_MACRO_VALUE_STRING2(__UINTMAX_TYPE__); 
#endif
#ifdef __DEC32_EPSILON__ //1E-6DF
 WRITE_MACRO_VALUE(__DEC32_EPSILON__); 
#endif
#ifdef __SCHAR_MAX__ 
 WRITE_MACRO_VALUE(__SCHAR_MAX__); 
#endif
#ifdef __USER_LABEL_PREFIX__ 
 WRITE_MACRO_VALUE_STRING2(__USER_LABEL_PREFIX__); 
#endif
#ifdef __STDC_HOSTED__ 
 WRITE_MACRO_VALUE(__STDC_HOSTED__); 
#endif
#ifdef __DEC64_MIN_EXP__ //(-383)
 WRITE_MACRO_VALUE(__DEC64_MIN_EXP__); 
#endif
#ifdef __DBL_DIG__ 
 WRITE_MACRO_VALUE(__DBL_DIG__); 
#endif
#ifdef __FLT_EPSILON__ //1.19209290e-7F
 WRITE_MACRO_VALUE(__FLT_EPSILON__); 
#endif
#ifdef __LDBL_MIN__ //3.36210314311209350626e-4932L
 WRITE_MACRO_VALUE(__LDBL_MIN__); 
#endif
#ifdef __DEC32_MAX__ //9.999999E96DF
 WRITE_MACRO_VALUE_STRING2(__DEC32_MAX__); 
#endif
#ifdef __unix__ 
 WRITE_MACRO_VALUE(__unix__); 
#endif
#ifdef __DECIMAL_DIG__ 
 WRITE_MACRO_VALUE(__DECIMAL_DIG__); 
#endif
#ifdef __LDBL_HAS_QUIET_NAN__ 
 WRITE_MACRO_VALUE(__LDBL_HAS_QUIET_NAN__); 
#endif
#ifdef __GNUC__ 
 WRITE_MACRO_VALUE(__GNUC__); 
#endif
#ifdef __pie__ 
 WRITE_MACRO_VALUE(__pie__); 
#endif
#ifdef __MMX__ 
 WRITE_MACRO_VALUE(__MMX__); 
#endif
#ifdef __FLT_HAS_DENORM__ 
 WRITE_MACRO_VALUE(__FLT_HAS_DENORM__); 
#endif
#ifdef __DBL_MAX__ //1.7976931348623157e+308
 WRITE_MACRO_VALUE_STRING2(__DBL_MAX__); 
#endif
#ifdef __DBL_HAS_INFINITY__ 
 WRITE_MACRO_VALUE(__DBL_HAS_INFINITY__); 
#endif
#ifdef __DEC32_MIN_EXP__ //(-95)
 WRITE_MACRO_VALUE(__DEC32_MIN_EXP__); 
#endif
#ifdef __LDBL_HAS_DENORM__ 
 WRITE_MACRO_VALUE(__LDBL_HAS_DENORM__); 
#endif
#ifdef __DEC32_MIN__ //1E-95DF
 WRITE_MACRO_VALUE(__DEC32_MIN__); 
#endif
#ifdef __DBL_MAX_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MAX_EXP__); 
#endif
#ifdef __DEC128_EPSILON__ //1E-33DL
 WRITE_MACRO_VALUE(__DEC128_EPSILON__); 
#endif
#ifdef __SSE2_MATH__ 
 WRITE_MACRO_VALUE(__SSE2_MATH__); 
#endif
#ifdef __amd64 
 WRITE_MACRO_VALUE(__amd64); 
#endif
#ifdef __LONG_LONG_MAX__ //9223372036854775807LL
 WRITE_MACRO_VALUE(__LONG_LONG_MAX__); 
#endif
#ifdef __GXX_ABI_VERSION 
 WRITE_MACRO_VALUE(__GXX_ABI_VERSION); 
#endif
#ifdef __FLT_MIN_EXP__ //(-125)
 WRITE_MACRO_VALUE(__FLT_MIN_EXP__); 
#endif
#ifdef __x86_64 
 WRITE_MACRO_VALUE(__x86_64); 
#endif
#ifdef __DBL_MIN__ //2.2250738585072014e-308
 WRITE_MACRO_VALUE(__DBL_MIN__); 
#endif
#ifdef __LP64__ 
 WRITE_MACRO_VALUE(__LP64__); 
#endif
#ifdef __DBL_HAS_QUIET_NAN__ 
 WRITE_MACRO_VALUE(__DBL_HAS_QUIET_NAN__); 
#endif
#ifdef __DEC128_MIN__ //1E-6143DL
 WRITE_MACRO_VALUE(__DEC128_MIN__); 
#endif
#ifdef __REGISTER_PREFIX__ 
 WRITE_MACRO_VALUE_STRING2(__REGISTER_PREFIX__); 
#endif
#ifdef __DBL_HAS_DENORM__ 
 WRITE_MACRO_VALUE(__DBL_HAS_DENORM__); 
#endif
#ifdef __NO_INLINE__ 
 WRITE_MACRO_VALUE(__NO_INLINE__); 
#endif
#ifdef __DEC_EVAL_METHOD__ 
 WRITE_MACRO_VALUE(__DEC_EVAL_METHOD__); 
#endif
#ifdef __DEC128_MAX__ //9.999999999999999999999999999999999E6144DL
 WRITE_MACRO_VALUE_STRING2(__DEC128_MAX__); 
#endif
#ifdef __FLT_MANT_DIG__ 
 WRITE_MACRO_VALUE(__FLT_MANT_DIG__); 
#endif
#ifdef __VERSION__ //"4.2.1 20070719 "
 WRITE_MACRO_VALUE_STRING(__VERSION__); 
#endif
#ifdef __OpenBSD__ 
 WRITE_MACRO_VALUE(__OpenBSD__); 
#endif
#ifdef __DEC64_EPSILON__ //1E-15DD
 WRITE_MACRO_VALUE(__DEC64_EPSILON__); 
#endif
#ifdef __DEC128_MIN_EXP__ //(-6143)
 WRITE_MACRO_VALUE(__DEC128_MIN_EXP__); 
#endif
#ifdef __SIZE_TYPE__ //long unsigned int
 WRITE_MACRO_VALUE_STRING2(__SIZE_TYPE__); 
#endif
#ifdef __DEC32_DEN__ //0.000001E-95DF
 WRITE_MACRO_VALUE_STRING2(__DEC32_DEN__); 
#endif
#ifdef __ELF__ 
 WRITE_MACRO_VALUE(__ELF__); 
#endif
#ifdef __FLT_RADIX__ 
 WRITE_MACRO_VALUE(__FLT_RADIX__); 
#endif
#ifdef __LDBL_EPSILON__ //1.08420217248550443401e-19L
 WRITE_MACRO_VALUE_STRING2(__LDBL_EPSILON__); 
#endif
#ifdef __SSE_MATH__ 
 WRITE_MACRO_VALUE(__SSE_MATH__); 
#endif
#ifdef __k8 
 WRITE_MACRO_VALUE(__k8); 
#endif
#ifdef __LDBL_DIG__ 
 WRITE_MACRO_VALUE(__LDBL_DIG__); 
#endif
#ifdef __x86_64__ 
 WRITE_MACRO_VALUE(__x86_64__); 
#endif
#ifdef __FLT_HAS_QUIET_NAN__ 
 WRITE_MACRO_VALUE(__FLT_HAS_QUIET_NAN__); 
#endif
#ifdef __FLT_MAX_10_EXP__ 
 WRITE_MACRO_VALUE(__FLT_MAX_10_EXP__); 
#endif
#ifdef __LONG_MAX__ //9223372036854775807L
 WRITE_MACRO_VALUE_STRING2(__LONG_MAX__); 
#endif
#ifdef __FLT_HAS_INFINITY__ 
 WRITE_MACRO_VALUE(__FLT_HAS_INFINITY__); 
#endif
#ifdef __DEC64_MAX__ //9.999999999999999E384DD
 WRITE_MACRO_VALUE_STRING2(__DEC64_MAX__); 
#endif
#ifdef __DEC64_MANT_DIG__ 
 WRITE_MACRO_VALUE(__DEC64_MANT_DIG__); 
#endif
#ifdef __DEC32_MAX_EXP__ 
 WRITE_MACRO_VALUE(__DEC32_MAX_EXP__); 
#endif
#ifdef __DEC128_DEN__ //0.000000000000000000000000000000001E-6143DL
 WRITE_MACRO_VALUE_STRING2(__DEC128_DEN__); 
#endif
#ifdef __LDBL_MANT_DIG__ 
 WRITE_MACRO_VALUE(__LDBL_MANT_DIG__); 
#endif
#ifdef __DEC32_MANT_DIG__ 
 WRITE_MACRO_VALUE(__DEC32_MANT_DIG__); 
#endif
#ifdef __k8__ 
 WRITE_MACRO_VALUE(__k8__); 
#endif
#ifdef __WCHAR_TYPE__ //int
 WRITE_MACRO_VALUE_STRING2(__WCHAR_TYPE__); 
#endif
#ifdef __pic__ 
 WRITE_MACRO_VALUE(__pic__); 
#endif
#ifdef __FLT_DIG__ 
 WRITE_MACRO_VALUE(__FLT_DIG__); 
#endif
#ifdef __INT_MAX__ //2147483647
 WRITE_MACRO_VALUE_STRING2(__INT_MAX__); 
#endif
#ifdef __FLT_MAX_EXP__ 
 WRITE_MACRO_VALUE(__FLT_MAX_EXP__); 
#endif
#ifdef __DBL_MANT_DIG__ 
 WRITE_MACRO_VALUE(__DBL_MANT_DIG__); 
#endif
#ifdef __DEC64_MIN__ //1E-383DD
 WRITE_MACRO_VALUE_STRING2(__DEC64_MIN__); 
#endif
#ifdef __WINT_TYPE__ //unsigned int
 WRITE_MACRO_VALUE_STRING2(__WINT_TYPE__); 
#endif
#ifdef __SSE__ 
 WRITE_MACRO_VALUE(__SSE__); 
#endif
#ifdef __LDBL_MIN_EXP__ //(-16381)
 WRITE_MACRO_VALUE_STRING2(__LDBL_MIN_EXP__); 
#endif
#ifdef __i386__ 
 WRITE_MACRO_VALUE(__i386__); 
#endif
#ifdef __amd64__ 
 WRITE_MACRO_VALUE(__amd64__); 
#endif
#ifdef __LDBL_MAX_EXP__ 
 WRITE_MACRO_VALUE(__LDBL_MAX_EXP__); 
#endif
#ifdef __LDBL_MAX_10_EXP__ 
 WRITE_MACRO_VALUE(__LDBL_MAX_10_EXP__); 
#endif
#ifdef __DBL_EPSILON__ //2.2204460492503131e-16
 WRITE_MACRO_VALUE_STRING2(__DBL_EPSILON__); 
#endif
#ifdef _LP64 
 WRITE_MACRO_VALUE(_LP64); 
#endif
#ifdef __GNUC_PATCHLEVEL__ 
 WRITE_MACRO_VALUE(__GNUC_PATCHLEVEL__); 
#endif
#ifdef __LDBL_HAS_INFINITY__ 
 WRITE_MACRO_VALUE(__LDBL_HAS_INFINITY__); 
#endif
#ifdef __ANSI_COMPAT 
 WRITE_MACRO_VALUE(__ANSI_COMPAT); 
#endif
#ifdef __INTMAX_MAX__ //9223372036854775807LL
 WRITE_MACRO_VALUE_STRING2(__INTMAX_MAX__); 
#endif
#ifdef __FLT_DENORM_MIN__ //1.40129846e-45F
 WRITE_MACRO_VALUE_STRING2(__FLT_DENORM_MIN__); 
#endif
#ifdef __PIC__ 
 WRITE_MACRO_VALUE(__PIC__); 
#endif
#ifdef __FLT_MAX__ //3.40282347e+38F
 WRITE_MACRO_VALUE_STRING2(__FLT_MAX__); 
#endif
#ifdef __SSE2__ 
 WRITE_MACRO_VALUE(__SSE2__); 
#endif
#ifdef __FLT_MIN_10_EXP__ //(-37)
 WRITE_MACRO_VALUE(__FLT_MIN_10_EXP__); 
#endif
#ifdef __INTMAX_TYPE__ //long long int
 WRITE_MACRO_VALUE_STRING2(__INTMAX_TYPE__); 
#endif
#ifdef __DEC128_MAX_EXP__ 
 WRITE_MACRO_VALUE(__DEC128_MAX_EXP__); 
#endif
#ifdef __GNUC_MINOR__ 
 WRITE_MACRO_VALUE(__GNUC_MINOR__); 
#endif
#ifdef __PIE__ 
 WRITE_MACRO_VALUE(__PIE__); 
#endif
#ifdef __DBL_MAX_10_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MAX_10_EXP__); 
#endif
#ifdef __LDBL_DENORM_MIN__ //3.64519953188247460253e-4951L
 WRITE_MACRO_VALUE(__LDBL_DENORM_MIN__); 
#endif
#ifdef __STDC__ 
 WRITE_MACRO_VALUE(__STDC__); 
#endif
#ifdef __PTRDIFF_TYPE__ //long int
 WRITE_MACRO_VALUE_STRING2(__PTRDIFF_TYPE__); 
#endif
#ifdef __DEC128_MANT_DIG__ 
 WRITE_MACRO_VALUE(__DEC128_MANT_DIG__); 
#endif
#ifdef __LDBL_MIN_10_EXP__ //(-4931)
 WRITE_MACRO_VALUE_STRING2(__LDBL_MIN_10_EXP__); 
#endif
#ifdef __GNUC_GNU_INLINE__ 
 WRITE_MACRO_VALUE(__GNUC_GNU_INLINE__); 
#endif
}; 


void print_misc2(void) { 

#ifdef _LP64 
 WRITE_MACRO_VALUE(_LP64); 
#endif
#ifdef _RET_PROTECTOR 
 WRITE_MACRO_VALUE(_RET_PROTECTOR); 
#endif
#ifdef __ATOMIC_ACQUIRE 
 WRITE_MACRO_VALUE(__ATOMIC_ACQUIRE); 
#endif
#ifdef __ATOMIC_ACQ_REL 
 WRITE_MACRO_VALUE(__ATOMIC_ACQ_REL); 
#endif
#ifdef __ATOMIC_CONSUME 
 WRITE_MACRO_VALUE(__ATOMIC_CONSUME); 
#endif
#ifdef __ATOMIC_RELAXED 
 WRITE_MACRO_VALUE(__ATOMIC_RELAXED); 
#endif
#ifdef __ATOMIC_RELEASE 
 WRITE_MACRO_VALUE(__ATOMIC_RELEASE); 
#endif
#ifdef __ATOMIC_SEQ_CST 
 WRITE_MACRO_VALUE(__ATOMIC_SEQ_CST); 
#endif
#ifdef __BIGGEST_ALIGNMENT__ 
 WRITE_MACRO_VALUE(__BIGGEST_ALIGNMENT__); 
#endif
#ifdef __BYTE_ORDER__ 
 WRITE_MACRO_VALUE(__BYTE_ORDER__); 
#endif
#ifdef __CHAR16_TYPE__ 
 WRITE_MACRO_VALUE(__CHAR16_TYPE__); 
#endif
#ifdef __CHAR32_TYPE__ 
 WRITE_MACRO_VALUE(__CHAR32_TYPE__); 
#endif
#ifdef __CHAR_BIT__ 
 WRITE_MACRO_VALUE(__CHAR_BIT__); 
#endif
#ifdef __CLANG_ATOMIC_BOOL_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_BOOL_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_CHAR16_T_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_CHAR16_T_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_CHAR32_T_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_CHAR32_T_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_CHAR_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_CHAR_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_INT_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_INT_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_LLONG_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_LLONG_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_LONG_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_LONG_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_POINTER_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_POINTER_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_SHORT_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_SHORT_LOCK_FREE); 
#endif
#ifdef __CLANG_ATOMIC_WCHAR_T_LOCK_FREE 
 WRITE_MACRO_VALUE(__CLANG_ATOMIC_WCHAR_T_LOCK_FREE); 
#endif
#ifdef __CONSTANT_CFSTRINGS__ 
 WRITE_MACRO_VALUE(__CONSTANT_CFSTRINGS__); 
#endif
#ifdef __DBL_DECIMAL_DIG__ 
 WRITE_MACRO_VALUE(__DBL_DECIMAL_DIG__); 
#endif
#ifdef __DBL_DENORM_MIN__ 
 WRITE_MACRO_VALUE(__DBL_DENORM_MIN__); 
#endif
#ifdef __DBL_DIG__ 
 WRITE_MACRO_VALUE(__DBL_DIG__); 
#endif
#ifdef __DBL_EPSILON__ 
 WRITE_MACRO_VALUE(__DBL_EPSILON__); 
#endif
#ifdef __DBL_HAS_DENORM__ 
 WRITE_MACRO_VALUE(__DBL_HAS_DENORM__); 
#endif
#ifdef __DBL_HAS_INFINITY__ 
 WRITE_MACRO_VALUE(__DBL_HAS_INFINITY__); 
#endif
#ifdef __DBL_HAS_QUIET_NAN__ 
 WRITE_MACRO_VALUE(__DBL_HAS_QUIET_NAN__); 
#endif
#ifdef __DBL_MANT_DIG__ 
 WRITE_MACRO_VALUE(__DBL_MANT_DIG__); 
#endif
#ifdef __DBL_MAX_10_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MAX_10_EXP__); 
#endif
#ifdef __DBL_MAX_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MAX_EXP__); 
#endif
#ifdef __DBL_MAX__ 
 WRITE_MACRO_VALUE(__DBL_MAX__); 
#endif
#ifdef __DBL_MIN_10_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MIN_10_EXP__); 
#endif
#ifdef __DBL_MIN_EXP__ 
 WRITE_MACRO_VALUE(__DBL_MIN_EXP__); 
#endif
#ifdef __DBL_MIN__ 
 WRITE_MACRO_VALUE(__DBL_MIN__); 
#endif
#ifdef __DECIMAL_DIG__ 
 WRITE_MACRO_VALUE(__DECIMAL_DIG__); 
#endif
#ifdef __ELF__ 
 WRITE_MACRO_VALUE(__ELF__); 
#endif
#ifdef __FINITE_MATH_ONLY__ 
 WRITE_MACRO_VALUE(__FINITE_MATH_ONLY__); 
#endif
#ifdef __FLOAT128__ 
 WRITE_MACRO_VALUE(__FLOAT128__); 
#endif
#ifdef __FLT_DECIMAL_DIG__ 
 WRITE_MACRO_VALUE(__FLT_DECIMAL_DIG__); 
#endif
#ifdef __FLT_DENORM_MIN__ 
 WRITE_MACRO_VALUE(__FLT_DENORM_MIN__); 
#endif
#ifdef __FLT_DIG__ 
 WRITE_MACRO_VALUE(__FLT_DIG__); 
#endif
#ifdef __FLT_EPSILON__ 
 WRITE_MACRO_VALUE(__FLT_EPSILON__); 
#endif
#ifdef __FLT_EVAL_METHOD__ 
 WRITE_MACRO_VALUE(__FLT_EVAL_METHOD__); 
#endif
#ifdef __FLT_HAS_DENORM__ 
 WRITE_MACRO_VALUE(__FLT_HAS_DENORM__); 
#endif
#ifdef __FLT_HAS_INFINITY__ 
 WRITE_MACRO_VALUE(__FLT_HAS_INFINITY__); 
#endif
#ifdef __FLT_HAS_QUIET_NAN__ 
 WRITE_MACRO_VALUE(__FLT_HAS_QUIET_NAN__); 
#endif
#ifdef __FLT_MANT_DIG__ 
 WRITE_MACRO_VALUE(__FLT_MANT_DIG__); 
#endif
#ifdef __FLT_MAX_10_EXP__ 
 WRITE_MACRO_VALUE(__FLT_MAX_10_EXP__); 
#endif
#ifdef __FLT_MAX_EXP__ 
 WRITE_MACRO_VALUE(__FLT_MAX_EXP__); 
#endif
#ifdef __FLT_MAX__ 
 WRITE_MACRO_VALUE(__FLT_MAX__); 
#endif
#ifdef __FLT_MIN_10_EXP__ 
 WRITE_MACRO_VALUE(__FLT_MIN_10_EXP__); 
#endif
#ifdef __FLT_MIN_EXP__ 
 WRITE_MACRO_VALUE(__FLT_MIN_EXP__); 
#endif
#ifdef __FLT_MIN__ 
 WRITE_MACRO_VALUE(__FLT_MIN__); 
#endif
#ifdef __FLT_RADIX__ 
 WRITE_MACRO_VALUE(__FLT_RADIX__); 
#endif
#ifdef __FXSR__ 
 WRITE_MACRO_VALUE(__FXSR__); 
#endif
#ifdef __GCC_ASM_FLAG_OUTPUTS__ 
 WRITE_MACRO_VALUE(__GCC_ASM_FLAG_OUTPUTS__); 
#endif
#ifdef __GCC_ATOMIC_BOOL_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_BOOL_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_CHAR16_T_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_CHAR16_T_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_CHAR32_T_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_CHAR32_T_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_CHAR_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_CHAR_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_INT_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_INT_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_LLONG_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_LLONG_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_LONG_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_LONG_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_POINTER_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_POINTER_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_SHORT_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_SHORT_LOCK_FREE); 
#endif
#ifdef __GCC_ATOMIC_TEST_AND_SET_TRUEVAL 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_TEST_AND_SET_TRUEVAL); 
#endif
#ifdef __GCC_ATOMIC_WCHAR_T_LOCK_FREE 
 WRITE_MACRO_VALUE(__GCC_ATOMIC_WCHAR_T_LOCK_FREE); 
#endif
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1); 
#endif
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2); 
#endif
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4); 
#endif
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8); 
#endif
#ifdef __GNUC_MINOR__ 
 WRITE_MACRO_VALUE(__GNUC_MINOR__); 
#endif
#ifdef __GNUC_PATCHLEVEL__ 
 WRITE_MACRO_VALUE(__GNUC_PATCHLEVEL__); 
#endif
#ifdef __GNUC_STDC_INLINE__ 
 WRITE_MACRO_VALUE(__GNUC_STDC_INLINE__); 
#endif
#ifdef __GNUC__ 
 WRITE_MACRO_VALUE(__GNUC__); 
#endif
#ifdef __GXX_ABI_VERSION 
 WRITE_MACRO_VALUE(__GXX_ABI_VERSION); 
#endif
#ifdef __INT16_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__INT16_C_SUFFIX__); 
#endif
#ifdef __INT16_FMTd__ 
 WRITE_MACRO_VALUE(__INT16_FMTd__); 
#endif
#ifdef __INT16_FMTi__ 
 WRITE_MACRO_VALUE(__INT16_FMTi__); 
#endif
#ifdef __INT16_MAX__ 
 WRITE_MACRO_VALUE(__INT16_MAX__); 
#endif
#ifdef __INT16_TYPE__ 
 WRITE_MACRO_VALUE(__INT16_TYPE__); 
#endif
#ifdef __INT32_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__INT32_C_SUFFIX__); 
#endif
#ifdef __INT32_FMTd__ 
 WRITE_MACRO_VALUE(__INT32_FMTd__); 
#endif
#ifdef __INT32_FMTi__ 
 WRITE_MACRO_VALUE(__INT32_FMTi__); 
#endif
#ifdef __INT32_MAX__ 
 WRITE_MACRO_VALUE(__INT32_MAX__); 
#endif
#ifdef __INT32_TYPE__ 
 WRITE_MACRO_VALUE(__INT32_TYPE__); 
#endif
#ifdef __INT64_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__INT64_C_SUFFIX__); 
#endif
#ifdef __INT64_FMTd__ 
 WRITE_MACRO_VALUE(__INT64_FMTd__); 
#endif
#ifdef __INT64_FMTi__ 
 WRITE_MACRO_VALUE(__INT64_FMTi__); 
#endif
#ifdef __INT64_MAX__ 
 WRITE_MACRO_VALUE(__INT64_MAX__); 
#endif
#ifdef __INT64_TYPE__ 
 WRITE_MACRO_VALUE(__INT64_TYPE__); 
#endif
#ifdef __INT8_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__INT8_C_SUFFIX__); 
#endif
#ifdef __INT8_FMTd__ 
 WRITE_MACRO_VALUE(__INT8_FMTd__); 
#endif
#ifdef __INT8_FMTi__ 
 WRITE_MACRO_VALUE(__INT8_FMTi__); 
#endif
#ifdef __INT8_MAX__ 
 WRITE_MACRO_VALUE(__INT8_MAX__); 
#endif
#ifdef __INT8_TYPE__ 
 WRITE_MACRO_VALUE(__INT8_TYPE__); 
#endif
#ifdef __INTMAX_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__INTMAX_C_SUFFIX__); 
#endif
#ifdef __INTMAX_FMTd__ 
 WRITE_MACRO_VALUE(__INTMAX_FMTd__); 
#endif
#ifdef __INTMAX_FMTi__ 
 WRITE_MACRO_VALUE(__INTMAX_FMTi__); 
#endif
#ifdef __INTMAX_MAX__ 
 WRITE_MACRO_VALUE(__INTMAX_MAX__); 
#endif
#ifdef __INTMAX_TYPE__ 
 WRITE_MACRO_VALUE(__INTMAX_TYPE__); 
#endif
#ifdef __INTMAX_WIDTH__ 
 WRITE_MACRO_VALUE(__INTMAX_WIDTH__); 
#endif
#ifdef __INTPTR_FMTd__ 
 WRITE_MACRO_VALUE(__INTPTR_FMTd__); 
#endif
#ifdef __INTPTR_FMTi__ 
 WRITE_MACRO_VALUE(__INTPTR_FMTi__); 
#endif
#ifdef __INTPTR_MAX__ 
 WRITE_MACRO_VALUE(__INTPTR_MAX__); 
#endif
#ifdef __INTPTR_TYPE__ 
 WRITE_MACRO_VALUE(__INTPTR_TYPE__); 
#endif
#ifdef __INTPTR_WIDTH__ 
 WRITE_MACRO_VALUE(__INTPTR_WIDTH__); 
#endif
#ifdef __INT_FAST16_FMTd__ 
 WRITE_MACRO_VALUE(__INT_FAST16_FMTd__); 
#endif
#ifdef __INT_FAST16_FMTi__ 
 WRITE_MACRO_VALUE(__INT_FAST16_FMTi__); 
#endif
#ifdef __INT_FAST16_MAX__ 
 WRITE_MACRO_VALUE(__INT_FAST16_MAX__); 
#endif
#ifdef __INT_FAST16_TYPE__ 
 WRITE_MACRO_VALUE(__INT_FAST16_TYPE__); 
#endif
#ifdef __INT_FAST32_FMTd__ 
 WRITE_MACRO_VALUE(__INT_FAST32_FMTd__); 
#endif
#ifdef __INT_FAST32_FMTi__ 
 WRITE_MACRO_VALUE(__INT_FAST32_FMTi__); 
#endif
#ifdef __INT_FAST32_MAX__ 
 WRITE_MACRO_VALUE(__INT_FAST32_MAX__); 
#endif
#ifdef __INT_FAST32_TYPE__ 
 WRITE_MACRO_VALUE(__INT_FAST32_TYPE__); 
#endif
#ifdef __INT_FAST64_FMTd__ 
 WRITE_MACRO_VALUE(__INT_FAST64_FMTd__); 
#endif
#ifdef __INT_FAST64_FMTi__ 
 WRITE_MACRO_VALUE(__INT_FAST64_FMTi__); 
#endif
#ifdef __INT_FAST64_MAX__ 
 WRITE_MACRO_VALUE(__INT_FAST64_MAX__); 
#endif
#ifdef __INT_FAST64_TYPE__ 
 WRITE_MACRO_VALUE(__INT_FAST64_TYPE__); 
#endif
#ifdef __INT_FAST8_FMTd__ 
 WRITE_MACRO_VALUE(__INT_FAST8_FMTd__); 
#endif
#ifdef __INT_FAST8_FMTi__ 
 WRITE_MACRO_VALUE(__INT_FAST8_FMTi__); 
#endif
#ifdef __INT_FAST8_MAX__ 
 WRITE_MACRO_VALUE(__INT_FAST8_MAX__); 
#endif
#ifdef __INT_FAST8_TYPE__ 
 WRITE_MACRO_VALUE(__INT_FAST8_TYPE__); 
#endif
#ifdef __INT_LEAST16_FMTd__ 
 WRITE_MACRO_VALUE(__INT_LEAST16_FMTd__); 
#endif
#ifdef __INT_LEAST16_FMTi__ 
 WRITE_MACRO_VALUE(__INT_LEAST16_FMTi__); 
#endif
#ifdef __INT_LEAST16_MAX__ 
 WRITE_MACRO_VALUE(__INT_LEAST16_MAX__); 
#endif
#ifdef __INT_LEAST16_TYPE__ 
 WRITE_MACRO_VALUE(__INT_LEAST16_TYPE__); 
#endif
#ifdef __INT_LEAST32_FMTd__ 
 WRITE_MACRO_VALUE(__INT_LEAST32_FMTd__); 
#endif
#ifdef __INT_LEAST32_FMTi__ 
 WRITE_MACRO_VALUE(__INT_LEAST32_FMTi__); 
#endif
#ifdef __INT_LEAST32_MAX__ 
 WRITE_MACRO_VALUE(__INT_LEAST32_MAX__); 
#endif
#ifdef __INT_LEAST32_TYPE__ 
 WRITE_MACRO_VALUE(__INT_LEAST32_TYPE__); 
#endif
#ifdef __INT_LEAST64_FMTd__ 
 WRITE_MACRO_VALUE(__INT_LEAST64_FMTd__); 
#endif
#ifdef __INT_LEAST64_FMTi__ 
 WRITE_MACRO_VALUE(__INT_LEAST64_FMTi__); 
#endif
#ifdef __INT_LEAST64_MAX__ 
 WRITE_MACRO_VALUE(__INT_LEAST64_MAX__); 
#endif
#ifdef __INT_LEAST64_TYPE__ 
 WRITE_MACRO_VALUE(__INT_LEAST64_TYPE__); 
#endif
#ifdef __INT_LEAST8_FMTd__ 
 WRITE_MACRO_VALUE(__INT_LEAST8_FMTd__); 
#endif
#ifdef __INT_LEAST8_FMTi__ 
 WRITE_MACRO_VALUE(__INT_LEAST8_FMTi__); 
#endif
#ifdef __INT_LEAST8_MAX__ 
 WRITE_MACRO_VALUE(__INT_LEAST8_MAX__); 
#endif
#ifdef __INT_LEAST8_TYPE__ 
 WRITE_MACRO_VALUE(__INT_LEAST8_TYPE__); 
#endif
#ifdef __INT_MAX__ 
 WRITE_MACRO_VALUE(__INT_MAX__); 
#endif
#ifdef __LDBL_DECIMAL_DIG__ 
 WRITE_MACRO_VALUE(__LDBL_DECIMAL_DIG__); 
#endif
#ifdef __LDBL_DENORM_MIN__ 
 WRITE_MACRO_VALUE(__LDBL_DENORM_MIN__); 
#endif
#ifdef __LDBL_DIG__ 
 WRITE_MACRO_VALUE(__LDBL_DIG__); 
#endif
#ifdef __LDBL_EPSILON__ 
 WRITE_MACRO_VALUE(__LDBL_EPSILON__); 
#endif
#ifdef __LDBL_HAS_DENORM__ 
 WRITE_MACRO_VALUE(__LDBL_HAS_DENORM__); 
#endif
#ifdef __LDBL_HAS_INFINITY__ 
 WRITE_MACRO_VALUE(__LDBL_HAS_INFINITY__); 
#endif
#ifdef __LDBL_HAS_QUIET_NAN__ 
 WRITE_MACRO_VALUE(__LDBL_HAS_QUIET_NAN__); 
#endif
#ifdef __LDBL_MANT_DIG__ 
 WRITE_MACRO_VALUE(__LDBL_MANT_DIG__); 
#endif
#ifdef __LDBL_MAX_10_EXP__ 
 WRITE_MACRO_VALUE(__LDBL_MAX_10_EXP__); 
#endif
#ifdef __LDBL_MAX_EXP__ 
 WRITE_MACRO_VALUE(__LDBL_MAX_EXP__); 
#endif
#ifdef __LDBL_MAX__ 
 WRITE_MACRO_VALUE(__LDBL_MAX__); 
#endif
#ifdef __LDBL_MIN_10_EXP__ 
 WRITE_MACRO_VALUE(__LDBL_MIN_10_EXP__); 
#endif
#ifdef __LDBL_MIN_EXP__ 
 WRITE_MACRO_VALUE(__LDBL_MIN_EXP__); 
#endif
#ifdef __LDBL_MIN__ 
 WRITE_MACRO_VALUE(__LDBL_MIN__); 
#endif
#ifdef __LITTLE_ENDIAN__ 
 WRITE_MACRO_VALUE(__LITTLE_ENDIAN__); 
#endif
#ifdef __LONG_LONG_MAX__ 
 WRITE_MACRO_VALUE(__LONG_LONG_MAX__); 
#endif
#ifdef __LONG_MAX__ 
 WRITE_MACRO_VALUE(__LONG_MAX__); 
#endif
#ifdef __LP64__ 
 WRITE_MACRO_VALUE(__LP64__); 
#endif
#ifdef __MMX__ 
 WRITE_MACRO_VALUE(__MMX__); 
#endif
#ifdef __NO_INLINE__ 
 WRITE_MACRO_VALUE(__NO_INLINE__); 
#endif
#ifdef __NO_MATH_INLINES 
 WRITE_MACRO_VALUE(__NO_MATH_INLINES); 
#endif
#ifdef __OBJC_BOOL_IS_BOOL 
 WRITE_MACRO_VALUE(__OBJC_BOOL_IS_BOOL); 
#endif
#ifdef __OPENCL_MEMORY_SCOPE_ALL_SVM_DEVICES 
 WRITE_MACRO_VALUE(__OPENCL_MEMORY_SCOPE_ALL_SVM_DEVICES); 
#endif
#ifdef __OPENCL_MEMORY_SCOPE_DEVICE 
 WRITE_MACRO_VALUE(__OPENCL_MEMORY_SCOPE_DEVICE); 
#endif
#ifdef __OPENCL_MEMORY_SCOPE_SUB_GROUP 
 WRITE_MACRO_VALUE(__OPENCL_MEMORY_SCOPE_SUB_GROUP); 
#endif
#ifdef __OPENCL_MEMORY_SCOPE_WORK_GROUP 
 WRITE_MACRO_VALUE(__OPENCL_MEMORY_SCOPE_WORK_GROUP); 
#endif
#ifdef __OPENCL_MEMORY_SCOPE_WORK_ITEM 
 WRITE_MACRO_VALUE(__OPENCL_MEMORY_SCOPE_WORK_ITEM); 
#endif
#ifdef __ORDER_BIG_ENDIAN__ 
 WRITE_MACRO_VALUE(__ORDER_BIG_ENDIAN__); 
#endif
#ifdef __ORDER_LITTLE_ENDIAN__ 
 WRITE_MACRO_VALUE(__ORDER_LITTLE_ENDIAN__); 
#endif
#ifdef __ORDER_PDP_ENDIAN__ 
 WRITE_MACRO_VALUE(__ORDER_PDP_ENDIAN__); 
#endif
#ifdef __OpenBSD__ 
 WRITE_MACRO_VALUE(__OpenBSD__); 
#endif
#ifdef __PIC__ 
 WRITE_MACRO_VALUE(__PIC__); 
#endif
#ifdef __PIE__ 
 WRITE_MACRO_VALUE(__PIE__); 
#endif
#ifdef __POINTER_WIDTH__ 
 WRITE_MACRO_VALUE(__POINTER_WIDTH__); 
#endif
#ifdef __PRAGMA_REDEFINE_EXTNAME 
 WRITE_MACRO_VALUE(__PRAGMA_REDEFINE_EXTNAME); 
#endif
#ifdef __PTRDIFF_FMTd__ 
 WRITE_MACRO_VALUE(__PTRDIFF_FMTd__); 
#endif
#ifdef __PTRDIFF_FMTi__ 
 WRITE_MACRO_VALUE(__PTRDIFF_FMTi__); 
#endif
#ifdef __PTRDIFF_MAX__ 
 WRITE_MACRO_VALUE(__PTRDIFF_MAX__); 
#endif
#ifdef __PTRDIFF_TYPE__ 
 WRITE_MACRO_VALUE(__PTRDIFF_TYPE__); 
#endif
#ifdef __PTRDIFF_WIDTH__ 
 WRITE_MACRO_VALUE(__PTRDIFF_WIDTH__); 
#endif
#ifdef __REGISTER_PREFIX__ 
 WRITE_MACRO_VALUE(__REGISTER_PREFIX__); 
#endif
#ifdef __SCHAR_MAX__ 
 WRITE_MACRO_VALUE(__SCHAR_MAX__); 
#endif
#ifdef __SEG_FS 
 WRITE_MACRO_VALUE(__SEG_FS); 
#endif
#ifdef __SEG_GS 
 WRITE_MACRO_VALUE(__SEG_GS); 
#endif
#ifdef __SHRT_MAX__ 
 WRITE_MACRO_VALUE(__SHRT_MAX__); 
#endif
#ifdef __SIG_ATOMIC_MAX__ 
 WRITE_MACRO_VALUE(__SIG_ATOMIC_MAX__); 
#endif
#ifdef __SIG_ATOMIC_WIDTH__ 
 WRITE_MACRO_VALUE(__SIG_ATOMIC_WIDTH__); 
#endif
#ifdef __SIZEOF_DOUBLE__ 
 WRITE_MACRO_VALUE(__SIZEOF_DOUBLE__); 
#endif
#ifdef __SIZEOF_FLOAT128__ 
 WRITE_MACRO_VALUE(__SIZEOF_FLOAT128__); 
#endif
#ifdef __SIZEOF_FLOAT__ 
 WRITE_MACRO_VALUE(__SIZEOF_FLOAT__); 
#endif
#ifdef __SIZEOF_INT128__ 
 WRITE_MACRO_VALUE(__SIZEOF_INT128__); 
#endif
#ifdef __SIZEOF_INT__ 
 WRITE_MACRO_VALUE(__SIZEOF_INT__); 
#endif
#ifdef __SIZEOF_LONG_DOUBLE__ 
 WRITE_MACRO_VALUE(__SIZEOF_LONG_DOUBLE__); 
#endif
#ifdef __SIZEOF_LONG_LONG__ 
 WRITE_MACRO_VALUE(__SIZEOF_LONG_LONG__); 
#endif
#ifdef __SIZEOF_LONG__ 
 WRITE_MACRO_VALUE(__SIZEOF_LONG__); 
#endif
#ifdef __SIZEOF_POINTER__ 
 WRITE_MACRO_VALUE(__SIZEOF_POINTER__); 
#endif
#ifdef __SIZEOF_PTRDIFF_T__ 
 WRITE_MACRO_VALUE(__SIZEOF_PTRDIFF_T__); 
#endif
#ifdef __SIZEOF_SHORT__ 
 WRITE_MACRO_VALUE(__SIZEOF_SHORT__); 
#endif
#ifdef __SIZEOF_SIZE_T__ 
 WRITE_MACRO_VALUE(__SIZEOF_SIZE_T__); 
#endif
#ifdef __SIZEOF_WCHAR_T__ 
 WRITE_MACRO_VALUE(__SIZEOF_WCHAR_T__); 
#endif
#ifdef __SIZEOF_WINT_T__ 
 WRITE_MACRO_VALUE(__SIZEOF_WINT_T__); 
#endif
#ifdef __SIZE_FMTX__ 
 WRITE_MACRO_VALUE(__SIZE_FMTX__); 
#endif
#ifdef __SIZE_FMTo__ 
 WRITE_MACRO_VALUE(__SIZE_FMTo__); 
#endif
#ifdef __SIZE_FMTu__ 
 WRITE_MACRO_VALUE(__SIZE_FMTu__); 
#endif
#ifdef __SIZE_FMTx__ 
 WRITE_MACRO_VALUE(__SIZE_FMTx__); 
#endif
#ifdef __SIZE_MAX__ 
 WRITE_MACRO_VALUE(__SIZE_MAX__); 
#endif
#ifdef __SIZE_TYPE__ 
 WRITE_MACRO_VALUE(__SIZE_TYPE__); 
#endif
#ifdef __SIZE_WIDTH__ 
 WRITE_MACRO_VALUE(__SIZE_WIDTH__); 
#endif
#ifdef __SSE2_MATH__ 
 WRITE_MACRO_VALUE(__SSE2_MATH__); 
#endif
#ifdef __SSE2__ 
 WRITE_MACRO_VALUE(__SSE2__); 
#endif
#ifdef __SSE_MATH__ 
 WRITE_MACRO_VALUE(__SSE_MATH__); 
#endif
#ifdef __SSE__ 
 WRITE_MACRO_VALUE(__SSE__); 
#endif
#ifdef __STDC_HOSTED__ 
 WRITE_MACRO_VALUE(__STDC_HOSTED__); 
#endif
#ifdef __STDC_UTF_16__ 
 WRITE_MACRO_VALUE(__STDC_UTF_16__); 
#endif
#ifdef __STDC_UTF_32__ 
 WRITE_MACRO_VALUE(__STDC_UTF_32__); 
#endif
#ifdef __STDC_VERSION__ 
 WRITE_MACRO_VALUE(__STDC_VERSION__); 
#endif
#ifdef __STDC__ 
 WRITE_MACRO_VALUE(__STDC__); 
#endif
#ifdef __UINT16_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__UINT16_C_SUFFIX__); 
#endif
#ifdef __UINT16_FMTX__ 
 WRITE_MACRO_VALUE(__UINT16_FMTX__); 
#endif
#ifdef __UINT16_FMTo__ 
 WRITE_MACRO_VALUE(__UINT16_FMTo__); 
#endif
#ifdef __UINT16_FMTu__ 
 WRITE_MACRO_VALUE(__UINT16_FMTu__); 
#endif
#ifdef __UINT16_FMTx__ 
 WRITE_MACRO_VALUE(__UINT16_FMTx__); 
#endif
#ifdef __UINT16_MAX__ 
 WRITE_MACRO_VALUE(__UINT16_MAX__); 
#endif
#ifdef __UINT16_TYPE__ 
 WRITE_MACRO_VALUE(__UINT16_TYPE__); 
#endif
#ifdef __UINT32_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__UINT32_C_SUFFIX__); 
#endif
#ifdef __UINT32_FMTX__ 
 WRITE_MACRO_VALUE(__UINT32_FMTX__); 
#endif
#ifdef __UINT32_FMTo__ 
 WRITE_MACRO_VALUE(__UINT32_FMTo__); 
#endif
#ifdef __UINT32_FMTu__ 
 WRITE_MACRO_VALUE(__UINT32_FMTu__); 
#endif
#ifdef __UINT32_FMTx__ 
 WRITE_MACRO_VALUE(__UINT32_FMTx__); 
#endif
#ifdef __UINT32_MAX__ 
 WRITE_MACRO_VALUE(__UINT32_MAX__); 
#endif
#ifdef __UINT32_TYPE__ 
 WRITE_MACRO_VALUE(__UINT32_TYPE__); 
#endif
#ifdef __UINT64_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__UINT64_C_SUFFIX__); 
#endif
#ifdef __UINT64_FMTX__ 
 WRITE_MACRO_VALUE(__UINT64_FMTX__); 
#endif
#ifdef __UINT64_FMTo__ 
 WRITE_MACRO_VALUE(__UINT64_FMTo__); 
#endif
#ifdef __UINT64_FMTu__ 
 WRITE_MACRO_VALUE(__UINT64_FMTu__); 
#endif
#ifdef __UINT64_FMTx__ 
 WRITE_MACRO_VALUE(__UINT64_FMTx__); 
#endif
#ifdef __UINT64_MAX__ 
 WRITE_MACRO_VALUE(__UINT64_MAX__); 
#endif
#ifdef __UINT64_TYPE__ 
 WRITE_MACRO_VALUE(__UINT64_TYPE__); 
#endif
#ifdef __UINT8_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__UINT8_C_SUFFIX__); 
#endif
#ifdef __UINT8_FMTX__ 
 WRITE_MACRO_VALUE(__UINT8_FMTX__); 
#endif
#ifdef __UINT8_FMTo__ 
 WRITE_MACRO_VALUE(__UINT8_FMTo__); 
#endif
#ifdef __UINT8_FMTu__ 
 WRITE_MACRO_VALUE(__UINT8_FMTu__); 
#endif
#ifdef __UINT8_FMTx__ 
 WRITE_MACRO_VALUE(__UINT8_FMTx__); 
#endif
#ifdef __UINT8_MAX__ 
 WRITE_MACRO_VALUE(__UINT8_MAX__); 
#endif
#ifdef __UINT8_TYPE__ 
 WRITE_MACRO_VALUE(__UINT8_TYPE__); 
#endif
#ifdef __UINTMAX_C_SUFFIX__ 
 WRITE_MACRO_VALUE(__UINTMAX_C_SUFFIX__); 
#endif
#ifdef __UINTMAX_FMTX__ 
 WRITE_MACRO_VALUE(__UINTMAX_FMTX__); 
#endif
#ifdef __UINTMAX_FMTo__ 
 WRITE_MACRO_VALUE(__UINTMAX_FMTo__); 
#endif
#ifdef __UINTMAX_FMTu__ 
 WRITE_MACRO_VALUE(__UINTMAX_FMTu__); 
#endif
#ifdef __UINTMAX_FMTx__ 
 WRITE_MACRO_VALUE(__UINTMAX_FMTx__); 
#endif
#ifdef __UINTMAX_MAX__ 
 WRITE_MACRO_VALUE(__UINTMAX_MAX__); 
#endif
#ifdef __UINTMAX_TYPE__ 
 WRITE_MACRO_VALUE(__UINTMAX_TYPE__); 
#endif
#ifdef __UINTMAX_WIDTH__ 
 WRITE_MACRO_VALUE(__UINTMAX_WIDTH__); 
#endif
#ifdef __UINTPTR_FMTX__ 
 WRITE_MACRO_VALUE(__UINTPTR_FMTX__); 
#endif
#ifdef __UINTPTR_FMTo__ 
 WRITE_MACRO_VALUE(__UINTPTR_FMTo__); 
#endif
#ifdef __UINTPTR_FMTu__ 
 WRITE_MACRO_VALUE(__UINTPTR_FMTu__); 
#endif
#ifdef __UINTPTR_FMTx__ 
 WRITE_MACRO_VALUE(__UINTPTR_FMTx__); 
#endif
#ifdef __UINTPTR_MAX__ 
 WRITE_MACRO_VALUE(__UINTPTR_MAX__); 
#endif
#ifdef __UINTPTR_TYPE__ 
 WRITE_MACRO_VALUE(__UINTPTR_TYPE__); 
#endif
#ifdef __UINTPTR_WIDTH__ 
 WRITE_MACRO_VALUE(__UINTPTR_WIDTH__); 
#endif
#ifdef __UINT_FAST16_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_FAST16_FMTX__); 
#endif
#ifdef __UINT_FAST16_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_FAST16_FMTo__); 
#endif
#ifdef __UINT_FAST16_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_FAST16_FMTu__); 
#endif
#ifdef __UINT_FAST16_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_FAST16_FMTx__); 
#endif
#ifdef __UINT_FAST16_MAX__ 
 WRITE_MACRO_VALUE(__UINT_FAST16_MAX__); 
#endif
#ifdef __UINT_FAST16_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_FAST16_TYPE__); 
#endif
#ifdef __UINT_FAST32_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_FAST32_FMTX__); 
#endif
#ifdef __UINT_FAST32_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_FAST32_FMTo__); 
#endif
#ifdef __UINT_FAST32_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_FAST32_FMTu__); 
#endif
#ifdef __UINT_FAST32_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_FAST32_FMTx__); 
#endif
#ifdef __UINT_FAST32_MAX__ 
 WRITE_MACRO_VALUE(__UINT_FAST32_MAX__); 
#endif
#ifdef __UINT_FAST32_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_FAST32_TYPE__); 
#endif
#ifdef __UINT_FAST64_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_FAST64_FMTX__); 
#endif
#ifdef __UINT_FAST64_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_FAST64_FMTo__); 
#endif
#ifdef __UINT_FAST64_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_FAST64_FMTu__); 
#endif
#ifdef __UINT_FAST64_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_FAST64_FMTx__); 
#endif
#ifdef __UINT_FAST64_MAX__ 
 WRITE_MACRO_VALUE(__UINT_FAST64_MAX__); 
#endif
#ifdef __UINT_FAST64_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_FAST64_TYPE__); 
#endif
#ifdef __UINT_FAST8_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_FAST8_FMTX__); 
#endif
#ifdef __UINT_FAST8_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_FAST8_FMTo__); 
#endif
#ifdef __UINT_FAST8_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_FAST8_FMTu__); 
#endif
#ifdef __UINT_FAST8_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_FAST8_FMTx__); 
#endif
#ifdef __UINT_FAST8_MAX__ 
 WRITE_MACRO_VALUE(__UINT_FAST8_MAX__); 
#endif
#ifdef __UINT_FAST8_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_FAST8_TYPE__); 
#endif
#ifdef __UINT_LEAST16_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST16_FMTX__); 
#endif
#ifdef __UINT_LEAST16_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_LEAST16_FMTo__); 
#endif
#ifdef __UINT_LEAST16_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_LEAST16_FMTu__); 
#endif
#ifdef __UINT_LEAST16_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_LEAST16_FMTx__); 
#endif
#ifdef __UINT_LEAST16_MAX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST16_MAX__); 
#endif
#ifdef __UINT_LEAST16_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_LEAST16_TYPE__); 
#endif
#ifdef __UINT_LEAST32_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST32_FMTX__); 
#endif
#ifdef __UINT_LEAST32_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_LEAST32_FMTo__); 
#endif
#ifdef __UINT_LEAST32_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_LEAST32_FMTu__); 
#endif
#ifdef __UINT_LEAST32_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_LEAST32_FMTx__); 
#endif
#ifdef __UINT_LEAST32_MAX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST32_MAX__); 
#endif
#ifdef __UINT_LEAST32_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_LEAST32_TYPE__); 
#endif
#ifdef __UINT_LEAST64_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST64_FMTX__); 
#endif
#ifdef __UINT_LEAST64_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_LEAST64_FMTo__); 
#endif
#ifdef __UINT_LEAST64_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_LEAST64_FMTu__); 
#endif
#ifdef __UINT_LEAST64_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_LEAST64_FMTx__); 
#endif
#ifdef __UINT_LEAST64_MAX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST64_MAX__); 
#endif
#ifdef __UINT_LEAST64_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_LEAST64_TYPE__); 
#endif
#ifdef __UINT_LEAST8_FMTX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST8_FMTX__); 
#endif
#ifdef __UINT_LEAST8_FMTo__ 
 WRITE_MACRO_VALUE(__UINT_LEAST8_FMTo__); 
#endif
#ifdef __UINT_LEAST8_FMTu__ 
 WRITE_MACRO_VALUE(__UINT_LEAST8_FMTu__); 
#endif
#ifdef __UINT_LEAST8_FMTx__ 
 WRITE_MACRO_VALUE(__UINT_LEAST8_FMTx__); 
#endif
#ifdef __UINT_LEAST8_MAX__ 
 WRITE_MACRO_VALUE(__UINT_LEAST8_MAX__); 
#endif
#ifdef __UINT_LEAST8_TYPE__ 
 WRITE_MACRO_VALUE(__UINT_LEAST8_TYPE__); 
#endif
#ifdef __USER_LABEL_PREFIX__ 
 WRITE_MACRO_VALUE(__USER_LABEL_PREFIX__); 
#endif
#ifdef __VERSION__ 
 WRITE_MACRO_VALUE(__VERSION__); 
#endif
#ifdef __WCHAR_MAX__ 
 WRITE_MACRO_VALUE(__WCHAR_MAX__); 
#endif
#ifdef __WCHAR_TYPE__ 
 WRITE_MACRO_VALUE(__WCHAR_TYPE__); 
#endif
#ifdef __WCHAR_WIDTH__ 
 WRITE_MACRO_VALUE(__WCHAR_WIDTH__); 
#endif
#ifdef __WINT_MAX__ 
 WRITE_MACRO_VALUE(__WINT_MAX__); 
#endif
#ifdef __WINT_TYPE__ 
 WRITE_MACRO_VALUE(__WINT_TYPE__); 
#endif
#ifdef __WINT_WIDTH__ 
 WRITE_MACRO_VALUE(__WINT_WIDTH__); 
#endif
#ifdef __amd64 
 WRITE_MACRO_VALUE(__amd64); 
#endif
#ifdef __amd64__ 
 WRITE_MACRO_VALUE(__amd64__); 
#endif
#ifdef __clang__ 
 WRITE_MACRO_VALUE(__clang__); 
#endif
#ifdef __clang_major__ 
 WRITE_MACRO_VALUE(__clang_major__); 
#endif
#ifdef __clang_minor__ 
 WRITE_MACRO_VALUE(__clang_minor__); 
#endif
#ifdef __clang_patchlevel__ 
 WRITE_MACRO_VALUE(__clang_patchlevel__); 
#endif
#ifdef __clang_version__ 
 WRITE_MACRO_VALUE(__clang_version__); 
#endif
#ifdef __clang_literal_encoding__
 WRITE_MACRO_VALUE(__clang_literal_encoding__); 
#endif
#ifdef __clang_wide_literal_encoding__
 WRITE_MACRO_VALUE(__clang_wide_literal_encoding__); 
#endif
#ifdef __code_model_small_ 
 WRITE_MACRO_VALUE(__code_model_small_); 
#endif
#ifdef __k8 
 WRITE_MACRO_VALUE(__k8); 
#endif
#ifdef __k8__ 
 WRITE_MACRO_VALUE(__k8__); 
#endif
#ifdef __llvm__ 
 WRITE_MACRO_VALUE(__llvm__); 
#endif
#ifdef __pic__ 
 WRITE_MACRO_VALUE(__pic__); 
#endif
#ifdef __pie__ 
 WRITE_MACRO_VALUE(__pie__); 
#endif
#ifdef __seg_fs 
 WRITE_MACRO_VALUE(__seg_fs); 
#endif
#ifdef __seg_gs 
 WRITE_MACRO_VALUE(__seg_gs); 
#endif
#ifdef __tune_k8__ 
 WRITE_MACRO_VALUE(__tune_k8__); 
#endif
#ifdef __unix 
 WRITE_MACRO_VALUE(__unix); 
#endif
#ifdef __unix__ 
 WRITE_MACRO_VALUE(__unix__); 
#endif
#ifdef __x86_64 
 WRITE_MACRO_VALUE(__x86_64); 
#endif
#ifdef __x86_64__ 
 WRITE_MACRO_VALUE(__x86_64__); 
#endif
#ifdef unix 
 WRITE_MACRO_VALUE(unix); 
#endif

}; 


void print_misc3(void) { 
#ifdef _PTHREADS
 WRITE_MACRO_VALUE(_PTHREADS); 
#endif

#if defined(__BOUNDS_CHECKING_ON)
 WRITE_MACRO_VALUE(__BOUNDS_CHECKING_ON); 
#endif

#if defined(__BASE_FILE__)
 WRITE_MACRO_VALUE(__BASE_FILE__); 
#endif

#if defined(__FILE__)
 WRITE_MACRO_VALUE(__FILE__); 
#endif

#if defined(__FILE_NAME__)
 WRITE_MACRO_VALUE(__FILE_NAME__); 
#endif

#if defined(__LINE__)
 WRITE_MACRO_VALUE(__LINE__); 
#endif

#if defined(__TIMESTAMP__)
 WRITE_MACRO_VALUE(__TIMESTAMP__); 
#endif

#if defined(__COUNTER__)
 WRITE_MACRO_VALUE(__COUNTER__); 
#endif

#if defined(__INCLUDE_LEVEL__)
 WRITE_MACRO_VALUE(__INCLUDE_LEVEL__); 
#endif

#if defined(__GFORTRAN__)
 WRITE_MACRO_VALUE(__GFORTRAN__); 
#endif

#if defined(__GNUG__)
 WRITE_MACRO_VALUE(__GNUG__); 
#endif

#if defined(__STRICT_ANSI__)
 WRITE_MACRO_VALUE(__STRICT_ANSI__); 
#endif

#if defined(__ELF__)
 WRITE_MACRO_VALUE(__ELF__); 
#endif

#if defined(__VERSION__)
 WRITE_MACRO_VALUE(__VERSION__); 
#endif

#if defined(__OPTIMIZE__)
 WRITE_MACRO_VALUE(__OPTIMIZE__); 
#endif

#if defined(__OPTIMIZE_SIZE__)
 WRITE_MACRO_VALUE(__OPTIMIZE_SIZE__); 
#endif

#if defined(__NO_INLINE__)
 WRITE_MACRO_VALUE(__NO_INLINE__); 
#endif

#if defined(__GNUC_GNU_INLINE__)
 WRITE_MACRO_VALUE(__GNUC_GNU_INLINE__); 
#endif

#if defined(__GNUC_STDC_INLINE__)
 WRITE_MACRO_VALUE(__GNUC_STDC_INLINE__); 
#endif

#if defined(__CHAR_UNSIGNED__)
 WRITE_MACRO_VALUE(__CHAR_UNSIGNED__); 
#endif

#if defined(__WCHAR_UNSIGNED__)
 WRITE_MACRO_VALUE(__WCHAR_UNSIGNED__); 
#endif

#if defined(__REGISTER_PREFIX__)
 WRITE_MACRO_VALUE(__REGISTER_PREFIX__); 
#endif

#if defined(__USER_LABEL_PREFIX__)
 WRITE_MACRO_VALUE(__USER_LABEL_PREFIX__); 
#endif

#if defined(__SIZE_TYPE__)
 WRITE_MACRO_VALUE(__SIZE_TYPE__); 
#endif

#if defined(__PTRDIFF_TYPE__)
 WRITE_MACRO_VALUE(__PTRDIFF_TYPE__); 
#endif

#if defined(__WCHAR_TYPE__)
 WRITE_MACRO_VALUE(__WCHAR_TYPE__); 
#endif

#if defined(__WINT_TYPE__)
 WRITE_MACRO_VALUE(__WINT_TYPE__); 
#endif

#if defined(__INTMAX_TYPE__)
 WRITE_MACRO_VALUE(__INTMAX_TYPE__); 
#endif

#if defined(__UINTMAX_TYPE__)
 WRITE_MACRO_VALUE(__UINTMAX_TYPE__); 
#endif

#if defined(__SIG_ATOMIC_TYPE__)
 WRITE_MACRO_VALUE(__SIG_ATOMIC_TYPE__); 
#endif

#if defined(__INT8_TYPE__)
 WRITE_MACRO_VALUE(__INT8_TYPE__); 
#endif

#if defined(__INT16_TYPE__)
 WRITE_MACRO_VALUE(__INT16_TYPE__); 
#endif

#if defined(__INT32_TYPE__)
 WRITE_MACRO_VALUE(__INT32_TYPE__); 
#endif

#if defined(__INT64_TYPE__)
 WRITE_MACRO_VALUE(__INT64_TYPE__); 
#endif

#if defined(__UINT8_TYPE__)
 WRITE_MACRO_VALUE(__UINT8_TYPE__); 
#endif

#if defined(__UINT16_TYPE__)
 WRITE_MACRO_VALUE(__UINT16_TYPE__); 
#endif

#if defined(__UINT32_TYPE__)
 WRITE_MACRO_VALUE(__UINT32_TYPE__); 
#endif

#if defined(__UINT64_TYPE__)
 WRITE_MACRO_VALUE(__UINT64_TYPE__); 
#endif

#if defined(__INT_LEAST8_TYPE__)
 WRITE_MACRO_VALUE(__INT_LEAST8_TYPE__); 
#endif

#if defined(__INT_LEAST16_TYPE__)
 WRITE_MACRO_VALUE(__INT_LEAST16_TYPE__); 
#endif

#if defined(__INT_LEAST32_TYPE__)
 WRITE_MACRO_VALUE(__INT_LEAST32_TYPE__); 
#endif

#if defined(__INT_LEAST64_TYPE__)
 WRITE_MACRO_VALUE(__INT_LEAST64_TYPE__); 
#endif

#if defined(__UINT_LEAST8_TYPE__)
 WRITE_MACRO_VALUE(__UINT_LEAST8_TYPE__); 
#endif

#if defined(__UINT_LEAST16_TYPE__)
 WRITE_MACRO_VALUE(__UINT_LEAST16_TYPE__); 
#endif

#if defined(__UINT_LEAST32_TYPE__)
 WRITE_MACRO_VALUE(__UINT_LEAST32_TYPE__); 
#endif

#if defined(__UINT_LEAST64_TYPE__)
 WRITE_MACRO_VALUE(__UINT_LEAST64_TYPE__); 
#endif

#if defined(__INT_FAST8_TYPE__)
 WRITE_MACRO_VALUE(__INT_FAST8_TYPE__); 
#endif

#if defined(__INT_FAST16_TYPE__)
 WRITE_MACRO_VALUE(__INT_FAST16_TYPE__); 
#endif

#if defined(__INT_FAST32_TYPE__)
 WRITE_MACRO_VALUE(__INT_FAST32_TYPE__); 
#endif

#if defined(__INT_FAST64_TYPE__)
 WRITE_MACRO_VALUE(__INT_FAST64_TYPE__); 
#endif

#if defined(__UINT_FAST8_TYPE__)
 WRITE_MACRO_VALUE(__UINT_FAST8_TYPE__); 
#endif

#if defined(__UINT_FAST16_TYPE__)
 WRITE_MACRO_VALUE(__UINT_FAST16_TYPE__); 
#endif

#if defined(__UINT_FAST32_TYPE__)
 WRITE_MACRO_VALUE(__UINT_FAST32_TYPE__); 
#endif

#if defined(__UINT_FAST64_TYPE__)
 WRITE_MACRO_VALUE(__UINT_FAST64_TYPE__); 
#endif

#if defined(__INTPTR_TYPE__)
 WRITE_MACRO_VALUE(__INTPTR_TYPE__); 
#endif

#if defined(__UINTPTR_TYPE__)
 WRITE_MACRO_VALUE(__UINTPTR_TYPE__); 
#endif

#if defined(__CHAR_BIT__)
 WRITE_MACRO_VALUE(__CHAR_BIT__); 
#endif

#if defined(__SCHAR_MAX__)
 WRITE_MACRO_VALUE(__SCHAR_MAX__); 
#endif

#if defined(__WCHAR_MAX__)
 WRITE_MACRO_VALUE(__WCHAR_MAX__); 
#endif

#if defined(__SHRT_MAX__)
 WRITE_MACRO_VALUE(__SHRT_MAX__); 
#endif

#if defined(__INT_MAX__)
 WRITE_MACRO_VALUE(__INT_MAX__); 
#endif

#if defined(__LONG_MAX__)
 WRITE_MACRO_VALUE(__LONG_MAX__); 
#endif

#if defined(__LONG_LONG_MAX__)
 WRITE_MACRO_VALUE(__LONG_LONG_MAX__); 
#endif

#if defined(__WINT_MAX__)
 WRITE_MACRO_VALUE(__WINT_MAX__); 
#endif

#if defined(__SIZE_MAX__)
 WRITE_MACRO_VALUE(__SIZE_MAX__); 
#endif

#if defined(__PTRDIFF_MAX__)
 WRITE_MACRO_VALUE(__PTRDIFF_MAX__); 
#endif

#if defined(__INTMAX_MAX__)
 WRITE_MACRO_VALUE(__INTMAX_MAX__); 
#endif

#if defined(__UINTMAX_MAX__)
 WRITE_MACRO_VALUE(__UINTMAX_MAX__); 
#endif

#if defined(__SIG_ATOMIC_MAX__)
 WRITE_MACRO_VALUE(__SIG_ATOMIC_MAX__); 
#endif

#if defined(__INT8_MAX__)
 WRITE_MACRO_VALUE(__INT8_MAX__); 
#endif

#if defined(__INT16_MAX__)
 WRITE_MACRO_VALUE(__INT16_MAX__); 
#endif

#if defined(__INT32_MAX__)
 WRITE_MACRO_VALUE(__INT32_MAX__); 
#endif

#if defined(__INT64_MAX__)
 WRITE_MACRO_VALUE(__INT64_MAX__); 
#endif

#if defined(__UINT8_MAX__)
 WRITE_MACRO_VALUE(__UINT8_MAX__); 
#endif

#if defined(__UINT16_MAX__)
 WRITE_MACRO_VALUE(__UINT16_MAX__); 
#endif

#if defined(__UINT32_MAX__)
 WRITE_MACRO_VALUE(__UINT32_MAX__); 
#endif

#if defined(__UINT64_MAX__)
 WRITE_MACRO_VALUE(__UINT64_MAX__); 
#endif

#if defined(__INT_LEAST8_MAX__)
 WRITE_MACRO_VALUE(__INT_LEAST8_MAX__); 
#endif

#if defined(__INT_LEAST16_MAX__)
 WRITE_MACRO_VALUE(__INT_LEAST16_MAX__); 
#endif

#if defined(__INT_LEAST32_MAX__)
 WRITE_MACRO_VALUE(__INT_LEAST32_MAX__); 
#endif

#if defined(__INT_LEAST64_MAX__)
 WRITE_MACRO_VALUE(__INT_LEAST64_MAX__); 
#endif

#if defined(__UINT_LEAST8_MAX__)
 WRITE_MACRO_VALUE(__UINT_LEAST8_MAX__); 
#endif

#if defined(__UINT_LEAST16_MAX__)
 WRITE_MACRO_VALUE(__UINT_LEAST16_MAX__); 
#endif

#if defined(__UINT_LEAST32_MAX__)
 WRITE_MACRO_VALUE(__UINT_LEAST32_MAX__); 
#endif

#if defined(__UINT_LEAST64_MAX__)
 WRITE_MACRO_VALUE(__UINT_LEAST64_MAX__); 
#endif

#if defined(__INT_FAST8_MAX__)
 WRITE_MACRO_VALUE(__INT_FAST8_MAX__); 
#endif

#if defined(__INT_FAST16_MAX__)
 WRITE_MACRO_VALUE(__INT_FAST16_MAX__); 
#endif

#if defined(__INT_FAST32_MAX__)
 WRITE_MACRO_VALUE(__INT_FAST32_MAX__); 
#endif

#if defined(__INT_FAST64_MAX__)
 WRITE_MACRO_VALUE(__INT_FAST64_MAX__); 
#endif

#if defined(__UINT_FAST8_MAX__)
 WRITE_MACRO_VALUE(__UINT_FAST8_MAX__); 
#endif

#if defined(__UINT_FAST16_MAX__)
 WRITE_MACRO_VALUE(__UINT_FAST16_MAX__); 
#endif

#if defined(__UINT_FAST32_MAX__)
 WRITE_MACRO_VALUE(__UINT_FAST32_MAX__); 
#endif

#if defined(__UINT_FAST64_MAX__)
 WRITE_MACRO_VALUE(__UINT_FAST64_MAX__); 
#endif

#if defined(__INTPTR_MAX__)
 WRITE_MACRO_VALUE(__INTPTR_MAX__); 
#endif

#if defined(__UINTPTR_MAX__)
 WRITE_MACRO_VALUE(__UINTPTR_MAX__); 
#endif

#if defined(__SCHAR_MIN__)
 WRITE_MACRO_VALUE(__SCHAR_MIN__); 
#endif

#if defined(__WCHAR_MIN__)
 WRITE_MACRO_VALUE(__WCHAR_MIN__); 
#endif

#if defined(__SHRT_MIN__)
 WRITE_MACRO_VALUE(__SHRT_MIN__); 
#endif

#if defined(__INT_MIN__)
 WRITE_MACRO_VALUE(__INT_MIN__); 
#endif

#if defined(__LONG_MIN__)
 WRITE_MACRO_VALUE(__LONG_MIN__); 
#endif

#if defined(__LONG_LONG_MIN__)
 WRITE_MACRO_VALUE(__LONG_LONG_MIN__); 
#endif

#if defined(__WINT_MIN__)
 WRITE_MACRO_VALUE(__WINT_MIN__); 
#endif

#if defined(__SIZE_MIN__)
 WRITE_MACRO_VALUE(__SIZE_MIN__); 
#endif

#if defined(__PTRDIFF_MIN__)
 WRITE_MACRO_VALUE(__PTRDIFF_MIN__); 
#endif

#if defined(__INTMIN_MIN__)
 WRITE_MACRO_VALUE(__INTMIN_MIN__); 
#endif

#if defined(__UINTMIN_MIN__)
 WRITE_MACRO_VALUE(__UINTMIN_MIN__); 
#endif

#if defined(__SIG_ATOMIC_MIN__)
 WRITE_MACRO_VALUE(__SIG_ATOMIC_MIN__); 
#endif

#if defined(__INT8_MIN__)
 WRITE_MACRO_VALUE(__INT8_MIN__); 
#endif

#if defined(__INT16_MIN__)
 WRITE_MACRO_VALUE(__INT16_MIN__); 
#endif

#if defined(__INT32_MIN__)
 WRITE_MACRO_VALUE(__INT32_MIN__); 
#endif

#if defined(__INT64_MIN__)
 WRITE_MACRO_VALUE(__INT64_MIN__); 
#endif

#if defined(__UINT8_MIN__)
 WRITE_MACRO_VALUE(__UINT8_MIN__); 
#endif

#if defined(__UINT16_MIN__)
 WRITE_MACRO_VALUE(__UINT16_MIN__); 
#endif

#if defined(__UINT32_MIN__)
 WRITE_MACRO_VALUE(__UINT32_MIN__); 
#endif

#if defined(__UINT64_MIN__)
 WRITE_MACRO_VALUE(__UINT64_MIN__); 
#endif

#if defined(__INT_LEAST8_MIN__)
 WRITE_MACRO_VALUE(__INT_LEAST8_MIN__); 
#endif

#if defined(__INT_LEAST16_MIN__)
 WRITE_MACRO_VALUE(__INT_LEAST16_MIN__); 
#endif

#if defined(__INT_LEAST32_MIN__)
 WRITE_MACRO_VALUE(__INT_LEAST32_MIN__); 
#endif

#if defined(__INT_LEAST64_MIN__)
 WRITE_MACRO_VALUE(__INT_LEAST64_MIN__); 
#endif

#if defined(__UINT_LEAST8_MIN__)
 WRITE_MACRO_VALUE(__UINT_LEAST8_MIN__); 
#endif

#if defined(__UINT_LEAST16_MIN__)
 WRITE_MACRO_VALUE(__UINT_LEAST16_MIN__); 
#endif

#if defined(__UINT_LEAST32_MIN__)
 WRITE_MACRO_VALUE(__UINT_LEAST32_MIN__); 
#endif

#if defined(__UINT_LEAST64_MIN__)
 WRITE_MACRO_VALUE(__UINT_LEAST64_MIN__); 
#endif

#if defined(__INT_FAST8_MIN__)
 WRITE_MACRO_VALUE(__INT_FAST8_MIN__); 
#endif

#if defined(__INT_FAST16_MIN__)
 WRITE_MACRO_VALUE(__INT_FAST16_MIN__); 
#endif

#if defined(__INT_FAST32_MIN__)
 WRITE_MACRO_VALUE(__INT_FAST32_MIN__); 
#endif

#if defined(__INT_FAST64_MIN__)
 WRITE_MACRO_VALUE(__INT_FAST64_MIN__); 
#endif

#if defined(__UINT_FAST8_MIN__)
 WRITE_MACRO_VALUE(__UINT_FAST8_MIN__); 
#endif

#if defined(__UINT_FAST16_MIN__)
 WRITE_MACRO_VALUE(__UINT_FAST16_MIN__); 
#endif

#if defined(__UINT_FAST32_MIN__)
 WRITE_MACRO_VALUE(__UINT_FAST32_MIN__); 
#endif

#if defined(__UINT_FAST64_MIN__)
 WRITE_MACRO_VALUE(__UINT_FAST64_MIN__); 
#endif

#if defined(__INTPTR_MIN__)
 WRITE_MACRO_VALUE(__INTPTR_MIN__); 
#endif

#if defined(__UINTPTR_MIN__)
 WRITE_MACRO_VALUE(__UINTPTR_MIN__); 
#endif

#if defined(__INT8_C)
 WRITE_MACRO_VALUE(__INT8_C); 
#endif

#if defined(__INT16_C)
 WRITE_MACRO_VALUE(__INT16_C); 
#endif

#if defined(__INT32_C)
 WRITE_MACRO_VALUE(__INT32_C); 
#endif

#if defined(__INT64_C)
 WRITE_MACRO_VALUE(__INT64_C); 
#endif

#if defined(__UINT8_C)
 WRITE_MACRO_VALUE(__UINT8_C); 
#endif

#if defined(__UINT16_C)
 WRITE_MACRO_VALUE(__UINT16_C); 
#endif

#if defined(__UINT32_C)
 WRITE_MACRO_VALUE(__UINT32_C); 
#endif

#if defined(__UINT64_C)
 WRITE_MACRO_VALUE(__UINT64_C); 
#endif

#if defined(__INTMAX_C)
 WRITE_MACRO_VALUE(__INTMAX_C); 
#endif

#if defined(__UINTMAX_C)
 WRITE_MACRO_VALUE(__UINTMAX_C); 
#endif

#if defined(__SCHAR_WIDTH__)
 WRITE_MACRO_VALUE(__SCHAR_WIDTH__); 
#endif

#if defined(__WCHAR_WIDTH__)
 WRITE_MACRO_VALUE(__WCHAR_WIDTH__); 
#endif

#if defined(__SHRT_WIDTH__)
 WRITE_MACRO_VALUE(__SHRT_WIDTH__); 
#endif

#if defined(__INT_WIDTH__)
 WRITE_MACRO_VALUE(__INT_WIDTH__); 
#endif

#if defined(__WINT_WIDTH__)
 WRITE_MACRO_VALUE(__WINT_WIDTH__); 
#endif

#if defined(__LONG_WIDTH__)
 WRITE_MACRO_VALUE(__LONG_WIDTH__); 
#endif

#if defined(__LONG_LONG_WIDTH__)
 WRITE_MACRO_VALUE(__LONG_LONG_WIDTH__); 
#endif

#if defined(__PTRDIFF_WIDTH__)
 WRITE_MACRO_VALUE(__PTRDIFF_WIDTH__); 
#endif

#if defined(__SIG_ATOMIC_WIDTH__)
 WRITE_MACRO_VALUE(__SIG_ATOMIC_WIDTH__); 
#endif

#if defined(__SIZE_WIDTH__)
 WRITE_MACRO_VALUE(__SIZE_WIDTH__); 
#endif

#if defined(__INT_LEAST8_WIDTH__)
 WRITE_MACRO_VALUE(__INT_LEAST8_WIDTH__); 
#endif

#if defined(__INT_LEAST16_WIDTH__)
 WRITE_MACRO_VALUE(__INT_LEAST16_WIDTH__); 
#endif

#if defined(__INT_LEAST32_WIDTH__)
 WRITE_MACRO_VALUE(__INT_LEAST32_WIDTH__); 
#endif

#if defined(__INT_LEAST64_WIDTH__)
 WRITE_MACRO_VALUE(__INT_LEAST64_WIDTH__); 
#endif

#if defined(__UINT_LEAST8_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_LEAST8_WIDTH__); 
#endif

#if defined(__UINT_LEAST16_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_LEAST16_WIDTH__); 
#endif

#if defined(__UINT_LEAST32_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_LEAST32_WIDTH__); 
#endif

#if defined(__UINT_LEAST64_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_LEAST64_WIDTH__); 
#endif

#if defined(__INT_FAST8_WIDTH__)
 WRITE_MACRO_VALUE(__INT_FAST8_WIDTH__); 
#endif

#if defined(__INT_FAST16_WIDTH__)
 WRITE_MACRO_VALUE(__INT_FAST16_WIDTH__); 
#endif

#if defined(__INT_FAST32_WIDTH__)
 WRITE_MACRO_VALUE(__INT_FAST32_WIDTH__); 
#endif

#if defined(__INT_FAST64_WIDTH__)
 WRITE_MACRO_VALUE(__INT_FAST64_WIDTH__); 
#endif

#if defined(__UINT_FAST8_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_FAST8_WIDTH__); 
#endif

#if defined(__UINT_FAST16_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_FAST16_WIDTH__); 
#endif

#if defined(__UINT_FAST32_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_FAST32_WIDTH__); 
#endif

#if defined(__UINT_FAST64_WIDTH__)
 WRITE_MACRO_VALUE(__UINT_FAST64_WIDTH__); 
#endif

#if defined(__INTPTR_WIDTH__)
 WRITE_MACRO_VALUE(__INTPTR_WIDTH__); 
#endif

#if defined(__UINTPTR_WIDTH__)
 WRITE_MACRO_VALUE(__UINTPTR_WIDTH__); 
#endif

#if defined(__INTMAX_WIDTH__)
 WRITE_MACRO_VALUE(__INTMAX_WIDTH__); 
#endif

#if defined(__UINTMAX_WIDTH__)
 WRITE_MACRO_VALUE(__UINTMAX_WIDTH__); 
#endif

#if defined(__SIZEOF_SHORT__)
 WRITE_MACRO_VALUE(__SIZEOF_SHORT__); 
#endif

#if defined(__SIZEOF_INT__)
 WRITE_MACRO_VALUE(__SIZEOF_INT__); 
#endif

#if defined(__SIZEOF_WINT__)
 WRITE_MACRO_VALUE(__SIZEOF_WINT__); 
#endif

#if defined(__SIZEOF_LONG__)
 WRITE_MACRO_VALUE(__SIZEOF_LONG__); 
#endif

#if defined(__SIZEOF_LONG_LONG__)
 WRITE_MACRO_VALUE(__SIZEOF_LONG_LONG__); 
#endif

#if defined(__SIZEOF_POINTER__)
 WRITE_MACRO_VALUE(__SIZEOF_POINTER__); 
#endif

#if defined(__SIZEOF_FLOAT__)
 WRITE_MACRO_VALUE(__SIZEOF_FLOAT__); 
#endif

#if defined(__SIZEOF_DOUBLE__)
 WRITE_MACRO_VALUE(__SIZEOF_DOUBLE__); 
#endif

#if defined(__SIZEOF_LONG_DOUBLE__)
 WRITE_MACRO_VALUE(__SIZEOF_LONG_DOUBLE__); 
#endif

#if defined(__SIZEOF_SIZE_T__)
 WRITE_MACRO_VALUE(__SIZEOF_SIZE_T__); 
#endif

#if defined(__SIZEOF_WCHAR_T__)
 WRITE_MACRO_VALUE(__SIZEOF_WCHAR_T__); 
#endif

#if defined(__SIZEOF_WINT_T__)
 WRITE_MACRO_VALUE(__SIZEOF_WINT_T__); 
#endif

#if defined(__SIZEOF_PTRDIFF_T__)
 WRITE_MACRO_VALUE(__SIZEOF_PTRDIFF_T__); 
#endif

#if defined(__BYTE_ORDER__)
 WRITE_MACRO_VALUE(__BYTE_ORDER__); 
#endif

#if defined(__ORDER_LITTLE_ENDIAN__)
 WRITE_MACRO_VALUE(__ORDER_LITTLE_ENDIAN__); 
#endif

#if defined(__ORDER_BIG_ENDIAN__)
 WRITE_MACRO_VALUE(__ORDER_BIG_ENDIAN__); 
#endif

#if defined(__ORDER_PDP_ENDIAN__)
 WRITE_MACRO_VALUE(__ORDER_PDP_ENDIAN__); 
#endif

#if defined(__FLOAT_WORD_ORDER__)
 WRITE_MACRO_VALUE(__FLOAT_WORD_ORDER__); 
#endif

#if defined(__DEPRECATED)
 WRITE_MACRO_VALUE(__DEPRECATED); 
#endif

#if defined(__EXCEPTIONS)
 WRITE_MACRO_VALUE(__EXCEPTIONS); 
#endif

#if defined(__GXX_RTTI)
 WRITE_MACRO_VALUE(__GXX_RTTI); 
#endif

#if defined(__USING_SJLJ_EXCEPTIONS__)
 WRITE_MACRO_VALUE(__USING_SJLJ_EXCEPTIONS__); 
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__)
 WRITE_MACRO_VALUE(__GXX_EXPERIMENTAL_CXX0X__); 
#endif

#if defined(__GXX_WEAK__)
 WRITE_MACRO_VALUE(__GXX_WEAK__); 
#endif

#if defined(__NEXT_RUNTIME__)
 WRITE_MACRO_VALUE(__NEXT_RUNTIME__); 
#endif

#if defined(__LP64__)
 WRITE_MACRO_VALUE(__LP64__); 
#endif

#if defined(_LP64)
 WRITE_MACRO_VALUE(_LP64); 
#endif

#if defined(__SSP__)
 WRITE_MACRO_VALUE(__SSP__); 
#endif

#if defined(__SSP_ALL__)
 WRITE_MACRO_VALUE(__SSP_ALL__); 
#endif

#if defined(__SSP_STRONG__)
 WRITE_MACRO_VALUE(__SSP_STRONG__); 
#endif

#if defined(__SSP_EXPLICIT__)
 WRITE_MACRO_VALUE(__SSP_EXPLICIT__); 
#endif

#if defined(__SSP_EXPLICIT__)
 WRITE_MACRO_VALUE(__SSP_EXPLICIT__); 
#endif

#if defined(__SANITIZE_ADDRESS__)
 WRITE_MACRO_VALUE(__SANITIZE_ADDRESS__); 
#endif

#if defined(__SANITIZE_THREAD__)
 WRITE_MACRO_VALUE(__SANITIZE_THREAD__); 
#endif

#if defined(__TIMESTAMP__)
 WRITE_MACRO_VALUE(__TIMESTAMP__); 
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1); 
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2); 
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4); 
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8); 
#endif

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
 WRITE_MACRO_VALUE(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16); 
#endif

#if defined(__HAVE_SPECULATION_SAFE_VALUE)
 WRITE_MACRO_VALUE(__HAVE_SPECULATION_SAFE_VALUE); 
#endif

#if defined(__GCC_HAVE_DWARF2_CFI_ASM)
 WRITE_MACRO_VALUE(__GCC_HAVE_DWARF2_CFI_ASM); 
#endif

#if defined(__FP_FAST_FMA)
 WRITE_MACRO_VALUE(__FP_FAST_FMA); 
#endif

#if defined(__FP_FAST_FMAF)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF); 
#endif

#if defined(__FP_FAST_FMAL)
 WRITE_MACRO_VALUE(__FP_FAST_FMAL); 
#endif

#if defined(__FP_FAST_FMAF16)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF16); 
#endif

#if defined(__FP_FAST_FMAF32)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF32); 
#endif

#if defined(__FP_FAST_FMAF64)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF64); 
#endif

#if defined(__FP_FAST_FMAF128)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF128); 
#endif

#if defined(__FP_FAST_FMAF32X)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF32X); 
#endif

#if defined(__FP_FAST_FMAF64X)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF64X); 
#endif

#if defined(__FP_FAST_FMAF128X)
 WRITE_MACRO_VALUE(__FP_FAST_FMAF128X); 
#endif

#if defined(__STDC_WANT_IEC_60559_TYPES_EXT__)
 WRITE_MACRO_VALUE(__STDC_WANT_IEC_60559_TYPES_EXT__); 
#endif

#if defined(__GCC_IEC_559)
 WRITE_MACRO_VALUE(__GCC_IEC_559); 
#endif

#if defined(__GCC_IEC_559_COMPLEX)
 WRITE_MACRO_VALUE(__GCC_IEC_559_COMPLEX); 
#endif

#if defined(__NO_MATH_ERRNO__)
 WRITE_MACRO_VALUE(__NO_MATH_ERRNO__); 
#endif

#if defined(__RECIPROCAL_MATH__)
 WRITE_MACRO_VALUE(__RECIPROCAL_MATH__); 
#endif

#if defined(__NO_SIGNED_ZEROS__)
 WRITE_MACRO_VALUE(__NO_SIGNED_ZEROS__); 
#endif

#if defined(__NO_TRAPPING_MATH__)
 WRITE_MACRO_VALUE(__NO_TRAPPING_MATH__); 
#endif

#if defined(__ASSOCIATIVE_MATH__)
 WRITE_MACRO_VALUE(__ASSOCIATIVE_MATH__); 
#endif

#if defined(__ROUNDING_MATH__)
 WRITE_MACRO_VALUE(__ROUNDING_MATH__); 
#endif

#if defined(__GNUC_EXECUTION_CHARSET_NAME)
 WRITE_MACRO_VALUE(__GNUC_EXECUTION_CHARSET_NAME); 
#endif

#if defined(__GNUC_WIDE_EXECUTION_CHARSET_NAME)
 WRITE_MACRO_VALUE(__GNUC_WIDE_EXECUTION_CHARSET_NAME); 
#endif

#if defined(__FILE__)
 WRITE_MACRO_VALUE(__FILE__); 
#endif

#if defined(__LINE__)
 WRITE_MACRO_VALUE(__LINE__); 
#endif

#if defined(__func__)
 WRITE_MACRO_VALUE(__func__); 
#endif

#if defined(__FUNCTION__)
 WRITE_MACRO_VALUE(__FUNCTION__); 
#endif

#if defined(__DATE__)
 WRITE_MACRO_VALUE(__DATE__); 
#endif

#if defined(__TIME__)
 WRITE_MACRO_VALUE(__TIME__); 
#endif

#if defined(__STDC__)
 WRITE_MACRO_VALUE(__STDC__); 
#endif

#if defined(__STDC_VERSION__)
 WRITE_MACRO_VALUE(__STDC_VERSION__); 
#endif

#if defined(__STDC_HOSTED__)
 WRITE_MACRO_VALUE(__STDC_HOSTED__); 
#endif

#if defined(__cplusplus)
 WRITE_MACRO_VALUE(__cplusplus); 
#endif

#if defined(__OBJC__)
 WRITE_MACRO_VALUE(__OBJC__); 
#endif

#if defined(__ASSEMBLER__)
 WRITE_MACRO_VALUE(__ASSEMBLER__); 
#endif
}; 


