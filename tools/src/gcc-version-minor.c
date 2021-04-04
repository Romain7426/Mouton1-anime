#include <stdio.h>

extern int main(void);

#define STRING(s) STRINGX(s)
#define STRINGX(s) #s


int main(void) {
#ifdef __GNUC_MINOR__
  printf("%s\n", STRING(__GNUC_MINOR__));
  return 0;
#else
  return 1;
#endif
}


