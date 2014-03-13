//VEZI COMENTARII CU EXPLICATII INAINTE DE int main() !!!!!!!!!!
#ifndef _FUNC_H
#define _FUNC_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include "constants.h"

class functii {

	public: 
		board table;
		int initial_position, final_position;
		board getBoard(void);
		functii(void);
		std::string convertToBitString( long long value);
		bool Is_Bit_Set(BITBOARD table, int pos);
		void Move_Piece(int initial_pos, int final_pos, bool white);
		void InitializeBitboard(void);
		bool generate_valid_move(int pos, bool white);
		bool generate_valid_attack(int pos, bool white);
		bool Random_Position_Pawn(bool white);
		bool Random_Piece(bool white);
		char* final_position_func(void);
		char* initial_position_func(void);
		void Update_Opponent_Move(char* positions,bool white);
};

#endif