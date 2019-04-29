#include <bitset>
#include <cstdint>
#ifndef DES_MAP_H
#define DES_MAP_H
/*All of the mappings in this file are generated from tables at
 https://github.com/Dreamgoing/DES/blob/master/src/DES.hpp
 with various amounts of modification*/
 
 //@brief DES S-box mappings
const uint8_t DESScrambleMapping[8][64] {
	{
		14,0,4,15,13,7,1,4,2,14,15,2,11,13,8,1,
		3,10,10,6,6,12,12,11,5,9,9,5,0,3,7,8,
		4,15,1,12,14,8,8,2,13,4,6,9,2,1,11,7,
		15,5,12,11,9,3,7,14,3,10,10,0,5,6,0,13,
	},{
		15,3,1,13,8,4,14,7,6,15,11,2,3,8,4,14,
		9,12,7,0,2,1,13,10,12,6,0,9,5,11,10,5,
		0,13,14,8,7,10,11,1,10,3,4,15,13,4,1,2,
		5,11,8,6,12,7,6,12,9,0,3,5,2,14,15,9
	},{
		10,13,0,7,9,0,14,9,6,3,3,4,15,6,5,10,
		1,2,13,8,12,5,7,14,11,12,4,11,2,15,8,1,
		13,1,6,10,4,13,9,0,8,6,15,9,3,8,0,7,
		11,4,1,15,2,14,12,3,5,11,10,5,14,2,7,12
	},{
		7,13,13,8,14,11,3,5,0,6,6,15,9,0,10,3,
		1,4,2,7,8,2,5,12,11,1,12,10,4,14,15,9,
		10,3,6,15,9,0,0,6,12,10,11,1,7,13,13,8,
		15,9,1,4,3,5,14,11,5,12,2,7,8,2,4,14
	},{
		2,14,12,11,4,2,1,12,7,4,10,7,11,13,6,1,
		8,5,5,0,3,15,15,10,13,3,0,9,14,8,9,6,
		4,11,2,8,1,12,11,7,10,1,13,14,7,2,8,13,
		15,6,9,15,12,0,5,9,6,10,3,4,0,5,14,3
	},{
		12,10,1,15,10,4,15,2,9,7,2,12,6,9,8,5,
		0,6,13,1,3,13,4,14,14,0,7,11,5,3,11,8,
		9,4,14,3,15,2,5,12,2,9,8,5,12,15,3,10,
		7,11,0,14,4,1,10,7,1,6,13,0,11,8,6,13
	},{
		4,13,11,0,2,11,14,7,15,4,0,9,8,1,13,10,
		3,14,12,3,9,5,7,12,5,2,10,15,6,8,1,6,
		1,6,4,11,11,13,13,8,12,1,3,4,7,10,14,7,
		10,9,15,5,6,0,8,15,0,14,5,2,9,3,2,12
	},{
		13,1,2,15,8,13,4,8,6,10,15,3,11,7,1,4,
		10,12,9,5,3,6,14,11,5,0,0,14,12,9,7,2,
		7,2,11,1,4,14,1,7,9,4,12,10,14,8,2,13,
		0,15,6,12,10,9,13,0,15,3,3,5,5,6,8,11
	}
};

//@brief P-box within DES Feistel function
const uint8_t DESFeistelPermMapping[32] {
	15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17, 30, 9,
	1, 7, 23, 13, 31, 26, 2, 8, 18, 12, 29, 5, 21, 10, 3, 24
};

//@brief Initial P-box in DES round key generation
const uint8_t DESRoundKeyInitialPerm[56] {
	56, 48, 40, 32, 24, 16, 8, 0,
	57, 49, 41, 33, 25, 17, 9, 1,
	58, 50, 42, 34, 26, 18, 10, 2,
	61, 51, 43, 35, 62, 54, 46, 38,
	30, 22, 14, 6, 61, 53, 45, 37,
	29, 21, 13, 5, 60, 52, 44, 36,
	28, 20, 12, 4, 27, 21, 13, 3
};

//@brief P-box used on lower half of keys in DES round key generation
const uint8_t DESRoundKeyRightMapping[24] {
	13, 16, 10, 23, 0, 4,
	2, 27, 14, 5, 20, 9,
	22, 18, 11, 3, 25, 7,
	15, 6, 26, 19, 12, 1
};

//@brief P-box used on upper half of keys in DES round key generation
const uint8_t DESRoundKeyLeftMapping[24] {
	40, 51, 30, 36, 46, 54,
	29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52,
	45, 41, 49, 35, 28, 31
};

//@brief E-box used on lower half of key in DES Feistel function
const uint8_t DESExpandMapping[48] {
	31, 0, 1, 2, 3, 4, 3, 4, 5, 6, 8, 8, 7, 8, 9, 10,
    11, 12, 11, 12, 13, 14, 15, 16, 15, 16, 17, 18, 19, 20, 19, 20,
	21, 22, 23, 24, 23, 24, 25, 26, 27, 26, 27, 28, 29, 30, 31, 0
};

/*@brief The permutation and shifts on master key state during DES round key gen
*
*@param upper half of master key state
*@param lower half of master key state
*@param round number
*@return 6-byte array representing a 48-bit round key
*/
void DESRoundKeyGenPerm (std::bitset<28>& L, std::bitset<28>& R, int rn, uint8_t* RKc) {
	switch (rn) {
		case 1:
		case 2:
		case 9:
		case 16:
		L <<= 1;
		R <<= 1;
		break;
		default:
		L <<= 2;
		R <<= 2;
	}
	for (int a = 0; a < 3; a++) {
		RKc[a] = 0;
		RKc[a+3] = 0;
		for (int b = 0; b < 8; b++) {
			if (R[DESRoundKeyRightMapping[a*8+b]]) {
				RKc[a] |= (1 << b);
			}
			if (L[DESRoundKeyLeftMapping[a*8+b]]) {
				RKc[a+3] |= (1 << b);
			}
		}
	}
}
#endif