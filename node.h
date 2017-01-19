typedef struct Node{
  char *word;
  int freq;
  int height;
  int level;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
  struct Node *next;
}node;

node *createNode();
