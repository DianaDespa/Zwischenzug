#include<iostream>
#include "constants.h"
#include<vector>
using namespace std;
string convertToBitString( long long value)
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
void Set_Bit(BITBOARD &table, int pos){
	table = table | ((BITBOARD)1<<pos);
}
void Unset_Bit(BITBOARD &table, int pos){
	table = table & ~((BITBOARD)1<<pos);
}
void Move_Pawn(board &table, int initial_pos, int final_pos, bool white){
	table.existance = table.existance & ~((BITBOARD)1<<(initial_pos));
	table.existance = table.existance | ((BITBOARD)1<<(final_pos));
	//Set_Bit(table.existance, initial_pos);
	//Unset_Bit(table.existance, final_pos);
	table.nametable[initial_pos] = EMPTY_CODE;
	if(white)
		table.nametable[final_pos] = WHITE_PAWN_CODE;
	else
		table.nametable[final_pos] = BLACK_PAWN_CODE;
}
bool Valid_Move_Pawn(board &table, int initial_pos, int final_pos, bool white){
	if( Is_Bit_Set(table.existance, initial_pos) ){
		if( !Is_Bit_Set(table.existance, final_pos) ){
			if(!white){
				if( table.nametable[initial_pos] == BLACK_PAWN_CODE)
					if( (55 - initial_pos) * (initial_pos - 48) >= 0){
						//SUNT PE POZITIA INITIALA A UNUI PION
						if( final_pos == initial_pos - 8 || final_pos == initial_pos - 16){
							Move_Pawn(table, initial_pos, final_pos, false);
							return true;
						}
						else{
							//EXCEPTIE: MUTARE INVALIDA
						}
					}
					else{
						//NU SUNT PE O POZITIE INITIALA A UNUI PION
						if( final_pos == initial_pos - 8){
							Move_Pawn(table, initial_pos, final_pos, false);
							return true;
						}
						else{
							//EXCEPTIE: MUTARE INVALIDA
						}
					}
				else{
					//EXCEPTIE: NU E PIONUL NEGRU ACOLO
				}
			}
			else {
				if( table.nametable[initial_pos] == WHITE_PAWN_CODE)
					if( (15 - initial_pos) * (initial_pos - 8) >= 0){
						//SUNT PE POZITIA INITIALA A UNUI PION
						if( final_pos == initial_pos + 8 || final_pos == initial_pos + 16){
							Move_Pawn(table, initial_pos, final_pos, true);
							return true;
						}
						else{
							//EXCEPTIE: MUTARE INVALIDA
						}
					}
					else{
						//NU SUNT PE O POZITIE INITIALA A UNUI PION
						if( final_pos == initial_pos + 8){
							Move_Pawn(table, initial_pos, final_pos, true);
							return true;
						}
						else{
							//EXCEPTIE: MUTARE INVALIDA
						}
					}
			}
		}
		else{
			//EXCEPTIE: POZITIA E OCUPATA, NU POT MUTA ACOLO
		}
	}
	else{
		//EXCEPTIE: PE TABLA DE EXISTENTA NU E MARCAT CA EXISTAND O PIESA PE POZITIA INITIALA
	}
	return false;
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
int* Generate_Valid_Moves_Pawn(board &table, int initial_pos, bool white){
	int *v;
	v = new int(2);
	if( Is_Bit_Set(table.existance, initial_pos) ){
		if(!white){
			if( table.nametable[initial_pos] == BLACK_PAWN_CODE)
				if( (55 - initial_pos) * (initial_pos - 48) >= 0){
					//SUNT PE POZITIA INITIALA A UNUI PION
					*v = initial_pos - 8;
					*(v+1) = initial_pos - 16;
				}
				else{
					if(initial_pos > 7)
						*v = initial_pos - 8;
					else{
						//EXCEPTIE: PION NEGRU PE ULTIMUL RAND
						// PRIMESTE  O PIESA
					}
				}
			else{
				//EXCEPTIE: NU E PIONUL NEGRU ACOLO
			}
		}
		else {
			if( table.nametable[initial_pos] == WHITE_PAWN_CODE)
				if( (15 - initial_pos) * (initial_pos - 8) >= 0){
					//SUNT PE POZITIA INITIALA A UNUI PION
					*v = initial_pos + 8;
					*(v+1) = initial_pos + 16;
				}
				else{
					//NU SUNT PE O POZITIE INITIALA A UNUI PION
					if(initial_pos < 56)
						*v = initial_pos + 8;
					else{
						//EXCEPTIE: PION ALB PE ULTIMUL RAND
						//  PRIMESTE  O PIESA
					}
				}
				else{
				//EXCEPTIE: NU E PIONUL ALB ACOLO
			}
		}
	}
	else{
		//EXCEPTIE: PE TABLA DE EXISTENTA NU E MARCAT CA EXISTAND O PIESA PE POZITIA INITIALA
	}
	//DE DEZALOCAT..CANDVA
	return v;
}
BITBOARD Generate_Valid_BitBoard_Pawn(board &table, int initial_pos, bool white){
	int* v = Generate_Valid_Moves_Pawn(table, initial_pos, white);
	BITBOARD T = 0ull;
	for(unsigned int i =0 ; i<=sizeof(v) / sizeof(v[0]); i++)
		T = T | ((BITBOARD)1<<(v[i]));
	return T;
}
bool Move_Random_Pawn(board &table, int initial_pos, bool white){
	int *v = Generate_Valid_Moves_Pawn(table, initial_pos, white);
	srand(time(NULL));
	int final_pos;
	if(white){
		if(sizeof(v)/sizeof(v[0]) == 1)
			final_pos = v[rand()%2];
		else
			final_pos = v[0];
		
		return Valid_Move_Pawn(table, initial_pos, final_pos, true);
	}
	else{
		if(sizeof(v)/sizeof(v[0]) == 1)
			final_pos = v[rand()%2];
		else
			final_pos = v[0];
		return Valid_Move_Pawn(table, initial_pos, final_pos, false);
	}
}
bool Random_Move(board &table, bool white){
	srand(time(NULL));
	vector<int> v;
	//rand()%64;
	for(unsigned int i = 0 ; i<= 63 ; i ++ ){
		if(white){
			if(table.nametable[i] == WHITE_PAWN_CODE )
				v.push_back(i);
		}
		else{
			if(table.nametable[i] == BLACK_PAWN_CODE )
				v.push_back(i);
		}
	}
	bool x = Move_Random_Pawn(table, v[rand()%v.size()], white);
}
int main(){
	BITBOARD b = 0;
	board T;
	T.existance = b;
	InitializeBitboard(T);
	for(unsigned int i = 0 ; i<= 63 ; i ++ ){

		cout<<T.nametable[i]<<" ";
		if(i%8 == 7)
			cout << "\n";
	}
	cout<<"\n";
	
//	cout<<Valid_Move_Pawn(T, 8, 16, true);
	//Move_Pawn(T, 48, 40, false);
	//int *v = new int(2);
	cout<<"A PUTUT MUTA? "<<Random_Move(T,true)<<"\n";
	string binar = convertToBitString(T.existance);
	/*BITBOARD bb = Generate_Valid_BitBoard_Pawn(T, 8, true);
	string bit_map = convertToBitString(bb);
	for(int j =7 ; j>=0 ; j--){ 
	for(int i = 8*j ; i<= 8*(j+1) -1  ; i ++ ){

		cout<<bit_map[i]<<" ";
	}
		cout << "\n";
	}*/
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
	}
	return 0;
}
