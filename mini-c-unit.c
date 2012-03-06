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

#define assertEqualsD(a,e,d) _assertEqualsD(a,e,d,__FILE__,__LINE__)

static void _assertEqualsD(double actual, double expected, double delta, char *file, int line) {
    double diff = actual > expected ? actual - expected : expected - actual;
    if (diff < delta) {
        printf("%s:%d:\033[0;32m %f OK\033[0m\n", file, line, actual);
    } else {
        printf("%s:%d:\033[0;31m expected %f but got %f\033[0m\n",
               file, line, expected, actual);
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

int main(void) {
    struct timeval start;
    gettimeofday(&start, 0);

    assertEqualsI(256 * 256, 65536);
    assertEqualsD(1.0 + 1.0, 2.0, 1e-9);
    assertTrue(1 + 1 == 2);
    assertFalse(1 + 1 == 3);

    printf("%f seconds\n", getElapsedSecondsSince(&start));

    return 0;
}
