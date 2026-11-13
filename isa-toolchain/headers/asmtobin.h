#ifndef ASMTOBIN_H
#define ASMTOBIN_H

#include <stdio.h>

/* Create function asmtobin()

Commands in a .txt must be seperated by newline

Proper ASM syntax:
SET REGA 2
SET REGB 3
ADD
SET MAR 1
STORE
LOOP 2 5 */

void asmtobin(const char *asm_str, FILE *output, const char type);

#endif
