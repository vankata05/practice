#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct queue {
    // int queue[MAX_QUEUE_SIZE];
    int* queue;
    int currSize;
    int head;
    int tail;
} queue;

void initQueue(queue *queue) {
    queue->queue = malloc(sizeof(int));
    queue->currSize = 0;
    queue->head = 0;
    queue->tail = 0;
}

int isEmpty(queue *queue) {
    return (queue->head == queue->tail);
}

/* twa e pri statichno zadelqne
int isFull(queue *queue) {
    return (queue->currSize == MAX_QUEUE_SIZE);
}
*/

void enqueue(queue *queue, int e) {
    //if (isFull(queue)) printf("Queue is full!");
    if(queue->currSize != 0)
        queue->queue = (int*) realloc(queue->queue, (queue->currSize+1) * sizeof(int));

    queue->queue[queue->tail] = e;
    queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
    queue->currSize = queue->currSize + 1;
}

int dequeue(queue *queue) {
    if (isEmpty(queue)) printf("Queue is empty!");

    int toDequeue = queue->head;
    queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
    queue->currSize = queue->currSize - 1;

    return toDequeue;
}

void printQueue(queue queue){
    for(int i = queue.head; i < queue.tail; i++){
        printf("%d", queue.queue[i]);
    }
}

int main() {
    queue q;
    initQueue(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    dequeue(&q);
    printQueue(q);

    return 0;
}