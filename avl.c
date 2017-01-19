#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "avl.h"

avl *createAvl(){
  avl *tree = (avl*) malloc(sizeof(avl));
  tree->root = NULL;
  return tree;
}

int max(int lch,int rch){
  return (lch > rch)? lch : rch;
}

int height(node *n){
  if (n == NULL) {
    return 0;
  }
  return n->height;
}

node *rotateRight(node *nod){
  node *lc = nod->left;
  node *rc = lc->right;

  lc->right = nod;
  nod->left = rc;

  nod->height =  max(height(nod->left), height(nod->right)) + 1;
  lc->height = max(height(lc->left), height(lc->right)) + 1;
  return lc;
}

node *rotateLeft(node *nod){

  node *rc = nod->right;
  node *lc = rc->left;

  rc->left = nod;
  nod->right = lc;

  nod->height = max(height(nod->left), height(nod->right)) + 1;
  rc->height = max(height(rc->left), height(rc->right)) + 1;

  return rc;
}

int getBalance(node *n){
  if (n == NULL) {return 0;}
  return height(n->left) - height(n->right);
}

node *minValueNode(node *n){
    node* temp = n;
    /* loop down to find the leftmost leaf */
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

node *insertInAvl(node *root,char *word){
  if (root == NULL) {return createNode(word);}
  if(strcmp(root->word,word) > 0){root->left = insertInAvl(root->left,word);}
  else if(strcmp(root->word,word) < 0){root->right = insertInAvl(root->right,word);}
  else if(strcmp(root->word,word) == 0){++(root->freq);}
  root->height = max(height(root->left),height(root->right)) + 1;
  int balance = getBalance(root);

  //Left Left case
  if(balance > 1 && strcmp(word,root->left->word) < 0){return rotateRight(root);}
  //Right Right case
  if(balance < -1 && strcmp(word,root->right->word) > 0){return rotateLeft(root);}
  //Left Right case
  if(balance > 1 && strcmp(word,root->left->word) > 0){
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }
  //Right Left case
  if(balance < -1 && strcmp(word,root->right->word) < 0){
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }
  return root;
}

node *deleteInAvl(node *root,char *word){
  if (root == NULL) {return root;}
  if (strcmp(root->word,word) > 0) {root->left = deleteInAvl(root->left,word);}
  else if(strcmp(root->word,word) < 0){root->right = deleteInAvl(root->right,word);}
  else if(strcmp(root->word,word) == 0){
    root->freq = root->freq - 1;
    if(root->freq == 0){
      //one or no children
      if ((root->left) == NULL || (root->right) == NULL) {
        node *temp = root->left ? root->left :root->right;
        //no child
        if(temp == NULL){
          temp = root;
          root = NULL;
        }
        else{
          *root = *temp;
        }
        free(temp);
      }
      else{
        node *temp = minValueNode(root->right);
        root->word = temp->word;
        root->right = deleteInAvl(root->right,temp->word);
        root->freq = root->freq + 1;
      }
    }
    if (root == NULL) {return root;}
    root->height = max(height(root->left),height(root->right)) + 1;
    int balance = getBalance(root);
    // left left case
    if (balance > 1 && getBalance(root->left) >= 0) {return rotateRight(root);}
    // left right case
    if (balance > 1 && getBalance(root->left) < 0) {
      root->left = rotateLeft(root->left);
      return rotateRight(root);
    }
    // right right case
    if (balance < -1 && getBalance(root->right) <= 0) {return rotateLeft(root);}
    // right left case
    if (balance < -1 && getBalance(root->right) > 0) {
      root->right = rotateRight(root->right);
      return rotateLeft(root);
    }
  }
  //root->height = max(height(root->left),height(root->right)) + 1;
  return root;
}
