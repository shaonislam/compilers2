/*
parser.c


______________ TESTING TREEE ______________________


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

/* INC: GOING THROUGH ARRAY OF KEYWORDS TO SCAN
	increases with each word */
/* LEVEL: TRACKING EACH DEPTH OF KEYWORDS 
	increases with each nonterminal */


/*_________Creating Node__________*/
Node *createNode(char *name, int level){

	Node *new_node;
	new_node = malloc(sizeof(Node));
	if(new_node == NULL)
	{
		fprintf(stderr, "Error: Node Not Creating Properly");
		exit(1);
	}
	
	strcpy(new_node->name, name);
	new_node->level = level;
	new_node->child_1 = NULL;
	new_node->child_2 = NULL;
	new_node->child_3 = NULL;
	new_node->child_4 = NULL;
	
	return new_node;
}



Node *parser(char tk_array[20][10], int line_array[])
{	
        /*fprintf(stderr, "** Parsing **\n");*/
	Node *root;
	root = program(tk_array, line_array);		

	/*_______Check if EOFTOK__________*/
	return root;
}


Node *program(char tk_array[20][10], int line_array[])
{

	 /* <program> : <vars> <block> */
	fprintf(stderr, "\n<Program:>\n");
	
	int inclvl [2];
	inclvl[0] = 0; /* incrementer */
	inclvl[1] = 0; /* level tracker */ 

	Node *newnode = createNode("<program>", inclvl[1]);

	Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;

	if (!strcmp(tok.tkString, "void"))
	{
		newnode->child_1 = vars(tk_array, line_array, inclvl);
		newnode->child_2 = block(tk_array, line_array, inclvl);
	}
	else
	{
		error(11);
		exit(1);
	}
	return newnode;
}


Node *vars(char tk_array[20][10], int line_array[], int inclvl[])
{
        /* <vars> : empty | var Identifier : Integer <vars> */

        fprintf(stderr, "\n<vars>");
	inclvl[1]++;
	Node *newnode = createNode("<vars>", inclvl[1]);
 
	Token tok;
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);  
	inclvl[0]++;

	if(!strcmp(tok.tkString, "var"))
        {
	
      	        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        	inclvl[0]++;

		if(!strcmp(tok.tkID,"Identifier"))
	        {
			/*fprintf(stderr, " Identifier %s\n", tok.tkString);*/
			
			newnode->token = tok;	
        	        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);                        
			inclvl[0]++;

			if (!strcmp(tok.tkString,":"))
			{
				newnode->token = tok;
				tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);	
				inclvl[0]++;

				if(!strcmp(tok.tkID, "Integer"))	
				{	
					fprintf(stderr, " Integer %s\n", tok.tkString);
					
					newnode->token = tok;
					newnode->child_1 = vars(tk_array, line_array, inclvl);
                                     
					return newnode;
				
				}
				else {error(3);}
			}
			else {error(2);}
		}
		else {error(1);}
	}else{
		inclvl[0]--; /*empty: not in vars*/

	} 

	return NULL;
}



Node *block(char tk_array[20][10], int line_array[], int inclvl[])
{
        /* <block> : start <vars> <stats> stop */
     
       	fprintf(stderr, "\n<block>\n");
	inclvl[1]++;
        Node *node = createNode("<block>", inclvl[1]);

        Token tok;
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
	inclvl[0]++; 

	if (!strcmp(tok.tkString, "start"))
	{
		
		node->child_1 = vars(tk_array, line_array, inclvl);
		node->child_2 = stats(tk_array, line_array, inclvl);

		tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
		inclvl[0]++;
		if(!strcmp(tok.tkString, "stop"))
		{
			return node;
		}
		else{
			error(5);
			exit(1);}				
	}
	else{
		error(4); 
		exit(1);}
} 


Node *stats(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <stats> : <stat> <mStat> */
	fprintf(stderr, "\n<stats>\n");
	inclvl[1]++;

	Node *node = createNode("<stats>", inclvl[1]);
	node->child_1 = stat(tk_array, line_array, inclvl);
	node->child_2 = mStat(tk_array, line_array, inclvl);
	return node;
} 

Node *mStat(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <mStat> : empty | <stat> <mStat> */
        
	fprintf(stderr, "\n<mStat>\n");
	inclvl[1]++;
	
        Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;

	char * stat_array [] = {"in", "out", "start", "if", "loop", "assign"};
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
	inclvl[0]--;
	if (match > 0)
	{
		Node *node = createNode("<mStat>", inclvl[1]);
		node->child_1 = stat(tk_array, line_array, inclvl);
		node->child_2 = mStat(tk_array, line_array, inclvl);		
		return node;
		
	}else
	{	/*empty*/
		return NULL;
	}
}


Node *stat(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <stat> : <in> | <out> | <block> | <ifs> | <loop> | <assign> */
	/* scan, out, start, if, loop, let */

	fprintf(stderr, "\n<stat>\n");
	inclvl[1]++;
	Node *node = createNode("<stat>", inclvl[1]);	
    
	Token tok; 
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);	
	inclvl[0]++;	
		

	if (!strcmp(tok.tkString, "scan"))
	{
		/*in*/
                inclvl[0]--;
		node->child_1 = in(tk_array, line_array, inclvl);
	}
	else if (!strcmp(tok.tkString, "out"))
	{
		/*out*/
                inclvl[0]--;		
                node->child_1 =	out(tk_array, line_array, inclvl);

	}
        else if	(!strcmp(tok.tkString, "start"))
        {
                /*block*/
		inclvl[0]--;
                node->child_1 =	block(tk_array, line_array, inclvl);
	
        }
        else if	(!strcmp(tok.tkString, "if"))
        {
                /*if*/
                inclvl[0]--;
		node->child_1 =	ifs(tk_array, line_array, inclvl);
	}
        else if	(!strcmp(tok.tkString, "loop"))
        {
                /*loop*/
                inclvl[0]--;
		node->child_1 = loop(tk_array, line_array, inclvl);
        }        
        else if	(!strcmp(tok.tkString, "let"))
        {
                /*assign*/
                inclvl[0]--;
		node->child_1 = assign(tk_array, line_array, inclvl);
        }
	else
	{
		error(6);
		exit(1);
	}

	return node;
}

Node *expr(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* NOPE <expr> : <A> <expr1> */ 
	/*<expr> -> <A> / <expr> | <A> * <expr> | <A>*/
	
	fprintf(stderr, "\n<expr>\n");
	inclvl[1]++;
        Node *node = createNode("<expr>",inclvl[1]);

	node->child_1 = A(tk_array, line_array, inclvl);

	Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;

	if (*tok.tkString == '/'){
		node->token = tok;
		node->child_2 = expr(tk_array, line_array, inclvl);
		return node;
	}
	else if (*tok.tkString == '*'){
		node->token = tok;
		node->child_2 = expr(tk_array, line_array, inclvl);
		return node;
	}
	else{
		inclvl[0]--;
		return node;}
}


Node  *A(char tk_array[20][10], int line_array[], int inclvl[])
{
	/*<A> -> <M> + < A> | <M> - <A> | <M>*/
	/* NOPE<A> : <M> <A1> */
	fprintf(stderr, "\n<A>\n");
        inclvl[1]++;
	Node *node = createNode("<A>", inclvl[1]);

	node->child_1 = M(tk_array, line_array, inclvl);
	Token tok;
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;

	if (*tok.tkString == '+') 
        {
                node->token = tok;
                node->child_2 = A(tk_array, line_array, inclvl);
         	return node;
        }
        else if (*tok.tkString == '-')
        {
                node->token = tok;
         	node->child_2 = A(tk_array, line_array, inclvl);
                return node;
        }
	else{
		inclvl[0]--;
		return node;
	}
}



Node  *M(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <M> : -<M> | <R> */ 
	
	fprintf(stderr, "\n<M>\n");
	inclvl[1]++;
        Node *node = createNode("<M>", inclvl[1]);

	Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;

	if (*tok.tkString == '-')
        {
		node->token = tok;
		node->child_1 = M(tk_array, line_array, inclvl); 
        }
	else
	{
		inclvl[0]--;
		node->child_1 = R(tk_array, line_array, inclvl);
	}
	return node;
}

Node *R(char tk_array[20][10], int line_array[], int inclvl[])
{
        /* <R> : (<expr>) | Identifier | Integer  */
	
        fprintf(stderr,	"\n<R>\n");
	inclvl[1]++;
	Node *node = createNode("<expr>", inclvl[1]);

	Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
	inclvl[0]++;
	
	if (*tok.tkString == '(')
	{
		node->child_1 = expr(tk_array, line_array, inclvl);		

	        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        	inclvl[0]++;
	        if (*tok.tkString == ')') 
        	{
			return node;
		}
		else 
			{error(2);}
		return NULL;
	}
	else if (!strcmp(tok.tkID, "Integer"))
	{	
		node->token = tok;
		return node; 
	}
	else if (!strcmp(tok.tkID, "Identifier"))
	{
		node->token = tok;
		return node;
	}else
		{error(9);}
	return node;
}

Node *in(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <in> : scan Identifier .*/

	fprintf(stderr, "\n<in>\n");
	inclvl[1]++;
	Node *node = createNode("<in>", inclvl[1]);        

	Token tok;
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
	inclvl[0]++;

	if (!strcmp(tok.tkString, "scan"))
	{
		tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
		inclvl[0]++;
		if (!strcmp(tok.tkString, "Identifier"))
		{
			node->token = tok;
			return node;
		}
		else
		{
            		error(7);
                	exit(1);
		}
	}
	else{
		error(7);
		exit(1);
	}
	return NULL;
}

Node  *out(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <out> : out [<expr>] . */
		
	fprintf(stderr, "\n<out>\n");
        inclvl[1]++;
        Node *node = createNode("<out>", inclvl[1]);

	Token tok;
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
	inclvl[0]++;

	if (!strcmp(tok.tkString, "out"))
	{
                tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
		inclvl[0]++;

        	if (*tok.tkString == '[')
        	{	
			node->child_1 = expr(tk_array, line_array, inclvl);
			tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);	
      			inclvl[0]++;

			if(*tok.tkString == ']')
			{
				tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        	        	inclvl[0]++;
                		if(*tok.tkString == '.')
                        	{	
					return node;
				} else {error(12);}
                	}else {error(12);}
		}
		else {error(8);}
	}
        else {error(8);}
	exit(1);
}

Node *ifs(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <ifs> : if (<expr> <RO> <expr>) <stat> */
 
       	fprintf(stderr, "\n<if>\n");
        inclvl[1]++;
	Node *node = createNode("<if>", inclvl[1]);
	
        Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;
	
        if (!strcmp(tok.tkString, "if"))
        {
		tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
		inclvl[0]++;
	
	        if (*tok.tkString == '(')
        	{
	                node->child_1 = expr(tk_array, line_array, inclvl);
                        node->child_2 = RO(tk_array, line_array, inclvl);
                        node->child_3 = expr(tk_array, line_array, inclvl);
		
                	if (*tok.tkString == ')')
                	{
				node->child_4 = stat(tk_array, line_array, inclvl);
				return node;
				
                	}
			else{error(14);}
                }else{error(14);}
        }else{error(14);}
	exit(1);
}

Node *loop(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <loop> : loop (<expr> <RO> <expr>) <stat> */

	fprintf(stderr, "\n<loop>\n");
	inclvl[1]++;
	
	Node *node = createNode("<loop>", inclvl[1]);

	Token tok;
	tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;
	
	if (!strcmp(tok.tkString, "loop"))
        {
       		if (*tok.tkString == '(')
       		{
			node->child_1 = expr(tk_array, line_array, inclvl);
			node->child_2 = RO(tk_array, line_array, inclvl);
			node->child_3 = expr(tk_array, line_array, inclvl);
	
	        	if (*tok.tkString == ')')
        		{       
				node->child_4  = stat(tk_array, line_array, inclvl);
				return node;
			}
			else{
				error(13);
				exit(1);}
		}else{
			error(13);
			exit(1);}
	}else{
		error(13);
		exit(1);
		}
}

Node *assign(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <assign> : let Identifier = <expr> . */

        fprintf(stderr, "\n<assign\n");
	inclvl[1]++;
	Node *node = createNode("<assign>", inclvl[1]);

	Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;
	
	if (!strcmp(tok.tkID, "Identifier"))
	{
		node->token = tok;
	        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
       		inclvl[0]++;
	        if (*tok.tkString == '=')
        	{
			node->child_1 = expr(tk_array, line_array, inclvl);
			return node;
		} else {error(2);
			exit(1);}
	} else {error(1);
		exit(1);}
}

Node *RO(char tk_array[20][10], int line_array[], int inclvl[])
{
	/* <RO> : < | < = | < | < = | = = | = */ 

        fprintf(stderr, "<RO>");
	inclvl[1]++;
	Node *node = createNode("<RO>", inclvl[1]);

	Token tok;
        tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
        inclvl[0]++;	
	
	if (!strcmp(tok.tkID, "Operator"))
        {
		node->token = tok;

                tok = scanner(tk_array[inclvl[0]], line_array[inclvl[0]]);
                inclvl[0]++;
                if (!strcmp(tok.tkID, "Operator"))
                {
			node->token2 = tok;
                	return node;
                } 
		else 
		{
			inclvl[0]--;
			return node;
		}
        } else {error(1);
		exit(1);}
}


void error(int i)
{
	fprintf(stderr, "\nError: %s\n", ERROR[i]);
	exit(1);
}

