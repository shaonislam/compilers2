#ifndef PARSER_H
#define PARSER_H

#include "node.h"


Node *parser(char tk_array[20][10], int line_array[]);
Node *program(char tk_array[20][10], int line_array[]);
Node *vars(char tk_array[20][10], int line_array[], int inclvl []);
Node *block(char tk_array[20][10], int line_array[], int inclvl []);
Node *expr(char tk_array[20][10], int line_array[], int inclvl []);
Node *expr1(char tk_array[20][10], int line_array[], int inclvl []);

Node *A(char tk_array[20][10], int line_array[], int inclvl []);
Node *A1(char tk_array[20][10], int line_array[], int inclvl []);
Node *M(char tk_array[20][10], int line_array[], int inclvl []);
Node *R(char tk_array[20][10], int line_array[], int inclvl []);

Node *mStat(char tk_array[20][10], int line_array[], int inclvl []);
Node *stat(char tk_array[20][10], int line_array[], int inclvl []);
Node *stats(char tk_array[20][10], int line_array[], int inclvl []);

Node *in(char tk_array[20][10], int line_array[], int inclvl []);
Node *out(char tk_array[20][10], int line_array[], int inclvl []);

Node *ifs(char tk_array[20][10], int line_array[], int inclvl []);
Node *loop(char tk_array[20][10], int line_array[], int inclvl []);

Node *assign(char tk_array[20][10], int line_array[], int inclvl []);
Node *RO(char tk_array[20][10], int line_array[], int inclvl []);

void error(int i);

/*
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
*/



#endif
