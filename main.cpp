// Zugzwang Chess Engine

#include <stdio.h>
#include "Parser.h"

// To be implemented for future project stages.
//Timer t;

// Execution entry point - flushes standard input and standard output buffers.
// Start interpreting commands from Xboard.
int main(int argc, char** argv){
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);

	Parser::interpretCommand();

	return 0;
}

