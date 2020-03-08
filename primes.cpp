#include <iostream>
#include <cmath>
using namespace std;

#define MAX_PRIMES 1000
#define START 2
#define STOP 100

int main(int argc, char const *argv[])
{
	int potentialPrime = START;
	int comparison = 2;
	bool notPrime = false;

	while (potentialPrime <= STOP)
	{
		notPrime = false;
		for (comparison = 2; comparison < potentialPrime; comparison++)
		{
			if (potentialPrime % comparison == 0)
			{
				notPrime = true;
				// cout << "nope" << endl;
				break;
			}

		}

		if (!notPrime) {
			cout << potentialPrime << " is prime" << endl;
		} else {
			// cout << potentialPrime << " is not prime" << endl;
		}

		potentialPrime++;
	}

	return 0;
}


// int main(int argc, const char *argv[])
// {
// 	unsigned long potentialPrime, stop, checkNo, comparison;
// 	unsigned long primes[MAX_PRIMES];
// 	bool notPrime;

// 	checkNo = 0;
// 	potentialPrime = 3;
// 	stop = 100;

// 	while (potentialPrime < stop)
// 	{
// 		notPrime = false;
// 		potentialPrime += 2;
// 		comparison = (checkNo+2)*2;

// 		while (comparison <= potentialPrime)
// 		{
// 			if (potentialPrime % comparison == 0)
// 			{
// 				notPrime = true;
// 				break;
// 			}
// 			checkNo++;
// 		}

// 		if (!notPrime)
// 		{
// 			cout << potentialPrime << endl;
// 		}
// 	}

// 	return 0;
// }
