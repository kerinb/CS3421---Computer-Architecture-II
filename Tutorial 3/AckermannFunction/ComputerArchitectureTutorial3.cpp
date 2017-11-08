#include "stdafx.h"
#include "targetver.h"
#include "time.h"
#include <assert.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

#define NUMBER_OF_RUNS 10000

int procedureCalls = 0;
int registerDepth = 0;
int maxRegisterDepth = 0;
int numberOfRegisterWindowsUsed = 1;
int numberOfOverflows = 0;
int numberOfUnderflows = 0;

void initialiseGlobals() {
	numberOfRegisterWindowsUsed = 1;
	registerDepth = procedureCalls = numberOfUnderflows = maxRegisterDepth = numberOfOverflows = 0;
}

int ackermann(int x, int y) {
	if (x == 0) {
		return y + 1;
	}
	else if (y == 0) {
		return ackermann(x-1, 1);
	}
	else {
		return ackermann(x - 1, ackermann(x, y-1));
	}
}

int ackermannTest(int x, int y, int numberOfWindows) {
	int returnValues;
	procedureCalls++;
	registerDepth++;
	if (registerDepth > maxRegisterDepth)
		maxRegisterDepth = registerDepth;
	assert((numberOfRegisterWindowsUsed > 0)&&(numberOfRegisterWindowsUsed <= numberOfWindows-1));

	numberOfRegisterWindowsUsed == (numberOfWindows - 1) ? numberOfOverflows++: numberOfRegisterWindowsUsed++;
	
	if (x == 0)
		returnValues = y + 1;
	else if (y == 0)
		returnValues = ackermannTest(x-1, 1, numberOfWindows);
	else
		returnValues = ackermannTest(x - 1, ackermannTest(x, y - 1, numberOfWindows), numberOfWindows);
	
	registerDepth--;

	assert((numberOfRegisterWindowsUsed > 0) && (numberOfRegisterWindowsUsed <= numberOfWindows-1));

	numberOfRegisterWindowsUsed > 1 ? numberOfRegisterWindowsUsed-- : numberOfUnderflows++;

	return returnValues;
}

void printAckermannTest(int a, int b, int c) {
	int v = ackermannTest(a, b, c);
	cout << " *** Ackermann(" << a << ", " << b << ") using " << c << " registers sets *** " << endl;
	cout << " Number of Procedure Calls made = " << procedureCalls << endl;
	cout << " Maximum Register Window Depth = " << maxRegisterDepth << endl;
	cout << " Number of Register Window Overflows = " << numberOfOverflows << endl;
	cout << " Number of Register Window Underflows = " << numberOfUnderflows << endl << endl;;
}

void getExecutionTime() {
	cout << " *** Beginning 10'000 runs for each max window size *** " << endl << endl;
	int timeElapsed = clock();
	
	int v = 0;
	for (int i = 0; i < NUMBER_OF_RUNS; i++) {
		v += ackermann(3, 6);
	}
	timeElapsed = clock() - timeElapsed;
	cout << " *** Ackermann(3, 6) *** " << endl;
	cout << " Average Execution Time Over 10'000 Runs = " << fixed << setprecision(2) << (double)timeElapsed*1000.00 / CLOCKS_PER_SEC/NUMBER_OF_RUNS << " ms" << endl;

}

int _tmain(int argc, _TCHAR* argv[]) {

	initialiseGlobals();
	printAckermannTest(3, 6, 6);
	
	initialiseGlobals();
	printAckermannTest(3, 6, 8);

	initialiseGlobals();
	printAckermannTest(3, 6, 16);

	getExecutionTime();

	getchar();

	return 0;
}