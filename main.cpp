#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Parser.h"
//Timer t;

int main(int argc, char** argv){
	
	
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	
	Parser parser; 
	parser.interpretCommand();
	
	return 0;
	
}