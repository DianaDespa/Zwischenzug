//VEZI COMENTARII CU EXPLICATII INAINTE DE int main() !!!!!!!!!!

#include "new_functii.h"
	
functii::functii(){
	InitializeBitboard();
}

board functii::getBoard(){
	return table;
}

std::string functii::convertToBitString( long long value){
		std::string str(64, '0');

		for(int i = 0; i < 64; i++)
		{
			if( (1ll << i) & value)
				str[i] = '1';
		}

		return str;
	}
	
bool functii::Is_Bit_Set(BITBOARD table, int pos){
	return ( table & ((BITBOARD)1 <<pos ) ) !=0;
}

void swap(char* a ,char* b ){
	char aux;
	aux = *a;
	*a = *b;
	*b = aux; 
}

void functii::Move_Piece(int initial_pos, int final_pos, bool white){
	table.existance = table.existance & ~((BITBOARD)1<<(initial_pos));
	table.existance = table.existance | ((BITBOARD)1<<(final_pos));
	//table.nametable[initial_pos] = EMPTY_CODE;
	if(white)
	swap(&table.nametable[initial_pos], &table.nametable[final_pos]);
	//table.nametable[final_pos] = WHITE_PAWN_CODE;
	else
	swap(&table.nametable[initial_pos], &table.nametable[final_pos]);
	//table.nametable[final_pos] = BLACK_PAWN_CODE;
}


void functii::InitializeBitboard(){
	table.existance = WHITE_PAWN | BLACK_PAWN | WHITE_ROOK | BLACK_ROOK
	| WHITE_KNIGHT | BLACK_KNIGHT | WHITE_BISHOP | BLACK_BISHOP
	| WHITE_QUEEN | BLACK_QUEEN | WHITE_KING | BLACK_KING ;

	table.nametable[0] = WHITE_ROOK_CODE;
	table.nametable[7] = WHITE_ROOK_CODE;
	table.nametable[1] = WHITE_KNIGHT_CODE;
	table.nametable[6] = WHITE_KNIGHT_CODE;
	table.nametable[2] = WHITE_BISHOP_CODE;
	table.nametable[5] = WHITE_BISHOP_CODE;
	table.nametable[3] = WHITE_QUEEN_CODE;
	table.nametable[4] = WHITE_KING_CODE;

	table.nametable[56] = BLACK_ROOK_CODE;
	table.nametable[63] = BLACK_ROOK_CODE;
	table.nametable[57] = BLACK_KNIGHT_CODE;
	table.nametable[62] = BLACK_KNIGHT_CODE;
	table.nametable[58] = BLACK_BISHOP_CODE;
	table.nametable[61] = BLACK_BISHOP_CODE;
	table.nametable[59] = BLACK_QUEEN_CODE;
	table.nametable[60] = BLACK_KING_CODE;

	unsigned int i;

	for( i = 8 ; i <= 15 ; i++)
	table.nametable[i] = WHITE_PAWN_CODE;

	for( i = 48 ; i <= 55 ; i++)
	table.nametable[i] = BLACK_PAWN_CODE;

	for( i = 16 ; i <= 47 ; i++)
	table.nametable[i] = EMPTY_CODE;
	}
bool functii::generate_valid_move(int pos, bool white){
	bool b1 = false;
	bool b2 = false;
	if(white){
	if( (15 - pos) * (pos - 8) >= 0){
	if( table.nametable[pos + 16] == '0'){
	b1 = true;
	}
	if( table.nametable[pos + 8] == '0') {
	b2 = true;
	}
	if( b1 && b2){
	srand(time(NULL));
	if(rand()%2==0){
	Move_Piece(pos, pos+8, white);
	final_position = pos+8;
	return true;
	}
	else{
	Move_Piece(pos, pos+16, white);
	final_position = pos+16;
	return true;
	}
	}
	else if(b2){
	Move_Piece(pos, pos+8, white);
	final_position = pos + 8;
	return true;
	}
	else {
	return false;
	}
	}
	else{
	if( table.nametable[pos + 8] == '0') {
	Move_Piece(pos, pos+8, white);
	final_position = pos+8;
	return true;
	}
	else{
	return false;
	}
	}
	}
	else{
	if( (55 - pos) * (pos - 48) >= 0){
	if( table.nametable[pos - 16] == '0'){
	b1 = true;
	}
	if( table.nametable[pos - 8] == '0') {
	b2 = true;
	}
	if( b1 && b2){
	srand(time(NULL));
	if(rand()%2==0){
	Move_Piece(pos, pos-8, white);
	final_position = pos-8;
	return true;
	}
	else{
	Move_Piece(pos, pos-16, white);
	final_position = pos-16;
	return true;
	}
	}
	else if(b2){
	Move_Piece(pos, pos-8, white);
	final_position = pos - 8;
	return true;
	}
	else {
	return false;
	}
	}
	else{
	if( table.nametable[pos - 8] == '0') {
	Move_Piece(pos, pos-8, white);
	final_position = pos-8;
	return true;
	}
	else{
	return false;
	}
	}
	}

}
bool functii::generate_valid_attack(int pos, bool white){
	bool b1 = false;
	bool b2 = false;
	if(white){
	if( pos % 8 == 0){
	if(table.nametable[pos+9] == BLACK_PAWN_CODE | table.nametable[pos+9] == BLACK_ROOK_CODE |
	table.nametable[pos+9] == BLACK_KNIGHT_CODE | table.nametable[pos+9] == BLACK_BISHOP_CODE |
	table.nametable[pos+9] == BLACK_QUEEN_CODE ){
	Move_Piece(pos, pos+9, white);
	final_position = pos+9;
	return true;
	}
	else
	return false;
	}
	else if( pos % 8 == 7 ) {
	if(table.nametable[pos+7] == BLACK_PAWN_CODE | table.nametable[pos+7] == BLACK_ROOK_CODE |
	table.nametable[pos+7] == BLACK_KNIGHT_CODE | table.nametable[pos+7] == BLACK_BISHOP_CODE |
	table.nametable[pos+7] == BLACK_QUEEN_CODE ){
	Move_Piece(pos, pos+7, white);
	final_position = pos+7;
	return true;
	}
	else
	return false;
	}
	else{
	if(table.nametable[pos+7] == BLACK_PAWN_CODE | table.nametable[pos+7] == BLACK_ROOK_CODE |
	table.nametable[pos+7] == BLACK_KNIGHT_CODE | table.nametable[pos+7] == BLACK_BISHOP_CODE |
	table.nametable[pos+7] == BLACK_QUEEN_CODE ) {
	b1 = true;
	}
	if(table.nametable[pos+9] == BLACK_PAWN_CODE | table.nametable[pos+9] == BLACK_ROOK_CODE |
	table.nametable[pos+9] == BLACK_KNIGHT_CODE | table.nametable[pos+9] == BLACK_BISHOP_CODE |
	table.nametable[pos+9] == BLACK_QUEEN_CODE ){
	b2 = true;
	}
	if( b1 && b2){
	srand(time(NULL));
	if(rand()%2==0){
	Move_Piece(pos, pos+9, white);
	final_position = pos+9;
	return true;
	}
	else{
	Move_Piece(pos, pos+7, white);
	final_position = pos+7;
	return true;
	}
	}
	else if(b1){
	Move_Piece(pos, pos+7, white);
	final_position = pos+7;
	return true;
	}
	else if(b2){
	Move_Piece(pos, pos+9, white);
	final_position = pos+9;
	return true;
	}
	else {
	return false;
	}
	}
	}
	else{
	if( pos % 8 == 0){
	if(table.nametable[pos-9] == WHITE_PAWN_CODE | table.nametable[pos-9] == WHITE_ROOK_CODE |
	table.nametable[pos-9] == WHITE_KNIGHT_CODE | table.nametable[pos-9] == WHITE_BISHOP_CODE |
	table.nametable[pos-9] == WHITE_QUEEN_CODE ){
	Move_Piece(pos, pos-9, white);
	final_position = pos-9;
	return true;
	}
	else
	return false;
	}
	else if( pos % 8 == 7 ) {
	if(table.nametable[pos-7] == WHITE_PAWN_CODE | table.nametable[pos-7] == WHITE_ROOK_CODE |
	table.nametable[pos-7] == WHITE_KNIGHT_CODE | table.nametable[pos-7] == WHITE_BISHOP_CODE |
	table.nametable[pos-7] == WHITE_QUEEN_CODE ){
	Move_Piece(pos, pos-7, white);
	final_position = pos-7;
	return true;
	}
	else
	return false;
	}
	else{
	if(table.nametable[pos-7] == WHITE_PAWN_CODE | table.nametable[pos-7] == WHITE_ROOK_CODE |
	table.nametable[pos-7] == WHITE_KNIGHT_CODE | table.nametable[pos-7] == WHITE_BISHOP_CODE |
	table.nametable[pos-7] == WHITE_QUEEN_CODE ) {
	b1 = true;
	}
	if(table.nametable[pos-9] == WHITE_PAWN_CODE | table.nametable[pos-9] == WHITE_ROOK_CODE |
	table.nametable[pos-9] == WHITE_KNIGHT_CODE | table.nametable[pos-9] == WHITE_BISHOP_CODE |
	table.nametable[pos-9] == WHITE_QUEEN_CODE ){
	b2 = true;
	}
	if( b1 && b2){
	srand(time(NULL));
	if(rand()%2==0){
	Move_Piece(pos, pos-9, white);
	final_position = pos-9;
	return true;
	}
	else{
	Move_Piece(pos, pos-7, white);
	final_position = pos-7;
	return true;
	}
	}
	else if(b1){
	Move_Piece(pos, pos-7, white);
	final_position = pos-7;
	return true;
	}
	else if(b2){
	Move_Piece(pos, pos-9, white);
	final_position = pos-9;
	return true;
	}
	else {
	return false;
	}
	}
	}
}
bool functii::Random_Position_Pawn(bool white){
	srand(time(NULL));
	std::vector<int> v;
	int p;
	if(white){
	for(unsigned int i = 8 ; i < 56 ; i ++ ){
	if(table.nametable[i] == WHITE_PAWN_CODE )
	v.push_back(i);
	}
	}
	else{
	for(unsigned int i = 55 ; i > 7 ; i -- ){
	if(table.nametable[i] == BLACK_PAWN_CODE )
	v.push_back(i);
	}
	}
	if(v.size() > 0){
	while(v.size()>0){
	srand(time(NULL));
	p = rand()%v.size();
	//cout<<"A ALES POZITIA INITIALA "<<v[p];
	if(generate_valid_attack(v[p], white)){
	initial_position = v[p];
	return true;
	}
	else if(generate_valid_move(v[p], white)){
	initial_position = v[p];
	return true;
	}
	v.erase(v.begin() + p);

	}
	return false;
	}
	else{
	return false;
	}
}
bool functii::Random_Piece(bool white){
	srand(time(NULL));
	return Random_Position_Pawn(white);
}

char* functii::final_position_func(){
	return ALPHA_NUMERIC_POSITIONS[final_position];
}

char* functii::initial_position_func(){
	return ALPHA_NUMERIC_POSITIONS[initial_position];
}

void functii::Update_Opponent_Move(char* positions,bool white){

	int file1 = positions[0]-97; int rank1 = positions[1] -49;
	int file2 = positions[2]-97; int rank2 = positions[3]-49;

	int initial_pos = rank1*8 + file1;
	int final_pos = rank2 *8 + file2;

	if (white)
		Move_Piece(initial_pos,final_pos,true);
	else
		Move_Piece(initial_pos,final_pos,true);
}