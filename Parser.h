#ifndef PARSER_h
#define PARSER_h
#include "AllHeader.h"

class Paser{

	//parses command from winboard/xboard
	char* getMove();
	void sendMove(char* command);
	
	int initialize;
	
	
	private:

	
	int parseCommand(char *command);
	
	void resignCommand();
    void moveCommand(char *command);
    void newCommand(char *command);
    void forceCommand(char *command);
    void goCommand(char *command);
    void whiteCommand(char *command);
    void blackCommand(char *command);
    void quitCommand(char *command);
	

}
#endif


