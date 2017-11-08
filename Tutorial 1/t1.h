#pragma once

//
// t1.h
//
// Copyright (C) 2012 - 2017 jones@scss.tcd.ie
//
// example of mixing C++ and IA32 assembly language
//

//
// NB: "extern C" to avoid procedure name mangling by compiler
//

extern "C" int _cdecl g;   // _cdecl calling convention
extern "C" int _cdecl min_IA32a(int, int, int);   // _cdecl calling convention
extern "C" int _cdecl p_IA32a(int, int, int, int);   // _cdecl calling convention
extern "C" int _cdecl gcd_IA32a(int, int);   // _cdecl calling convention

// eof