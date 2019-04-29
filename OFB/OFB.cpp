#include <bitset>
#include <vector>
#include <random>
#include <cstdint>
using namespace std;

template <int L, int B, bitset<B> (*do_encrypt)(bitset<B>, bitset<L>)>
void OFB_E (vector<bitset<B>>& X, bitset<L> K) {
	bitset<B> IV (0);
	uint32_t IVt;
	random_device rd;
	for (int n = 0; n < B/32; n++) {
		//TODO: add redundancy for random device failure
		IVt = rd();
		IV |= (bitset<B>(IVt) << n*32);
	}
	size_t xs = X.size();
	X.push_back(bitset<B> (0));
	bitset<B> toe = X.front();
	X[0] = IV;
	for (size_t n = 1; n <= xs; n++) {
		bitset<B> fwd = X[n];
		bitset<B> KS = do_encrypt(X[n-1], K);
		X[n] = KS ^ toe;
		toe = fwd;
	}
}

template <int L, int B, bitset<B> (*do_encrypt)(bitset<B>, bitset<L>)>
void OFB_D (vector<bitset<B>>& Y, bitset<L> K) {
	bitset<B> tod = Y.back();
	Y[Y.size() - 1] = bitset<B> (0);
	for (size_t n = Y.size() - 1; n > 0; n--) {
		bitset<B> fwd = Y[n-1];
		bitset<B> KS = do_encrypt(fwd, K);
		Y[n-1] = KS ^ tod;
		tod = fwd;
	}
	Y.pop_back();
}