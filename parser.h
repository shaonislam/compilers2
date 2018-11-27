#ifndef PARSER_H
#define PARSER_H

#include "node.h"

struct parse_Treenode{
	char *nonterm;
	struct parse_Treenode *children[10];		
};



Node parser(char tk_array[20][10], int line_array[]);
Node program(char tk_array[20][10], int line_array[], int inc);
Node vars(char tk_array[20][10], int line_array[], int inc);
Node block(char tk_array[20][10], int line_array[], int inc);
Node expr(char tk_array[20][10], int line_array[], int inc);
Node expr1(char tk_array[20][10], int line_array[], int inc);

Node A(char tk_array[20][10], int line_array[], int inc);
Node A1(char tk_array[20][10], int line_array[], int inc);
Node M(char tk_array[20][10], int line_array[], int inc); 
Node R(char tk_array[20][10], int line_array[], int inc); 

Node mStat(char tk_array[20][10], int line_array[], int inc);
Node stat(char tk_array[20][10], int line_array[], int inc); 
Node stats(char tk_array[20][10], int line_array[], int inc); 

Node in(char tk_array[20][10], int line_array[], int inc);
Node out(char tk_array[20][10], int line_array[], int inc);   

Node ifs(char tk_array[20][10], int line_array[], int inc);
Node loop(char tk_array[20][10], int line_array[], int inc);

Node assign(char tk_array[20][10], int line_array[], int inc); 
Node RO(char tk_array[20][10], int line_array[], int inc);    
 
void error(int i);




#endif
