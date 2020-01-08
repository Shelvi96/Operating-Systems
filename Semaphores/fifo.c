#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "fifo.h"

Node* initNode(int val) {
	Node* ret = (Node*)malloc(sizeof(Node));
	ret->val = val;
	ret->next = ret;
	return ret;
}

FIFO* initFIFO() {
	FIFO* ret = (FIFO*)malloc(sizeof(FIFO));
	ret->buffer = initNode(-1);
	ret->size = 0;
	return ret;
}

bool isEmpty(FIFO* q) {
	return q->size == 0 ? true : false;
}

int size(FIFO* q) {
	return q->size;
}

void put(FIFO* q, int val) {
	Node* n = initNode(val);
	n->next = q->buffer->next;
	q->buffer->next = n;
	q->size++;
}

int get(FIFO* q) {
	if(isEmpty(q)) 
		return -1;
	int ret = q->buffer->next->val;
	Node* old = q->buffer->next;
	q->buffer->next = q->buffer->next->next;
	free(old);
	q->size--;
	return ret;
}

void del(FIFO* q) {
	Node* n = q->buffer-> next;
	while(n != q->buffer) {
		Node* prev = n;
		n = n->next;
		free(prev);
	}
	free(q->buffer);
	free(q);
}

void printQueue(FIFO* q) {
	Node* n = q->buffer->next;
	while(n != q->buffer) {
		printf("%d, ", n->val);
		n = n->next;
	}
	printf("\n");
}
/*
int main() {
	FIFO* q;
	q = initFIFO();
	put(q, 12);
	assert(size(q) == 1);
	int ret = get(q);
	assert(ret == 12);
	ret = get(q);
	assert(ret == -1);
	assert(size(q) == 0);
	del(q);

	return 0;
}
*/