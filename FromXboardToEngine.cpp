#include "FromXboardtoEngine.h"

FromXboardtoEngine::FromXboardtoEngine(void) {
}

FromXboardtoEngine::~FromXboardtoEngine(void) {
}

void FromXboardtoEngine::xboardCommand(void) {
	XBOARD_MODE = true;
}

void FromXboardtoEngine::newCommand(void) {
//Initialize board
//wait for white user to move
//set black
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

//AM MODIFICAT resignCommand ---> FROMENGINETOXBOARD
/*void FromXboardtoEngine::resignCommand(void) {
	//
	/*char comm1[30]="1-0 {BLACK resigns}\n";
	char comm2[30]="0-1 {WHITE resigns}\n";
	if(joc.colorEngine==BLACK) giveCommandToXboard(comm1);
         else
             giveCommandToXboard(comm2);
}*/

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
/*char* backupCommand = strdup(command);
char* move = strtok(backupCommand, " ");
int file1 = move[0] - 97;
int rank1 = move[1] - 49;
int file2 = move[2] - 97;
int rank2 = move[3] - 49;
int initPos = rank1 * 8 + file1;
int movePos = rank2 * 8 + file2;
*/
functii book;
book.Update_Opponent_Move(command,WHITE_MODE);
//TODO update table
//valid_move(initPos, movePos):
// a b c d e f g h => 97 98 ...
}