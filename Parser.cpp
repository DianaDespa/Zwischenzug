#include "Parser.h"
	
	/*Parser::Parser(){
	logFile = fopen("log","w");		
	}
	
	Parser::~Parser(){
	fclose(logFile);
	}*/
	
	int Parser::interpretCommand(){
		
		FromXboardtoEngine XBOARD;
		FromEnginetoXboard ENGINE;
		
		
		setbuf(stdout, NULL);
		setbuf(stdin, NULL);	
		
		std::string command;
		while (1){
	
			std::cin >> command;
			setbuf(stdin, NULL);
			
			if(command.compare("xboard") == 0){
		        std::cout<<"feature myname=\"Team\""<< std::endl;
				setbuf(stdout, NULL);
		    }

		    else  if(command.compare("quit") == 0){
				XBOARD.quitCommand();
		        break;
		    }

			else if (command.compare("new") == 0){
				//fputs(command, logFile);
				XBOARD.newCommand();
				}
			else if(command.compare("force") == 0){
				//fputs(command, logFile);
				XBOARD.forceCommand();
				}
			else if(command.compare("go") == 0){			
				//fputs(command, logFile);
				XBOARD.goCommand();
				}
			else if(command.compare("white") == 0){
				//fputs(command, logFile);
				XBOARD.whiteCommand();
				}
			else if(command.compare("black") == 0){
				//fputs(command, logFile);
				XBOARD.blackCommand();
				}
			
			else{ 
				char* cmd = strdup(command.c_str());
				XBOARD.moveCommand(cmd);
				//std::cout<<"move e7e5"<<std::endl;
				ENGINE.parseMovetoXboard();
		        }
		   }
		return 0;
	
	}

