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
#include "node.h"

char ERROR[100][100] =
{
        "Error",
        "Identifier Missing",
        "Operator Missing",
	"Integer Missing",
	"Incomplete block, start terminal missing",
        "Incomplete block, stop terminal missing",
	"Incorrect direction to <stat>, no match to nonterminals",
	"No Identifier present to scan",
	"<out>: Square Brackets missing []",
	"Invalid <R> terminal",
        "Other",
	"Invalid: Void missing"
};


int inc = 0;

Node parser(char tk_array[20][10], int line_array[])
{
        fprintf(stderr, "** Parsing **\n");
	
       	fprintf(stderr, "ikey: %s line: %d\n", tk_array[inc], line_array[inc]);

	Node root;
	root.name = "Parsing";	

/*	Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
	inc++;
*/
	root = program(tk_array, line_array, inc);		
	return root;
}


Node program(char tk_array[20][10], int line_array[], int inc)
{
	 /* <program> : <vars> <block> */
	fprintf(stderr, "\n<Program:>\n");

	Node node;
	node.name = "program";
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	if (strcmp(tok.String, "void"))
	{
	node.child_1 = vars(tk_array, line_array, inc);
	node.child_2 = block(tk_array, line_array, inc);
	}
	else
	{
		exit(11);
	}
	return node;
}


Node vars(char tk_array[20][10], int line_array[], int inc)
{
        fprintf(stderr, "\n<vars:>\n");
	Node node;
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
			inc++;
			if (!strcmp(tok.tkString,":"))
			{
				tok = scanner(tk_array[inc], line_array[inc]);	
				inc++;
				if(!strcmp(tok.tkID, "Integer"))	
				{	
				       	/* predicts <vars> next */
                                        vars(tk_array, line_array, inc);
				}
				else {error(3);}
			}
			else {error(2);}
		}
		else {error(1);}
	} 
	else {/*empty*/ return;}	
}

Node block(char tk_array[20][10], int line_array[], int inc)
{
        /* <block> : start <vars> <stats> stop */
     
        fprintf(stderr, "\n<block:>\n");

        Node node;
        Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
	inc++; 

	if (!strcmp(tok.tkString, "start"))
	{
		vars(tk_array, line_array, inc);
		/*stats(tk_array, line_array, inc);*/
		
		tok = scanner(tk_array[inc], line_array[inc]);
		inc++;
		if(!strcmp(tok.tkString, "stop"))
		{
			return;
		}
		else
		{error(5);}				
	}
	else
	{error(4);}
} 


Node stats(char tk_array[20][10], int line_array[], int inc)
{
	/* <stats> : <stat> <mStat> */
	fprintf(stderr, "\n<stats>\n");

	Node node;
	stat(tk_array, line_array, inc);
	mStat(tk_array, line_array, inc);
	return node;
} 


Node mStat(char tk_array[20][10], int line_array[], int inc)
{
	/* <mStat> : empty | <stat> <mStat> */
        
	fprintf(stderr, "\n<mStat>\n");
	
        Node node;
	stat(tk_array, line_array, inc);
	mStat(tk_array, line_array, inc);
	return node;	
}


Node stat(char tk_array[20][10], int line_array[], int inc)
{
	/* <stat> : <in> | <out> | <block> | <ifs> | <loop> | <assign> */
	/* scan, out, start, if, loop, let */

        Node node;
	Token tok; 
	tok = scanner(tk_array[inc], line_array[inc]);	
	inc++;	

	if (!strcmp(tok.tkString, "scan"))
	{
		/*in*/
		in(tk_array, line_array, inc);
	}
	else if (!strcmp(tok.tkString, "out"))
	{
		/*out*/
		out(tk_array, line_array, inc);
	}
        else if	(!strcmp(tok.tkString, "start"))
        {
                /*block*/
		block(tk_array, line_array, inc);
        }
        else if	(!strcmp(tok.tkString, "if"))
        {
                /*if*/
		ifs(tk_array, line_array, inc);
	}
        else if	(!strcmp(tok.tkString, "loop"))
        {
                /*loop*/
		loop(tk_array, line_array, inc);
        }        
        else if	(!strcmp(tok.tkString, "let"))
        {
                /*assign*/
		assign(tk_array, line_array, inc);
        }
	else
	{
		error(6);
	}

	return node;
}

Node expr(char tk_array[20][10], int line_array[], int inc)
{
	/* <expr> : <A> <expr1> */ 

        Node node;
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	A(tk_array, line_array, inc);
	expr1(tk_array, line_array, inc);
	return;
}

Node expr1 (char tk_array[20][10], int line_array[], int inc)
{
	/* <expr1> : / <expr> | * <expr> | empty */

        Node node;
        Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

        if (!strcmp(tok.tkString, "*"))
        {
		expr(tk_array, line_array, inc);
        }
        else if (!strcmp(tok.tkString, "/"))
        {
		expr(tk_array, line_array, inc);
        }
	else
	{
		inc--;
		return;
	}
}

Node A(char tk_array[20][10], int line_array[], int inc)
{
	/* <A> : <M> <A1> */

        Node node;
	M(tk_array, line_array, inc);
	A1(tk_array, line_array, inc);
	return;
}

Node A1(char tk_array[20][10], int line_array[], int inc)
{
	/* <A1> : + <A> | - <A> | empty */

        Node node;
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	if (!strcmp(tok.tkString, "+"))
        {
                A(tk_array, line_array, inc);
        }
        else if (!strcmp(tok.tkString, "-"))
        {
                A(tk_array, line_array, inc);
        }
        else
	{
                inc--;
                return;
        }
}

Node M(char tk_array[20][10], int line_array[], int inc)
{
	/* <M> : -<M> | <R> */ 

        Node node;
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	if (!strcmp(tok.tkString, "-"))
        {
                M(tk_array, line_array, inc);
        }
	else
	{
		R(tk_array, line_array, inc);
		return;
	}

}

Node R(char tk_array[20][10], int line_array[], int inc)
{
        /* <R> : (<expr>) | Identifier | Integer  */
	
        Node node;
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
	inc++;
	
	if (!strcmp(tok.tkID, "Operator"))
	{
		expr(tk_array, line_array, inc);
	        tok = scanner(tk_array[inc], line_array[inc]);
        	inc++;
	        if (!strcmp(tok.tkID, "Operator")) 
        	{
			return;
		}
		else {error(2);}
	}
	else if (!strcmp(tok.tkID, "Integer"))
		return;
	else if (!strcmp(tok.tkID, "Identifier"))
		return;
	else
		error(9);
}

Node in(char tk_array[20][10], int line_array[], int inc)
{
	/* <in> : scan Identifier .*/

        Node node;
	Token token;
	token = scanner(tk_array[inc], line_array[inc]);

	if (!strcmp(token.tkID, "Identifier"))
		return;
	else
		error(7);
}

Node out(char tk_array[20][10], int line_array[], int inc)
{
	/* <out> : out [<expr>] . */

        Node node;
	Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
	inc++;

        if (!strcmp(tok.tkID, "Operator"))
        {
                expr(tk_array, line_array, inc);
		tok = scanner(tk_array[inc], line_array[inc]);	
      		inc++;
		if(!strcmp(tok.tkID, "Operator"))
		{
			return;
		}
		else {error(8);}
	}
        else {error(8);}
}

Node ifs(char tk_array[20][10], int line_array[], int inc)
{
	/* <ifs> : if (<expr> <RO> <expr>) <stat> */
        Node node;
	return node;
}

Node loop(char tk_array[20][10], int line_array[], int inc)
{
	/* <loop> : loop (<expr> <RO> <expr>) <stat> */
	Node node;
	return node;
}

Node assign(char tk_array[20][10], int line_array[], int inc)
{
	/* <assign> : let Identifier = <expr> . */

        Node node;
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;
	
	if (!strcmp(tok.tkID, "Identifier"))
	{
	        tok = scanner(tk_array[inc], line_array[inc]);
       		inc++;
	        if (!strcmp(tok.tkID, "Operator"))
        	{
			expr(tk_array, line_array, inc);
			return;
		} else {error(2);}
	} else {error(1);}
}

Node RO(char tk_array[20][10], int line_array[], int inc)
{
	/* <RO> : < | < = | < | < = | = = | = */ 

        Node node;
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;	
	
	if (!strcmp(tok.tkID, "Operator"))
        {
                tok = scanner(tk_array[inc], line_array[inc]);
                inc++;
                if (!strcmp(tok.tkID, "Operator"))
                {
                      return;
                } 
		else 
		{
			inc--;
			return;
		}
        } else {error(1);}
}


void error(int i)
{
	fprintf(stderr, "\nError: %s\n", ERROR[i]);
	exit(1);
}

