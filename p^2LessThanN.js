'use strict';

const fs = require('fs');

const stop = 10000;
const primes = JSON.parse(fs.readFileSync('primes.json', {encoding: 'utf-8'}));

let potentialPrime = primes.lastChecked;

outer: while (potentialPrime < stop) {
	potentialPrime += 2;

	let checkNo = 0;
	while (primes.valid[checkNo] ** 2 <= potentialPrime) {
		if (potentialPrime % primes.valid[checkNo] === 0) {
			continue outer;
		}
		checkNo++;
	}

	console.log(potentialPrime);
	primes.valid.push(potentialPrime);
}

primes.lastChecked = potentialPrime;

fs.writeFileSync('primes.json', JSON.stringify(primes));
