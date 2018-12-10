#ifndef NODE_H
#define NODE_H

#include "token.h"

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

#endif
