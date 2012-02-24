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

#define assertEqualsF(a,e,d) _assertEqualsF(a,e,d,__FILE__,__LINE__)

static void _assertEqualsF(float actual, float expected, float delta, char *file, int line) {
    float diff = actual > expected ? actual - expected : expected - actual;
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
        printf("%s:%d:\033[0;31m got %d\033[0m\n",
               file, line, actual);
    }
}

int main(void) {
    struct timeval start;
    struct timeval now;
    gettimeofday(&start, 0);

    assertEqualsF(1.0 + 1.0, 2.0, 1e-5);
    assertTrue(1 + 1 == 2);
    assertFalse(1 + 1 == 3);

    gettimeofday(&now, 0);
    printf("%f\n", now.tv_usec * 1e-6 - start.tv_usec * 1e-6 +
           (now.tv_sec - start.tv_sec));

    return 0;
}
