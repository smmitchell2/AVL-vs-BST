#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "bst.h"

bst *createBST(){
  bst *tree = (bst*) malloc(sizeof(bst));
  tree->root = NULL;
  return tree;
}

node *insertInBST(node *root,char *word){
  node *n = createNode(word);
  if(root == NULL){ root = n;root->parent = root;}
  else if(strcmp(root->word,word) == 0){++root->freq;}
  else if(strcmp(root->word,word) < 0){
    root->right = insertInBST(root->right,word);
    root->right->parent = root;
    }
  else if(strcmp(root->word,word) > 0){
    root->left = insertInBST(root->left,word);
    root->left->parent = root;
    }
  return root;
}

node *deleteInBST(node *root,char *word){
  if (root == NULL) { return root;}
  if(strcmp(root->word,word) < 0){root->right = deleteInBST(root->right,word);}
  else if(strcmp(root->word,word) > 0){root->left = deleteInBST(root->left,word);}
  else if(strcmp(root->word,word) == 0){
    --root->freq;
    if (root->freq == 0){
      if (root->left != NULL && root->right != NULL) {
        node *temp = root->right;
        root->left->parent = root->parent;
        root->right->parent = root->left;
        root = root->left;
        root->right = temp;
        //root->left = root->left->left;

      }
      else if (root->left != NULL && root->right == NULL){
        root->left->parent = root->parent;
        root = root->left;
        //root->left = root->left;
      }
      else if (root->left == NULL && root->right != NULL){
        root->right->parent = root->parent;
        root = root->right;
        //root->right = root->right;
      }
      else {root = NULL;}
    }
  }
  return root;
}

void inorder(node *root){
  if(root == NULL){return;}
  inorder(root->left);
  printf("word:%s freq:%d \n",root->word,root->freq );
  inorder(root->right);
}
