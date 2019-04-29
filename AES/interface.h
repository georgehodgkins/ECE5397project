#include <bitset>

bitset<128> AES_128_E (bitset<128> X, bitset<128> K);
bitset<128> AES_128_D (bitset<128> Y, bitset<128> K);
bitset<128> AES_192_E (bitset<128> X, bitset<192> K);
bitset<128> AES_192_D (bitset<128> Y, bitset<192> K);
bitset<128> AES_256_E (bitset<128> X, bitset<256> K);
bitset<128> AES_256_D (bitset<128> Y, bitset<256> K);