#include <stdio.h>
#include <pthread.h>
#include <math.h>
typedef unsigned long __largeuint_t;

// fun stuff to mess with
// if you can add commandline params
// to replace recompiling every time,
// ill merge it in

char calcSingle = 0;  // whether to calculate a single input (1) or the range (0)

unsigned long input = 5000000029;  // single input number to test

__largeuint_t start = 1;    // start of calculation range
__largeuint_t   end = 100;  // end of calculation range

// now the booring things


// determine if a number is a prime or not
char isPrime(__largeuint_t input) {
    __largeuint_t maxCompare = input / 3;

    if (input % 2 == 0)
    {
        return 0;
    }

    for (__largeuint_t compare = 3; compare <= maxCompare; compare += 2)
    {
        if (input % compare == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main() {
    if (calcSingle) {
        printf("Begining calculation of %lu\n", input);
        if (isPrime(input) == 1) {
            printf("%lu is prime\ndone\n", input);
        } else {
            printf("%lu is not prime\ndone\n", input);
        }
    } else {
        printf("Calculating primes from %lu to %lu\n", start, end);
        for (__largeuint_t input = start; input < end; input++)
        {
            if (isPrime(input) == 1) {
                printf("%lu\n", input);
            }
        }
    }

    return 0;
}
