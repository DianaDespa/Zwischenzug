#include "FromEnginetoXboard.h"

extern functii ChessBoard;
extern FILE* f;

void FromEnginetoXboard::parseMove(char* move){
	//scrie efectiv mutarea pentru consola XBOARD
	std::cout<<"move "<<move<<std::endl;
	setbuf(stdout, NULL);
}

void FromEnginetoXboard::parseMovetoXboard(){
	
	//board T;	
	char movePiece[6];
	//verifica daca poate muta vreo piesa
	//daca nu poate atunci da resign
	//altfel se parseaza mutarea la consola  
	
	if (!ChessBoard.randomPiece(WHITE_MODE))
		resignCommand();
	else {
		char* initial = ChessBoard.initialPosFunc();
		char* final = ChessBoard.finalPosFunc();	
		strcpy(movePiece, initial);
		strcat(movePiece, final);
		fprintf(f,"%s\n", movePiece);
		parseMove(movePiece);
		WHITE_MOVING = !WHITE_MOVING;
		BLACK_MOVING = !BLACK_MOVING;
	}
	
}
 
void FromEnginetoXboard::resignCommand(void){
	//scrie efectiv ca da resign culoarea pe care suntem setati 
	//daca culoarea curenta este alb
	
	if (WHITE_MODE){
		std::cout<<"0-1 {WHITE resigns}"<<std::endl;
	}
	else{
		std::cout<<"1-0 {BLACK resigns}"<<std::endl;
	}
	setbuf(stdout, NULL);
}