#include <iostream>
#include "mymonitor.h"

std::queue<int> copy_queue(const std::queue<int> &Q) {
	std::queue<int> Q2 = Q;
	return Q2;
}

void print_queue(const std::queue<int> &Q) {
	std::queue<int> q = copy_queue(Q);
    while(!q.empty()) {
    	std::cout << q.front() << " ";
    	q.pop();
    }
    std::cout << std::endl;
}

MyMonitor::MyMonitor() {
  	numEven = 0;
  	numOdd = 1;
}

void* MyMonitor::procA1() {
  	while(true) {
	    enter();
	    
	    if(bufEven.size() >= 10)
	    	wait(A1);

	    bufEven.push(numEven);
	    printf("Zapisano %d\n", numEven);
	    printf("rozmiar bufEven: %ld, rozmiar bufOdd %ld\n", bufEven.size(), bufOdd.size());
	    std::cout << "bufEven: ";
	    print_queue(bufEven);
	    std::cout << "bufOdd ";
	    print_queue(bufOdd);
	    std::cout << std::endl;
	    numEven += 2;
	    numEven = numEven%100;

	    if(bufEven.size() >= 3)
	    	signal(B1);

	    if(bufEven.size() > bufOdd.size())
	    	signal(A2);
	    
	    leave();
  	}
}

void* MyMonitor::procA2() {
	while(true) {
		enter();

		if(bufEven.size() <= bufOdd.size())
			wait(A2);

		bufOdd.push(numOdd);
		printf("Zapisano %d\n", numOdd);
		printf("rozmiar bufEven: %ld, rozmiar bufOdd %ld\n", bufEven.size(), bufOdd.size());
		std::cout << "bufEven: ";
	    print_queue(bufEven);
	    std::cout << "bufOdd ";
	    print_queue(bufOdd);
	    std::cout << std::endl;
		numOdd += 2;
		numOdd = numOdd%100;

		if(bufOdd.size() >= 7)
			signal(B2);

		leave();
	}
}

void* MyMonitor::procB1() {
	while(true) {
		enter();

		if(bufEven.size() < 3)
			wait(B1);

		printf("Odczytano %d\n", bufEven.front());
		bufEven.pop();
		printf("rozmiar bufEven: %ld, rozmiar bufOdd %ld\n", bufEven.size(), bufOdd.size());
		std::cout << "bufEven: ";
	    print_queue(bufEven);
	    std::cout << "bufOdd ";
	    print_queue(bufOdd);
	    std::cout << std::endl;
		if(bufEven.size() < 10)
			signal(A1);

		if(bufEven.size() > bufOdd.size())
    		signal(A2);

		leave();
	}
}
	
void* MyMonitor::procB2() {
	while(true) {
		enter();

		if(bufOdd.size() < 7)
			wait(B2);

		printf("Odczytano %d\n", bufOdd.front());
		bufOdd.pop();
		printf("rozmiar bufEven: %ld, rozmiar bufOdd %ld\n", bufEven.size(), bufOdd.size());
		std::cout << "bufEven: ";
	    print_queue(bufEven);
	    std::cout << "bufOdd ";
	    print_queue(bufOdd);
	    std::cout << std::endl;
		if(bufEven.size() > bufOdd.size())
    		signal(A2);

		leave();
	}
}
