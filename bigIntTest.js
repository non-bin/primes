'use strict';

const fs = require('fs');

BigInt.prototype.toJSON = function toJSON() {
	return this.toString();
};

const stop = 10;
const primes = JSON.parse(fs.readFileSync('primes.json', {encoding: 'utf-8'}));

const validPrimes = new BigUint64Array(Math.floor(stop / 3));

let primeIndex = 0;
for (; primeIndex < primes.valid.length; primeIndex++) {
	validPrimes[primeIndex] = BigInt(primes.valid[primeIndex]);
}

let potentialPrime = BigInt(primes.lastChecked);

outer: while (potentialPrime < stop) {
	potentialPrime += 2n;

	for (let checkNo = 0; checkNo < validPrimes.length; checkNo++) {
		if (potentialPrime % validPrimes[checkNo] === 0) {
			continue outer;
		}
	}

	console.log(potentialPrime);
	validPrimes[primeIndex] = potentialPrime;
	primeIndex++;
}

primes.lastChecked = potentialPrime.toString();

fs.writeFileSync('primes.json', JSON.stringify(primes));
