// Zugzwang Chess Engine - stage 1

#ifndef _FUNC_H
#define _FUNC_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include "constants.h"
#include "pawn.h"
#include "auxiliary.h"

// Class that implements the chess board's current state and functions for
// generating moves and checking move validity.
class ChessBoard {
private:

	static std::string ALPHA_NUMERIC_POSITIONS[64];
	static int initial_position, final_position;
	static bool generateValidPawnMove(int pos, bool isWhite);
	static bool generateValidPawnAttack(int pos, bool isWhite);
	static bool randomPositionPawn(bool isWhite);
	static void updateBoard(void);


public:
	ChessBoard(void);
	~ChessBoard(void);
    static int kingInDanger(bool isWhite);
	static int kingIsSafe(bool isWhite);
	static int white_en_passant, black_en_passant, final_pos_opponent;
    static int flag;
	static void updateOpponentMove(char* positions, bool isWhite);
	static void initializeBitboard(void);
	static void movePiece(int initial_pos, int final_pos);
	static int randomPiece(bool isWhite);
	static std::string finalPosFunc(void);
	static std::string initialPosFunc(void);
	static void en_passant_recognition(bool isWhite);
	static void castling_recognition(bool isWhite, bool isSmall);
    static bool try_moving_piece(int start, int end, bool isWhite);
	//MUTA
	static board* table;
	static std::vector<int> generateValidKingMove(int pos, bool isWhite);
	static std::vector<int> generateValidKnightMove(int pos, bool isWhite);
	static std::vector<int> generateValidBishopMove(int pos, bool isWhite);
	static std::vector<int> generateValidRookMove(int pos, bool isWhite);
	static std::vector<int> generateValidQueenMove(int pos, bool isWhite);
};

#endif

