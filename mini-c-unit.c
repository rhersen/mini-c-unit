#include <math.h>
#include <stdio.h>
#include <sys/time.h>

#define assertEqualsI(a,e) _assertEqualsI(a,e,__FILE__,__LINE__)

static void _assertEqualsI(int actual, int expected, char *file, int line) {
  if (actual == expected) {
    printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
  } else {
    printf("%s:%d:\033[0;31m expected %d but got %d\033[0m\n",
	   file, line, expected, actual);
  }
}

#define assertEqualsL(a,e) _assertEqualsL(a,e,__FILE__,__LINE__)

static void _assertEqualsL(long actual, long expected, char *file, int line) {
  if (actual == expected) {
    printf("%s:%d:\033[0;32m %ld OK\033[0m\n", file, line, actual);
  } else {
    printf("%s:%d:\033[0;31m expected %ld but got %ld\033[0m\n",
	   file, line, expected, actual);
  }
}

#define assertEqualsShort(a,e) _assertEqualsShort(a,e,__FILE__,__LINE__)

static void _assertEqualsShort(short actual, short expected, char *file, int line) {
  if (actual == expected) {
    printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
  } else {
    printf("%s:%d:\033[0;31m expected %d but got %d\033[0m\n",
	   file, line, expected, actual);
  }
}

#define assertEqualsD(a,e,d) _assertEqualsD(a,e,d,__FILE__,__LINE__)

static void _assertEqualsD(double actual, double expected, int decimals, char *file, int line) {
  double diff = actual > expected ? actual - expected : expected - actual;
  double delta = pow(10, -decimals);
  if (diff < delta) {
    printf("%s:%d:\033[0;32m %.*g OK\033[0m\n", file, line, decimals, actual);
  } else {
    printf("%s:%d:\033[0;31m expected %.*g but got %.*g\033[0m\n",
	   file, line, decimals, expected, decimals, actual);
  }
}

#define assertFalse(a) _assertTrue(!(a),__FILE__,__LINE__)
#define assertTrue(a) _assertTrue((a),__FILE__,__LINE__)

static void _assertTrue(int actual, char *file, int line) {
  if (actual) {
    printf("%s:%d:\033[0;32m %d OK\033[0m\n", file, line, actual);
  } else {
    printf("%s:%d:\033[0;31m got %d\033[0m\n", file, line, actual);
  }
}

static double getElapsedSecondsSince(struct timeval* start) {
  struct timeval now;
  gettimeofday(&now, 0);
  int usec = now.tv_usec - start->tv_usec;
  int sec = now.tv_sec - start->tv_sec;

  return usec * 1e-6 + sec;
}

static void euler1divc(unsigned long three, unsigned long five) {
  unsigned long sum=0;
  unsigned long index = 15000 - 1;
  unsigned long numerator;
  unsigned long remainder;
 loop: remainder = 0;
  numerator = index;
  remainder = numerator % three;
  if (remainder == 0) goto add;
  remainder = 0;
  numerator = index;
  remainder = numerator % five;
  if (remainder != 0) goto next;
 add: sum += index;
 next: if (--index) goto loop;

  assertEqualsL(sum, 52492500);
}

static void euler1gcc() {
  long sum = 0;
  int index = 1500000000;

  while (--index) {
    int m3 = index % 3;
    int m5 = index % 5;
    if (!m3 || !m5) sum += index;
  }

  assertEqualsL(sum, 52499999925e7);
}

static double sqroot(double x) {
  double guess;
  double diff;
  double sign;
  double lower = 0;
  double upper = x;
  double less;

  do {
    guess = (lower + upper) * 0.5;
    diff = guess * guess - x;
    less = diff < 0 ? 1.0 : 0.0;

    lower += less * (guess - lower);
    upper += (1 - less) * (guess - upper);
  } while ((1 - 2 * less) * diff > 1e-15);

  return guess;
}

long euler1asm(long limit);
double euler1xmm(double limit);

int main(void) {
  struct timeval start;
  gettimeofday(&start, 0);

  /* assertEqualsI(256 * 256, 65536); */
  /* assertEqualsD(sqroot(3), sqrt(3), 15); */
  /* assertEqualsD(sqroot(2), sqrt(2), 15); */
  /* assertTrue(1 + 1 == 2); */
  /* assertFalse(1 + 1 == 3); */

  /* xchgl(); */
  /* movzFillsWithZeroes(); */
  /* movsFillsWithOnes(); */
  /* div(); */
  //euler1gcc();
  assertEqualsD(euler1xmm(1e3), 233168, 6);

  printf("%f seconds\n", getElapsedSecondsSince(&start));
  return 0;
}
