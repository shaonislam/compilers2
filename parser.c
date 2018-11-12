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

char ERROR[40][40] =
{
        "Error",
        "Identifier Missing",
        "Operator : Missing",
	"Integer Missing",
        "Other"
};


int parser(char tk_array[20][10], int line_array[])
{
        fprintf(stderr, "** Parsing **\n");
	
	int inc = 0; /*incrementer */
       	fprintf(stderr, "ikey: %s line: %d\n", tk_array[inc], line_array[inc]);

	Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
	inc++;

	program(tk_array, line_array, inc);		
	return 0;
}


void program(char tk_array[20][10], int line_array[], int inc)
{
	fprintf(stderr, "\n<Program:>\n");
	Token tok;

        /* Predicts: <vars> <block> */
	vars(tk_array, line_array, inc);
	block(tk_array, line_array, inc);
}


void vars(char tk_array[20][10], int line_array[], int inc)
{
        fprintf(stderr, "\n<vars:>\n");
	Token tok;

	/* <vars> : empty | var Identifier : Integer <vars> */


	tok = scanner(tk_array[inc], line_array[inc]);  
	inc++;

	if(!strcmp(tok.tkString,"var"))
        {
   	        tok = scanner(tk_array[inc], line_array[inc]);
        	inc++;
   	
		if(!strcmp(tok.tkID,"Identifier"))
	        {
        	        tok = scanner(tk_array[inc], line_array[inc]);                        
	
			if (!strcmp(tok.tkString,":"))
			{
				inc++;
				tok = scanner(tk_array[inc], line_array[inc]);	
			
				if(strcmp(tok.tkID,"Integer"))	
				{	
					error(3);	
				}
				else
				{
					/* predicts <vars> next */
					inc++;
					vars(tk_array, line_array, inc);
				}
			}
			else 
			{
				error(2);
			}
		}
		else
		{
			error(1);
		}
	}

	else
	{	/*empty*/
		fprintf(stderr, "empty\n");
		return;
	}	
}

void block(char tk_array[20][10], int line_array[], int inc)
{
        fprintf(stderr, "\n<block:>\n");
        Token tok;

        /* <block> : start <vars> <stats> stop */
	

} 


void stats(char tk_array[20][10], int line_array[], int inc)
{} 


void error(int i)
{
	fprintf(stderr, "Error: %s\n", ERROR[i]);
}

