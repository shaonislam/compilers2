/*
parser.c

parser func generates error or returns the parse tree to main.

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "parser.h"
#include "token.h"



int parser(FILE *file1)
{
	fprintf(stderr, "** Parsing **\n");
		
	int line_num = 1;
	Token temptk;

	
	temptk = scanner(file1, &line_num);		
	

	fprintf(stderr, "test: %s\n", temptk.tkString);	

	error();
	
	return 0;
}

void error()
{
	fprintf(stderr, "Error: \n");
}

void program()
{
	
		
}
