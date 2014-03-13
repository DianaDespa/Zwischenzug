#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include "FromEnginetoXboard.h"
#include "FromXboardtoEngine.h"

class Parser{
	
	FILE* logFile;
	//parses command from winboard/xboard
	public:
		int interpretCommand();
		//Parser();
		//~Parser();
	//char* getMove();
	//void sendMove(char* command);
	
	//int initialize;
	
	
	//private:

	
	/*int parseCommand(char *command);
	
	void resignCommand();
    void moveCommand(char *command);
    void newCommand(char *command);
    void forceCommand(char *command);
    void goCommand(char *command);
    void whiteCommand(char *command);
    void blackCommand(char *command);
    void quitCommand(char *command);
	*/

};
#endif


