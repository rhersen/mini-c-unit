#include <math.h>

double euler1xmm(double limit) {
  double i = limit - 1;
  double r = 0;

  do {
    double q3 = i / 3;
    double q5 = i / 5;
    double t3 = trunc(q3);
    double t5 = trunc(q5);
    double nz = (q3 - t3) * (q5 - t5) != 0;

    r += i * !nz;
  } while (--i > 0);

  return r;
}
