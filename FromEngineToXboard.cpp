// Zugzwang Chess Engine - stage 1

#include "FromEngineToXboard.h"

// Send move command to Xboard. Clear output buffer.
void FromEnginetoXboard::parseMove(std::string move){
	std::cout<<"move "<<move<<std::endl;
	setbuf(stdout, NULL);
}

// Checks for valid moves. If not found, engine resigns, else sends move to
// Xboard. Set opponent on move.
void FromEnginetoXboard::parseMovetoXboard(){
	std::string movePiece;
	int commandResult = ChessBoard::randomPiece(WHITE_MODE);
	if (commandResult == 2)
		stalemateCommand();
	else if (commandResult == -1)
		checkmateCommand();
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
		std::cout << "0-1 {WHITE resigns}" << std::endl;
	}
	else{
		std::cout << "1-0 {BLACK resigns}" << std::endl;
	}
	setbuf(stdout, NULL);
}

void FromEnginetoXboard::checkmateCommand(void){
	if (BLACK_MODE){
		std::cout << "1-0 {WHITE mates}" << std::endl;
	}
	else{
		std::cout << "0-1 {BLACK mates}" << std::endl;
	}
	setbuf(stdout, NULL);
}

void FromEnginetoXboard::stalemateCommand(void){
	std::cout << "1/2-1/2 {Stalemate}" << std::endl;
	setbuf(stdout, NULL);
}
