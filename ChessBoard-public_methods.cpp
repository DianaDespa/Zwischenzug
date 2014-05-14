// Zugzwang Chess Engine

// Methods: deleteTable,
//			initializeBitboard
//			randomPiece,
//			updateOpponentMove,
//			initialPosFunc,
//			finalPosFunc.

#include "ChessBoard.h"

using namespace Auxiliary;

// Frees allocated memory for table.
void ChessBoard::deleteTable() {
	if (table != NULL)
		delete table;
}

// Initialises all the bitboards, the board of piece codes, the flags and the
// class variables.
void ChessBoard::initializeBitboard() {

	table = new board();
	srand(time(NULL));
	table->occupied = WHITE_PAWN | BLACK_PAWN | WHITE_ROOK | BLACK_ROOK
					| WHITE_KNIGHT | BLACK_KNIGHT | WHITE_BISHOP | BLACK_BISHOP
					| WHITE_QUEEN | BLACK_QUEEN | WHITE_KING | BLACK_KING ;


	table->whitePieces = WHITE_PAWN | WHITE_ROOK | WHITE_KNIGHT |
						WHITE_BISHOP | WHITE_QUEEN | WHITE_KING;
	table->blackPieces = BLACK_PAWN | BLACK_ROOK | BLACK_KNIGHT |
						BLACK_BISHOP | BLACK_QUEEN | BLACK_KING;

	table->whitePawns = WHITE_PAWN;
	table->blackPawns = BLACK_PAWN;
	table->whiteRooks = WHITE_ROOK;
	table->blackRooks = BLACK_ROOK;
	table->whiteBishops = WHITE_BISHOP;
	table->blackBishops = BLACK_BISHOP;
	table->whiteKnights = WHITE_KNIGHT;
	table->blackKnights = BLACK_KNIGHT;
	table->whiteQueens = WHITE_QUEEN;
	table->blackQueens = BLACK_QUEEN;
	table->whiteKing = WHITE_KING;
	table->blackKing = BLACK_KING;

	table->pieces[0].name = WHITE_ROOK_CODE;
	table->pieces[7].name = WHITE_ROOK_CODE;

	table->pieces[1].name = WHITE_KNIGHT_CODE;
	table->pieces[6].name = WHITE_KNIGHT_CODE;

	table->pieces[2].name = WHITE_BISHOP_CODE;
	table->pieces[5].name = WHITE_BISHOP_CODE;
	
	table->pieces[3].name = WHITE_QUEEN_CODE;
	table->pieces[4].name = WHITE_KING_CODE;

	table->pieces[56].name = BLACK_ROOK_CODE;
	table->pieces[63].name = BLACK_ROOK_CODE;

	table->pieces[57].name = BLACK_KNIGHT_CODE;
	table->pieces[62].name = BLACK_KNIGHT_CODE;

	table->pieces[58].name = BLACK_BISHOP_CODE;
	table->pieces[61].name = BLACK_BISHOP_CODE;
	
	table->pieces[59].name = BLACK_QUEEN_CODE;
	table->pieces[60].name = BLACK_KING_CODE;

	int i;

	for (i = 8 ; i <= 15 ; ++i) {
		table->pieces[i].name = WHITE_PAWN_CODE;
	}

	for (i = 48 ; i <= 55 ; ++i) {
		table->pieces[i].name = BLACK_PAWN_CODE;
	}

	for (i = 16 ; i <= 47 ; ++i) {
		table->pieces[i].name = EMPTY_CODE;
	}
	
	for (i = 0; i < 64; ++i) {	
		table->pieces[i].nextAttacks = 0ULL;
		table->pieces[i].nextMoves = 0ULL;
	}
	queen_flag = false;
	castling_possible = true;
	initial_position = 0;
	final_position = 0;
	white_en_passant = 0;
	black_en_passant = 0;
	final_pos_opponent = 0;
	table->whiteLostPieces.clear();
	table->blackLostPieces.clear();
	updateBoard();
}

// Returns the algebraic notation corresponding to initial_position.
std::string ChessBoard::initialPosFunc(){
	return ALPHA_NUMERIC_POSITIONS[initial_position];
}

// Returns the algebraic notation corresponding to final_position.
std::string ChessBoard::finalPosFunc(){
	return ALPHA_NUMERIC_POSITIONS[final_position];
}

// Moves opponent's piece on the board.
void ChessBoard::updateOpponentMove(char* positions, bool isWhite) {	
	int file1 = positions[0] - 'a'; int rank1 = positions[1] - '1';
	int file2 = positions[2] - 'a'; int rank2 = positions[3] - '1';

	int initial_pos = rank1 * 8 + file1;
	final_pos_opponent = rank2 * 8 + file2;
	movePiece(initial_pos, final_pos_opponent);
	
	// Check for castling move from the opponent.
	if (castling_recognition(initial_pos, final_pos_opponent, isWhite))
		return;
	
	// Check for en passant move from the opponent.
	en_passant_recognition(isWhite);
}

// Chooses a random available piece to move on the board.
// Returns 0 if there is a piece that can simply be moved, 1 if a piece was 
// moved and the engine won, -1 if the engine cannot make a valid move (the
// engine lost), 2 if the engine is in stalemate.
int ChessBoard::getMove(bool isWhite) {
    int security = kingIsSafe(isWhite);
	if (security == 0) { // everyhting is ok
		score_max sc = negaMax(INT_MIN, INT_MAX, 4, isWhite);
		if (sc.positions.first != -1) {
			movePiece(sc.positions.first, sc.positions.second);
			initial_position = sc.positions.first;
			final_position = sc.positions.second;
			return 0;
		} else {
			return 2;
		}
	} else if (security == 1) {
		return 0; // everyhting is ok
	}
	return -1; // lost game
}

