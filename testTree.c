#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "testTree.h"

void printTree(Node *root){

        if (root == NULL){
                printf("Error: Array is Empty\n");
                return;
        }

       	if(root->token.tkString != NULL && root->token2.tkString != NULL){
                printf("%*s%-9s\n", root->level*2," ", concat(concat(root->name, root->token.tkString), root->token2.tkString));
        }
        else if(root->token.tkString != NULL && root->token2.tkString == NULL){
		/*______________________*/
        }
	else{
        	printf("%*s%-9s\n", root->level*2," ", root->name);
	}        

        if (root->child_1 != NULL)
                printTree(root->child_1);
        if (root->child_2 != NULL)
                printTree(root->child_2);
        if (root->child_3 != NULL)
                printTree(root->child_3);
        if (root->child_4 != NULL)
                printTree(root->child_4);

}


char *concat(const char *s1, const char *s2){
  char *ns = malloc(snprintf(NULL, 0, "%s %s", s1, s2) + 1);
  if(ns == NULL){
        printf("Concat Failed\n");
        exit(EXIT_FAILURE);
  }
  sprintf(ns, "%s %s", s1, s2);
  return ns;
}
