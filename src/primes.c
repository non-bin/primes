#include <stdio.h>
#include <pthread.h>
#include <math.h>

// fun stuff to mess with
// if you can add commandline params
// to replace recompiling every time,
// ill merge it in

char       calcSingle = 1;           // whether to calculate the single input (1) or the range (0)
__uint64_t input      = 5000000029;  // single input number to test
__uint64_t start      = 0;           // start of calculation range
__uint64_t end        = 1000;        // end of calculation range

// now the booring things


// determine if a number is a prime or not
char isPrime(__uint64_t input) {
    __uint64_t maxCompare = input / 3;
    int count = 0;

    if (input % 2 == 0)
    {
        return 0;
    }

    for (__uint64_t compare = 3; compare <= maxCompare; compare += 2)
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
        for (__uint64_t input = start; input < end; input++)
        {
            if (isPrime(input) == 1) {
                printf("%lu\n", input);
            }
        }
    }

    return 0;
}
