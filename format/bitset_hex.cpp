#include <bitset>
#include <sstream>
#include <cstdint>
#include <stdexcept>
#include <string>
using namespace std;

int _hexnum(char);
char _numhex(int);

template <int L>
string bitset_to_hex (bitset<L> X) {
	stringstream Y;
	for (int a = L-4; a >= 0; a -= 4) {
		uint8_t x = 0;
		for (int b = 0; b < 4; b++) {
			if (X[a+b]) {
				x += (1 << b);
			}
		}
		Y << _numhex(x);
	}
	return Y.str();
}

template <int L>
bitset<L> hex_to_bitset (string Y) {
	if (L%4) {
		throw invalid_argument("Bitset length must be divisible by 4.");
	}
	if (Y.size() != L/4) {
		throw invalid_argument("Input string must match the capacity of the bitset.");
	}
	bitset<L> X (0);
	stringstream Ys (Y);
	for (int a = Y.size()-1; a >= 0; a--) {
		char c;
		Ys >> c;
		bitset<L> rhs (_hexnum(c));
		rhs <<= a*4;
		X |= rhs;
	}
	return X;
}

int _hexnum (char c) {
	int r = -1;
	switch(c) {
		case '0'...'9':
		r = c - 0x30;
		break;
		case 'a'...'f':
		r = c - 87;
		break;
		case 'A'...'F':
		r = c - 55;
		break;
	}
	return r;
}

char _numhex (int i) {
	char r = 'x';
	if (i < 10) {
		r = i + 0x30;
	} else {
		r = i + 87;
	}
	return r;
}