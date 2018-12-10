#ifndef PARSER_H
#define PARSER_H

#include "node.h"

struct parse_Treenode{
	char *nonterm;
	struct parse_Treenode *children[10];		
};



struct Node parser(char tk_array[20][10], int line_array[]);
void program(char tk_array[20][10], int line_array[], int inc);
int vars(char tk_array[20][10], int line_array[], int inc);
int block(char tk_array[20][10], int line_array[], int inc);
int expr(char tk_array[20][10], int line_array[], int inc);
int expr1(char tk_array[20][10], int line_array[], int inc);

int A(char tk_array[20][10], int line_array[], int inc);
int A1(char tk_array[20][10], int line_array[], int inc);
int M(char tk_array[20][10], int line_array[], int inc); 
int R(char tk_array[20][10], int line_array[], int inc); 

int mStat(char tk_array[20][10], int line_array[], int inc);
int stat(char tk_array[20][10], int line_array[], int inc); 
int stats(char tk_array[20][10], int line_array[], int inc); 

int in(char tk_array[20][10], int line_array[], int inc);
int out(char tk_array[20][10], int line_array[], int inc);   

int ifs(char tk_array[20][10], int line_array[], int inc);
int loop(char tk_array[20][10], int line_array[], int inc);

int assign(char tk_array[20][10], int line_array[], int inc); 
int RO(char tk_array[20][10], int line_array[], int inc);    
 
void error(int i);




#endif
