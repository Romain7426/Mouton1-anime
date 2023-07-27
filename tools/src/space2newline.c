#include <stdio.h>

#define true (0 == 0)

static int c;


int main(void) {
  do {
    c = getchar();
    if (c == EOF) { putchar('\n'); return 0; }
    if (c == ' ') putchar('\n');
    else putchar(c);
  } while (true);
}

