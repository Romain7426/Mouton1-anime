#include <stdio.h>

extern int main(void);

#define STRING(s) STRINGX(s)
#define STRINGX(s) #s


int main(void) {
#ifdef __GNUC_PATCHLEVEL__
  printf("%s\n", STRING(__GNUC_PATCHLEVEL__));
  return 0;
#else
  return 1;
#endif
}


