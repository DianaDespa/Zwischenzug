#ifndef _FUNC_H
#define _FUNC_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "constants.h"

class ChessBoard {
private:
	static char* ALPHA_NUMERIC_POSITIONS[64];
	static board* table;
	static int initial_position, final_position;
	static bool generateValidPawnMove(int pos, bool white);
	static bool generateValidPawnAttack(int pos, bool white);
	static bool randomPositionPawn(bool white);
	static std::string convertToBitString(long long value);

public:
	ChessBoard(void);
	~ChessBoard(void);
	
	static void updateOpponentMove(char* positions, bool isWhite);
	static void initializeBitboard(void);
	static void movePiece(int initial_pos, int final_pos);
	static bool randomPiece(bool white);
	static char* finalPosFunc(void);
	static char* initialPosFunc(void);
};

#endif
