#include <stdio.h>
#include <pthread.h>
#include <math.h>
typedef unsigned long __largeuint_t;

// fun stuff to mess with
// if you can add commandline params
// to replace recompiling every time,
// ill merge it in

char calcSingle = 1;  // whether to calculate the single input (1) or the range (0)

__largeuint_t input = 5000000029;  // single input number to test

__largeuint_t start = 1000000000;     // start of calculation range
__largeuint_t end   = 1000000200;  // end of calculation range

__largeuint_t chunkSize   = 10000000;  // the number of calculations for a thread to perform before checking in
char          threadCount = 4;         // number of threads to create

// now the booring things


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // create the mutex

__largeuint_t globalInput;
__largeuint_t globalChunk;
__largeuint_t globalMaxCompare;
char globalContinue;
char globalIsPrime;

// do a chunk of comparasons
char checkChunk(__largeuint_t input, __largeuint_t start) {
    const __largeuint_t end = start + chunkSize;

    for (__largeuint_t compare = start; compare <= end; compare += 2) {
        if (input % compare == 0) {
            return 0;
        }
    }

    return 1;
}

void *thread() {
    __largeuint_t chunkStart;

    while(globalContinue) {
        pthread_mutex_lock(&mutex);
        chunkStart = globalChunk;

        // if we're at the last chunk
        if (chunkStart + chunkSize >= globalMaxCompare) {
            globalContinue = 0; // tell the rest of the threads to stop
        } else {
            globalChunk += chunkSize;
        }
        pthread_mutex_unlock(&mutex);

        // if it's not a prime
        if (!checkChunk(globalInput, chunkStart)) {
            globalContinue = 0; // tell all threads to stop
            globalIsPrime  = 0; // tell the main thread it's not a prime
            break; // break out
        }
    }

    return NULL;
}

char isPrime(__largeuint_t input) {
    int rc;
    pthread_t threads[16];

    globalInput      = input;
    globalContinue   = 1;
    globalIsPrime    = 1;
    globalChunk      = 3;
    globalMaxCompare = input / 3;

    if (input % 2 == 0) {
        return 0;
    }

    for(char i = 0; i < threadCount; i++)
    {
        if( (rc=pthread_create( &threads[i], NULL, &thread, NULL)) )
        {
            printf("Thread %d creation failed: %d\n", i, rc);
        }
    }

    for(char i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return globalIsPrime;
}

int main(int argc, char const *argv[])
{
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
