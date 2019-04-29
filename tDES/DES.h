#pragma once
#include <bitset>
using namespace std;


bitset<128> DES_E(bitset<128> X, bitset<64> K);

bitset<128> DES_D(bitset<128> Y, bitset<64> K);