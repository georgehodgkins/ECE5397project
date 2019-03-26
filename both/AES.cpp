#include <stdexcept>
#include <cstdint>
#include <bitset>
#include "AES_mappings.h"//stores fixed mappings for subBytes, shiftRows, and mixColumns
using namespace std;

AESroundE (uint8_t* state, uint8_t* roundKey, bool noMixCols = false) {
	//subBytes
	for (int n = 0; n < 16; n++) {
		state[n] = subBytes[state[n]];/
	}
	//shiftRows
	shiftRows(state);
	//mixColumns
	for (int n = 0; n < 16; n++) {
		state[n] = (state[n/4]*mixCols[n%4][0]) ^
		(state[n/4+1]*mixCols[n%4][1]) ^
		(state[n/4+2]*mixCols[n%4][2]) ^
		(state[n/4+3]*mixcols[n%4][3]);  //not the prettiest, but it works
	}