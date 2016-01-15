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

long euler1asm(long limit);
double euler1(double limit, double three, double five);
/* double euler3(double limit, double one, double sum, double rounded, double quotient); */
double euler6(double limit);
double euler7(double limit);
double euler10(double n);
double euler25(double n);
double sine(double x, double limit);
double cond(double x, double y);

int main(void) {
  struct timeval start;
  gettimeofday(&start, 0);

  assertEqualsD(euler1(999, 3, 5), 233168, 6);
  assertEqualsD(euler6(10), 2640, 8);
  /* assertEqualsD(euler7(2, 1), 1, 6); */
  /* assertEqualsD(euler7(3, 1), 1, 6); */
  /* assertEqualsD(euler7(4, 1), 0, 6); */
  /* assertEqualsD(euler7(5, 1), 1, 6); */
  /* assertEqualsD(euler7(9, 1), 0, 6); */
  /* assertEqualsD(euler7(13, 1), 1, 6); */
  /* assertEqualsD(euler7(104743, 1), 1, 6); */
  /* assertEqualsD(euler7(295075153, 1), 1, 6); */
  /* assertEqualsD(euler7(10967535067, 1), 0, 6); */
  
  assertEqualsD(euler7(1), 2, 6);
  assertEqualsD(euler7(2), 3, 6);
  assertEqualsD(euler7(3), 5, 6);
  assertEqualsD(euler7(6), 13, 6);
  assertEqualsD(euler7(10001), 104743, 6);

  assertEqualsD(euler10(4), 5, 6);
  assertEqualsD(euler10(10), 17, 6);
  /* assertEqualsD(euler10(2e6), 142913828922, 12); */

  assertEqualsD(euler25(2), 7, 6);
  assertEqualsD(euler25(3), 12, 6);
  assertEqualsD(euler25(10), 45, 6);
  assertEqualsD(euler25(100), 476, 6);
  assertEqualsD(euler25(200), 954, 6);
  assertEqualsD(euler25(300), 1433, 6);
  assertEqualsD(euler25(1000), 4782, 6);

  assertEqualsD(sine(1, 1e-15), 0.841470984807897, 15);
  assertEqualsD(sine(0.5, 1e-15), 0.479425538604203, 15);
  assertEqualsD(sine(0, 1e-15), 0, 15);
  assertEqualsD(sine(3.141592653589793/2, 1e-15), 1, 15);
  assertEqualsD(sine(3.141592653589793, 1e-15), 0, 15);

  assertEqualsD(cond(1, 2), 1, 9);

  /* assertEqualsD(euler3(3, 1, 0, 0, 0), 3, 6); */
  /* assertEqualsD(euler3(4, 1, 0, 0, 0), 2, 6); */
  /* assertEqualsD(euler3(5, 1, 0, 0, 0), 5, 6); */
  /* assertEqualsD(euler3(6, 1, 0, 0, 0), 2, 6); */
  /* assertEqualsD(euler3(9, 1, 0, 0, 0), 3, 6); */
  /* assertEqualsD(euler3(13195, 1, 0, 0, 0), 5, 6); */

  /* double i, n = 600851475143; */
  /* do { */
  /*   i = euler3(n, 1, 0, 0, 0); */
  /*   printf("%f\n", i); */
  /*   n = n / i; */
  /* } while (n != 1); */
  
  printf("%f seconds\n", getElapsedSecondsSince(&start));
  return 0;
}
