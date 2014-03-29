//Zugzwang Chess Engine - stage 1

#include "ChessBoard.h"

// Keeps track of the board's current starte.
board* ChessBoard::table = new board();

// Positions from and to which a piece moves.
int ChessBoard::initial_position = 0, 
	ChessBoard::final_position = 0;

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

// Get the bitboard with the possible attack directions for the piece located
// on the pos position.
BITBOARD ChessBoard::getAttacks(int pos) {
	BITBOARD temp = 0ULL;
	int i;
	
	switch (table->nametable[pos].name) {
	case 'P':
		if (pos % 8 == 0) {
			temp = 1ULL<<(pos + 9);
		} else if (pos % 8 == 7) {
			temp = 1ULL<<(pos + 7);
		} else {
			temp = (1ULL<<(pos + 9)) | (1ULL<<(pos + 7));
		}
		break;
	case 'p':
		if (pos % 8 == 0) {
			temp = 1ULL<<(pos - 7);
		} else if (pos % 8 == 7) {
			temp = 1ULL<<(pos - 9);
		} else {
			temp = (1ULL<<(pos - 9)) | (1ULL<<(pos - 7));
		}
		break;
	case 'R':
	case 'r':
		i = pos;
		while (i < ((int)(pos / 8) + 1) * 8) {
			temp |= 1ULL<< i;
			i++;
		}
		i = pos;
		while (i >= (int)(pos / 8) * 8) {
			temp |= 1ULL<< i;
			i--;
		}
		i = pos;
		while (i <= 56 + pos % 8) {
			temp |= 1ULL<< i;
			i += 8; 
		}
		i = pos;
		while (i >= pos % 8) {
			temp |= 1ULL<< i;
			i -= 8; 
		}	
		break;
	case 'B':
	case 'b':
		i = pos;
		while (i % 8 != 0 && i < 64) {
			temp |= 1ULL<< i;
			i += 7;
		}
		if (i < 64) temp |= 1ULL<< i;
		i = pos;
		while (i % 8 != 7 && i < 64) {
			temp |= 1ULL<< i;
			i += 9;
		}
		if (i < 64) temp |= 1ULL<< i;
		i = pos;
		while (i % 8 != 7 && i > 0) {
			temp |= 1ULL<< i;
			i -= 7; 
		}
		if (i > 0) temp |= 1ULL<< i;
		i = pos;
		while (i % 8 != 0 && i > 0) {
			temp |= 1ULL<< i;
			i -= 9;
		}
		if (i > 0) temp |= 1ULL<< i;
		break;
	case 'N':
	case 'n':
		if (((pos + 15) % 8 == pos % 8 - 1) && (pos + 15 < 63)) {
			temp |= 1ULL<<(pos + 15);
		}
		if (((pos + 17) % 8 == pos % 8 + 1) && (pos + 17 <= 63)) {
			temp |= 1ULL<<(pos + 17);
		}
		if (((pos - 17) % 8 == pos % 8 - 1) && (pos - 17 >= 0)) {
			temp |= 1ULL<<(pos - 17); 
		}
		if (((pos - 15) % 8 == pos % 8 + 1) && (pos - 15 > 0)) {
			temp |= 1ULL<<(pos - 15);
		}
		if (((pos + 6) % 8 == pos % 8 - 2) && (pos / 8 + 1 == (pos + 6) / 8)
			&& (pos + 6 < 64)) {
			temp |= 1ULL<<(pos + 6);
		}
		if (((pos - 10) % 8 == pos % 8 - 2) && (pos / 8 - 1 == (pos - 10) / 8)
			&& (pos - 10 >= 0)) {
			temp |= 1ULL<<(pos - 10);
		}
		if (((pos + 10) % 8 == pos % 8 + 2) && (pos / 8 + 1 == (pos + 10) / 8)
			&&(pos + 10 < 64)) {
			temp |= 1ULL<<(pos + 10);
		}
		if (((pos - 6) % 8 == pos % 8 + 2) && (pos / 8 - 1 == (pos - 6) / 8)
			&&(pos - 6 >= 0)) {
			temp |= 1ULL<<(pos - 6);
		}
		break;
	case 'Q':
	case 'q':
		i = pos;
		while (i % 8 != 0 && i < 64) {
			temp |= 1ULL<< i;
			i += 7;
		}
		if (i < 64) temp |= 1ULL<< i;
		i = pos;
		while (i % 8 != 7 && i < 64) {
			temp |= 1ULL<< i;
			i += 9;
		}
		if (i < 64) temp |= 1ULL<< i;
		i = pos;
		while (i % 8 != 7 && i > 0) {
			temp |= 1ULL<< i;
			i -= 7; 
		}
		if (i > 0) temp |= 1ULL<< i;
		i = pos;
		while (i % 8 != 0 && i > 0) {
			temp |= 1ULL<< i;
			i -= 9;
		}
		if (i > 0) temp |= 1ULL<< i;
		i = pos;
		while (i < ((int)(pos / 8) + 1) * 8) {
			temp |= 1ULL<< i;
			i++;
		}
		i = pos;
		while (i >= (int)(pos / 8) * 8) {
			temp |= 1ULL<< i;
			i--;
		}
		i = pos;
		while (i <= 56 + pos % 8) {
			temp |= 1ULL<< i;
			i += 8; 
		}
		i = pos;
		while (i >= pos % 8) {
			temp |= 1ULL<< i;
			i -= 8; 
		}	
		break;
	}
	return temp;
}

// Checks if the king is in danger in the current state of the board.
bool ChessBoard::kingInDanger(bool isWhite) {
	BITBOARD attacks = 0;
	int i;
	 
	if (isWhite) {
		for (i = 0; i < 64; i++) {
			if (table->nametable[i].name > 'a') {
				attacks |= getAttacks(i);
			}
		}
		return !(attacks & table->whiteKing);
	}
	else {
		for (i = 0; i < 64; i++) {
			if (table->nametable[i].name < 'a') {
				attacks |= getAttacks(i);
			}
		}
		return !(attacks & table->blackKing);
	}
}

// Returns a string consisting of the bits of the argument "value", sorted from
// least significant to most significant.
// For debugging purposes.
std::string ChessBoard::convertToBitString(long long value){
	std::string str(64, '0');

	for (int i = 0; i < 64; i++)
	{
		if ((1ll << i) & value)
			str[i] = '1';
	}

	return str;
}

// Swap the values of two chars.
void swap(char* a ,char* b ){
	char aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

// Swap the values of two bitboards.
void swap(BITBOARD* a, BITBOARD* b ){
	BITBOARD aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

// Move a piece across the board from initial_pos to final_pos.
// Update the bitboards for the occupied squares, white pieces, black pieces,
// and all the piece types, depending on the piece that moves and whether the
// move is a capture.
void ChessBoard::movePiece(int initial_pos, int final_pos){

	// Set the bit for the initial position to 0.
	table->occupied &= ~(1ULL << (initial_pos));

	// Swap squares.
	swap(&table->nametable[initial_pos].name,
		&table->nametable[final_pos].name);
	swap(&table->nametable[initial_pos].nextMoves, 
		&table->nametable[final_pos].nextMoves);

	// Check for capture. If there was a piece on the final position (which is
	// now on the final position) the move is a capture, and the bitboards
	// corresponding to the captures piece are updated.
	if (table->nametable[initial_pos].name != EMPTY_CODE) {
		if (table->nametable[initial_pos].name < 'a') {
			switch (table->nametable[initial_pos].name){
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
				table->whiteQueen = 0ULL;
				break;
			}
			table->whitePieces &= ~(1ULL << final_pos);
		}else {
			switch(table->nametable[initial_pos].name) {
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
				table->blackQueen = 0ULL;
				break;
			}
			table->blackPieces &= ~(1ULL << final_pos);
		}
		table->nametable[initial_pos].name = EMPTY_CODE;
		table->nametable[initial_pos].nextMoves = 0ULL;
	}
	
	// If the move is not a capture, then uptade the bitboard for occupied
	// squares.
	else {
		table->occupied |= 1ULL << (final_pos);
	}

	// Update the bitboards corresponding to the moving piece.
	if (table->nametable[final_pos].name < 'a') {
		switch (table->nametable[final_pos].name){
		case 'P':
			table->whitePawns &= ~(1ULL << initial_pos);
			table->whitePawns |= 1ULL << final_pos;
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
			table->whiteQueen = 1ULL << final_pos;
			break;
		}
		table->whitePieces &= ~(1ULL << initial_pos);
		table->whitePieces |= 1ULL << final_pos;
	}else {
		switch(table->nametable[final_pos].name) {
		case 'p':
			table->blackPawns &= ~(1ULL << initial_pos);
			table->blackPawns |= 1ULL << final_pos;
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
			table->blackQueen = 1ULL << final_pos;
			break;
		}
		table->blackPieces &= ~(1ULL << initial_pos);
		table->blackPieces |= 1ULL << final_pos;
	}
}

// Initialises all the bitboards and the board of piece codes.
void ChessBoard::initializeBitboard(){

	table->occupied = WHITE_PAWN | BLACK_PAWN | WHITE_ROOK | BLACK_ROOK
					| WHITE_KNIGHT | BLACK_KNIGHT | WHITE_BISHOP | BLACK_BISHOP
					| WHITE_QUEEN | BLACK_QUEEN | WHITE_KING | BLACK_KING ;


	table->whitePieces = WHITE_PAWN | WHITE_ROOK | WHITE_KNIGHT |
						WHITE_BISHOP | WHITE_QUEEN | WHITE_KING;
	table->blackPieces = table->whitePieces ^ table->occupied;

	table->whitePawns = WHITE_PAWN;
	table->blackPawns = BLACK_PAWN;
	table->whiteRooks = WHITE_ROOK;
	table->blackRooks = BLACK_ROOK;
	table->whiteBishops = WHITE_BISHOP;
	table->blackBishops = BLACK_BISHOP;
	table->whiteKnights = WHITE_KNIGHT;
	table->blackKnights = BLACK_KNIGHT;
	table->whiteQueen = WHITE_QUEEN;
	table->blackQueen = BLACK_QUEEN;
	table->whiteKing = WHITE_KING;
	table->blackKing = BLACK_KING;

	table->nametable[0].name = WHITE_ROOK_CODE;
	table->nametable[7].name = WHITE_ROOK_CODE;
	table->nametable[1].name = WHITE_KNIGHT_CODE;
	table->nametable[6].name = WHITE_KNIGHT_CODE;
	table->nametable[2].name = WHITE_BISHOP_CODE;
	table->nametable[5].name = WHITE_BISHOP_CODE;
	table->nametable[3].name = WHITE_QUEEN_CODE;
	table->nametable[4].name = WHITE_KING_CODE;

	table->nametable[56].name = BLACK_ROOK_CODE;
	table->nametable[63].name = BLACK_ROOK_CODE;
	table->nametable[57].name = BLACK_KNIGHT_CODE;
	table->nametable[62].name = BLACK_KNIGHT_CODE;
	table->nametable[58].name = BLACK_BISHOP_CODE;
	table->nametable[61].name = BLACK_BISHOP_CODE;
	table->nametable[59].name = BLACK_QUEEN_CODE;
	table->nametable[60].name = BLACK_KING_CODE;

	unsigned int i;

	for (i = 8 ; i <= 15 ; i++)
		table->nametable[i].name = WHITE_PAWN_CODE;

	for (i = 48 ; i <= 55 ; i++)
		table->nametable[i].name = BLACK_PAWN_CODE;

	for (i = 16 ; i <= 47 ; i++)
		table->nametable[i].name = EMPTY_CODE;
}

// Checks if there is a valid move for the pawn on the pos position.
// If there are more than one, chooses randomly, moves the pawn and updates
// final_position.
// Returns true if a valid move exists, false if not.
bool ChessBoard::generateValidPawnMove(int pos, bool isWhite){
	bool b1 = false;
	bool b2 = false;

	srand(time(NULL));

	if (isWhite){
		// If playing white, check ahead 8 positions in array of codes, and
		// check ahead 16 positions if pawn is in start position (second row)
		// for existing pieces.
		if	(table->nametable[pos + 8].name == EMPTY_CODE) {
			b2 = true;
			if (((15 - pos) * (pos - 8) >= 0) &&
				(table->nametable[pos + 16].name == EMPTY_CODE)){
				b1 = true;
			}
		}
		if (b2){
			if (b1) {
				if(rand() % 2 == 0){
					movePiece(pos, pos + 8);
					final_position = pos + 8;
					return true;
				}
				else{
					movePiece(pos, pos + 16);
					final_position = pos + 16;
					return true;
				}
			}
			else {
				movePiece(pos, pos + 8);
				final_position = pos + 8;
				return true;
			}
		}
	}
	else{
		// If playing black, check behind 8 positions in array of codes, and
		// check behind 16 positions if pawn is in start position (second to
		// last row) for existing pieces.
		if (table->nametable[pos - 8].name == EMPTY_CODE) {
			b2 = true;
			if (((55 - pos) * (pos - 48) >= 0) &&
				(table->nametable[pos - 16].name == EMPTY_CODE)){
				b1 = true;
			}
		}
		if (b2){
			if (b1) {
				if(rand() % 2 == 0){
					movePiece(pos, pos - 8);
					final_position = pos - 8;
					return true;
				}
				else{
					movePiece(pos, pos - 16);
					final_position = pos - 16;
					return true;
				}
			}
			else {
				movePiece(pos, pos - 8);
				final_position = pos - 8;
				return true;
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
	srand(time(NULL));

	if (isWhite){
		// If playing white and pawn is on the margin of the board, checks ahead
		// in the array of codes for existing pieces, depending on which margin
		// the pawn is on.
		if (pos % 8 == 0){
			if (table->nametable[pos + 9].name == BLACK_PAWN_CODE |
				table->nametable[pos + 9].name == BLACK_ROOK_CODE |
				table->nametable[pos + 9].name == BLACK_KNIGHT_CODE |
				table->nametable[pos + 9].name == BLACK_BISHOP_CODE |
				table->nametable[pos + 9].name == BLACK_QUEEN_CODE ){

				movePiece(pos, pos + 9);
				final_position = pos + 9;
				return true;
			}
			return false;
		}
		else if (pos % 8 == 7){
			if (table->nametable[pos + 7].name == BLACK_PAWN_CODE |
				table->nametable[pos + 7].name == BLACK_ROOK_CODE |
				table->nametable[pos + 7].name == BLACK_KNIGHT_CODE |
				table->nametable[pos + 7].name == BLACK_BISHOP_CODE |
				table->nametable[pos + 7].name == BLACK_QUEEN_CODE ){

				movePiece(pos, pos + 7);
				final_position = pos + 7;
				return true;
			}
			return false;
		}
		else{
			// If playing white and pawn is not on the margin of the board,
			// checks ahead for existing pieces in the array of codes.
			if (table->nametable[pos + 7].name == BLACK_PAWN_CODE |
				table->nametable[pos + 7].name == BLACK_ROOK_CODE |
				table->nametable[pos + 7].name == BLACK_KNIGHT_CODE |
				table->nametable[pos + 7].name == BLACK_BISHOP_CODE |
				table->nametable[pos + 7].name == BLACK_QUEEN_CODE ) {
				b1 = true;
			}
			if (table->nametable[pos + 9].name == BLACK_PAWN_CODE |
				table->nametable[pos + 9].name == BLACK_ROOK_CODE |
				table->nametable[pos + 9].name == BLACK_KNIGHT_CODE |
				table->nametable[pos + 9].name == BLACK_BISHOP_CODE |
				table->nametable[pos + 9].name == BLACK_QUEEN_CODE ){
				b2 = true;
			}
			if (b1 && b2){
				srand(time(NULL));
				if (rand() % 2 == 0){
					movePiece(pos, pos + 9);
					final_position = pos + 9;
					return true;
				}
				else{
					movePiece(pos, pos + 7);
					final_position = pos + 7;
					return true;
				}
			}
			else if (b1){
				movePiece(pos, pos + 7);
				final_position = pos + 7;
				return true;
			}
			else if (b2){
				movePiece(pos, pos + 9);
				final_position = pos + 9;
				return true;
			}
			return false;
		}
	}
	else{
		// If playing black and pawn is on the margin of the board, checks
		// behind in the array of codes for existing pieces, depending on
		// which margin the pawn is on.
		if (pos % 8 == 0){
			if (table->nametable[pos - 7].name == WHITE_PAWN_CODE |
				table->nametable[pos - 7].name == WHITE_ROOK_CODE |
				table->nametable[pos - 7].name == WHITE_KNIGHT_CODE |
				table->nametable[pos - 7].name == WHITE_BISHOP_CODE |
				table->nametable[pos - 7].name == WHITE_QUEEN_CODE ){

				movePiece(pos, pos - 7);
				final_position = pos - 7;
				return true;
			}
			return false;
		}
		else if (pos % 8 == 7) {
			if (table->nametable[pos - 9].name == WHITE_PAWN_CODE |
				table->nametable[pos - 9].name == WHITE_ROOK_CODE |
				table->nametable[pos - 9].name == WHITE_KNIGHT_CODE |
				table->nametable[pos - 9].name == WHITE_BISHOP_CODE |
				table->nametable[pos - 9].name == WHITE_QUEEN_CODE ){

				movePiece(pos, pos - 9);
				final_position = pos - 9;
				return true;
			}
			return false;
		}
		else{
			// If playing white and pawn is not on the margin of the board,
			// checks behind for existing pieces in the array of codes.
			if (table->nametable[pos - 7].name == WHITE_PAWN_CODE |
				table->nametable[pos - 7].name == WHITE_ROOK_CODE |
				table->nametable[pos - 7].name == WHITE_KNIGHT_CODE |
				table->nametable[pos - 7].name == WHITE_BISHOP_CODE |
				table->nametable[pos - 7].name == WHITE_QUEEN_CODE ) {
				b1 = true;
			}
			if (table->nametable[pos - 9].name == WHITE_PAWN_CODE |
				table->nametable[pos - 9].name == WHITE_ROOK_CODE |
				table->nametable[pos - 9].name == WHITE_KNIGHT_CODE |
				table->nametable[pos - 9].name == WHITE_BISHOP_CODE |
				table->nametable[pos - 9].name == WHITE_QUEEN_CODE ){
				b2 = true;
			}
			if (b1 && b2){
				srand(time(NULL));
				if(rand()%2==0){
					movePiece(pos, pos - 9);
					final_position = pos - 9;
					return true;
				}
				else{
					movePiece(pos, pos - 7);
					final_position = pos - 7;
					return true;
				}
			}
			else if (b1){
				movePiece(pos, pos - 7);
				final_position = pos - 7;
				return true;
			}
			else if (b2){
				movePiece(pos, pos - 9);
				final_position = pos - 9;
				return true;
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
	srand(time(NULL));
	board* backup = new board();

	// Keeps track of all available pawns, depending on the color of the engine
	// in the vector v.
	if (isWhite){
		for (unsigned int i = 8 ; i < 56 ; i ++){
			if (table->nametable[i].name == WHITE_PAWN_CODE)
				v.push_back(i);
		}
	}
	else{
		for (unsigned int i = 55 ; i > 7 ; i --){
			if (table->nametable[i].name == BLACK_PAWN_CODE)
				v.push_back(i);
		}
	}

	if (v.size() > 0){
		// Checks pawns for possible captures and moves. When one is found,
		// update initial_position.
		while (v.size() > 0){
			p = rand() % v.size();
			*backup = *table;
			if (generateValidPawnAttack(v[p], isWhite)){
				// Doesn't make the move if the king will be in danger
				if (!kingInDanger(isWhite)) {
					initial_position = v[p];
					delete backup;
					return true;
				}
				else {
					*table = *backup;
				}
			}
			else
			if (generateValidPawnMove(v[p], isWhite)){
				if (!kingInDanger(isWhite)) {
					initial_position = v[p];
					delete backup;
					return true;
				}
				else {
					*table = *backup;
				}
			}
			v.erase(v.begin() + p);
		}
	}
	return false;
}

// Chooses a random available piece to move on the board.
// Returns true if there is a piece that can be moved, false otherwise.
bool ChessBoard::randomPiece(bool isWhite){
	return randomPositionPawn(isWhite);
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
void ChessBoard::updateOpponentMove(char* positions){

	int file1 = positions[0] - 97; int rank1 = positions[1] - 49;
	int file2 = positions[2] - 97; int rank2 = positions[3] - 49;

	int initial_pos = rank1 * 8 + file1;
	int final_pos = rank2 * 8 + file2;

	movePiece(initial_pos,final_pos);
}

