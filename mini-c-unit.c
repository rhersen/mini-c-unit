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

static void xchgl() {
    unsigned int foo = 131, bar = 128;
    asm volatile("xchgl %1, %0"
                 :"+r"(foo), "+r"(bar)
                 :
                 );

    assertEqualsI(foo, 128);
    assertEqualsI(bar, 131);
}

static void movzFillsWithZeroes() {
    short s;
    char b = 0xaf;

    asm("movzbw %1, %0"
        : "=r"(s)
        : "r"(b)
        );

    assertEqualsShort(s, 0xaf);
}

static void movsFillsWithOnes() {
    short s;
    char b = 0xaf;

    asm("movsbw %1, %0"
        : "=r"(s)
        : "r"(b)
        );

    assertEqualsShort(s, 0xffaf);
}

static void euler1div(unsigned long three, unsigned long five) {
    unsigned long sum = 0;
    unsigned long index = 150000000 - 1;
    unsigned long numerator = index;
    unsigned long remainder = 0;
    asm ("for: mov $0, %[remainder] \n"
         "mov %[index], %[numerator] \n"
         "div %[three] \n"
         "test %[remainder], %[remainder] \n"
         "jz add \n"
         "mov $0, %[remainder] \n"
         "mov %[index], %[numerator] \n"
         "div %[five] \n"
         "test %[remainder], %[remainder] \n"
         "jnz next \n"
         "add: add %[index], %[sum] \n"
         "next: loop for \n"
         :[sum] "+r"(sum)
         :[index] "c"(index),
          [three] "r"(three),
          [five] "r"(five),
          [numerator] "a"(numerator),
          [remainder] "d"(remainder));

    assertEqualsL(sum, 5249999925e6);
}

static void euler1divc(unsigned long three, unsigned long five) {
    register unsigned long sum;
    register unsigned long index asm("rcx") = 150000000 - 1;
    register unsigned long numerator asm("rax");
    register unsigned long remainder asm("rdx");
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

    assertEqualsL(sum, 5249999925e6);
}

static void euler1gcc(unsigned long three, unsigned long five) {
    unsigned long sum = 0;

    for (unsigned long index = 0; index < 150000000; ++index) {
        if (index % three == 0 || index % five == 0) {
            sum += index;
        }
    }

    assertEqualsL(sum, 5249999925e6);
}

static void div() {
    register unsigned int numerator asm("eax") = 80;
    register unsigned int limit asm("ecx") = 10;
    register unsigned int remainder asm("edx") = 0;
    unsigned int denominator = 11;
    asm volatile("decl %2 \n"
                 "divl %3 \n"
                 :"+r"(numerator), "+r"(remainder)
                 :"r"(limit), "r"(denominator)
                 );

    assertEqualsI(numerator, 7);
    assertEqualsI(remainder, 3);
}

int main(void) {
    struct timeval start;
    gettimeofday(&start, 0);

    /* assertEqualsI(256 * 256, 65536); */
    /* assertEqualsD(1.0 + 1.0, 2.0, 1e-9); */
    /* assertTrue(1 + 1 == 2); */
    /* assertFalse(1 + 1 == 3); */

    /* xchgl(); */
    /* movzFillsWithZeroes(); */
    /* movsFillsWithOnes(); */
    /* div(); */
    euler1divc(3, 5);

    printf("%f seconds\n", getElapsedSecondsSince(&start));
    return 0;
}
