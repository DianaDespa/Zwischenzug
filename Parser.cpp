#include "Parser.h"

using namespace FromXboardtoEngine;
using namespace FromEnginetoXboard;

int Parser::interpretCommand(){

	std::string command;

	setbuf(stdout, NULL);
	setbuf(stdin, NULL);

	while (1){
		std::cin >> command;

		if (command.compare("xboard") == 0){
			xboardCommand();
		}
		else if (command.compare("protover") == 0){
			std::cout<<"feature myname=\"Team\""<< std::endl;
			std::cout<<"feature usermove=1"<< std::endl;
			std::cout<<"feature sigint=0"<< std::endl;
			std::cout<<"feature sigterm=0"<< std::endl;	
		}
		else if (command.compare("new") == 0){
			newCommand();
			break;
		}
	}

	while (1) {
		std::cin >> command;

		if (command.compare("quit") == 0){
			quitCommand();
		    break;
		}
		else if (command.compare("new") == 0){
			newCommand();
		}
		else if (command.compare("force") == 0){
			forceCommand();
		}
		else if (command.compare("go") == 0){
			goCommand();
			parseMovetoXboard();
		}
		else if (command.compare("white") == 0){
			whiteCommand();
		}
		else if (command.compare("black") == 0){
			blackCommand();
		}
		else if (command.compare("usermove") == 0){
			std::cin >> command;
			char* cmd = strdup(command.c_str());
			moveCommand(cmd);
			if (!FORCE_MODE && ((BLACK_MODE == BLACK_MOVING) 
								&& (WHITE_MODE == WHITE_MOVING))) {
				parseMovetoXboard();
			}
		}
	}

	return 0;	
}
