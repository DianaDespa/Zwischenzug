#ifndef PAWN_H_
#define PAWN_H_

#include "constants.h"

namespace Pawn {
	BITBOARD pawnAttacks(int pos, bool isWhite);
	BITBOARD pawnMove(int pos, bool isWhite);
}

#endif /* PAWN_H_ */
