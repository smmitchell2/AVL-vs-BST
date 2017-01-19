typedef struct Queue{
  node *head;
  node *tail;
}queue;

queue *createQueue();
int isEmpty(queue *q);
void enqueue(queue *q,node *n);
node *dequeue(queue *q);
