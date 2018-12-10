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
        "1 Identifier Missing",
        "2 Operator Missing",
	"3 Integer Missing",
	"4 Incomplete block, start terminal missing",
        "5 Incomplete block, stop terminal missing",
	"6 Incorrect direction to <stat>, no match to nonterminals",
	"7 No Identifier present to scan",
	"8 <out>: Square Brackets missing []",
	"9 Invalid <R> terminal",
        "10 Other",
	"11 Invalid: Void missing",
	"12 <out>: . missing",
	"13 Incorrect Loop issue",
        "14 Incorrect If statement issue"
};


int inc = 0;

struct Node parser(char tk_array[20][10], int line_array[])
{
	
        /*fprintf(stderr, "** Parsing **\n");*/
	struct Node root;
	program(tk_array, line_array, inc);		
	return root;
}


void program(char tk_array[20][10], int line_array[], int inc)
{
	 /* <program> : <vars> <block> */
	fprintf(stderr, "\n<Program:>\n");
	

	struct Node newnode;
	strcpy(newnode.name, "program");
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
	/*fprintf(stderr, "In tok: %s\n", tok.tkString);*/
        inc++;

	if (!strcmp(tok.tkString, "void"))
	{
		/*
		*newnode.child_1 = vars(tk_array, line_array, inc);
		*newnode.child_2 = block(tk_array, line_array, inc);
		*/

		/*fprintf(stderr, "prog inc = %d\n", inc);*/
		inc = vars(tk_array, line_array, inc);
	        /*fprintf(stderr,	"prog inc = %d\n", inc);*/
		inc = block(tk_array, line_array, inc);
	}
	else
	{
		exit(11);
	}
	return;
}


int vars(char tk_array[20][10], int line_array[], int inc)
{
        fprintf(stderr, "\n<vars>");
	struct Node newnode; 
	Token tok;

	/* <vars> : empty | var Identifier : Integer <vars> */

	
	tok = scanner(tk_array[inc], line_array[inc]);  
	inc++;
	
	/*fprintf(stderr, "Token in Vars: %s\n", tok.tkString);*/
	if(!strcmp(tok.tkString, "var"))
        {
		strcpy(newnode.name,"var");
		newnode.token = tok;
   
   	        tok = scanner(tk_array[inc], line_array[inc]);
        	inc++;
   	
		if(!strcmp(tok.tkID,"Identifier"))
	        {
			/*fprintf(stderr, " Identifier %s\n", tok.tkString);*/
			/*strcpy(newnode.child_1->name, "Identifier");
			newnode.child_1->token = tok;*/

        	        tok = scanner(tk_array[inc], line_array[inc]);                        
			inc++;

			if (!strcmp(tok.tkString,":"))
			{
				/*fprintf(stderr,	" : \n");*/
                                /*strcpy(newnode.child_2->name, " : ");
                                newnode.child_2->token = tok;*/
			
				tok = scanner(tk_array[inc], line_array[inc]);	
				inc++;

				if(!strcmp(tok.tkID, "Integer"))	
				{	
					fprintf(stderr, " Integer %s\n", tok.tkString);
					/*
					strcpy(newnode.child_3->name, "Integer");
				       	newnode.child_3->token = tok;
					*/
                                        inc = vars(tk_array, line_array, inc); 
				
				}
				else {error(3);}
			}
			else {error(2);}
		}
		else {error(1);}
	}else{
		inc--; /*empty: not in vars*/
	} 

	/*fprintf(stderr, "inc = %d\n", inc);*/
	return inc;
}

int block(char tk_array[20][10], int line_array[], int inc)
{
        /* <block> : start <vars> <stats> stop */
     
        fprintf(stderr, "\n<block>\n");
        /*fprintf(stderr, "inc = %d\n", inc); */

        struct Node node;
	strcpy(node.name,"block");
        Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
	/*fprintf(stderr, "In block testing: %s\n", tok.tkString);*/
	inc++; 

	if (!strcmp(tok.tkString, "start"))
	{
		inc = vars(tk_array, line_array, inc);
		inc = stats(tk_array, line_array, inc);
		
		tok = scanner(tk_array[inc], line_array[inc]);
		inc++;
		if(!strcmp(tok.tkString, "stop"))
		{
			return inc;
		}
		else
		{error(5);}				
	}
	else
	{error(4);}
		
	return inc;
} 


int stats(char tk_array[20][10], int line_array[], int inc)
{
	/* <stats> : <stat> <mStat> */
	fprintf(stderr, "\n<stats>\n");

	struct Node node;
	strcpy(node.name,"stats");
	inc = stat(tk_array, line_array, inc);
	inc = mStat(tk_array, line_array, inc);
	return inc;
} 


int mStat(char tk_array[20][10], int line_array[], int inc)
{
	/* <mStat> : empty | <stat> <mStat> */
        
	fprintf(stderr, "\n<mStat>\n");
	
        struct Node node;
	strcpy(node.name,"mStats");

        Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	char * stat_array [] = {"in", "out", "block", "if", "loop", "assign"};
	int i;
	int match = 0;

	for (i = 0; i < 6; i++)
	{
		int result = strcmp(stat_array[i], tok.tkString);
		if (result == 0)
		{
			/* matches */
			match++;
		}
	}
	inc--;
	if (match > 0)
	{
		inc = stat(tk_array, line_array, inc);
		inc = mStat(tk_array, line_array, inc);
	}else
	{	/*empty*/
		return inc;
	}

	return inc;	
}


int stat(char tk_array[20][10], int line_array[], int inc)
{
	/* <stat> : <in> | <out> | <block> | <ifs> | <loop> | <assign> */
	/* scan, out, start, if, loop, let */

	fprintf(stderr, "\n<stat>\n");
	
        struct Node node;
	strcpy(node.name,"stat");

	Token tok; 
	tok = scanner(tk_array[inc], line_array[inc]);	
	inc++;	
		

	/*fprintf(stderr, "Coming in <STAT>: %s\n", tok.tkString);*/

	if (!strcmp(tok.tkString, "scan"))
	{
		/*in*/
                inc--;
		inc = in(tk_array, line_array, inc);
	}
	else if (!strcmp(tok.tkString, "out"))
	{
		/*out*/
                inc--;
		inc = out(tk_array, line_array, inc);
	}
        else if	(!strcmp(tok.tkString, "start"))
        {
                /*block*/
		inc--;
		inc = block(tk_array, line_array, inc);
        }
        else if	(!strcmp(tok.tkString, "if"))
        {
                /*if*/
                inc--;
		inc = ifs(tk_array, line_array, inc);
	}
        else if	(!strcmp(tok.tkString, "loop"))
        {
                /*loop*/
                inc--;
		inc = loop(tk_array, line_array, inc);
        }        
        else if	(!strcmp(tok.tkString, "let"))
        {
                /*assign*/
                inc--;
		inc = assign(tk_array, line_array, inc);
        }
	else
	{
		error(6);
	}

	return inc;
}

int expr(char tk_array[20][10], int line_array[], int inc)
{
	/* <expr> : <A> <expr1> */ 

	fprintf(stderr, "\n<expr>\n");

        struct Node node;
	strcpy(node.name,"expr");

	inc = A(tk_array, line_array, inc);
	inc = expr1(tk_array, line_array, inc);
	return inc;
}

int expr1 (char tk_array[20][10], int line_array[], int inc)
{
	/* <expr1> : / <expr> | * <expr> | empty */

        fprintf(stderr,	"\n<expr1>\n");
        struct Node node;
	strcpy(node.name,"expr1");
        Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

        if (*tok.tkString == '*')
        {
		inc = expr(tk_array, line_array, inc);
        }
        else if (*tok.tkString == '/')
        {
		inc = expr(tk_array, line_array, inc);
        }
	else
	{
		inc--;
	}
	return inc;
}

int A(char tk_array[20][10], int line_array[], int inc)
{
	/* <A> : <M> <A1> */
	fprintf(stderr, "\n<A>\n");
        struct Node node;
	strcpy(node.name,"A");
	inc = M(tk_array, line_array, inc);
	inc = A1(tk_array, line_array, inc);
	return inc;
}

int A1(char tk_array[20][10], int line_array[], int inc)
{
	/* <A1> : + <A> | - <A> | empty */
	fprintf(stderr, "\n<A1>\n");
        struct Node node;
	strcpy(node.name,"A1");
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	if (*tok.tkString == '+')
        {
                inc = A(tk_array, line_array, inc);
        }
        else if (*tok.tkString == '-')
        {
                inc = A(tk_array, line_array, inc);
        }
        else
	{	/*empty*/
                inc--;
        }
	return inc;
}

int M(char tk_array[20][10], int line_array[], int inc)
{
	/* <M> : -<M> | <R> */ 
	
	fprintf(stderr, "\n<M>\n");

        struct Node node;
	strcpy(node.name,"M");
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;

	if (*tok.tkString == '-')
        {
               /* *node.child_1 = M(tk_array, line_array, inc);*/
		inc = M(tk_array, line_array, inc);
        }
	else
	{
		/* *node.child_1 = R(tk_array, line_array, inc);*/
		inc--;
		inc = R(tk_array, line_array, inc);
	}
	return inc;
}

int R(char tk_array[20][10], int line_array[], int inc)
{
        /* <R> : (<expr>) | Identifier | Integer  */
	
        fprintf(stderr,	"\n<R> ");

        struct Node node;
	strcpy(node.name,"R");
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
	inc++;
	
	/*fprintf(stderr, "Coming in to <R>: %s\n", tok.tkString);*/
	
	if (*tok.tkString == '(')
	{
		inc = expr(tk_array, line_array, inc);
	        tok = scanner(tk_array[inc], line_array[inc]);
        	inc++;
	        if (*tok.tkString == ')') 
        	{
			return inc;
		}
		else {error(2);}
	}
	else if (!strcmp(tok.tkID, "Integer"))
	{	
		fprintf(stderr, "Integer %s\n", tok.tkString);
		return inc; 
	}
	else if (!strcmp(tok.tkID, "Identifier"))
	{
                fprintf(stderr, "Identifier  %s\n", tok.tkString);
		return inc;
	}else
		{error(9);}
	return inc;
}

int in(char tk_array[20][10], int line_array[], int inc)
{
	/* <in> : scan Identifier .*/

	fprintf(stderr, "\n<in>\n");
        struct Node node;
	strcpy(node.name,"in");
	Token token;
	token = scanner(tk_array[inc], line_array[inc]);
	inc++;

	if (!strcmp(token.tkString, "scan"))
		return inc;
	else
		error(7);
	return inc;
}

int out(char tk_array[20][10], int line_array[], int inc)
{
	/* <out> : out [<expr>] . */
	
	fprintf(stderr, "\n<out>\n");
               
        struct Node node;
	strcpy(node.name,"out");
	Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
	inc++;

	if (!strcmp(tok.tkString, "out"))
	{
                tok = scanner(tk_array[inc], line_array[inc]);
		inc++;

        	if (*tok.tkString == '[')
        	{
                	inc = expr(tk_array, line_array, inc);
			tok = scanner(tk_array[inc], line_array[inc]);	
			/*fprintf(stderr, "BACK IN OUT AFTER EXPR: %s\n", tok.tkString);*/
      			inc++;

			if(*tok.tkString == ']')
			{
				tok = scanner(tk_array[inc], line_array[inc]);
        	        	inc++;
                		if(*tok.tkString == '.')
                        	{	
					return inc;
				} else {error(12);}
                	}else {error(12);}
		}
		else {error(8);}
	}
        else {error(8);}
	return inc;
}

int ifs(char tk_array[20][10], int line_array[], int inc)
{
	/* <ifs> : if (<expr> <RO> <expr>) <stat> */
 
       	fprintf(stderr, "\n<if>\n");
        struct Node node;
	strcpy(node.name,"if");

        Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;
        if (!strcmp(tok.tkString, "if"))
        {
		tok = scanner(tk_array[inc], line_array[inc]);
		inc++;
	        if (*tok.tkString == '(')
        	{
                	inc = expr(tk_array, line_array, inc);
                	inc = RO(tk_array, line_array, inc);
                	inc = expr(tk_array, line_array, inc);

                	if (*tok.tkString == ')')
                	{
                        	inc = stat(tk_array, line_array, inc);
				
                	}else{error(14);}
                }else{error(14);}
        }else{error(14);}

	return inc;
}

int loop(char tk_array[20][10], int line_array[], int inc)
{
	/* <loop> : loop (<expr> <RO> <expr>) <stat> */

	fprintf(stderr, "\n<loop>\n");
	struct Node node;
	strcpy(node.name,"loop");

	Token tok;
	tok = scanner(tk_array[inc], line_array[inc]);
        inc++;
	
	if (!strcmp(tok.tkString, "loop"))
        {
       		if (*tok.tkString == '(')
       		{
			inc = expr(tk_array, line_array, inc);
			inc = RO(tk_array, line_array, inc);
			inc = expr(tk_array, line_array, inc);
	
	        	if (*tok.tkString == ')')
        		{       
				inc = stat(tk_array, line_array, inc);
			}
			else{error(13);}
		}else{error(13);}
	}else{error(13);}
	
	return inc;
}

int assign(char tk_array[20][10], int line_array[], int inc)
{
	/* <assign> : let Identifier = <expr> . */

        struct Node node;
	strcpy(node.name,"assign");
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;
	
	if (!strcmp(tok.tkID, "Identifier"))
	{
	        tok = scanner(tk_array[inc], line_array[inc]);
       		inc++;
	        if (*tok.tkString == '=')
        	{
			expr(tk_array, line_array, inc);
			return inc;
		} else {error(2);}
	} else {error(1);}
	return inc;
}

int RO(char tk_array[20][10], int line_array[], int inc)
{
	/* <RO> : < | < = | < | < = | = = | = */ 

        struct Node node;
	strcpy(node.name,"RO");
	Token tok;
        tok = scanner(tk_array[inc], line_array[inc]);
        inc++;	
	
	if (!strcmp(tok.tkID, "Operator"))
        {
                tok = scanner(tk_array[inc], line_array[inc]);
                inc++;
                if (!strcmp(tok.tkID, "Operator"))
                {
                      return inc;
                } 
		else 
		{
			inc--;
			return inc;
		}
        } else {error(1);}
	
	return inc;
}


void error(int i)
{
	fprintf(stderr, "\nError: %s\n", ERROR[i]);
	exit(1);
}

