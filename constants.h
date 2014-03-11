#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define WHITE_PAWN 0x000000000000FF00
#define BLACK_PAWN 0x00FF000000000000
#define WHITE_ROOK 0x0000000000000081
#define BLACK_ROOK 0x8100000000000000
#define WHITE_KNIGHT 0x0000000000000042
#define BLACK_KNIGHT 0x4200000000000000
#define WHITE_BISHOP 0x0000000000000024
#define BLACK_BISHOP 0x2400000000000000
#define WHITE_QUEEN 0x0000000000000010
#define BLACK_QUEEN 0x1000000000000000
#define WHITE_KING 0x0000000000000008
#define BLACK_KING 0x0800000000000000

typedef unsigned long long BITBOARD;

typedef enum COLOUR { WHITE, BLACK };

typedef enum PIECE { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, EMPTY };


#endif
