#include "DES.cpp"
#include <bitset>
#include "../format/bitset_hex.cpp"
#include <iostream>
using namespace std;

int main () {
	string ptext_h ("de094ca012bf6473");
	string key_h ("f45ec21348eab90a");
	bitset<64> ptext = hex_to_bitset<64> (ptext_h);
	bitset<64> key = hex_to_bitset<64> (key_h);
	cout << "Sample plaintext: " << ptext_h << "\n\n";
	cout << "Sample key: " << key_h << "\n";
	cout << "Encrypting...";
	bitset<64> ctext = DES_E(ptext, key);
	cout << "done. \nCiphertext: " << bitset_to_hex<64>(ctext) << "\n";
	cout << "Decrypting...";
	bitset<64> dtext = DES_D(ctext, key);
	cout << "done.\nDecrypted ciphertext: " << bitset_to_hex<64>(dtext) << '\n';
	return 0;
}