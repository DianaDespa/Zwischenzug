//VEZI COMENTARII CU EXPLICATII INAINTE DE int main() !!!!!!!!!!
#ifndef _FUNC_H
#define _FUNC_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include "constants.h"

class functii {

//private:
	
public:
	board table;
	int initial_position, final_position;
	board getBoard(void);
	functii(void);
	std::string convertToBitString( long long value);
	bool isBitSet(BITBOARD table, int pos);
	void movePiece(int initial_pos, int final_pos);
	void initializeBitboard(void);
	bool generateValidPawnMove(int pos, bool white);
	bool generateValidPawnAttack(int pos, bool white);
	bool randomPositionPawn(bool white);
	bool randomPiece(bool white);
	char* finalPosFunc(void);
	char* initialPosFunc(void);
	void updateOpponentMove(char* positions,bool white);
};

#endif