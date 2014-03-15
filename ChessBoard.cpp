//VEZI COMENTARII CU EXPLICATII INAINTE DE int main() !!!!!!!!!!

#include "ChessBoard.h"
//extern FILE* f;

board* ChessBoard::table = new board();
char* ChessBoard::ALPHA_NUMERIC_POSITIONS[64] = {"a1","b1","c1","d1","e1","f1","g1","h1",
												"a2","b2","c2","d2","e2","f2","g2","h2",
												"a3","b3","c3","d3","e3","f3","g3","h3",
												"a4","b4","c4","d4","e4","f4","g4","h4",
												"a5","b5","c5","d5","e5","f5","g5","h5",
												"a6","b6","c6","d6","e6","f6","g6","h6",
												"a7","b7","c7","d7","e7","f7","g7","h7",
												"a8","b8","c8","d8","e8","f8","g8","h8"};
int ChessBoard::initial_position = 0, ChessBoard::final_position = 0;

ChessBoard::ChessBoard(){
}

ChessBoard::~ChessBoard() {
	delete table;
}

std::string ChessBoard::convertToBitString(long long value){
	std::string str(64, '0');

	for (int i = 0; i < 64; i++)
	{
		if ((1ll << i) & value)
			str[i] = '1';
	}

	return str;
}

void swap(char* a ,char* b ){
	char aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void swap(BITBOARD* a, BITBOARD* b ){
	BITBOARD aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void ChessBoard::movePiece(int initial_pos, int final_pos){

	table->occupied &= ~(1ULL << (initial_pos));
	swap(&table->nametable[initial_pos].name,
		&table->nametable[final_pos].name);
	swap(&table->nametable[initial_pos].nextMoves, 
		&table->nametable[final_pos].nextMoves);

	//pt ca le-am interschimbat verific ce e pe poz initiala
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
			case 'K':
				table->whiteKing = 0ULL;
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
			case 'k':
				table->blackKing = 0ULL;
				break;
			}
			table->blackPieces &= ~(1ULL << final_pos);
		}
		table->nametable[initial_pos].name = EMPTY_CODE;
		table->nametable[initial_pos].nextMoves = 0ULL;
	}
	else {
		table->occupied |= 1ULL << (final_pos);
	}
	
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
		case 'K':
			table->whiteKing = 1ULL << final_pos;
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
		case 'k':
			table->blackKing = 1ULL << final_pos;
			break;
		}
		table->blackPieces &= ~(1ULL << initial_pos);
		table->blackPieces |= 1ULL << final_pos;
	}

	/*fprintf(f, "\nBLACK");
	for (int i=0; i<64; i++){
		if (i%8==0) fprintf(f, "\n");
		fprintf(f, "%c", convertToBitString(table->blackPawns)[i]);
	}
	fprintf(f, "\n");
	fprintf(f, "\nWHITE");
	for (int i=0; i<64; i++){
		if (i%8==0) fprintf(f, "\n");
		fprintf(f, "%c", convertToBitString(table->whitePawns)[i]);
	}
	fprintf(f, "\n");*/
}

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

bool ChessBoard::generateValidPawnMove(int pos, bool isWhite){
	bool b1 = false;
	bool b2 = false;

	srand(time(NULL));

	if (isWhite){
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
bool ChessBoard::generateValidPawnAttack(int pos, bool isWhite){
	bool b1 = false;
	bool b2 = false;
	srand(time(NULL));

	if (isWhite){
		if (pos % 8 == 0){
			if (table->nametable[pos+9].name == BLACK_PAWN_CODE | table->nametable[pos+9].name == BLACK_ROOK_CODE |
				table->nametable[pos+9].name == BLACK_KNIGHT_CODE | table->nametable[pos+9].name == BLACK_BISHOP_CODE |
				table->nametable[pos+9].name == BLACK_QUEEN_CODE ){

				movePiece(pos, pos + 9);
				final_position = pos + 9;
				return true;
			}
			return false;
		}
		else if (pos % 8 == 7){
			if (table->nametable[pos+7].name == BLACK_PAWN_CODE | table->nametable[pos+7].name == BLACK_ROOK_CODE |
				table->nametable[pos+7].name == BLACK_KNIGHT_CODE | table->nametable[pos+7].name == BLACK_BISHOP_CODE |
				table->nametable[pos+7].name == BLACK_QUEEN_CODE ){

				movePiece(pos, pos + 7);
				final_position = pos + 7;
				return true;
			}
			return false;
		}
		else{
			if (table->nametable[pos+7].name == BLACK_PAWN_CODE | table->nametable[pos+7].name == BLACK_ROOK_CODE |
				table->nametable[pos+7].name == BLACK_KNIGHT_CODE | table->nametable[pos+7].name == BLACK_BISHOP_CODE |
				table->nametable[pos+7].name == BLACK_QUEEN_CODE ) {
				b1 = true;
			}
			if (table->nametable[pos+9].name == BLACK_PAWN_CODE | table->nametable[pos+9].name == BLACK_ROOK_CODE |
				table->nametable[pos+9].name == BLACK_KNIGHT_CODE | table->nametable[pos+9].name == BLACK_BISHOP_CODE |
				table->nametable[pos+9].name == BLACK_QUEEN_CODE ){
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
		if (pos % 8 == 0){
			if (table->nametable[pos-7].name == WHITE_PAWN_CODE | table->nametable[pos-7].name == WHITE_ROOK_CODE |
				table->nametable[pos-7].name == WHITE_KNIGHT_CODE | table->nametable[pos-7].name == WHITE_BISHOP_CODE |
				table->nametable[pos-7].name == WHITE_QUEEN_CODE ){

				movePiece(pos, pos - 7);
				final_position = pos - 7;
				return true;
			}
			return false;
		}
		else if (pos % 8 == 7) {
			if (table->nametable[pos-9].name == WHITE_PAWN_CODE | table->nametable[pos-9].name == WHITE_ROOK_CODE |
				table->nametable[pos-9].name == WHITE_KNIGHT_CODE | table->nametable[pos-9].name == WHITE_BISHOP_CODE |
				table->nametable[pos-9].name == WHITE_QUEEN_CODE ){

				movePiece(pos, pos - 9);
				final_position = pos - 9;
				return true;
			}
			return false;
		}
		else{
			if (table->nametable[pos-7].name == WHITE_PAWN_CODE | table->nametable[pos-7].name == WHITE_ROOK_CODE |
				table->nametable[pos-7].name == WHITE_KNIGHT_CODE | table->nametable[pos-7].name == WHITE_BISHOP_CODE |
				table->nametable[pos-7].name == WHITE_QUEEN_CODE ) {
				b1 = true;
			}
			if (table->nametable[pos-9].name == WHITE_PAWN_CODE | table->nametable[pos-9].name == WHITE_ROOK_CODE |
				table->nametable[pos-9].name == WHITE_KNIGHT_CODE | table->nametable[pos-9].name == WHITE_BISHOP_CODE |
				table->nametable[pos-9].name == WHITE_QUEEN_CODE ){
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

bool ChessBoard::randomPositionPawn(bool isWhite){
	std::vector<int> v;
	int p;
	srand(time(NULL));

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
		while (v.size() > 0){
			p = rand() % v.size();
			//cout<<"A ALES POZITIA INITIALA "<<v[p];
			if (generateValidPawnAttack(v[p], isWhite)){
				initial_position = v[p];
				return true;
			}
			else
			if (generateValidPawnMove(v[p], isWhite)){
				initial_position = v[p];
				return true;
			}
			v.erase(v.begin() + p);
		}
	}
	return false;
}

bool ChessBoard::randomPiece(bool isWhite){
	return randomPositionPawn(isWhite);
}

char* ChessBoard::finalPosFunc(){
	return ALPHA_NUMERIC_POSITIONS[final_position];
}

char* ChessBoard::initialPosFunc(){
	return ALPHA_NUMERIC_POSITIONS[initial_position];
}

void ChessBoard::updateOpponentMove(char* positions, bool isWhite){

	int file1 = positions[0] - 97; int rank1 = positions[1] - 49;
	int file2 = positions[2] - 97; int rank2 = positions[3] - 49;

	int initial_pos = rank1 * 8 + file1;
	int final_pos = rank2 * 8 + file2;

	movePiece(initial_pos,final_pos);
}

/*
int main() {
	ChessBoard f;

	f.initializeBitboard();
	for (int i=0; i<64; i++){
		if (i%8 == 0)  std::cout<<std::endl;
		std::cout << f.convertToBitString(f.table->occupied)[i];
	}
	std::cout<<std::endl;
	for (int i=0; i<64; i++){
		if (i%8 == 0)  std::cout<<std::endl;
		std::cout << f.convertToBitString(~f.table->occupied)[i];
	}
	std::cout<<std::endl;
	for (int i=0; i<64; i++){
		if (i%8 == 0)  std::cout<<std::endl;
		std::cout << f.convertToBitString(f.table->whitePawns)[i];
	}
	std::cout<<std::endl;
	for (int i=0; i<64; i++){
		if (i%8 == 0)  std::cout<<std::endl;
		std::cout << f.convertToBitString(f.table->blackPawns)[i];
	}
	std::cout<<std::endl;

	f.movePiece(8,16);

	for (int i=0; i<64; i++){
		if (i%8 == 0)  std::cout<<std::endl;
		std::cout << f.convertToBitString(f.table->whitePawns)[i];
	}
	std::cout<<std::endl;

	char movePiece[6];
	while(f.randomPiece(true)) {
		char* initial = f.initialPosFunc();
		char* final = f.finalPosFunc();
		strcpy(movePiece, initial);
		strcat(movePiece, final);
		std::cout << movePiece <<std::endl;
		for (int i=0; i<64; i++){
			if (i%8 == 0)  std::cout<<std::endl;
			std::cout << f.table->nametable[i].name;
		}
		std::cout<<std::endl;
	}

	char a[100];
	std::cin >> a;
	return 0;
}*/
