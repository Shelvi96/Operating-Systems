#ifndef MYMONITOR_H
#define MYMONITOR_H
#include <bits/stdc++.h>
#include "monitor.h"

class MyMonitor: Monitor {
public:
	MyMonitor();
  	void* procA1(void);
  	static void* procA1_helper(void* context) {
  		return ((MyMonitor *)context)->procA1();
  	}
  	void* procB1(void);
  	static void* procB1_helper(void* context) {
  		return ((MyMonitor *)context)->procB1();
  	}
  	void* procA2(void);
  	static void* procA2_helper(void* context) {
  		return ((MyMonitor *)context)->procA2();
  	}
  	void* procB2(void);
  	static void* procB2_helper(void* context) {
  		return ((MyMonitor *)context)->procB2();
  	}
  
private:
  	std::queue<int>bufEven;
  	std::queue<int>bufOdd;
  
  	int numEven, numOdd;

  	Condition A1, B1, A2, B2;
};

#endif /* MYMONITOR_H */