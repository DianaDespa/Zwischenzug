// Zugzwang Chess Engine

#include "auxiliary.h"

std::string Auxiliary::convertToBitString(BITBOARD value) {
	std::string str(64, '0');

	for (int i = 0; i < 64; i++)
	{
		if ((1ll << i) & value)
			str[i] = '1';
	}

	return str;
}

void Auxiliary::printBitboard(BITBOARD b) {
	std::string str = convertToBitString(b);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::cout << str[i * 8 + j] << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<int> Auxiliary::getOneBits(BITBOARD x) {
	std::vector<int> res;
	for (int i = 0; i < 64; ++i) {
		if ((1ULL << i) & x) {
			res.push_back(i);
		}
	}
	return res;
}
