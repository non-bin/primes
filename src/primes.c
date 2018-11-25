#include <stdio.h>
#include <pthread.h>
#include <math.h>

// determine if a number is a prime or not
char isPrime(unsigned long long input) {
    unsigned long long maxCompare = input / 5;
    int count = 0;

    if (input % 2 == 0)
    {
        return 0;
    }

    if (input % (input / 3) == 0)
    {
        return 0;
    }

    for (unsigned long long compare = 3; compare <= maxCompare; compare += 2)
    {
        if (input % compare == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main() {
    unsigned long long input = 5000000029; // 5000000029 383

    if (isPrime(input) == 1) {
        printf("Yeah\n");
    } else {
        printf("Nah\n");
    }

    // for (unsigned long long input = 5000000029; input < 50000000000; input++)
    // {
    //     if (isPrime(input) == 1) {
    //         printf("%llu\n", input);
    //     }
    // }

    return 0;
}
