#include "AES.cpp"
#include <iostream>
#include <bitset>
#include <string>
#include <cstdint>
using namespace std;

int main () {
	//debugger-look test
	bitset<128> testDat (3367540201);
	bitset<128> testKey (123456789);
	cout << "Test dat (bin):\n" << testDat.to_string() << '\n';
	bitset<128> encr = AES_E<128> (testDat, testKey);
	cout << "\nEncrypted dat (bin):\n" << encr.to_string() << '\n';
	bitset<128> decr = AES_D<128> (encr, testKey);
	cout << "\nDecrypted dat (bin):\n" << decr.to_string();
	return 0;
}
	