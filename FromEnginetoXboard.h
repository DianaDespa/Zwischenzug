#ifndef _TOXBOARD_H
#define _TOXBOARD_H

#include <stdio.h>
#include <iostream>
#include "Modes.h"
#include "ChessBoard.h"

using namespace Modes;

namespace FromEnginetoXboard{
	void parseMove(char* move);
	void resignCommand(void);
	void parseMovetoXboard();

};
#endif
