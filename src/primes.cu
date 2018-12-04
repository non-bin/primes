#include <iostream>
#include <math.h>

typedef unsigned long __largeuint_t;

// fun stuff to mess with
// if you can add commandline params
// to replace recompiling every time,
// ill merge it in

char calcSingle = 1;  // whether to calculate the single input (1) or the range (0)

__largeuint_t singleInput = 50000000021;  // single input number to test

__largeuint_t start = 20;  // start of calculation range
__largeuint_t end   = 20;  // end of calculation range

// end fun stuff, start boring stuff

// Kernel function
__global__
void kernel(__largeuint_t input, __largeuint_t globalMaxCompare, int *globalIsPrime) {
    __largeuint_t index  = blockIdx.x * blockDim.x + threadIdx.x * 2 + 3;
    __largeuint_t stride = blockDim.x * gridDim.x * 2;

    if (index == 0 || index == 1) {
        printf("INDEX IS %lu! SOMETHING HAS GOME WRONG!\n\n", index, blockIdx.x, blockDim.x, threadIdx.x);
        *globalIsPrime = 0;
        return;
    }

    for (__largeuint_t compare = index; compare < globalMaxCompare && globalIsPrime; compare += stride) {
        if (input % compare == 0) {
            printf("%lu is devisable by %lu\n", input, compare);
            *globalIsPrime = 0;
            break;
        }
    }
}

int isPrime(__largeuint_t globalInput) {
    __largeuint_t globalMaxCompare = globalInput / 3;
    int *globalIsPrime;

    if (globalInput % 2 == 0) {
        printf("%lu is devisable by 2\n", globalInput);
        return 0;
    }

    // Allocate Unified Memory – accessible from CPU or GPU
    cudaMallocManaged(&globalIsPrime, sizeof(int));

    *globalIsPrime = 1;

    // Run kernel on 1M elements on the GPU
    int blockSize = 512;
    int numBlocks = (globalMaxCompare/2 + blockSize - 1) / blockSize;
    kernel<<<numBlocks, blockSize>>>(globalInput, globalMaxCompare, globalIsPrime);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    int output = *globalIsPrime;

    // Free memory
    cudaFree(globalIsPrime);

    return output;
}

int main() {
    if (calcSingle) {
        printf("Begining calculation of %lu\n", singleInput);
        if (isPrime(singleInput) == 1) {
            printf("%lu is prime\ndone\n", singleInput);
        } else {
            printf("%lu is not prime\ndone\n", singleInput);
        }
    } else {
        printf("Calculating primes from %lu to %lu\n", start, end);
        for (__largeuint_t i = start; i < end; i++)
        {
            if (isPrime(i) == 1) {
                printf("%lu\n", i);
            }
        }
    }

    return 0;
}
