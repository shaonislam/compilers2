/*
scanner.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "token.h"


Token scanner(FILE *file1, int *line)
{
        fprintf(stderr, "** SCANNING **\n");
	Token tk;

	tk.line = *line;
	tk.tkString = "test";
	tk.tkID = 999;

	return tk;
	
}

