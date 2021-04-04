#include <stdio.h>
#include <assert.h>
//#  include <machine/endian.h> 
//#  include <sys/endian.h> 
//#  include <endian.h> 
/* *** machine/endian.h ***
 * 
 * Definitions for byte order, according to byte significance from low address to high.
 * 
 * #define	LITTLE_ENDIAN	1234	// LSB first: i386, vax 
 * #define	BIG_ENDIAN	4321	// MSB first: 68000, ibm, net, ppc
 * #define	PDP_ENDIAN	3412	// LSB first in word, MSW first in long
 * 
 * #define	BYTE_ORDER	BIG_ENDIAN
 */

#define LIBPROG_STRINGX(s) #s
#define LIBPROG_STRING(s) LIBPROG_STRINGX(s)


union swpp {
  unsigned short int u16;
  unsigned char u8[2];
};


#define TEST_SIZEOF(type_t,taille)                                      \
  {static int test_array[((sizeof (type_t)) == (taille)) ? 1 : -1];}



int main(void) {
  TEST_SIZEOF(union swpp,2);
  TEST_SIZEOF(unsigned short int,2);
  TEST_SIZEOF(unsigned char,1);

#if 0
  printf("sizeof 'swpp' = %u\n", (unsigned int) (sizeof (union swpp)));
  printf("sizeof 'unsigned short int' = %u\n", (unsigned int) (sizeof (unsigned short int)));
  printf("sizeof 'unsigned char' = %u\n", (unsigned int) (sizeof (unsigned char)));
  printf("BYTE_ORDER = %s\n", LIBPROG_STRING(BYTE_ORDER));
#endif

  union swpp p;
  p.u16 = 0;
  p.u8[0] = 0;
  p.u8[1] = 0;

  p.u16 = 1;

#if 0
  printf("p.u16 = %u\n", (unsigned int) p.u16);
  printf("p.u8[0] = %u\n", (unsigned int) p.u8[0]);
  printf("p.u8[1] = %u\n", (unsigned int) p.u8[1]);
#endif

  if ((0 == p.u8[0]) && (0 == p.u8[1])) {
    printf("error\n");
    return 1;
  }

  if (0 != p.u8[0])
    printf("little\n");
  else
    printf("big\n");

  return 0;
}
