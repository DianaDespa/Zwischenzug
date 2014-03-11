#include "FromXboardToEngine.h"
#include "Modes.h"
#include <stdlib.h>
#include <string.h>

FromXboardToEngine::FromXboardToEngine(void) {
}

FromXboardToEngine::~FromXboardToEngine(void) {
}

void FromXboardToEngine::xboardCommand(void) {
	XBOARD_MODE = true;
}

void FromXboardToEngine::newCommand(void) {
	//Initialize board
	//wait for white user to move
	//set black
	WHITE_MOVING = true;
	BLACK_MOVING = false;
	WHITE_MODE = false;
	BLACK_MODE = true;
	FORCE_MODE = false;
	//reset & stop clocks
}

void FromXboardToEngine::quitCommand(void) {
	exit(0);
}

void FromXboardToEngine::resignCommand(void) {
	// ???????
	;
}

void FromXboardToEngine::forceCommand(void) {
	FORCE_MODE = true;
	WHITE_MODE = false;
	BLACK_MODE = false;
	//stop clocks
}

void FromXboardToEngine::goCommand(void) {
	FORCE_MODE = false;
	//play color that is on the move
	if (WHITE_MOVING) {
		WHITE_MODE = true;
		BLACK_MODE = false;
	} else {
		WHITE_MODE = false;
		BLACK_MODE = true;
	}	
	//associate clock with playing color
	//start thinking & make move
} 

void FromXboardToEngine::whiteCommand(void) {
	//Set White on move. Set the engine to play Black. Stop clocks.
	WHITE_MOVING = true;
	BLACK_MOVING = false;
	WHITE_MODE = false;
	BLACK_MODE = true;
	//clock stops;
}

void FromXboardToEngine::blackCommand(void) {
	//Set Black on move. Set the engine to play White. Stop clocks.
	WHITE_MOVING = false;
	BLACK_MOVING = true;
	WHITE_MODE = true;
	BLACK_MODE = false;
	//stop clocks;
}

void FromXboardToEngine::moveCommand(char* command) {
	char* backupCommand = strdup(command);
	char* move = strtok(backupCommand, " ");
	int file1 = move[0] - 97, rank1 = move[1] - 49;
	int file2 = move[2] - 97, rank2 = move[3] - 49;
	int initPos = rank1 * 8 + file2;
	int movePos = rank2 * 8 + file2;

	//valid_move(initPos, movePos);
	// a b c d e f g h =>  97 98 ...
}

	