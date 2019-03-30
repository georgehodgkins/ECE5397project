#pragma once
#include <stdexcept>
#include <cstdint>
#include <bitset>
#include "AES_mappings.h"//stores various fixed mappings
#include "AES_round.cpp"//per-round fcns and key schedule
#include "AES.cpp"
#include "../generic_utils.cpp"
using namespace std;

template <int L>
bitset<128> AES_E (bitset<128> X, bitset<L> K) {
	//get the correct number of rounds
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
	//convert data bitset into state array
	uint8_t state[16];
	bitset_chunk8<128> (X, state, 16);
	X.reset();
	//generate round key array
	uint8_t *roundKeySet = AESRoundKeyGen<L> (K);
	//initial addRoundKey
	for (int n = 0; n < 16; n++) {
		state[n] ^= roundKeySet[n];
	}
	//rounds of encryption
	for (int r = 1; r < R; r++) {
		AESRoundE(state, &roundKeySet[16*r]);
	}
	AESRoundE(state, &roundKeySet[16*R], true); //no mixCols in last round
	delete[] roundKeySet;//allocated in AESRoundKeyGen
	return bitset_dechunk8<128> (state);
}

template <int L>
bitset<128> AES_D (bitset<128> Y, bitset<L> K) {
	//get the correct number of rounds
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
	//convert data bitset into state array
	uint8_t state[16];
	bitset_chunk8<128> (Y, state, 16);
	Y.reset();
	//generate round key array
	uint8_t *roundKeySet = AESRoundKeyGen<L> (K);
	//one round w/o mixCols
	AESRoundD(state, &roundKeySet[16*R], true);
	//rounds of decryption
	for (int r = R-1; r > 0; r--) {
		AESRoundD(state, &roundKeySet[16*r]);
	}
	//reverse initial addRoundKey
	for (int n = 0; n < 16; n++) {
		state[n] ^= roundKeySet[n];
	}
	delete[] roundKeySet;
	return bitset_dechunk8<128> (state);
}