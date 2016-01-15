#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static double getElapsedSecondsSince(struct timeval* start) {
  struct timeval now;
  gettimeofday(&now, 0);
  int usec = now.tv_usec - start->tv_usec;
  int sec = now.tv_sec - start->tv_sec;

  return usec * 1e-6 + sec;
}

long euler1asm(long limit);
double euler1xmm(double limit);

double absolute(double x);

int main(void) {
  long N = 8000000;
  double max = (double)RAND_MAX;
  double sum = 0;
  double values[N];
  
  for (long i = 0; i < N; ++i) {
    values[i] = 2.0 * rand() / max - 1;
  }

  struct timeval start;
  gettimeofday(&start, 0);

  for (long i = 0; i < N; ++i) {
    sum += absolute(values[i]);
  }

  printf("%.9f\n", sum);

  printf("%f seconds\n", getElapsedSecondsSince(&start));
  return 0;
}
