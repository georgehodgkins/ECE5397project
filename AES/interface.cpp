#include "interface.h"
#include "AES.h"

bitset<128> AES_128_E (bitset<128> X, bitset<128> K) {
	return AES_E<128>(X, K);
}

bitset<128> AES_128_D (bitset<128> Y, bitset<128> K) {
	return AES_D<128>(Y, K);
}

bitset<128> AES_192_E (bitset<128> X, bitset<192> K) {
	return AES_E<192>(X, K);
}

bitset<128> AES_192_D (bitset<128> Y, bitset<192> K) {
	return AES_D<192>(Y, K);
}

bitset<128> AES_256_E (bitset<128> X, bitset<256> K) {
	return AES_E<256>(X, K);
}

bitset<128> AES_256_D (bitset<128> Y, bitset<256> K) {
	return AES_D<256>(Y, K);
}