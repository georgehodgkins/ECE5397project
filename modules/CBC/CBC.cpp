#include <bitset>
#include <vector>
#include <random>
#include <cstdint>
using namespace std;

template <int L>
void CBC_E (vector<bitset<128>>& X, bitset<128> (*do_encrypt)(bitset<128>, bitset<L>), bitset<L> K) {
	bitset<128> IV (0);
	uint32_t IVt;
	random_device rd;
	for (int n = 0; n < 4; n++) {
		//TODO: add redundancy for random device failure
		IVt = rd();
		IV |= (bitset<128>(IVt) << n*32);
	}
	size_t xs = X.size();
	X.push_back(bitset<128> (0));
	bitset<128> toe = X[0];
	X[0] = IV;
	for (size_t n = 1; n <= xs; n++) {
		bitset<128> fwd = X[n];
		X[n] = (do_encrypt(toe, K) ^ X[n-1]);
		toe = fwd;
	}
}

template <int L>
void CBC_D (vector<bitset<128>>& Y, bitset<128> (*do_decrypt)(bitset<128>, bitset<L>), bitset<L> K) {
	bitset<128> tod = Y[Y.size() - 1];
	Y[Y.size()-1] = bitset<128> (0);
	for (size_t n = Y.size() - 1; n > 0; n--) {
		bitset<128> fwd = Y[n-1];
		Y[n-1] = do_decrypt(tod ^ fwd, K);
		tod = fwd;
	}
	Y.pop_back();
}