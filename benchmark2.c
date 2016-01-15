#include <math.h>
#include <stdio.h>
#include <sys/time.h>

#define assertEqualsI(a,e) _assertEqualsI(a,e,__FILE__,__LINE__)

#define assertEqualsL(a,e) _assertEqualsL(a,e,__FILE__,__LINE__)

#define assertEqualsShort(a,e) _assertEqualsShort(a,e,__FILE__,__LINE__)

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

#define assertEqualsD(a,e,d) _assertEqualsD(a,e,d,__FILE__,__LINE__)

#define assertFalse(a) _assertTrue(!(a),__FILE__,__LINE__)
#define assertTrue(a) _assertTrue((a),__FILE__,__LINE__)

static double getElapsedSecondsSince(struct timeval* start) {
  struct timeval now;
  gettimeofday(&now, 0);
  int usec = now.tv_usec - start->tv_usec;
  int sec = now.tv_sec - start->tv_sec;

  return usec * 1e-6 + sec;
}

double euler1intel(double limit);
double euler1xmm(double limit);

int main(void) {
  struct timeval start;
  gettimeofday(&start, 0);
  assertEqualsD(euler1intel(1000), 233168, 6);
  printf("%f seconds\n", getElapsedSecondsSince(&start));
  return 0;
}
