#include <stdio.h>
#include <pthread.h>
#include <math.h>

// set the chunk size for each thread to calculate
const __uint64_t chunkSize = 10000;

char threadCount = 2;

// create shared variables for threads
__uint64_t potentialPrime = 0;
__uint64_t nextChunkStart = 3;
__uint64_t maxCompare     = 0;
char       couldBePrime   = 1;
char       keepGoing      = 1;

// create the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// do a chunk of comparasons
char checkChunk(__uint64_t input, __uint64_t start) {
    const __uint64_t end = start + chunkSize;

    for (__uint64_t compare = start; compare <= end; compare += 2) {
        if (input % compare == 0) {
            printf("%lu is devisable by %lu\n", );
            return 0;
        }
    }

    return 1;
}

void *thread() {
    __uint64_t chunkStart = 3;

    while (keepGoing) {
        pthread_mutex_lock(&mutex); // lock

        chunkStart      = nextChunkStart;
        nextChunkStart += chunkSize;

        // if we're on the last chunk
        if (chunkStart + chunkSize >= maxCompare) {
            keepGoing = 0; // tell other threads to stop at the end of their chunk
        }

        pthread_mutex_unlock(&mutex);


        if (!checkChunk(potentialPrime, chunkStart)) {
            pthread_mutex_lock(&mutex); // lock
            keepGoing    = 0;  // tell other threads to stop at the end of their chunk
            couldBePrime = 0;
        }
    }

    return NULL;
}

char isPrime(__uint64_t input) {
    maxCompare = input / 3;
    pthread_t threads[16];
    int threadError;

    if (input % 2 == 0) {
        return 0;
    }

    couldBePrime = 1;

    for (char i = 0; i < threadCount; i++)
    {
        if( (threadError=pthread_create( &threads[i], NULL, &thread, NULL)) )
        {
            printf("Thread creation failed: %d\n", threadError);
        }
    }

    for (char i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    if (couldBePrime) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    if (1) {
        __uint64_t input = 50000000021; // 50000000021 10000000019 5000000029 383

        if (isPrime(input) == 1) {
            printf("Yeah\n");
        } else {
            printf("Nah\n");
        }
    } else {
        for (__uint64_t input = 0; input < 100; input++)
        {
            if (isPrime(input) == 1) {
                printf("%lu\n", input);
            }
        }
    }

    return 0;
}
