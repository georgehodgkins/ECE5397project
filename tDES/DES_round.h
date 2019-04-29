#ifndef DES_ROUND_H
#define DES_ROUND_H
#include <cstdint>
#include <bitset>

void DESRoundE (uint32_t& L, uint32_t& R, uint8_t *roundKey);

void DESRoundD (uint32_t& L, uint32_t& R, uint8_t *roundKey);

void DESFeistel(uint32_t& X, uint8_t *roundKey);

uint8_t* DESExpand(uint32_t X, uint8_t *EX);

uint32_t DESScramble(uint8_t *EX);

void DESFeistelPerm(uint32_t& X);

void DESRoundKeyGen(std::bitset<64> K, uint8_t **RK);
#endif