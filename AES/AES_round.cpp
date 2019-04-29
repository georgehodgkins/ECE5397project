#pragma once
#include <bitset>
#include <cstdint>
#include "AES_mappings.h"
#include "../generic_utils.cpp"
using namespace std;

void AESRoundE (uint8_t *state, uint8_t *roundKey, bool noMixCols = false) {
	//subBytes
	for (int n = 0; n < 16; n++) {
		state[n] = subBytesE[state[n]];
	}
	//shiftRows
	shiftRowsE(state);
	//mixColumns
	if (!noMixCols) {
		for (int a = 0; a < 16; a += 4) {
			uint8_t tmp[4];
			for (int b = 0; b < 4; b++) {
				tmp[b] =
				GFmul(state[a],mixColsE[b][0]) ^
				GFmul(state[a+1],mixColsE[b][1]) ^
				GFmul(state[a+2],mixColsE[b][2]) ^
				GFmul(state[a+3],mixColsE[b][3]); 
			}
			for (int b = 0; b < 4; b++) {
				state[a+b] = tmp[b];
			}
		}
	}
	//addRoundKey
	for (int n = 0; n < 16; n++) {
		state[n] ^= roundKey[n];
	}
}

void AESRoundD (uint8_t *state, uint8_t *roundKey, bool noMixCols = false) {
	//addRoundKey (subtractRoundKey?)
	for (int n = 0; n < 16; n++) {
		state[n] ^= roundKey[n];
	}
	//mixColumns (unmixColumns?)
	if (!noMixCols) {
		for (int a = 0; a < 16; a += 4) {
			uint8_t tmp[4];
			for (int b = 0; b < 4; b++) {
				tmp[b] =
				GFmul(state[a],mixColsD[b][0]) ^
				GFmul(state[a+1],mixColsD[b][1]) ^
				GFmul(state[a+2],mixColsD[b][2]) ^
				GFmul(state[a+3],mixColsD[b][3]); 
			}
			for (int b = 0; b < 4; b++) {
				state[a+b] = tmp[b];
			}
		}
	}
	//shiftRows
	shiftRowsD(state);
	//subBytes
	for (int n = 0; n < 16; n++) {
		state[n] = subBytesD[state[n]];
	}
}

template <int L>
uint8_t* AESRoundKeyGen (bitset<L> K) {
	int N = L/32;
	int R;
	switch (L) {
		case 128:
		R = 10;
		break;
		case 192:
		R = 12;
		break;
		case 256:
		R = 14;
		break;
		default:
		throw invalid_argument("AES key length must be 128, 192, or 256");
	}
	uint8_t *RK = new uint8_t[(R+1)*16]; //deallocated in caller function (AES_E or AES_D)
	//first N RK words are just the words of the key
	bitset_chunk8<L> (K, &RK[0], N*4);
	for (int n = N; n < (R+1)*4; n += N) {
		uint8_t g_out[4];
		g_out[0] = subBytesE[RK[n-12]] ^ RC[n/N];
		g_out[1] = subBytesE[RK[n-8]];
		g_out[2] = subBytesE[RK[n-4]];
		g_out[3] = subBytesE[RK[n-16]];
		xor4bytes(&RK[n], g_out, &RK[n-N]);
		for (int p = 4; p < N*4; p+= 4) {
			if (L == 256 && p == 16) {
				g_out[0] = subBytesE[RK[n+12]];//aka n+p-4
				g_out[1] = subBytesE[RK[n+13]];//aka n+p-3
				g_out[2] = subBytesE[RK[n+14]];//aka n+p-2
				g_out[3] = subBytesE[RK[n+15]];//aka n+p-1
				xor4bytes(&RK[n+p], g_out, &RK[n+p-N]);
			} else {
				xor4bytes(&RK[n+p], &RK[n+p-4], &RK[n+p-N]);
			}
		}
	}
	return RK;
}