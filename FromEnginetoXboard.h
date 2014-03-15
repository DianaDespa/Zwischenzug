#ifndef _TOXBOARD_H
#define _TOXBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "Modes.h"
#include "ChessBoard.h"

using namespace Modes;

class FromEnginetoXboard{
public:
	void parseMove(char* move);
	void resignCommand(void);
	void parseMovetoXboard();

};
#endif