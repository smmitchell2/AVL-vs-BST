#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "queue.h"

queue *createQueue(){
  queue *q = (queue*) malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

int queueIsEmpty(queue *q){
  if(q->head == NULL){return 1;}
  else{return 0;}
}

void enqueue(queue *q,node *n){
  if(queueIsEmpty(q)){q->head = n; q->tail = n;}
  else{
    q->tail->next = n;
    q->tail = n;
  }
}

node *dequeue(queue *q){
  if(queueIsEmpty(q)){return NULL;}
  node *tmp = q->head;
  q->head = q->head->next;
  if(q->head == NULL){q->tail = NULL;}
  return tmp;
}
