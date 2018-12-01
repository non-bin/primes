# Primes Single Core

## Prerequisites

You will need `gcc`, and some programing knowledge.  

NOTE: I've only tested this on 64bit linux with `gcc`, but there's no reason it shouldn't work on windows and mac 32 or 64bit with any other compiler.

## Installing

First, make a folder for the binary. You only need to do this once.

    mkdir -p bin

Then compile and run the program.

    gcc src/primes.c -o bin/primes && ./bin/primes

You only need to recompile if you change something in the program, so to just run it again, you can use

    ./bin/primes

And if you want to benchmark performance, you can run it with `time`

    time ./bin/primes

## Usage

For the moment all settings are in the `primes.c` file, and the program must be recompiled whenever they are changed.  
Some easy things to mess with are the config variables on lines 10-15

## Some Primes To Test On

    992429121339693967
    50000000021
    10000000019
    5000000029
    383
