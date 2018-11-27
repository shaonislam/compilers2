#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef struct node
{
        int level;
	char *name;
       	Token token;
        struct Node *child_1;
        struct Node *child_2;
	struct Node *child_3;
	struct Node *child_4;
} Node;

#endif
