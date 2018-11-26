#include <stdio.h>
#include <pthread.h>
#include <math.h>

// set the chunk size for each thread to calculate
const unsigned long long chunkSize = 10000;

char threadCount = 2;

// create shared variables for threads
unsigned long long input     = 0;
unsigned long long nextChunk = 3;

char lastChunk = 0; // is it the last chunk?
char prime     = 0; // is it a prime? (0=yes 1=no)

// create the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// do a chunk of comparasons
char checkChunk(unsigned long long input, unsigned long long start) {
    const unsigned long long end = start + chunkSize;

    for (unsigned long long compare = start; compare <= end; compare += 2) {
        if (input % compare == 0) {
            return 1;
        }
    }

    return 0;
}

void *thread() {
    unsigned long long chunkStart = 3;

    while(1) {
        // if it's not a prime
        if (prime) {
            break;
        }

        // ask for chunk
        pthread_mutex_lock(&mutex); // lock

        chunkStart = nextChunk;

        // if this is the last chunk for this input
        if (nextChunk + chunkSize >= input / 5) {
            lastChunk = 1; // save that fact
        } else {
            nextChunk += chunkSize;
        }

        pthread_mutex_unlock(&mutex); // unlock


        // if it's not prime
        if (checkChunk(input, chunkStart)) {
            pthread_mutex_lock(&mutex); // lock
            prime = 1;
            pthread_mutex_unlock(&mutex); // unlock
            break;
        } else {
            // so far it's a prime, if it's also the last chunk
            if (lastChunk) {
                break;
            }
        }
    }

    return NULL;
}

// determine if a number is a prime or not
char isPrime(unsigned long long inputToTest) {
    input = inputToTest;
    unsigned long long maxCompare = input / 5;
    int rc[16];
    pthread_t threads[16];

    if (input % 2 == 0) {
        return 1;
    }

    if (input % (input / 3) == 0) {
        return 1;
    }

    for(char i = 0; i < threadCount; i++)
    {
        if( (rc[i]=pthread_create( &threads[i], NULL, &thread, NULL)) )
        {
            printf("Thread creation failed: %d\n", rc[i]);
        }
    }

    for(char i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    if (1) {
        unsigned long long input = 50000000021; // 50000000021 10000000019 5000000029 383

        if (isPrime(input) == 0) {
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
