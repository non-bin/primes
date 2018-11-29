#include <stdio.h>
#include <pthread.h>
#include <math.h>

// set the chunk size for each thread to calculate
const unsigned long long chunkSize = 10000;

// create shared variables for threads
unsigned long long nextInput = 0;
unsigned long long nextChunk = 3;

// create the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// do a chunk of comparasons
char checkChunk(unsigned long long input, unsigned long long start) {
    const unsigned long long end = start + chunkSize;

    for (unsigned long long compare = start; compare <= end; compare += 2) {
        if (input % compare == 0) {
            return 0;
        }
    }

    return 1;
}

void *thread() {
    unsigned long long input = 0;
    unsigned long long chunkStart = 3;
    char lastChunk = 0;

    while (1) {
        // ask for chunk
        pthread_mutex_lock(&mutex); // lock

        input       = nextInput; // take the next input
        chunkStart  = nextChunk; // and chunk start

        // if we're on the last chunk
        if (nextChunk + chunkSize > input / 5) {
            lastChunk  = 1;  // save that fact for later
            nextChunk  = 3;  // reset the chunk
            nextInput += 2;  // increment the input
        } else {
            nextChunk  += chunkSize; // increment the nextChunk
        }

        pthread_mutex_unlock(&mutex); // unlock


        // if it's not prime
        if (checkChunk(input, chunkStart) == 0) {
            nextChunk  = 3;  // reset the chunk
            nextInput += 2;  // increment the input
        } else {
            // so far it's a prime, if it's also the last chunk
            if (lastChunk) {
                // we have a prime!
                printf("%llu\n", input);
            }
        }
    }
}

// determine if a number is a prime or not
char isPrime(unsigned long long input) {
    unsigned long long maxCompare = input / 5;
    int rc1, rc2;
    pthread_t thread1, thread2;

    if (input % 2 == 0) {
        return 0;
    }

    if (input % (input / 3) == 0) {
        return 0;
    }

    if( (rc1=pthread_create( &thread1, NULL, &thread, NULL)) )
    {
       printf("Thread creation failed: %d\n", rc1);
    }

    if( (rc2=pthread_create( &thread2, NULL, &thread, NULL)) )
    {
       printf("Thread creation failed: %d\n", rc2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 1;
}

int main() {
    if (1) {
        unsigned long long input = 50000000021; // 50000000021 10000000019 5000000029 383

        if (isPrime(input) == 1) {
            printf("Yeah\n");
        } else {
            printf("Nah\n");
        }
    } else {
        for (unsigned long long input = 50000000000; input < 100000000000; input++)
        {
            if (isPrime(input) == 1) {
                printf("%llu\n", input);
            }
        }
    }

    return 0;
}
