#include <stdlib.h>
#include <stdio.h>
#include "node.h"

node *createNode(char *word){
  node *n = (node*)malloc(sizeof(node));
  n->word = word;
  n->freq = 1;
  n->height = 1;
  n->level = 0;
  n->parent = NULL;
  n->left = NULL;
  n->right = NULL;
  n->next = NULL;
  return n;
}
