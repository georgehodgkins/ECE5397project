#include "OFB.cpp"
#include "../tDES/tDES.cpp"
#include "../format/bitset_hex.cpp"
#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>
using namespace std;

int main () {
	ifstream readin ("test_input.txt");
	string x_init;
	getline(readin, x_init);
	vector<bitset<64>> X (0);
	readin.close();
	cout << "Blocked plaintext:\n";
	for (size_t n = 0; n < x_init.size(); n += 16) {
		string r (x_init, n, 16);
		cout << r << '\n';
		X.emplace_back(hex_to_bitset<64>(r));
	}
	string key_h ("6fec7323da898c03f21473e78920f09ab748d5e52760a6e1");
	bitset<192> K = hex_to_bitset<192> (key_h);
	cout << "\nEncrypting...";
	OFB_E<192, 64> (X, tDES_E, K);
	cout << "done.\n\n";
	string iv = bitset_to_hex<64>(X[0]);
	cout << "initial vector: " << iv << "\n\n";
	cout << "blocked ciphertext:\n";
	for (size_t n = 1; n < X.size(); n++) {
		cout << bitset_to_hex<64>(X[n]) << '\n';
	}
	cout << "\nDecrypting...";
	OFB_D<192, 64> (X, tDES_E, K);
	cout << "done.\n\n";
	cout << "Decrypted plaintext blocks:\n";
	for (size_t n = 0; n < X.size(); n++) {
		cout << bitset_to_hex<64>(X[n]) << '\n';
	}
	cout << '\n';
	return 0;
}