#include <stdio.h>

//extern int main(void);

#define STRING(s) STRINGX(s)
#define STRINGX(s) #s


//int main(void) {
int main(int argc, char * * argv) {
#ifdef __GNUC__
  printf("%s\n", STRING(__GNUC__));
  return 0;
#else
  return 1;
#endif
}


