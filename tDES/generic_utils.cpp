#pragma once
#include <bitset>
#include <stdexcept>
#include <cstdint>
using namespace std;

template <int L>
void bitset_chunk8(bitset<L> B, uint8_t *A, int n, int o = 0) {
	if (n*8 + o*8 > L) {
		throw invalid_argument("You cannot copy more chunks than exist in the bitset.");
	}
	for (int a = 0; a < n; a++) {
		A[a] = 0;
		for (int b = 0; b < 8; b++) {
			if (B[8*a + b + 8*o]) {
				A[a] += 0x1 << b;
			}
		}
	}
}

template <int L>
void bitset_chunk32(bitset<L> B, uint32_t *A, int n, int o = 0) {
	if (n*32 + o*32 > L) {
		throw invalid_argument("You cannot copy more chunks than exist in the bitset.");
	}
	for (int a = 0; a < n; a++) {
		A[a] = 0;
		for (int b = 0; b < 32; b++) {
			if (B[32*a + b + 32*o]) {
				A[a] += 0x1 << b;
			}
		}
	}
}

template <int L>
bitset<L> bitset_dechunk8(uint8_t *A) {
	bitset<L> B (0);
	for (int a = 0; a < L/8; a++) {
		for (int b = 0; b < 8; b++) {
			if (A[a] & (0x1 << b)) {
				B.set(8*a + b);
			}
		}
	}
	return B;
}

template <int L>
bitset<L> bitset_dechunk32(uint32_t *A) {
	bitset<L> B (0);
	for (int a = 0; a < L/32; a++) {
		for (int b = 0; b < 32; b++) {
			if (A[a] & (0x1 << b)) {
				B.set(32*a + b);
			}
		}
	}
	return B;
}

inline void xor4bytes (uint8_t *dest, uint8_t *x1, uint8_t *x2) {
	for (int n = 0; n < 4; n++) {
		dest[n] = x1[n] ^ x2[n];
	}
}

//this bitwise method taken from https://en.wikipedia.org/wiki/Rijndael_MixColumns
uint8_t GFmul(uint8_t a, uint8_t b) {
	uint8_t r = 0;
	for (int n = 0; n < 8; n++) {
		if (b & 1) {
			r^= a;
		}
		bool overflow = ((a & 0x80) != 0);
		a <<= 1;
		b >>= 1;
		if (overflow) {
			a ^= 0x1B;//AES polynomial in binary
		}
	}
	return r;
}

