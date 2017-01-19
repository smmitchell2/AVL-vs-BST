typedef struct BST{
  node *root;
}bst;

bst *createBST();
node *insertInBST(node *root,char *word);
node *deleteInBST(node *root,char *word);
void inorder(node *root);
