#include "FromEnginetoXboard.h"

void FromEnginetoXboard::parseMove(char* move){
	//scrie efectiv mutarea pentru consola XBOARD
	std::cout<<"move "<<move<<std::endl;
	
}

void FromEnginetoXboard::parseMovetoXboard(){
	
	//board T;	
	char movePiece[6];
	functii book;
	//verifica daca poate muta vreo piesa
	//daca nu poate atunci da resign
	//altfel se parseaza mutarea la consola  
	
	if(!book.Random_Piece(WHITE_MODE))
		resignCommand();
	else {
		char* initial = book.initial_position_func();
		char* final = book.final_position_func();
		strcpy(movePiece, initial);
		strcat(movePiece, final);
		parseMove(movePiece);
	}
	
}
 
void FromEnginetoXboard::resignCommand(void){
	//scrie efectiv ca da resign culoarea pe care suntem setati 
	//daca culoarea curenta este alb
	
	if(WHITE_MODE){
		std::cout<<"0-1 {WHITE resigns}"<<std::endl;
	}
	
	else{
		std::cout<<"1-0 {BLACK resigns}"<<std::endl;
	}
}