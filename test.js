'use strict';

BigInt.prototype.toJSON = function toJSON() {
	return this.toString();
};

console.log(JSON.stringify({a: 2}));
