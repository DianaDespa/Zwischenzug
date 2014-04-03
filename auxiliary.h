#ifndef AUXILIARY_H_
#define AUXILIARY_H_

#include <string>
#include <vector>
#include "constants.h"

namespace Auxiliary {
	std::string convertToBitString(BITBOARD value);
	std::vector<int> getOneBits(BITBOARD x);
};

#endif /* AUXILIARY_H_ */
