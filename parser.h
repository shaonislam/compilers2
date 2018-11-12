#ifndef PARSER_H
#define PARSER_H



struct parse_Treenode{
	char *nonterm;
	struct parse_Treenode *children[10];		
};



int parser(char	tk_array[20][10], int line_array[]);
void program(char tk_array[20][10], int line_array[], int inc);
void vars(char tk_array[20][10], int line_array[], int inc);
void block(char tk_array[20][10], int line_array[], int inc);
void expr(char tk_array[20][10], int line_array[], int inc);

void A(char tk_array[20][10], int line_array[], int inc);
void M(char tk_array[20][10], int line_array[], int inc); 
void R(char tk_array[20][10], int line_array[], int inc); 

void mStats(char tk_array[20][10], int line_array[], int inc);
void stat(char tk_array[20][10], int line_array[], int inc); 
void stats(char tk_array[20][10], int line_array[], int inc); 

void in(char tk_array[20][10], int line_array[], int inc);
void out(char tk_array[20][10], int line_array[], int inc);   

void ifs(char tk_array[20][10], int line_array[], int inc);
void loop(char tk_array[20][10], int line_array[], int inc);

void assign(char tk_array[20][10], int line_array[], int inc); 
void RO(char tk_array[20][10], int line_array[], int inc);    
 
void error(int i);




#endif
