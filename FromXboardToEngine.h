#ifndef _XBOARD_TO_ENGINE_H
#define _XBOARD_TO_ENGINE_H

#include <string>
#include "Modes.h"
#include "ChessBoard.h"
//#include "Timer.h"

using namespace Modes;

namespace FromXboardtoEngine {
	void xboardCommand(void);
	void newCommand(void);
	void quitCommand(void);
	void forceCommand(void);
	void goCommand(void);
	void whiteCommand(void);
	void blackCommand(void);
	void moveCommand(char* command);
};

#endif
