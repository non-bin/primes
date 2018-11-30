mkdir -p bin
gcc src/primes.c -o bin/primes -l pthread && ./bin/primes
