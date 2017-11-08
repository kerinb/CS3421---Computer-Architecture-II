//
// t2Test.cpp
//
// Copyright (C) 2012 - 2017 jones@scss.tcd.ie
//
// 09/10/17	first version
//

#include "stdafx.h"			// pre-compiled headers
#include <iostream>			// cout
#include <conio.h>			// _getch
#include "fib64.h"			//
#include "t2.h"				//

using namespace std;		// cout

_int64 _g = 4;

//
// fib: C++
//
_int64 fib(_int64 n) {
	_int64 fi, fj, t;
	if (n <= 1)
		return n;
	fi = 0;
	fj = 1;
	while (n > 1) {
		t = fj;
		fj = fi + fj;
		fi = t;
		n--;
	}
	return fj;
}


//
// min: C++
//
_int64 min(_int64 a, _int64 b, _int64 c) {
	_int64 v = a;
	if (b < v)
		v = b;
	if (c < v)
		v = c;
	return v;
}


//
// p: C++
//
_int64 p(_int64 i, _int64 j, _int64 k, _int64 l) {
	_int64 v = min(g, i, j);
	return min(v, k, l);
	// return min(min(g, i, j), k, l);
}

//
// gcd: C++
//
_int64 gcd(_int64 a, _int64 b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

_int64 q(_int64 a, _int64 b, _int64 c, _int64 d, _int64 e) {
	_int64 sum = a + b + c + d + e;
	printf("a = %I64d b = %I64d c = %I64d d = %I64d e = %I64d sum = %I64d\n", a, b, c, d, e, sum);
	return sum;
}

//
// check
//
void check(char *s, _int64 v, _int64 expected) {
	cout << s << " = " << v;
	if (v == expected) {
		cout << " OK";
	}
	else {
		cout << " ERROR: should be " << expected;
	}
	cout << endl;
}


//
// _tmain
//
int _tmain(int argc, _TCHAR* argv[]) {

	min(1, 2, 3);

	//
	// tutorial 2
	//
	check("_g", _g, 4);
	_g++;
	check("_g", _g, 5);
	_g--;
	check("_g", _g, 4);

	check("min(1, 2, 3)", min(1, 2, 3), 1);
	check("min(3, 1, 2)", min(3, 1, 2), 1);
	check("min(2, 3, 1)", min(2, 3, 1), 1);
	check("min(-1, -2, -3)", min(-1, -2, -3), -3);
	check("min(-3, -1, -2)", min(-3, -1, -2), -3);
	check("min(-2, -3, -1)", min(-2, -3, -1), -3);
	check("min(-1, 2, 3)", min(-1, 2, 3), -1);
	check("min(3, -1, 2)", min(3, -1, 2), -1);
	check("min(2, 3, -1)", min(2, 3, -1), -1);

	check("p(0, 1, 2, 3)", p(0, 1, 2, 3), 0);
	check("p(5, 6, 7, 8)", p(5, 6, 7, 8), 4);
	check("p(3, 2, 1, 0)", p(3, 2, 1, 0), 0);
	check("p(8, 7, 6, 5)", p(8, 7, 6, 5), 4);

	check("gcd(14, 21)", gcd(14, 21), 7);
	check("gcd(1406700, 164115)", gcd(1406700, 164115), 23445);

	check("q(1, 2, 3, 4, 5)", q(1, 2, 3, 4, 5), 15);
	check("q(-1, 2, -3, 4, -5)", q(-1, 2, -3, 4, -5), -3);

	//check("qns()", qns(), 0);

	cout << endl;

	//
	// fib: C++
	//
	cout << "fib c++" << endl;
	for (int i = -1; i < 20; i++)
		cout << fib(i) << " ";
	cout << endl;

	//
	// fib: x64 assembly language
	//
	cout << "fibX64" << endl;
	fibX64(10);
	for (int i = -1; i < 20; i++)
		cout << fibX64(i) << " ";
	cout << endl;

	check("minX64(1, 2, 3)", minX64(1, 2, 3), 1);
	check("minX64(3, 1, 2)", minX64(3, 1, 2), 1);
	check("minX64(2, 3, 1)", minX64(2, 3, 1), 1);
	check("minX64(-1, -2, -3)", minX64(-1, -2, -3), -3);
	check("minX64(-3, -1, -2)", minX64(-3, -1, -2), -3);
	check("minX64(-2, -3, -1)", minX64(-2, -3, -1), -3);
	check("minX64(-1, 2, 3)", minX64(-1, 2, 3), -1);
	check("minX64(3, -1, 2)", minX64(3, -1, 2), -1);
	check("minX64(2, 3, -1)", minX64(2, 3, -1), -1);

	check("pX64(0, 1, 2, 3)", pX64(0, 1, 2, 3), 0);
	check("pX64(5, 6, 7, 8)", pX64(5, 6, 7, 8), 4);
	check("pX64(3, 2, 1, 0)", pX64(3, 2, 1, 0), 0);
	check("pX64(8, 7, 6, 5)", pX64(8, 7, 6, 5), 4);

	check("gcdX64(14, 21)", gcdX64(14, 21), 7);
	check("gcdX64(1406700, 164115)", gcdX64(1406700, 164115), 23445);

	check("qX64(1, 2, 3, 4, 5)", qX64(1, 2, 3, 4, 5), 15);
	check("qX64(-1, 2, -3, 4, -5)", qX64(-1, 2, -3, 4, -5), -3);

	_getch();

	return 0;
}

// eof