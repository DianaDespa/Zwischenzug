// Zugzwang Chess Engine - stage 1

#include "FromEnginetoXboard.h"

// Send move command to Xboard. Clear output buffer.
void FromEnginetoXboard::parseMove(std::string move){
	std::cout<<"move "<<move<<std::endl;
	setbuf(stdout, NULL);
}

// Checks for valid moves. If not found, engine resigns, else sends move to
// Xboard. Set opponent on move.
void FromEnginetoXboard::parseMovetoXboard(){
	std::string movePiece;
	if (!ChessBoard::randomPiece(WHITE_MODE))
		resignCommand();
	else {
		std::string initial = ChessBoard::initialPosFunc();
		std::string final = ChessBoard::finalPosFunc();
		movePiece.append(initial);
		movePiece.append(final);
		parseMove(movePiece);
		WHITE_MOVING = !WHITE_MOVING;
		BLACK_MOVING = !BLACK_MOVING;
	}
	
}

// Send resign command for the engine, for the corresponding color.
void FromEnginetoXboard::resignCommand(void){
	if (WHITE_MODE){
		std::cout<<"0-1 {WHITE resigns}"<<std::endl;
	}
	else{
		std::cout<<"1-0 {BLACK resigns}"<<std::endl;
	}
	setbuf(stdout, NULL);
}
