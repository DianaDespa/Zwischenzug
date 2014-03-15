#include "FromXboardtoEngine.h"

void FromXboardtoEngine::xboardCommand(void) {
	XBOARD_MODE = true;
}

void FromXboardtoEngine::newCommand(void) {
	//Initialize board
	//wait for white user to move
	//set black
	ChessBoard::initializeBitboard();
	WHITE_MOVING = true;
	BLACK_MOVING = false;
	WHITE_MODE = false;
	BLACK_MODE = true;
	FORCE_MODE = false;
	//reset & stop clocks
	//whiteMove.resetTimer();
	//blackMove.resetTimer();
}

void FromXboardtoEngine::quitCommand(void) {
	exit(0);
}

void FromXboardtoEngine::forceCommand(void) {
	FORCE_MODE = true;
	WHITE_MODE = false;
	BLACK_MODE = false;
	//stop clocks
	//whiteMove.stopTimer();
	//blackMove.stopTimer();
}

void FromXboardtoEngine::goCommand(void) {
	FORCE_MODE = false;
	//play color that is on the move
	//associate clock with playing color
	if (WHITE_MOVING) {
		WHITE_MODE = true;
		BLACK_MODE = false;
		//whiteMove.startTimer();
	} else {
		WHITE_MODE = false;
		BLACK_MODE = true;
		//blackMove.startTimer();
	}	

	//start thinking & make moveistina7 Andy
	//TODO se preia clasa Cristina& Andy
	//se parseaza catre FromEnginetoXBoard
	//Cum se face chestia asta???? cum declar board????

}

void FromXboardtoEngine::whiteCommand(void) {
	//Set White on move. Set the engine to play Black. Stop clocks.
	WHITE_MOVING = true;
	BLACK_MOVING = false;
	WHITE_MODE = false;
	BLACK_MODE = true;
	//clock stops;
	//whiteMove.stopTimer();
	//blackMove.stopTimer();
}

void FromXboardtoEngine::blackCommand(void) {
	//Set Black on move. Set the engine to play White. Stop clocks.
	WHITE_MOVING = false;
	BLACK_MOVING = true;
	WHITE_MODE = true;
	BLACK_MODE = false;
	//stop clocks;
	//whiteMove.stopTimer();
	//blackMove.stopTimer();
}

void FromXboardtoEngine::moveCommand(char* command) {
	if (!FORCE_MODE) {
		ChessBoard::updateOpponentMove(command, BLACK_MODE);
	} //else check valid
	WHITE_MOVING = !WHITE_MOVING;
	BLACK_MOVING = !BLACK_MOVING;
}
