#include <stdio.h>
#include <pthread.h>
#include <math.h>

const __uint64_t chunkSize = 50000000; // set the chunk size for each thread to calculate
char threadCount = 4; // number of threads to create
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // create the mutex

__uint64_t globalInput;
__uint64_t globalChunk;
__uint64_t globalMaxCompare;
char globalContinue;
char globalIsPrime;

// do a chunk of comparasons
char checkChunk(__uint64_t input, __uint64_t start) {
    const __uint64_t end = start + chunkSize;

    for (__uint64_t compare = start; compare <= end; compare += 2) {
        // printf("%d - %lu\n", threadNo, compare);
        if (input % compare == 0) {
            printf("%lu is devisable by %lu\n", globalInput, compare);
            return 0;
        }
    }

    return 1;
}

void *thread() {
    printf("Starting thread\n");
    __uint64_t chunkStart;

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

        // print where we're up to
        // printf("%lu\n%lu\n\n", globalMaxCompare, chunkStart);
    }

    return NULL;
}

char isPrime(__uint64_t input) {
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
        } else {
            printf("Created thread %d\n", i);
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
    __uint64_t input = 50000000021;

    if (isPrime(input)) {
        printf("yee\n");
    } else {
        printf("nah\n");
    }

    return 0;
}
