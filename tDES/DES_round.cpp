#include <bitset>
#include <cstdint>
#include "DES_round.h"
#include "DES_mappings.h"

void DESRoundE (uint32_t& L, uint32_t& R, uint8_t *roundKey) {
	uint32_t oldL = L;
	L = R;
	DESFeistel(R, roundKey);
	R ^= oldL;
}

void DESRoundD (uint32_t& L, uint32_t& R, uint8_t *roundKey) {
	uint32_t oldR = R;
	R = L;
	DESFeistel(L, roundKey);
	L ^= oldR;
}

void DESFeistel(uint32_t& X, uint8_t *roundKey) {
	uint8_t EX[6] = {0, 0, 0, 0, 0, 0};
	DESExpand(X, EX);
	for (int n = 0; n < 6; n++) {
		EX[n] ^= roundKey[n];
	}
	X = DESScramble(EX);
	DESFeistelPerm(X);
}

uint8_t* DESExpand(uint32_t X, uint8_t *EX) {
	for (int a = 0; a < 6; a++) {
		for (int b = 0; b < 8; b++) {
			if (X & (1 << DESExpandMapping[a*8 + b])) {
				EX[a] |= (1 << b);
			}
		}
	}
	return EX;
}

uint32_t DESScramble(uint8_t *EX) {
	uint32_t ret = 0;
	uint64_t EXi = EX[0];
	for (int n = 1; n < 6; n++) {
		EXi |= EX[n] << 8*n;
	}
	for (int n = 0; n < 8; n++) {
		ret |= (DESScrambleMapping[n][(EXi >> 6*n) & 0b111111] << 4*n);
	}
	return ret;
}

void DESFeistelPerm(uint32_t& X) {
	uint32_t Xi = X;
	X = 0;
	for (int n = 0; n < 32; n++) {
		if (Xi & (1 << DESFeistelPermMapping[n])) {
			X |= (1 << n);
		}
	}
}

void DESRoundKeyGen(std::bitset<64> K, uint8_t **RK) {
	std::bitset<28> K_R (0);
	std::bitset<28> K_L (0);
	for (int n = 0; n < 28; n++) {
		K_R[n] = K[DESRoundKeyInitialPerm[n]];
		K_L[n] = K[DESRoundKeyInitialPerm[n+28]];
	}
	for (int n = 0; n < 16; n++) {
		DESRoundKeyGenPerm(K_R, K_L, n, RK[n]);
	}
}