#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


void initiate_queue(queue_t *q){
    q->front = NULL;
    q->end = NULL;
}

void push(queue_t *q, int value){
    node_t *new = (node_t*)malloc(sizeof(node_t));
    new->data = value;
    new->next = NULL;
    if(q->front == NULL){
        q->front = new;
    } else {
        q->end->next = new;
    }
    q->end = new;
}

int pop(queue_t *q){
    if(q->front == NULL){
        return;
    }
    node_t *temp = q->front;
    int removed = temp->data;
    q->front = q->front->next;
    if(q->front == NULL){
        q->end = NULL;
    }
    free(temp);
    return removed;
}

void drop_queue(queue_t *q){
    while(q->front != NULL){
        pop(q);
    }
    free(q);
}