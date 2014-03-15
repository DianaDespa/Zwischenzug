#include <stdio.h>
#include "Parser.h"

//Urmeaza sa implementam.
//Timer t;

int main(int argc, char** argv){
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	Parser::interpretCommand();
	return 0;
	
}
