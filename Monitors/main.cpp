#include <iostream>
#include "mymonitor.h"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 5) {
		cout << "Syntax: main [num_of_A1] [num_of_A2] [num_of_B1] [num_of_B2]" << endl;
		return 1;
	}

	int numofA1 = atoi(argv[1]), numofA2 = atoi(argv[2]),
		numofB1 = atoi(argv[3]), numofB2 = atoi(argv[4]);

	if(numofA1 <= 0 || numofA2 <= 0 || numofB1 <= 0 || numofB2 <= 0) {
		cout << "Error: expected positive integers." << endl;
		return 1;
	}

	pthread_t threads[numofA1+numofA2+numofB1+numofB2];
	MyMonitor monitorek;

	for(int i = 0; i < numofA1; ++i)
		pthread_create(&threads[i], NULL, &MyMonitor::procA1_helper, &monitorek);
	for(int i = numofA1; i < numofA1+numofA2; ++i)
		pthread_create(&threads[i], NULL, &MyMonitor::procA2_helper, &monitorek);
	for(int i = numofA1+numofA2; i < numofA1+numofA2+numofB1; ++i)
		pthread_create(&threads[i], NULL, &MyMonitor::procB1_helper, &monitorek);
	for(int i = numofA1+numofA2+numofB1; i < numofA1+numofA2+numofB1+numofB2; ++i)
		pthread_create(&threads[i], NULL, &MyMonitor::procB2_helper, &monitorek);

	for(int i = 0; i < numofA1+numofA2+numofB1+numofB2; ++i)
		pthread_join(threads[i], NULL);

	return 0;  
}
