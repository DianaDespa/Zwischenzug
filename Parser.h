// Zugzwang Chess Engine - stage 1

#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <cstring>
#include "FromEnginetoXboard.h"
#include "FromXboardtoEngine.h"

// Class for the interpretation of Xboard commands.
class Parser{
	public:
		static void interpretCommand(void);
};

#endif
