//Zugzwang Chess Engine - stage 1

#include "ChessBoard.h"

using namespace Pawn;
using namespace Auxiliary;

// Keeps track of the board's current start.
board* ChessBoard::table = new board();

// Positions from and to which a piece moves.
int ChessBoard::initial_position = 0,
	ChessBoard::final_position = 0;
int ChessBoard::flag = 0;
int ChessBoard::final_pos_opponent = 0,
	ChessBoard::white_en_passant = 0, 
	ChessBoard::black_en_passant = 0;

// Algebraic notation for each square of the board.
std::string ChessBoard::ALPHA_NUMERIC_POSITIONS[64] =
	{"a1","b1","c1","d1","e1","f1","g1","h1",
	"a2","b2","c2","d2","e2","f2","g2","h2",
	"a3","b3","c3","d3","e3","f3","g3","h3",
	"a4","b4","c4","d4","e4","f4","g4","h4",
	"a5","b5","c5","d5","e5","f5","g5","h5",
	"a6","b6","c6","d6","e6","f6","g6","h6",
	"a7","b7","c7","d7","e7","f7","g7","h7",
	"a8","b8","c8","d8","e8","f8","g8","h8"};

// Constructor
ChessBoard::ChessBoard(){
}

// Destructor
ChessBoard::~ChessBoard() {
	delete table;
}

int ChessBoard::kingInDanger(bool isWhite) {
	std::vector<int> v;
	size_t i;
	if (isWhite) {
		v = getOneBits(table->blackPieces);
		for (i = 0; i < v.size(); ++i) {
			//displayB(table->pieces[v[i]].nextMoves);
			if (table->pieces[v[i]].nextAttacks & table->whiteKing) {
				return v[i];
			}
		}
	}
	else {
		v = getOneBits(table->whitePieces);
		for (i = 0; i < v.size(); ++i) {
			//displayB(table->pieces[v[i]].nextMoves);
			if (table->pieces[v[i]].nextAttacks & table->blackKing) {
				return v[i];
			}
		}
	}
	return -1;
}

bool ChessBoard::try_moving_piece(int start, int end, bool isWhite) {
    board* backup = new board();
    *backup = *table;

    movePiece(start, end);
    if(kingInDanger(isWhite) == -1) {
    	initial_position = start;
    	final_position = end;
        free(backup);        
        return true;
    }
    *table = *backup;
    free(backup); 
    return false;
}

// Move a piece across the board from initial_pos to final_pos.
// Update the bitboards for the occupied squares, white pieces, black pieces,
// and all the piece types, depending on the piece that moves and whether the
// move is a capture.
void ChessBoard::movePiece(int initial_pos, int final_pos) {

	// Set the bit for the initial position to 0.
	table->occupied &= ~(1ULL << (initial_pos));

	// Swap squares.
	char aux = table->pieces[initial_pos].name;
	table->pieces[initial_pos].name = table->pieces[final_pos].name;
	table->pieces[final_pos].name = aux;

	// Check for capture. If there was a piece on the final position (which is
	// now on the final position) the move is a capture, and the bitboards
	// corresponding to the captures piece are updated.
	if (table->pieces[initial_pos].name != EMPTY_CODE) {
		if (table->pieces[initial_pos].name < 'a') {
			switch (table->pieces[initial_pos].name){
			case 'P':
				table->whitePawns &= ~(1ULL << final_pos);
				break;
			case 'R':
				table->whiteRooks &= ~(1ULL << final_pos);
				break;
			case 'N':
				table->whiteKnights &= ~(1ULL << final_pos);
				break;
			case 'B':
				table->whiteBishops &= ~(1ULL << final_pos);
				break;
			case 'Q':
				table->whiteQueens &= ~(1ULL << final_pos);
				break;
			}
			table->whitePieces &= ~(1ULL << final_pos);
			table->whiteLostPieces.push_back(table->pieces[initial_pos].name);
		}else {
			switch(table->pieces[initial_pos].name) {
			case 'p':
				table->blackPawns &= ~(1ULL << final_pos);
				break;
			case 'r':
				table->blackRooks &= ~(1ULL << final_pos);
				break;
			case 'n':
				table->blackKnights &= ~(1ULL << final_pos);
				break;
			case 'b':
				table->blackBishops &= ~(1ULL << final_pos);
				break;
			case 'q':
				table->blackQueens &= ~(1ULL << final_pos);
				break;
			}
			table->blackPieces &= ~(1ULL << final_pos);
			table->blackLostPieces.push_back(table->pieces[initial_pos].name);
		}
		table->pieces[initial_pos].name = EMPTY_CODE;
		table->pieces[initial_pos].nextMoves = 0ULL;
		table->pieces[initial_pos].nextAttacks = 0ULL;
	}

	// If the move is not a capture, then update the bitboard for occupied
	// squares.
	//else {
		table->occupied |= 1ULL << (final_pos);
	//}

	// Update the bitboards corresponding to the moving piece.
	if (table->pieces[final_pos].name < 'a') {
		switch (table->pieces[final_pos].name){
		case 'P':
			table->whitePawns &= ~(1ULL << initial_pos);
			//white pawn promotion
			if (56 <= final_pos && final_pos <= 63) {
				table->whiteQueens |= 1ULL << final_pos;
				table->pieces[final_pos].name = 'Q';
			} else {
				table->whitePawns |= 1ULL << final_pos;
			}
			break;
		case 'R':
			table->whiteRooks &= ~(1ULL << initial_pos);
			table->whiteRooks |= 1ULL << final_pos;
			break;
		case 'N':
			table->whiteKnights &= ~(1ULL << initial_pos);
			table->whiteKnights |= 1ULL << final_pos;
			break;
		case 'B':
			table->whiteBishops &= ~(1ULL << initial_pos);
			table->whiteBishops |= 1ULL << final_pos;
			break;
		case 'Q':
			table->whiteQueens &= ~(1ULL << initial_pos);
			table->whiteQueens |= 1ULL << final_pos;
			break;
		case 'K':
			table->whiteKing = 1ULL << final_pos;
			break;
		}
		table->whitePieces &= ~(1ULL << initial_pos);
		table->whitePieces |= 1ULL << final_pos;
	}else {
		switch(table->pieces[final_pos].name) {
		case 'p':
			table->blackPawns &= ~(1ULL << initial_pos);
			// black pawn promotion
			if (0 <= final_pos && final_pos <= 7) {
				table->blackQueens |= 1ULL << final_pos;
				table->pieces[final_pos].name = 'q';
			} else {
				table->blackPawns |= 1ULL << final_pos;
			}
			break;
		case 'r':
			table->blackRooks &= ~(1ULL << initial_pos);
			table->blackRooks |= 1ULL << final_pos;
			break;
		case 'n':
			table->blackKnights &= ~(1ULL << initial_pos);
			table->blackKnights |= 1ULL << final_pos;
			break;
		case 'b':
			table->blackBishops &= ~(1ULL << initial_pos);
			table->blackBishops |= 1ULL << final_pos;
			break;
		case 'q':
			table->blackQueens &= ~(1ULL << initial_pos);
			table->blackQueens |= 1ULL << final_pos;
			break;
		case 'k':
			table->blackKing = 1ULL << final_pos;
			break;
		}
		table->blackPieces &= ~(1ULL << initial_pos);
		table->blackPieces |= 1ULL << final_pos;
	}

	updateBoard();
}

// Initialises all the bitboards and the board of piece codes.
void ChessBoard::initializeBitboard() {

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
		table->pieces[i].nextMoves = pawnMove(i, true);
	}

	for (i = 48 ; i <= 55 ; ++i) {
		table->pieces[i].name = BLACK_PAWN_CODE;
		table->pieces[i].nextMoves = pawnMove(i, false);
	}

	for (i = 16 ; i <= 47 ; ++i) {
		table->pieces[i].name = EMPTY_CODE;
	}
	
	for (i = 0; i < 64; ++i) {	
		table->pieces[i].nextAttacks = 0ULL;
		table->pieces[i].nextMoves = 0ULL;
	}
	flag = 0;
	table->whiteLostPieces.clear();
	table->blackLostPieces.clear();
}


void ChessBoard::updateBoard(){
	for (int i = 0; i < 64; ++i) {
		switch (table->pieces[i].name) {
		case 'P':
			if (table->pieces[i + 8].name == EMPTY_CODE){
				table->pieces[i].nextMoves = pawnMove(i, true) & ~table->occupied;
			}else{
				table->pieces[i].nextMoves = 0ULL;
			}
			table->pieces[i].nextAttacks = pawnAttacks(i, true) & table->blackPieces;
			break;
		case 'p':
			if (table->pieces[i - 8].name == EMPTY_CODE){
				table->pieces[i].nextMoves = pawnMove(i, false) & ~table->occupied;
			}else{
				table->pieces[i].nextMoves = 0ULL;
			}
			table->pieces[i].nextAttacks = pawnAttacks(i, false) & table->whitePieces;
			break;
		case 'R':
            generateValidRookMove(i, true);
			break;
		case 'r':
            generateValidRookMove(i, false);
			break;
		case 'B':
			generateValidBishopMove(i, true);
			break;
		case 'b':
			generateValidBishopMove(i, false);
			break;
		case 'N':
            generateValidKnightMove(i, true);
			break;
		case 'n':
            generateValidKnightMove(i, false);
			break;
		case 'Q':
            generateValidQueenMove(i, true);
			break;
		case 'q':
            generateValidQueenMove(i, false);
			break;
		case 'K':
            generateValidKingMove(i, true);
			break;
		case 'k':
            generateValidKingMove(i, false);
			break;
		}
	}
}

// Checks if there is a valid move for the pawn on the pos position.
// If there are more than one, chooses randomly, moves the pawn and updates
// final_position.
// Returns true if a valid move exists, false if not.
bool ChessBoard::generateValidPawnMove(int pos, bool isWhite){
	bool b1 = false;
	bool b2 = false;

	if (isWhite){
		// If playing white, check ahead 8 positions in array of codes, and
		// check ahead 16 positions if pawn is in start position (second row)
		// for existing pieces.
		if	(table->pieces[pos + 8].name == EMPTY_CODE) {
			b2 = true;
			if ((15 >= pos) && (pos >= 8) &&
				(table->pieces[pos + 16].name == EMPTY_CODE)){
				b1 = true;
			}
		}
		if (b2){
			if (b1) {
				if(rand() % 2 == 0){
					if (try_moving_piece(pos, pos + 8, isWhite)){
						return true;
					}
				}
				else{
					if (try_moving_piece(pos, pos + 16, isWhite)) {
						white_en_passant = final_position;
						return true;
					}
				}
			}
			else {
				if (try_moving_piece(pos, pos + 8, isWhite)) {
					return true;
				}
			}
		}
	}
	else{
		// If playing black, check behind 8 positions in array of codes, and
		// check behind 16 positions if pawn is in start position (second to
		// last row) for existing pieces.
		if (table->pieces[pos - 8].name == EMPTY_CODE) {
			b2 = true;
			if ((55 >= pos) && (pos >= 48) &&
				(table->pieces[pos - 16].name == EMPTY_CODE)){
				b1 = true;
			}
		}
		if (b2){
			if (b1) {
				if(rand() % 2 == 0){
					if (try_moving_piece(pos, pos - 8, isWhite)) {
						return true;
					}
				}
				else{
					if (try_moving_piece(pos, pos - 16, isWhite)) {
						black_en_passant = final_position;
						return true;
					}
				}
			}
			else {
				if (try_moving_piece(pos, pos - 8, isWhite)) {
					return true;
				}
			}
		}
	}
	return false;
}

// Checks if the pawn on the pos position can attack a neighboring piece.
// A pawn captures diagonally, one square forward and to the left or right.
// If there are more than one possible captures, chooses randomly, moves the
// pawn and updates final_position.
// Returns true if a capture is possible, false if not.
bool ChessBoard::generateValidPawnAttack(int pos, bool isWhite){
	bool b1 = false;
	bool b2 = false;

	if (isWhite){
		// If playing white and pawn is on the margin of the board, checks ahead
		// in the array of codes for existing pieces, depending on which margin
		// the pawn is on.
		if (pos % 8 == 0){
			if (table->pieces[pos + 9].name == BLACK_PAWN_CODE |
				table->pieces[pos + 9].name == BLACK_ROOK_CODE |
				table->pieces[pos + 9].name == BLACK_KNIGHT_CODE |
				table->pieces[pos + 9].name == BLACK_BISHOP_CODE |
				table->pieces[pos + 9].name == BLACK_QUEEN_CODE ){

				if (try_moving_piece(pos, pos + 9, isWhite)) {
					return true;
				}
			}
			return false;
		}
		else if (pos % 8 == 7){
			if (table->pieces[pos + 7].name == BLACK_PAWN_CODE |
				table->pieces[pos + 7].name == BLACK_ROOK_CODE |
				table->pieces[pos + 7].name == BLACK_KNIGHT_CODE |
				table->pieces[pos + 7].name == BLACK_BISHOP_CODE |
				table->pieces[pos + 7].name == BLACK_QUEEN_CODE ){

				if (try_moving_piece(pos, pos + 7, isWhite)) {
					return true;
				}
			}
			return false;
		}
		else{
			// If playing white and pawn is not on the margin of the board,
			// checks ahead for existing pieces in the array of codes.
			if (table->pieces[pos + 7].name == BLACK_PAWN_CODE |
				table->pieces[pos + 7].name == BLACK_ROOK_CODE |
				table->pieces[pos + 7].name == BLACK_KNIGHT_CODE |
				table->pieces[pos + 7].name == BLACK_BISHOP_CODE |
				table->pieces[pos + 7].name == BLACK_QUEEN_CODE ) {
				b1 = true;
			}
			if (table->pieces[pos + 9].name == BLACK_PAWN_CODE |
				table->pieces[pos + 9].name == BLACK_ROOK_CODE |
				table->pieces[pos + 9].name == BLACK_KNIGHT_CODE |
				table->pieces[pos + 9].name == BLACK_BISHOP_CODE |
				table->pieces[pos + 9].name == BLACK_QUEEN_CODE ){
				b2 = true;
			}
			if (b1 && b2){
				if (rand() % 2 == 0){
					if (try_moving_piece(pos, pos + 9, isWhite)) {
						return true;
					}
				}
				else{
					if (try_moving_piece(pos, pos + 7, isWhite)) {
						return true;
					}
				}
			}
			else if (b1){
				if (try_moving_piece(pos, pos + 7, isWhite)) {
					return true;
				}
			}
			else if (b2){
				if (try_moving_piece(pos, pos + 9, isWhite)) {
					return true;
				}
			}
			return false;
		}
	}
	else{
		// If playing black and pawn is on the margin of the board, checks
		// behind in the array of codes for existing pieces, depending on
		// which margin the pawn is on.
		if (pos % 8 == 0){
			if (table->pieces[pos - 7].name == WHITE_PAWN_CODE |
				table->pieces[pos - 7].name == WHITE_ROOK_CODE |
				table->pieces[pos - 7].name == WHITE_KNIGHT_CODE |
				table->pieces[pos - 7].name == WHITE_BISHOP_CODE |
				table->pieces[pos - 7].name == WHITE_QUEEN_CODE ){

				if (try_moving_piece(pos, pos - 7, isWhite)) {
					return true;
				}
			}
			return false;
		}
		else if (pos % 8 == 7) {
			if (table->pieces[pos - 9].name == WHITE_PAWN_CODE |
				table->pieces[pos - 9].name == WHITE_ROOK_CODE |
				table->pieces[pos - 9].name == WHITE_KNIGHT_CODE |
				table->pieces[pos - 9].name == WHITE_BISHOP_CODE |
				table->pieces[pos - 9].name == WHITE_QUEEN_CODE ){

				if (try_moving_piece(pos, pos - 9, isWhite)) {
					return true;
				}
			}
			return false;
		}
		else{
			// If playing white and pawn is not on the margin of the board,
			// checks behind for existing pieces in the array of codes.
			if (table->pieces[pos - 7].name == WHITE_PAWN_CODE |
				table->pieces[pos - 7].name == WHITE_ROOK_CODE |
				table->pieces[pos - 7].name == WHITE_KNIGHT_CODE |
				table->pieces[pos - 7].name == WHITE_BISHOP_CODE |
				table->pieces[pos - 7].name == WHITE_QUEEN_CODE ) {
				b1 = true;
			}
			if (table->pieces[pos - 9].name == WHITE_PAWN_CODE |
				table->pieces[pos - 9].name == WHITE_ROOK_CODE |
				table->pieces[pos - 9].name == WHITE_KNIGHT_CODE |
				table->pieces[pos - 9].name == WHITE_BISHOP_CODE |
				table->pieces[pos - 9].name == WHITE_QUEEN_CODE ){
				b2 = true;
			}
			if (b1 && b2){
				if(rand() % 2 == 0){
					if (try_moving_piece(pos, pos - 9, isWhite)) {
						return true;
					}
				}
				else{
					if (try_moving_piece(pos, pos - 7, isWhite)) {
						return true;
					}
				}
			}
			else if (b1){
				if (try_moving_piece(pos, pos - 7, isWhite)) {
					return true;
				}
			}
			else if (b2){
				if (try_moving_piece(pos, pos - 9, isWhite)) {
					return true;
				}
			}
			return false;
		}
	}
}


// Chooses a random available pawn to move on the board.
// Returns true if there is a pawn that can be moved, false otherwise.
bool ChessBoard::randomPositionPawn(bool isWhite){
	std::vector<int> v;
	int p;

	// Keeps track of all available pawns, depending on the color of the engine
	// in the vector v.
	if (isWhite)
		v = getOneBits(table->whitePawns);
	else
		v = getOneBits(table->blackPawns);

	// Checks pawns for possible captures and moves. When one is found,
	// update initial_position.
	while (v.size() > 0) {
		p = rand() % v.size();
		if (generateValidPawnAttack(v[p], isWhite)){
			return true;
		}
		if (generateValidPawnMove(v[p], isWhite)){
			return true;
		}
		v.erase(v.begin() + p);
	}
	return false;
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
void ChessBoard::updateOpponentMove(char* positions, bool isWhite){
	if(strcmp(positions,"O-O") == 0){
		//true = rocada mica
		castling_recognition(isWhite, true);
		return;
	}
	else if(strcmp(positions,"O-O-O") == 0) {
		//false = rocada mare
		castling_recognition(isWhite, false);
		return;
	}
		
		
	int file1 = positions[0] - 'a'; int rank1 = positions[1] - '1';
	int file2 = positions[2] - 'a'; int rank2 = positions[3] - '1';

	int initial_pos = rank1 * 8 + file1;
	final_pos_opponent = rank2 * 8 + file2;
	movePiece(initial_pos, final_pos_opponent);
	//en_passant_recognition(isWhite);
	return;
}

std::vector<int> ChessBoard::generateValidQueenMove(int pos, bool isWhite) {
	std::vector<int> available_positions;
	
	
	flag = 1;
    available_positions = generateValidBishopMove(pos, isWhite);
	std::vector<int> aux_vector = generateValidRookMove(pos, isWhite);
    available_positions.insert(available_positions.end(), aux_vector.begin(), aux_vector.end());
    flag = 0;
 

    return available_positions;
}

std::vector<int> ChessBoard::generateValidKingMove(int pos, bool isWhite){
	int offset [] = { 9 , 8, 7, 1, -1, -7, -8, -9};
	std::vector<int> available_positions;
	int final_pos;
	table->pieces[pos].nextMoves = 0ULL;
	
	if (isWhite) {
		for (int i = 0; i < 8; ++i) {
			final_pos = pos + offset[i];
			if (final_pos * (63 - final_pos) >=0 && abs(pos % 8 - final_pos % 8) <= 2) {
				if (table->pieces[final_pos].name == EMPTY_CODE || table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
			}
		}
		table->pieces[pos].nextAttacks = table->pieces[pos].nextMoves & table->blackPieces;
	}
	else{
		for(int i = 0; i < 8; ++i){
			final_pos = pos + offset[i];
			if (final_pos * (63 - final_pos) >=0 && abs(pos % 8 - final_pos % 8) <= 2) {
				if (table->pieces[final_pos].name == EMPTY_CODE || table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
			}
		}
		table->pieces[pos].nextAttacks = table->pieces[pos].nextMoves & table->whitePieces;
	}
	table->pieces[pos].nextMoves &= ~table->occupied;
    return available_positions;
}

std::vector<int> ChessBoard::generateValidKnightMove(int pos, bool isWhite){
	int offset [] = { 10 , 17, 15, 6, -10, -17, -15, -6};
	std::vector<int> available_positions;
	int final_pos;
	table->pieces[pos].nextAttacks = 0ULL;
	table->pieces[pos].nextMoves = 0ULL;
	
	if (isWhite) {
		for (int i = 0; i < 8; ++i) {
			final_pos = pos + offset[i];
			if (final_pos * ( 63 - final_pos) >=0 && abs(pos % 8 - final_pos % 8) <= 2) {
				if (table->pieces[final_pos].name == EMPTY_CODE || table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
			}
		}
        table->pieces[pos].nextAttacks = table->pieces[pos].nextMoves & table->blackPieces;
	} else {
		for (int i = 0; i < 8; i++) {
			final_pos = pos + offset[i];
			if (final_pos * (63 - final_pos) >=0 && abs(pos % 8 - final_pos % 8) <= 2) {
				if (table->pieces[final_pos].name == EMPTY_CODE || table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
			}
		}
        table->pieces[pos].nextAttacks = table->pieces[pos].nextMoves & table->whitePieces;
	}

    table->pieces[pos].nextMoves &= ~table->occupied;

    return available_positions;
}

std::vector<int> ChessBoard::generateValidBishopMove(int pos, bool isWhite) {
	std::vector<int> available_positions;
	int final_pos;
    table->pieces[pos].nextAttacks = 0ULL;
    table->pieces[pos].nextMoves = 0ULL;
	
	if (isWhite) {
		for (int i = 1; i < 8 - pos % 8; ++i) {
			final_pos = pos + 9 * i;
            if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		for (int i = 1; i <= pos % 8; ++i) {
			final_pos = pos - 9 * i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i <= pos % 8; ++i) {
			final_pos = pos + 7 * i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 7  ) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}

		for (int i = 1; i < 8 - pos % 8; ++i) {
			final_pos = pos - 7 * i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
	} else {
		for (int i = 1; i < 8 - pos % 8; ++i) {
			final_pos = pos + 9 * i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i <= pos % 8; ++i) {
			final_pos = pos - 9 * i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i <= pos % 8; ++i) {
			final_pos = pos + 7 * i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i < 8 - pos % 8; ++i) {
			final_pos = pos - 7 * i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
	}
	return available_positions;
}

std::vector<int> ChessBoard::generateValidRookMove(int pos, bool isWhite){
	std::vector<int> available_positions;

	int final_pos;
	if(flag == 0) {
        table->pieces[pos].nextAttacks = 0ULL;
        table->pieces[pos].nextMoves = 0ULL;
    }
	if (isWhite) {
		for (int i = 1; i < 8 - pos % 8; ++i) {
            final_pos = pos + i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i < 8 - pos / 8; ++i) {
			final_pos = pos + 8 * i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a')
				break;
			if (final_pos * (63 - final_pos) >=0 && final_pos / 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		for (int i = 1; i <= pos / 8; ++i) {
			final_pos = pos - 8 * i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a'))
				break;
			if (final_pos * (63 - final_pos) >=0 && final_pos /8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}

		for (int i = 1; i <= pos % 8; ++i) {
			final_pos = pos - i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name < 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				}
				if (table->pieces[final_pos].name > 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
	} else {
		for (int i = 1; i < 8 - pos / 8; ++i) {
			final_pos = pos + 8 * i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a'){
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i <= pos / 8; ++i) {
			final_pos = pos - 8 * i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos / 8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i <= 8 - pos % 8; ++i) {
			final_pos = pos + i;
			if (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a')
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 0) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a') {
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
		
		for (int i = 1; i <= pos % 8; ++i) {
			final_pos = pos - i;
			if (final_pos < 0 || (table->pieces[final_pos].name != EMPTY_CODE && table->pieces[final_pos].name > 'a'))
				break;
			if (final_pos * (63 - final_pos) >= 0 && final_pos % 8 != 7) {
				if (table->pieces[final_pos].name == EMPTY_CODE) {
					available_positions.push_back(final_pos);
                    table->pieces[pos].nextMoves |= 1ULL << final_pos;
				} else
				if (table->pieces[final_pos].name < 'a'){
					available_positions.push_back(final_pos);
					table->pieces[pos].nextAttacks |= 1ULL << final_pos;
					break;
				}
			}
		}
	}
    return available_positions;
}

int ChessBoard::kingIsSafe(bool isWhite) {
	int attacker = kingInDanger(isWhite);
	if (attacker != -1) {
		// se inaltura amenintarea
		std::vector<int> v;
		size_t i;
		if (isWhite) {
			v = getOneBits(table->whitePieces);
		}
		else {
			v = getOneBits(table->blackPieces);
		}
		for (i = 0; i < v.size(); ++i) {
			if (table->pieces[v[i]].nextAttacks & (1ULL << attacker)) {
				if (try_moving_piece(v[i], attacker, isWhite)) {
					return 1;
				}
			}
		}

		//se muta regele
		std::vector<int> king_position, valid_final_moves;
		if(isWhite)
			king_position = getOneBits(table->whiteKing);
		else
			king_position = getOneBits(table->blackKing);

		valid_final_moves = generateValidKingMove(king_position[0], isWhite);

		while (valid_final_moves.size() != 0) {
			int final_king = rand() % valid_final_moves.size();
			if(try_moving_piece(king_position[0], valid_final_moves[final_king], isWhite)) {
				return 1;
			}
			valid_final_moves.erase(valid_final_moves.begin() + final_king);
		}

		//kamikaze

		if ((table->pieces[attacker].name != 'n' && table->pieces[attacker].name != 'p') ||
			(table->pieces[attacker].name != 'N' && table->pieces[attacker].name != 'P')) {

			int file_k = king_position[0] % 8,
				rank_k = king_position[0] / 8,
				file_a = attacker % 8,
				rank_a = attacker / 8;
			int dif_file = file_a - file_k,
				dif_rank = rank_a - rank_k;
			int step;
			BITBOARD mask = 0ULL;
			if (file_k == file_a) {
				step = (rank_k > rank_a) ? 8 : -8;
			} else if (rank_k == rank_a){
				step = (file_k > file_a) ? 1 : -1;
			} else {
				if (dif_rank > 0 && dif_file > 0)
					step = 7;
				else if (dif_rank < 0 && dif_file < 0)
					step = -9;
				else if (dif_rank > 0 && dif_file < 0)
					step = 9;
				else
					step = -7;
			}
			i = attacker + step;
			while (i != king_position[0]) {
				mask |= 1ULL << i;
				i += step;
			}

			std::vector<int> aux;

			if (isWhite) {
				v = getOneBits(table->whitePawns);
				aux = getOneBits(table->whiteBishops);
				v.insert(v.end(), aux.begin(), aux.end());
				aux = getOneBits(table->whiteRooks);
				v.insert(v.end(), aux.begin(), aux.end());
				aux = getOneBits(table->whiteKnights);
				v.insert(v.end(), aux.begin(), aux.end());
				aux = getOneBits(table->whiteQueens);
				v.insert(v.end(), aux.begin(), aux.end());
			}
			else {
				v = getOneBits(table->blackPawns);
				aux = getOneBits(table->blackBishops);
				v.insert(v.end(), aux.begin(), aux.end());
				aux = getOneBits(table->blackRooks);
				v.insert(v.end(), aux.begin(), aux.end());
				aux = getOneBits(table->blackKnights);
				v.insert(v.end(), aux.begin(), aux.end());
				aux = getOneBits(table->blackQueens);
				v.insert(v.end(), aux.begin(), aux.end());
			}

			for (i = 0; i < v.size(); ++i) {
				std::vector<int> intersect = getOneBits(table->pieces[v[i]].nextMoves & mask);
				if (intersect.size() != 0) {
					if(try_moving_piece(v[i], intersect[0], isWhite)) { 
						return 1;
					}
				}
			}
		}
		return -1;
	}
	return 0;
}

// Chooses a random available piece to move on the board.
// Returns true if there is a piece that can be moved, false otherwise.
bool ChessBoard::randomPiece(bool isWhite) {
    int security = kingIsSafe(isWhite);
	if (security == 0) {
		std::vector<char> random_piece(6);
	
		int random_piece_white[6]  = {'P','R','K','Q','B','N'};
		int random_piece_black[6] = {'p','r','k','q','b','n'};    

		if(isWhite)
			random_piece.assign(&random_piece_white[0],&random_piece_white[0] + 6);
		else random_piece.assign(&random_piece_black[0], &random_piece_black[0] + 6);
	
		std::vector<int> rook_positions;
		std::vector<int> king_positions;
		std::vector<int> queen_positions;
		std::vector<int> bishop_positions;
		std::vector<int> knight_positions;
		std::vector<int> valid_final_moves;
    
		board* backup;

		while(random_piece.size() != 0) {
			int pos = rand() % random_piece.size();
			switch(pos){
			case 0:
				backup = new board();
				*backup = *table;
				if(randomPositionPawn(isWhite)) {
					if (kingInDanger(isWhite) != -1) {
						*table = *backup;
						free(backup);
					} else {
						free(backup);
						return true;
					}
				}
				//random_piece.erase(random_piece.begin());
				//break;
			case 1:
				if (isWhite)
					rook_positions = getOneBits(table->whiteRooks);
				else
					rook_positions = getOneBits(table->blackRooks);
				while (rook_positions.size() != 0){
					int chosen_rook = rand() % rook_positions.size();
					valid_final_moves = generateValidRookMove(rook_positions[chosen_rook], isWhite);
					while (valid_final_moves.size() != 0){
						int final_rook = rand() % valid_final_moves.size();
						if(try_moving_piece(rook_positions[chosen_rook],valid_final_moves[final_rook], isWhite)) {
							return true;
						}
						valid_final_moves.erase(valid_final_moves.begin() + final_rook);
					}
					rook_positions.erase(rook_positions.begin() + chosen_rook);
				}
				//random_piece.erase(random_piece.begin()+ 1);
				//break;
			case 2:
				if (isWhite)
					king_positions = getOneBits(table->whiteKing);
				else
					king_positions = getOneBits(table->blackKing);

				valid_final_moves = generateValidKingMove(king_positions[0], isWhite);
				while (valid_final_moves.size() != 0){
					int final_king = rand() % valid_final_moves.size();
					if(try_moving_piece(king_positions[0],valid_final_moves[final_king], isWhite)) {
						return true;
					}
					valid_final_moves.erase(valid_final_moves.begin() + final_king);
				}
				//break;
			case 3:
				if (isWhite)
					queen_positions = getOneBits(table->whiteQueens);
				else
					queen_positions = getOneBits(table->blackQueens);

				while (queen_positions.size() != 0){
					int chosen_queen = rand() % queen_positions.size() ;
					valid_final_moves = generateValidQueenMove(queen_positions[chosen_queen], isWhite);

					while (valid_final_moves.size() != 0){
						int final_queen = rand() % valid_final_moves.size();
						if(try_moving_piece(queen_positions[chosen_queen], valid_final_moves[final_queen], isWhite)) {
							return true;
						}
						valid_final_moves.erase(valid_final_moves.begin() + final_queen);
					}
					queen_positions.erase(queen_positions.begin() + chosen_queen);
				}
				//random_piece.erase(random_piece.begin()+3);
				//break;
			case 4:
				if (isWhite)
					bishop_positions = getOneBits(table->whiteBishops);
				else
					bishop_positions = getOneBits(table->blackBishops);

				while (bishop_positions.size() != 0){
					int chosen_bishop = rand() % bishop_positions.size() ;
					valid_final_moves = generateValidBishopMove(bishop_positions[chosen_bishop], isWhite);
					while (valid_final_moves.size() != 0){
						int final_bishop = rand() % valid_final_moves.size();
						if(try_moving_piece(bishop_positions[chosen_bishop], valid_final_moves[final_bishop], isWhite)) {
							return true;
						}
						valid_final_moves.erase(valid_final_moves.begin() + final_bishop);
					}
					bishop_positions.erase(bishop_positions.begin() + chosen_bishop);
				}
				//random_piece.erase(random_piece.begin()+ 4);
				//break;
			case 5:
				if (isWhite)
					knight_positions = getOneBits(table->whiteKnights);
				else
					knight_positions = getOneBits(table->blackKnights);

				while (knight_positions.size() != 0){
					int chosen_knight = rand() % knight_positions.size() ;
					valid_final_moves = generateValidKnightMove
										(knight_positions[chosen_knight], isWhite);
					while (valid_final_moves.size() != 0){
						int final_knight = rand() % valid_final_moves.size();
						if(try_moving_piece(knight_positions[chosen_knight], valid_final_moves[final_knight], isWhite)) {
							return true;
						}
						valid_final_moves.erase(valid_final_moves.begin() + final_knight);
					}
					knight_positions.erase(knight_positions.begin() + chosen_knight);
				}
				//random_piece.erase(random_piece.begin() + 5);
				//break;
			}
		}
	} else if (security == 1) {
		return true;
	}
	return false;
}

void ChessBoard::en_passant_recognition(bool isWhite){
	if(isWhite){
		//daca la mine s-au mutat 2 fata de pozitia initiala
		if ( black_en_passant != 0 ){
			if( final_pos_opponent == black_en_passant + 8 && table->pieces[final_pos_opponent].name == 'P' ){
				table->blackLostPieces.push_back('p');
				table->blackPawns &= ~(1ULL << black_en_passant);
				table->blackPieces &= ~(1ULL << black_en_passant);
				table->occupied &= ~(1ULL << (black_en_passant));
				table->pieces[black_en_passant].name = EMPTY_CODE;
				table->pieces[black_en_passant].nextMoves = 0ULL;
				table->pieces[black_en_passant].nextAttacks = 0ULL;
				black_en_passant = 0;
			}
		}
	}
	else{
		if ( white_en_passant != 0 ){
			if( final_pos_opponent == white_en_passant - 8 && table->pieces[final_pos_opponent].name == 'p'  ){
				table->whiteLostPieces.push_back('P');
				table->whitePawns &= ~(1ULL << white_en_passant);
				table->whitePieces &= ~(1ULL << white_en_passant);
				table->occupied &= ~(1ULL << (white_en_passant));
				table->pieces[white_en_passant].name = EMPTY_CODE;
				table->pieces[white_en_passant].nextMoves = 0ULL;
				table->pieces[white_en_passant].nextAttacks = 0ULL;
				white_en_passant = 0;
			}
		}
	}
}

void ChessBoard::castling_recognition(bool isWhite, bool isSmall){
	if(isWhite){
		if(isSmall){
			movePiece(60, 62);
			movePiece(63, 61);
		}
		else{
			movePiece(60, 58);
			movePiece(56, 59);
		}
	}
	else{		
		if(isSmall){
			movePiece(4, 6);
			movePiece(7, 5);
		}
		else{
			movePiece(4, 2);
			movePiece(0, 3);
		}
	}
}

/*
int main(){
	ChessBoard c;
	c.initializeBitboard();

	//c.movePiece(2,47);
	//std::vector<int> v = c.generateValidRookMove(0,true);
	//c.randomPiece(true);
	//c.updateOpponentMove("O-O", true);
    
    c.movePiece(1, 18);
    c.movePiece(48, 40);
    c.movePiece(6, 21);
    c.movePiece(56, 48);
    c.movePiece(18,35);
   //if(c.kingInDanger(true) != -1)
     //    std::cout<<"bau";

    std::string a, b;
    std::cout << "\n";

        		for(int j =7 ; j>=0 ; j--){
        		for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

        			std::cout<<c.table->pieces[i].name<<" ";
        		}
        			std::cout << "\n";
        	}

        	std::cout << "\n";

    	std::cout << "\n";
        b = convertToBitString(c.table->pieces[51].nextMoves);
        	for(int j =7 ; j>=0 ; j--){
    		for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

    			std::cout<<b[i]<<" ";
    		}
    			std::cout << "\n";
    	}

    	std::cout << "\n";

   // if(c.randomPiece(false))
    //	std::cout << "AM MUTAT" <<std::endl;

		for(int j =7 ; j>=0 ; j--){
		for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

			std::cout<<c.table->pieces[i].name<<" ";
		}
			std::cout << "\n";
	}

	std::cout << "\n";

	for (size_t i = 0; i < c.table->blackLostPieces.size(); ++i) {
		std::cout << c.table->blackLostPieces[i] << " ";
	}

	std::cout << "\n";

	for (size_t i = 0; i < c.table->whiteLostPieces.size(); ++i) {
		std::cout << c.table->whiteLostPieces[i] << " ";
	}
	return 0;
}

*/
