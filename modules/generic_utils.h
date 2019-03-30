#include <bitset>
#include <cstdint>
using namespace std;

template <int L>
void bitset_chunk8<L>(bitset<L> B, uint8_t *A, int n, int o = 0);

template <int L>
bitset<L> bitset_dechunk8(uint8_t *A);

inline void xor4bytes (uint8_t *dest, uint8_t *x1, uint8_t *x2);

uint8_t GFmul(uint8_t a, uint8_t b);