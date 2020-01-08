#ifndef FIFO_H
#define FIFO_H

typedef struct Node {
	struct Node* next;
	int val;
} Node;

Node* initNode(int val);

typedef struct FIFO {
	Node* buffer;
	int size;
} FIFO;

FIFO* initFIFO();

bool isEmpty(FIFO* q);
int size(FIFO* q);
void put(FIFO* q, int val);
int get(FIFO* q);
void del(FIFO* q);
void printQueue(FIFO* q);

#endif /* FIFO_H */