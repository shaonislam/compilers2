#ifndef NODE_H
#define NODE_H

#include "token.h"



typedef struct node{
	char name[50];
	int level;
	Token token;
	Token token2;
	
	struct node *child_1;
	struct node *child_2;
	struct node *child_3;
	struct node *child_4;	
} Node;


/*
struct Node
{
        int level;
	char name[50];
       	Token token;
        struct Node *child_1;
        struct Node *child_2;
	struct Node *child_3;
	struct Node *child_4;
};
*/
#endif
