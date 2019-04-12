#include "CBC.cpp"
#include "../AES/AES.cpp"
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
	vector<bitset<128>> X (0);
	readin.close();
	cout << "Blocked plaintext:\n";
	for (size_t n = 0; n < x_init.size(); n += 32) {
		string r (x_init, n, 32);
		cout << r << '\n';
		X.emplace_back(hex_to_bitset<128>(r));
	}
	string key_h ("6fec7323da898c038392fde094ca012bf6473829a401234da850c8594bbaf371");
	bitset<256> K = hex_to_bitset<256> (key_h);
	cout << "\nEncrypting...";
	CBC_E<256> (X, AES_E<256>, K);
	cout << "done.\n\n";
	string iv = bitset_to_hex<128>(X[0]);
	cout << "initial vector: " << iv << "\n\n";
	cout << "blocked ciphertext:\n";
	for (size_t n = 1; n < X.size(); n++) {
		cout << bitset_to_hex<128>(X[n]) << '\n';
	}
	cout << "\nDecrypting...";
	CBC_D<256> (X, AES_D<256>, K);
	cout << "done.\n\n";
	cout << "Decrypted plaintext blocks:\n";
	for (size_t n = 0; n < X.size(); n++) {
		cout << bitset_to_hex<128>(X[n]) << '\n';
	}
	cout << '\n';
	return 0;
}