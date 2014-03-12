#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define WHITE_PAWN 0x000000000000FF00ULL
#define BLACK_PAWN 0x00FF000000000000ULL
#define WHITE_ROOK 0x0000000000000081ULL
#define BLACK_ROOK 0x8100000000000000ULL
#define WHITE_KNIGHT 0x0000000000000042ULL
#define BLACK_KNIGHT 0x4200000000000000ULL
#define WHITE_BISHOP 0x0000000000000024ULL
#define BLACK_BISHOP 0x2400000000000000ULL
#define WHITE_QUEEN 0x0000000000000010ULL
#define BLACK_QUEEN 0x1000000000000000ULL
#define WHITE_KING 0x0000000000000008ULL
#define BLACK_KING 0x0800000000000000ULL

#define WHITE_PAWN_CODE 'P' 
#define BLACK_PAWN_CODE 'p'
#define WHITE_ROOK_CODE 'R'
#define BLACK_ROOK_CODE 'r'
#define WHITE_KNIGHT_CODE 'N'
#define BLACK_KNIGHT_CODE 'n'
#define WHITE_BISHOP_CODE 'B'
#define BLACK_BISHOP_CODE 'b'
#define WHITE_QUEEN_CODE 'Q'
#define BLACK_QUEEN_CODE 'q'
#define WHITE_KING_CODE 'K'
#define BLACK_KING_CODE 'k'
#define EMPTY_CODE '0'
typedef unsigned long long BITBOARD;

typedef struct board {
	BITBOARD existance;
	char nametable[64];
};
char* ALPHA_NUMERIC_POSITIONS[64] = {"a1","b1","c1","d1","e1","f1","g1","h1",
										  "a2","b2","c2","d2","e2","f2","g2","h2",
										  "a3","b3","c3","d3","e3","f3","g3","h3",
										  "a4","b4","c4","d4","e4","f4","g4","h4",
										  "a5","b5","c5","d5","e5","f5","g5","h5",
										  "a6","b6","c6","d6","e6","f6","g6","h6",
										  "a7","b7","c7","d7","e7","f7","g7","h7",
										  "a8","b8","c8","d8","e8","f8","g8","h8"};


#endif
