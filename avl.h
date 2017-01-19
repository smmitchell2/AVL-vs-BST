typedef struct AVL{
  node *root;
}avl;

avl *createAvl();
int max(int lch,int rch);
int height(node *n);
node *rotateRight(node *nod);
node *rotateLeft(node *nod);
int getBalance(node *n);
node *minValueNode(node *node);
node *insertInAvl(node *root,char *word);
node *deleteInAvl(node *root,char *word);
