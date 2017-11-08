//
// t1.cpp
//
// Copyright (C) 2017 jones@scss.tcd.ie
//
// 02/10/17	first version
//

#include <iostream>         // cout
#include "conio.h"          // _getch
#include "stdafx.h"
#include "t1.h"             //

using namespace std;        // cout

int g = 4;

int min(int a, int b, int c);
int min_IA32(int a, int b, int c);
int p(int i, int j, int k, int l);
int p_IA32(int i, int j, int k, int l);
int gcd(int a, int b);
int gcd_IA32(int a, int b);

//
// check
//
void check(char *s, int v, int expected) {
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
int _tmain(int argc) {

	//
	// t1
	//
	check("g", g, 4);

	check("min(1, 2, 3)", min(1, 2, 3), 1);
	check("min(3, 1, 2)", min(3, 1, 2), 1);
	check("min(2, 3, 1)", min(2, 3, 1), 1);
	check("min(-1, -2, -3)", min(-1, -2, -3), -3);
	check("min(-3, -1, -2)", min(-3, -1, -2), -3);
	check("min(-2, -3, -1)", min(-2, -3, -1), -3);
	check("min(-1, 2, 3)", min(-1, 2, 3), -1);
	check("min(3, -1, 2)", min(3, -1, 2), -1);
	check("min(2, 3, -1)", min(2, 3, -1), -1);

	check("p(1, 2, 3, 4)", p(1, 2, 3, 4), 1);
	check("p(5, 6, 7, 8)", p(5, 6, 7, 8), 4);

	check("gcd(14, 21)", gcd(14, 21), 7);
	check("gcd(1406700, 164115)", gcd(1406700, 164115), 23445);

	cout << endl;

	check("min_IA32(1, 2, 3)", min_IA32(1, 2, 3), 1);
	check("min_IA32(3, 1, 2)", min_IA32(3, 1, 2), 1);
	check("min_IA32(2, 3, 1)", min_IA32(2, 3, 1), 1);
	check("min_IA32(-1, -2, -3)", min_IA32(-1, -2, -3), -3);
	check("min_IA32(-3, -1, -2)", min_IA32(-3, -1, -2), -3);
	check("min_IA32(-2, -3, -1)", min_IA32(-2, -3, -1), -3);
	check("min_IA32(-1, 2, 3)", min_IA32(-1, 2, 3), -1);
	check("min_IA32(3, -1, 2)", min_IA32(3, -1, 2), -1);
	check("min_IA32(2, 3, -1)", min_IA32(2, 3, -1), -1);

	check("p_IA32(1, 2, 3, 4)", p_IA32(1, 2, 3, 4), 1);
	check("p_IA32(5, 6, 7, 8)", p_IA32(5, 6, 7, 8), 4);

	check("gcd_IA32(14, 21)", gcd_IA32(14, 21), 7);
	check("gcd_IA32(1406700, 164115)", gcd_IA32(1406700, 164115), 23445);

	cout << endl;

//c:\Users\kerinb\documents\visual studio 2017\Projects\compArchTut1\compArchTut1\t1.cpp

//	check("min_IA32a(1, 2, 3)", min_IA32a(1, 2, 3), 1);
//	check("min_IA32a(3, 1, 2)", min_IA32a(3, 1, 2), 1);
//	check("min_IA32a(2, 3, 1)", min_IA32a(2, 3, 1), 1);
//	check("min_IA32a(-1, -2, -3)", min_IA32a(-1, -2, -3), -3);
//	check("min_IA32a(-3, -1, -2)", min_IA32a(-3, -1, -2), -3);
//	check("min_IA32a(-2, -3, -1)", min_IA32a(-2, -3, -1), -3);/
	//check("min_IA32a(-1, 2, 3)", min_IA32a(-1, 2, 3), -1);
	//check("min_IA32a(3, -1, 2)", min_IA32a(3, -1, 2), -1);
	//check("min_IA32a(2, 3, -1)", min_IA32a(2, 3, -1), -1);

//	check("p_IA32a(1, 2, 3, 4)", p_IA32a(1, 2, 3, 4), 1);
//	check("p_IA32a(5, 6, 7, 8)", p_IA32a(5, 6, 7, 8), 4);

	//check("gcd_IA32a(14, 21)", gcd_IA32a(14, 21), 7);
	//check("gcd_IA32a(1406700, 164115)", gcd_IA32a(1406700, 164115), 23445);

	cout << endl;

	_getch();

	return 0;
}

//
// min: C++
//
int min(int a, int b, int c) {
	int v = a;
	if (b < v)
		v = b;
	if (c < v)
		v = c;
	return v;
}

//
// min: C/C++ and inline IA32 assembly language
//
int min_IA32(int a, int b, int c) {
	_asm {        mov eax, a          }   // eax = a
	_asm {        mov ebx, b          }   // ebx = b
	_asm {        cmp ebx, eax        }   // if(eax > ebx)
	_asm {        jg  notIfB          }   // jmp to notIfB
	_asm {        mov eax, ebx        }   // eax = ebx
	_asm {notIfB: mov ebx, c          }   // mov c into eax
	_asm {        cmp ebx, eax        }   // if(eax > v)
	_asm {        jg  notIfC          }   // jmp to ifNotC
	_asm {        mov eax, ebx        }   // mov c into eax
	_asm {notIfC:		              }   // end
}

//
// p: C++
//
int p(int i, int j, int k, int l) {
	int v = min(g, i, j);
	return min(v, k, l);
	// return min(min(g, i, j), k, l);
}

//
// p:  C/C++ and inline IA32 assembly language
//
int p_IA32(int i, int j, int k, int l) {
	_asm {       mov  eax, j             }   // eax = j
	_asm {       push eax                }   // push eax to the stack
	_asm {       mov  ebx, i             }   // ebx = i
	_asm {       push ebx                }   // push ebx to the stack
	_asm {       mov  ecx, g             }   // ecx = g
	_asm {       push ecx                }   // push ecx to the stack
	_asm {       call min_IA32           }   // mov a into eax
	_asm {		 add esp, 12			 }
	_asm {       mov  ebx, l             }   // ebx = l
	_asm {       push ebx                }   // push ebx to the stack
	_asm {       mov  ecx, k             }   // mov k into ecx
	_asm {       push ecx                }   // push ecx to the stack
	_asm {       mov  edx, eax           }   // mov eax into edx
	_asm {       push edx                }   // push edx to the stack
	_asm {       call min_IA32	         }   // mov a into eax
	_asm {		 add esp, 12			 }
}

//
// gcd: C++
//
int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

int gcd_IA32(int a, int b) {
	_asm {       mov  eax, b           }   // mov b into eax
	_asm {       cmp  eax, 0           }   // if(b != 0)
	_asm {       jne  notE             }   // jmp to notE
	_asm {       mov  eax, a           }   // mov a into eax
	_asm {       jmp  END			   }   // jmp to end
	_asm {notE:  mov  eax, a           }   // mov a into eax
	_asm {       xor  edx, edx         }   // clear destination
	_asm {       mov  ebx, b           }   // 
	_asm {       cdq				   }   // 
	_asm {       div ebx               }   // eax = eax/a%b
	_asm {       mov  eax, edx         }   
	_asm {       push eax              }   // 
	_asm {       push ebx              }   // 
	_asm {       call gcd_IA32         }   // call gcd(b, a%b)
	_asm {		 add esp, 8 		   }
	_asm {END:						   }   // end 
}
