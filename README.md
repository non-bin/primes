# Primes Cuda Accelerated

## STILL IN PRODUCTION

The cuda gpu accelerated branch is still under production, and currently non functional

## Prerequisites

You will need:

- a cuda enabled GPU ([https://developer.nvidia.com/cuda-gpus](https://developer.nvidia.com/cuda-gpus))
- a linux (maybe mac or windows) operating system
- the `cuda` framework
- the `nvidia-cuda-toolkit` (linux at least)
- some programing knowledge.

NOTE: I've only tested this on 64bit linux, but it should work on 32bit, and may work on mac and Windows (can someone verify? issue #1)

## Installing

First, make a folder for the binary. You only need to do this once.

    mkdir -p bin

Then compile and run the program with the pthread library.

    nvcc src/primes.cu -o bin/primes && ./bin/primes

You only need to recompile if you change something in the program, so to just run it again, you can use

    ./bin/primes

And if you want to benchmark performance, you can run it with `time` to show you overall time info, and or `nvprof` for GPU specific stats

    time nvprof ./bin/primes

## Usage

For the moment all settings are in the `primes.c` file, and the program must be recompiled whenever they are changed.  
Some easy things to mess with are the config variables on lines 10-20. You can see the impact of adding threads by using `time` and changing the `threadCount` variable (usually you want this to be equal to your cpu's core count).

## Some Primes To Test On

    992429121339693967
    50000000021
    10000000019
    5000000029
    383
