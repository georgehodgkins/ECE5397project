#include "DES_round.cpp"
#include "../generic_utils.cpp"
#include <bitset>
using namespace std;

bitset<64> DES_E(bitset<64> X, bitset<64> K) {
	uint8_t RK[16][6];
	DESRoundKeyGen(K, RK);
	uint32_t Xa[2];
	bitset_chunk32<64>(X, Xa, 2);
	for (int n = 0; n < 16; n++) {
		DESRoundE(Xa[1], Xa[0], RK[n]);
	}
	return bitset_dechunk32<64>(Xa);
}

bitset<64> DES_D(bitset<64> Y, bitset<64> K) {
	uint8_t RK[16][6];
	DESRoundKeyGen(K, RK);
	uint32_t Ya[2];
	bitset_chunk32<64>(Y, Ya, 2);
	for (int n = 15; n >= 0; n--) {
		DESRoundD(Ya[1], Ya[0], RK[n]);
	}
	return bitset_dechunk32<64>(Ya);
}