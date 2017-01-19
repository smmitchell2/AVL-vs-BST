#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "node.h"
#include "bst.h"
#include "avl.h"
#include "scanner.h"
#include "queue.h"

int min(int lch,int rch){
  return (lch < rch)? lch : rch;
}

int nodeLevel(node *root){
  int level = 0;
  if(root->parent == root){return level;}
  else{
    while(root->parent != root){
      level = level + 1;
      root = root->parent;
    }
    return level;
  }
}

char favorite(node *n){
  char f = '\0';
  if (n->left == NULL && n->right != NULL) {
    f = '+';
  }
  else if (n->right == NULL && n->left != NULL) {
    f = '-';
  }
  else if (height(n->right) > height(n->left)) {
    f = '+';
  }
  else if (height(n->right) < height(n->left)) {
    f = '-';
  }
  return f;
}

char whichChild(node *root){
  char right = 'R';
  char left = 'L';
  char c = 'X';
  if (root == root->parent->left) {
    c = left;
  }
  else if (root == root->parent->right) {
    c = right;
  }
  else if (root == root->parent) {
    return c;
  }
  return c;
}

int isLeaf(node *root){
  if (root->left == NULL && root->right == NULL ) {
      return 1;
  }
  else{
    return 0;
  }
}

char leaf(node *root){
  char l = '=';
  char a = '\0';
  if (isLeaf(root)) {
    return l;
  }
  return a;
}

char *grammar(char *word){
  int i;
  int spot = 0;
  char *newWord = malloc(sizeof(char)*strlen(word)+1);
  for(i = 0; i < (int) strlen(word); i++){
    if(isalpha(word[i])){
      spot = 0;
      word[i] = tolower(word[i]);
      sprintf(newWord,"%s%c",newWord,word[i]);
    }
    else if(isspace(word[i]) && spot == 0){
      sprintf(newWord,"%s ",newWord);
      spot = 1;
    }
  }
  return newWord;
}

int countNodes(node *root){
  int count = 1;
  if(root->left != NULL){count += countNodes(root->left);}
  if (root->right != NULL){count += countNodes(root->right);}
  return count;
}

int count(node *root){
  int count = 0;
  if(root != NULL){count = countNodes(root);}
  return count;
}

int minDepth(node *root){
  if (root == NULL) {return -1;}
  else{
    /* compute the depth of each subtree */
    int lDepth = minDepth(root->left);
    int rDepth = minDepth(root->right);
    /* use the smaller one */
    if (lDepth < rDepth){return(lDepth)+1;}
    else {return(rDepth)+1;}
  }
}

int maxDepth(node* root){
  if (root==NULL){return -1;}
  else{
    /* compute the depth of each subtree */
    int lDepth = maxDepth(root->left);
    int rDepth = maxDepth(root->right);
    /* use the larger one */
    if (lDepth > rDepth){return(lDepth)+1;}
    else {return(rDepth)+1;}
  }
}

void statistics(node *root){
  if (root == NULL) {printf("Empty tree\n" );return;}
  printf("Number of nodes in tree: %d\n",count(root));
  printf("Distance from root to closest null child: %d\n", minDepth(root));
  printf("Distance from root to furthest null child: %d \n" ,maxDepth(root));
}

node *wordFreq(node *root,char *word){
  if (root == NULL) {return NULL;}
  if(strcmp(root->word,word) > 0){root->left = wordFreq(root->left,word);}
  else if(strcmp(root->word,word) < 0){root->right = wordFreq(root->right,word);}
  else if(strcmp(root->word,word) == 0){return root;}
  return root;
}


void levelOrderAVL(node *root){
  if(root == NULL){printf("Empty tree\n" );return;}
  queue *q = createQueue();
  enqueue(q,root);
  root->parent = root;
  root->level = nodeLevel(root);
  int i = root->level;
  printf("%d: ",root->level );
  while(root != NULL){
    node *p = dequeue(q);
    if(p == NULL){return;}
    p->level = nodeLevel(p);
    if(i == p->level){
      if(p->left == NULL && p->right == NULL){
        printf("=%s%c(%s%c)%d%c ",p->word,favorite(p),p->parent->word,favorite(p->parent),p->freq,whichChild(p) );
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
      else{
        printf("%s%c(%s%c)%d%c ",p->word,favorite(p),p->parent->word,favorite(p->parent),p->freq,whichChild(p));
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
    }
    else{
      if(p->left == NULL && p->right == NULL){
        printf("\n" );
        printf("%d: =%s%c(%s%c)%d%c ",p->level,p->word,favorite(p),p->parent->word,favorite(p->parent),p->freq,whichChild(p));
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
      else{
        printf("\n" );
        printf("%d: %s%c(%s%c)%d%c ",p->level,p->word,favorite(p),p->parent->word,favorite(p->parent),p->freq,whichChild(p));
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
    }
    i = p->level;
  }
}

void levelOrderBST(node *root){
  if(root == NULL){printf("Empty tree\n" );return;}
  queue *q = createQueue();
  enqueue(q,root);
  root->parent = root;
  root->level = nodeLevel(root);
  int i = root->level;
  printf("%d: ",root->level );
  while(root != NULL){
    node *p = dequeue(q);
    if(p == NULL){return;}
    p->level = nodeLevel(p);
    if(i == p->level){
      if(p->left == NULL && p->right == NULL){
        printf("=%s(%s)%d%c ",p->word,p->parent->word,p->freq,whichChild(p) );
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
      else{
        printf("%s(%s)%d%c ",p->word,p->parent->word,p->freq,whichChild(p));
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
    }
    else{
      if(p->left == NULL && p->right == NULL){
        printf("\n" );
        printf("%d: =%s(%s)%d%c ",p->level,p->word,p->parent->word,p->freq,whichChild(p));
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
      else{
        printf("\n" );
        printf("%d: %s(%s)%d%c ",p->level,p->word,p->parent->word,p->freq,whichChild(p));
        if(p->left != NULL){ p->left->parent = p; enqueue(q,p->left);}
        if(p->right != NULL){p->right->parent = p;enqueue(q,p->right);}
      }
    }
    i = p->level;
  }
}

char *readWord(FILE *fp){
    char *word = NULL;
    char ch;
    ch = fgetc(fp);
    while (ch == ' ' || ch == '\n') {
      ch = fgetc(fp);
    }
    switch (ch) {
      case '"':
        ungetc(ch,fp);
        word = readString(fp);
        break;
      case ' ':
        break;
      default:
        ungetc(ch,fp);
        word = readToken(fp);
        break;
      }
    return word;
}

node *readInput(char const *a,FILE *fp){
  char *word;
  if (strcmp(a,"-b") == 0) {
    bst *bst = createBST();
    word = readWord(fp);
    word = grammar(word);
    bst->root = insertInBST(bst->root,word);
    while(word!=NULL){
      word = readWord(fp);
      if(word!=NULL){
        word = grammar(word);
        bst->root = insertInBST(bst->root,word);
      }
    }
    return bst->root;
  }
  else if (strcmp(a,"-a") == 0) {
    avl *avl = createAvl();
    word = readWord(fp);
    word = grammar(word);
    avl->root = insertInAvl(avl->root,word);
    while(word!=NULL){
      word = readWord(fp);
      if(word!=NULL){
        word = grammar(word);
        avl->root = insertInAvl(avl->root,word);
      }
    }
    return avl->root;
  }
  exit(0);
}

void readCommandsAVL(node *root, FILE *cp){
  char *word = readWord(cp);
  node *r = root;
  while(word != NULL){
    word = grammar(word);
    if (strcmp(word,"i") == 0) {
      word = readWord(cp);
      word = grammar(word);
      root = insertInAvl(root,word);
    }
    else if (strcmp(word,"d") == 0) {
      word = readWord(cp);
      word = grammar(word);
      root = deleteInAvl(root,word);
      if (root != r) {
        r  = root;
      }
    }
    else if (strcmp(word,"f") == 0) {
      word = readWord(cp);
      word = grammar(word);
      root = r;
      if (wordFreq(root,word) != NULL) {
        printf("%s frequency: %d\n",word,(wordFreq(root,word))->freq);
      }
      else{
        printf("%s not found\n",word );
      }
    }
    else if(strcmp(word,"s") == 0){
      printf("\n" );
      root = r;
      levelOrderAVL(root);
      printf("\n" );
    }
    else if (strcmp(word,"r") == 0) {
      root = r;
      statistics(root);
    }
    root = r;
    word = readWord(cp);
  }
}

void readCommandsBST(node *root, FILE *cp){
  char *word = readWord(cp);
  node *r = root;
  while(word != NULL){
    word = grammar(word);
    if (strcmp(word,"i") == 0) {
      word = readWord(cp);
      word = grammar(word);
      root = insertInBST(root,word);
    }
    else if (strcmp(word,"d") == 0) {
      word = readWord(cp);
      word = grammar(word);
      root = deleteInBST(root,word);
      if (root != r) {
        r = root;
      }
    }
    else if (strcmp(word,"f") == 0) {
      word = readWord(cp);
      word = grammar(word);
      if (wordFreq(root,word) != NULL) {
        printf("%s frequency: %d\n",word,(wordFreq(root,word))->freq );
      }
      else{
        printf("%s not found\n",word );
      }
      root = r;
    }
    else if(strcmp(word,"s") == 0){
      printf("\n" );
      levelOrderBST(root);
      printf("\n" );
    }
    else if (strcmp(word,"r") == 0) {
      statistics(root);
    }
    root = r;
    word = readWord(cp);
  }
}

int main(int argc, char const *argv[]) {
  char const *a = argv[1];
  FILE *fp = fopen(argv[2],"r");
  FILE *cp = fopen(argv[3],"r");
  bst *bst = createBST();
  avl *avl = createAvl();
  node *root = readInput(a,fp);
  if (strcmp(a,"-b") == 0) {
    bst->root = root;
    readCommandsBST(bst->root,cp);
  }
  else if (strcmp(a,"-a") == 0) {
    avl->root = root;
    readCommandsAVL(avl->root,cp);
  }
  fclose(fp);
  fclose(cp);

  return 0;
}
