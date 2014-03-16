// Zugzwang Chess Engine - stage 1

#ifndef _FUNC_H
#define _FUNC_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "constants.h"

// Class that implements the chess board's current state and functions for
// generating moves and checking move validity.
class ChessBoard {
private:
	static std::string ALPHA_NUMERIC_POSITIONS[64];
	static board* table;
	static int initial_position, final_position;
	static bool generateValidPawnMove(int pos, bool isWhite);
	static bool generateValidPawnAttack(int pos, bool isWhite);
	static bool randomPositionPawn(bool isWhite);
	
	static bool kingInDanger(bool isWhite);
	

public:
	ChessBoard(void);
	~ChessBoard(void);
	static std::string convertToBitString(long long value);
	static BITBOARD getAttacks(int pos);
	
	static void updateOpponentMove(char* positions);
	static void initializeBitboard(void);
	static void movePiece(int initial_pos, int final_pos);
	static bool randomPiece(bool isWhite);
	static std::string finalPosFunc(void);
	static std::string initialPosFunc(void);
};

#endif
