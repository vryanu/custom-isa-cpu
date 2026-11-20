#ifndef BINTOASM_H
#define BINTOASM_H

#include <stdio.h>

/* Create function bintoasm()

Commands in a .txt must be seperated by newline

Proper BIN syntax:
000 ADD   00 REG B
001 SUB   01 REG A
010 MUL   10 MAR
011 DIV   11 ACC
100 MOD
101 AND
110 OR
111 XOR
ART [5 BITS 0] [3 BITS OP]
RAM [2 BITS MOV/SET VAL] [MOV] [LOAD] [STORE] [SET (REQUIRES MOV)] [2 BITS MOV/SET LOC]
LOOP [3 BITS AMOUNT][2 BITS ENABLE] [3 BITS SUBTRACT FROM COUNT] 
PRINT [3 BITS 0] [ENABLE] [0] [ENABLE] [2 BITS SOURCE]*/

//print acc 00010111
void bintoasm(const char *binary_str, FILE *output);

#endif