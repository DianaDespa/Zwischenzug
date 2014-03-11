#include "Lib.h"
#include "FromXboardtoEngine.h"
#include "FromEnginetoXboard.h"

class Parser{

	Parser::Parser(){
	FILE* logFile = fopen("log","w");		
	}
	
	Parser::~Parser(){
	fclose(logFile);
	}
	
	void Parser::interpretCommand(){
		
		FromXboardtoEngine XBOARD;
		
		char* command = (char *)malloc(30);
		char* move = (char*)malloc(10);
		fgets(command, 30,stdin);
		
		fputs(command, logFile);
		
		while (1){
			if (strcmp(command,"xboard\n")==0){
				XBOARD.xboardCommand;
				break;}
			else if (strcmp(command, "new\n") == 0){
				XBOARD.newCommand();
				break;}
			else if(strcmp(command,"quit\n" == 0)){
				XBOARD.quitCommand();
				break;}
			else if(strcmp(command, "force\n") == 0){
				XBOARD.foceCommand();
				break;}
			else if(strcmp(command, "go\n")){			
				XBOARD.goCommand();
				break;}
			else if(strcmp(command,"white\n") == 0){
				XBOARD.whiteCommand();
				break;}
			else if(strcmp(command, "black\n") == 0){
				XBOARD.blackCommand();
				break;}
			else {
				printf("%s", move);
				XBOARD.moveCommand(move);
				}
		}
		free(command);
	
	} 
}
