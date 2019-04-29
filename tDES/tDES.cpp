#include "DES.cpp"
#include <bitset>
using namespace std;

bitset<64> tDES_E(bitset<64> X, bitset<192> K) {
	bitset<64> k1, k2, k3;
	for (int n = 0; n < 64; n++) {
		k1[n] = K[n];
		k2[n] = K[n+64];
		k3[n] = K[n+128];
	}
	X = DES_E(X, k1);
	X = DES_D(X, k2);
	X = DES_E(X, k3);
	return X;
}

bitset<64> tDES_D(bitset<64> X, bitset<192> K) {
	bitset<64> k1, k2, k3;
	for (int n = 0; n < 64; n++) {
		k1[n] = K[n];
		k2[n] = K[n+64];
		k3[n] = K[n+128];
	}
	X = DES_D(X, k3);
	X = DES_E(X, k2);
	X = DES_D(X, k1);
	return X;
}