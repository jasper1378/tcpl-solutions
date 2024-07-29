#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#define exp2(arg_) pow(2, (arg_))

#define RANGE_MIN(type_) ((type_)(-exp2(sizeof(type_) * CHAR_BIT)))
#define RANGE_MAX(type_) ((type_)(exp2(sizeof(type_) * CHAR_BIT) - 1))

int main() {
  printf("using headers:\n");
  printf("char: %d - %d\n", SCHAR_MIN, SCHAR_MAX);
  printf("uchar: %u - %u\n", 0, UCHAR_MAX);
  printf("short: %hd - %hd\n", SHRT_MIN, SHRT_MAX);
  printf("ushort: %hu - %hu\n", 0, USHRT_MAX);
  printf("int: %d - %d\n", INT_MIN, INT_MAX);
  printf("uint: %u - %u\n", 0, UINT_MAX);
  printf("long: %ld - %ld\n", LONG_MIN, LONG_MAX);
  printf("ulong: %lu - %lu\n", 0ul, ULONG_MAX);
  printf("float: %e - %e\n", FLT_MIN, FLT_MAX);
  printf("double: %e - %e\n", DBL_MIN, DBL_MAX);

  putchar('\n');

  printf("by computation:\n");
  printf("char: %d - %d\n", RANGE_MIN(char), RANGE_MAX(char));
  printf("uchar: %u - %u\n", RANGE_MIN(unsigned char),
         RANGE_MAX(unsigned char));
  printf("short: %hd - %hd\n", RANGE_MIN(short), RANGE_MAX(short));
  printf("ushort: %hu - %hu\n", RANGE_MIN(unsigned short),
         RANGE_MAX(unsigned short));
  printf("int: %d - %d\n", RANGE_MIN(int), RANGE_MAX(int));
  printf("uint: %u - %u\n", RANGE_MIN(unsigned), RANGE_MAX(unsigned));
  printf("long: %ld - %ld\n", RANGE_MIN(long), RANGE_MAX(long));
  printf("ulong: %lu - %lu\n", RANGE_MIN(unsigned long),
         RANGE_MAX(unsigned long));
}
