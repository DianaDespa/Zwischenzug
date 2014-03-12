//VEZI COMENTARII CU EXPLICATII INAINTE DE int main() !!!!!!!!!!

#include<iostream>
#include "constants.h"
#include<vector>
using namespace std;
class functii{
public: int initial_position, final_position;
public: functii(board &table){
	InitializeBitboard(table);
}
public: string convertToBitString( long long value)
{
    string str(64, '0');

    for(int i = 0; i < 64; i++)
    {
        if( (1ll << i) & value)
            str[i] = '1';
    }

    return str;
}
bool Is_Bit_Set(BITBOARD table, int pos){
	return ( table & ((BITBOARD)1 <<pos ) ) !=0;
}
public: void Move_Pawn(board &table, int initial_pos, int final_pos, bool white){
	table.existance = table.existance & ~((BITBOARD)1<<(initial_pos));
	table.existance = table.existance | ((BITBOARD)1<<(final_pos));
	table.nametable[initial_pos] = EMPTY_CODE;
	if(white)
		table.nametable[final_pos] = WHITE_PAWN_CODE;
	else
		table.nametable[final_pos] = BLACK_PAWN_CODE;
}

void InitializeBitboard(board &table){
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
bool generate_valid_move(board &table, int pos, bool white){
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
					Move_Pawn(table, pos, pos+8, white);
					final_position = pos+8;
					return true;
				}
				else{
					Move_Pawn(table, pos, pos+16, white);
					final_position = pos+16;
					return true;
				}
			}
			else if(b2){
				Move_Pawn(table, pos, pos+8, white);
				final_position = pos + 8;
				return true;
			}
			else {
				return false;
			}
		}
		else{
			if( table.nametable[pos + 8] == '0') {
				Move_Pawn(table, pos, pos+8, white);
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
					Move_Pawn(table, pos, pos-8, white);
					final_position = pos-8;
					return true;
				}
				else{
					Move_Pawn(table, pos, pos-16, white);
					final_position = pos-16;
					return true;
				}
			}
			else if(b2){
				Move_Pawn(table, pos, pos-8, white);
				final_position = pos - 8;
				return true;
			}
			else {
				return false;
			}
		}
		else{
			if( table.nametable[pos - 8] == '0') {
				Move_Pawn(table, pos, pos-8, white);
				final_position = pos-8;
				return true;
			}
			else{
				return false;
			}
		}
	}
	
}
bool generate_valid_attack(board &table, int pos, bool white){
	bool b1 = false;
	bool b2 = false;
	if(white){
		if( pos % 8 == 0){
			if(table.nametable[pos+9] == BLACK_PAWN_CODE | table.nametable[pos+9] == BLACK_ROOK_CODE | 
				table.nametable[pos+9] == BLACK_KNIGHT_CODE | table.nametable[pos+9] == BLACK_BISHOP_CODE |
				table.nametable[pos+9] == BLACK_QUEEN_CODE ){
					Move_Pawn(table, pos, pos+9, white);
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
					Move_Pawn(table, pos, pos+7, white);
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
					Move_Pawn(table, pos, pos+9, white);
					final_position = pos+9;
					return true;
				}
				else{
					Move_Pawn(table, pos, pos+7, white);
					final_position = pos+7;
					return true;
				}
			}
			else if(b1){
				Move_Pawn(table, pos, pos+7, white);
				final_position = pos+7;
				return true;
			}
			else if(b2){
				Move_Pawn(table, pos, pos+9, white);
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
					Move_Pawn(table, pos, pos-9, white);
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
					Move_Pawn(table, pos, pos-7, white);
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
					Move_Pawn(table, pos, pos-9, white);
					final_position = pos-9;
					return true;
				}
				else{
					Move_Pawn(table, pos, pos-7, white);
					final_position = pos-7;
					return true;
				}
			}
			else if(b1){
				Move_Pawn(table, pos, pos-7, white);
				final_position = pos-7;
				return true;
			}
			else if(b2){
				Move_Pawn(table, pos, pos-9, white);
				final_position = pos-9;
				return true;
			}
			else {
				return false;
			}
		}
	}
}
public: bool Random_Position_Pawn(board &table, bool white){
	srand(time(NULL));
	vector<int> v;
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
			if(generate_valid_attack(table, v[p], white)){
				initial_position = v[p];
				return true;
			}
			else if(generate_valid_move(table, v[p], white)){
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
bool Random_Piece(board &table, bool white){
	srand(time(NULL));
	return Random_Position_Pawn(table, white);
}

public:
	char* final_position_func(){
	return ALPHA_NUMERIC_POSITIONS[final_position];
}

public:
	char* initial_position_func(){
	return ALPHA_NUMERIC_POSITIONS[initial_position];
}
void resign(board &table, bool white){
	if(!Random_Piece(table, white)){
		cout<<"NE DAM BATUTI";
	}
};
//CLASA "functii" MUTA O PIESA (MAI EXACT) UN SINGUR PION DE PE O POZITIE RANDOM.
//TREBUIE SA PUI UN 
// board T;
// functii f(T)
// si f.Random_Piece(T, true) -> pentru a muta alb
//    f.Random_Piece(T, false) -> pentru a muta negru
//Pentru a avea acces la pozitia initiala apelezi: f.initial_position_func()
//Pentru a avea acces la pozitia finala apelezi : f.final_position_func()
//Daca apelezi functia resign iti va spune daca te dai batut sau nu
//(daca Random_Piece nu a gasit nicio piesa care sa se mute => intoarce 0 => ne dam batuti)
int main(){
	board T;
	functii f(T);
	bool x = f.Random_Piece(T, true);
	/*for(int j =7 ; j>=0 ; j--){ 
	for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

		cout<<T.nametable[i]<<" ";
	}
		cout << "\n";
	}
	cout<<"\n";
	f.Move_Pawn(T, 8, 18, true);
	f.Move_Pawn(T, 13, 20, true);
	f.Move_Pawn(T, 9, 19, true);
	f.Move_Pawn(T, 53, 34, false);*/
	//cout<<"\nPOZITIA INITIALA A PIONULUI : "<<ALPHA_NUMERIC_POSITIONS[f.initial_position]<<" \n POZITIA FINALA A PIONULUI : "
		//<<ALPHA_NUMERIC_POSITIONS[f.final_position];
		//cout<<f.initial_position_func();
		//cout<<f.final_position_func();
//	cout<<Valid_Move_Pawn(T, 8, 16, true);
	//Move_Pawn(T, 48, 40, false);
	////int *v = new int(2);
	//cout<<"A PUTUT MUTA? "<<Random_Move(T,true)<<"\n";
	/*string binar = f.convertToBitString(T.existance);
	cout<<"\n";
	for(int j =7 ; j>=0 ; j--){ 
	for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

		cout<<T.nametable[i]<<" ";
	}
		cout << "\n";
	}
	cout<<"\n";
	for(int j =7 ; j>=0 ; j--){ 
	for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

		cout<<binar[i]<<" ";
	}
		cout << "\n";
	}*/
	return 0;
}
