'use strict';

const fs = require('fs');

const stop = 1000;
const primes = JSON.parse(fs.readFileSync('primes.json', {encoding: 'utf-8'}));

let potentialPrime = primes.lastChecked;

outer: while (potentialPrime < stop) {
	potentialPrime += 2;

	for (let checkNo = 0; checkNo < primes.valid.length; checkNo++) {
		if (potentialPrime % primes.valid[checkNo] === 0) {
			continue outer;
		}
	}

	console.log(potentialPrime);
	primes.valid.push(potentialPrime);
}

primes.lastChecked = potentialPrime;

fs.writeFileSync('primes.json', JSON.stringify(primes));
