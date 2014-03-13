#ifndef _XBOARD_TO_ENGINE_H
#define _XBOARD_TO_ENGINE_H

#include <stdlib.h>
#include <string.h>
//#include "Timer.h"
#include "Modes.h"
#include "new_functii.h"

using namespace Modes;

class FromXboardtoEngine {
public:
	//Timer whiteMove,blackMove;
	
	FromXboardtoEngine(void);
	~FromXboardtoEngine(void);

	void xboardCommand(void);
	void newCommand(void);
	void quitCommand(void);
	//AM MODIFICAT resignCommand ---> FROMENGINETOXBOARD
	//void resignCommand(void);
	void forceCommand(void);
	void goCommand(void);
	void whiteCommand(void);
	void blackCommand(void);
	void moveCommand(char* command);
};

#endif