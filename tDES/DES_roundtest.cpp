#include "DES_round.cpp"
#include "../format/bitset_hex.cpp"
#include "../generic_utils.cpp"
#include <bitset>
#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main () {
	/*int sigdig = 0;
	for (uint64_t x = 0; x < ULLONG_MAX; x++) {
		if (x == (1 << sigdig)) {
			cout << "\nsigdig: " << sigdig << '\n';
			sigdig++;
		}
		bitset<64> ptext (x);
		uint32_t Xsamp[2];
		uint8_t RKS[6] = {0x3F, 0x1E, 0x02, 0x49, 0x5D, 0xBA};
		bitset_chunk32<64> (ptext, Xsamp, 2);
		DESRoundE(Xsamp[1], Xsamp[0], RKS);
		DESRoundD(Xsamp[1], Xsamp[0], RKS);
		cout << '\n' << bitset_to_hex<64> (ptext);
		cout << '\n' << bitset_to_hex<64> (bitset_dechunk32<64> (Xsamp)) << '\n';
	}
	*/
	cout << "Give int plaintext: ";
	uint64_t d;
	cin >> d;
	bitset<64> ptext (d);
	uint32_t X[2];
	uint8_t RKS[6] = {0x3F, 0x1E, 0x02, 0x49, 0x5D, 0xBA};
	bitset_chunk32<64>(ptext, X, 2);
	//cout << "Ptext: " << bitset_to_hex<64>(bitset_dechunk32<64>(X)) << "\n";
	//string poptext = bitset_to_hex<64>(bitset_dechunk32<64>(X));
	//cout << "Ptext: " << poptext << "\n";
	DESRoundE(X[1], X[0], RKS);
	//cout << "Ctext: " << bitset_to_hex<64>(bitset_dechunk32<64>(X)) << "\n";
	//string coptext = bitset_to_hex<64>(bitset_dechunk32<64>(X));
	//cout << "Ctext: " << coptext << "\n";
	DESRoundD(X[1], X[0], RKS);
	cout << "Dtext: " << bitset_to_hex<64>(bitset_dechunk32<64>(X)) << "\n";
	return 0;
}