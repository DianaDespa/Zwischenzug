#include "Parser.h"
	
	/*Parser::Parser(){
	logFile = fopen("log","w");		
	}
	
	Parser::~Parser(){
	fclose(logFile);
	}*/
	
FILE *f  = fopen("log","w");

int Parser::interpretCommand(){

	FromXboardtoEngine XBOARD;
	FromEnginetoXboard ENGINE;
		
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);	
		
	std::string command;
	while (1){
	
		std::cin >> command;

		if (command.compare("xboard") == 0){
			XBOARD.xboardCommand();
		}
		else if (command.compare("protover") == 0){
			std::cout<<"feature myname=\"Team\""<< std::endl;
			std::cout<<"feature usermove=1"<< std::endl;
			std::cout<<"feature sigint=0"<< std::endl;
			std::cout<<"feature sigterm=0"<< std::endl;	
		}
		else if (command.compare("new") == 0){
			XBOARD.newCommand();
			break;
		}
	}

	while (1) {
		std::cin >> command;

		fputs(command.data(), f);fputs("   comanda noua\n",f);

		if (command.compare("quit") == 0){
			XBOARD.quitCommand();
		    break;
		}
		else if (command.compare("new") == 0){
			XBOARD.newCommand();
		}
		else if (command.compare("force") == 0){
			XBOARD.forceCommand();
		}
		else if (command.compare("go") == 0){
			XBOARD.goCommand();
			ENGINE.parseMovetoXboard();
		}
		else if (command.compare("white") == 0){
			XBOARD.whiteCommand();
		}
		else if (command.compare("black") == 0){
			XBOARD.blackCommand();
		}
		else if (command.compare("usermove") == 0){
			std::cin >> command;
			fputs(command.data(), f);fputs("\n",f);
			char* cmd = strdup(command.c_str());
			XBOARD.moveCommand(cmd);
			if (!FORCE_MODE && ((BLACK_MODE == BLACK_MOVING) 
								&& (WHITE_MODE == WHITE_MOVING))) {
				ENGINE.parseMovetoXboard();
			}
		}
	}
	fclose(f);
	return 0;	
}
