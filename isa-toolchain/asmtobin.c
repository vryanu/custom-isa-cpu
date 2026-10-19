#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "headers/asmtobin.h"

#define EDIT_BIN(b, n) bin[b] = n 

#define MOV_BIT   2
#define LOAD_BIT  3
#define STORE_BIT 4
#define SET_BIT   5

char bin[9];

static bool findArgs(const char *asm_str, const char *op);
static void findCommand(const char *asm_str, char op[6]);
static char *ntob(int num);

static inline void op_add(){ EDIT_BIN(6, '0'), EDIT_BIN(7, '0'), EDIT_BIN(8, '0'); }
static inline void op_sub(){ EDIT_BIN(8, '1'); }
static inline void op_mul(){ EDIT_BIN(7, '1'); }
static inline void op_div(){ EDIT_BIN(8, '1'), EDIT_BIN(7, '1'); }
static inline void op_mod(){ EDIT_BIN(6, '1'); }
static inline void op_and(){ EDIT_BIN(5, '1'), EDIT_BIN(7, '1'); }
static inline void op_or(){ EDIT_BIN(6, '1'), EDIT_BIN(7, '1'); }
static inline void op_xor(){ EDIT_BIN(6, '1'), EDIT_BIN(7, '1'), EDIT_BIN(8, '1'); }
static inline void op_load(){ EDIT_BIN(LOAD_BIT, '1'); }
static inline void op_store(){ EDIT_BIN(STORE_BIT, '1'); }
static inline void op_mov(){ EDIT_BIN(MOV_BIT, '1'); }
static inline void op_set(){ op_mov(); EDIT_BIN(SET_BIT, '1'); }
static inline void op_loop(){ op_load(); op_store(); }

static inline void regb(char pos){if (pos == 'u') { EDIT_BIN(0, '0'); EDIT_BIN(1, '0'); } else { EDIT_BIN(6, '0'); EDIT_BIN(7, '0'); }}
static inline void rega(char pos){if (pos == 'u') { EDIT_BIN(0, '0'); EDIT_BIN(1, '1'); } else { EDIT_BIN(6, '0'); EDIT_BIN(7, '1'); }}
static inline void mar(char pos){if (pos == 'u') { EDIT_BIN(0, '1'); EDIT_BIN(1, '1'); } else { EDIT_BIN(6, '1'); EDIT_BIN(7, '0'); }}
static inline void acc(char pos){if (pos == 'u') { EDIT_BIN(0, '1'); EDIT_BIN(1, '1'); } else { EDIT_BIN(6, '1'); EDIT_BIN(7, '1'); }}

void asmtobin(const char *asm_str, FILE *output, const char type)
{
    memset(bin, '0', 8);
    bin[8] = '\0';

    char op[6] = {0};
    findCommand(asm_str, op);

    if (op[0] == '\0')
    {
        fprintf(stderr, "Unknown command\n");
        return;
    }

    if (!findArgs(asm_str, op))
    {
        fprintf(stderr, "Invalid Argument %s\n", op);
        return;
    }

    if (type == 'b')
        fprintf(output, "%s\n", bin);
    else if (type == 'h')
        fprintf(output, "%lX\n", strtol(bin, NULL, 2));
}

static void findCommand(const char *asm_str, char op[6])
{
    if (sscanf(asm_str, "%5s", op) != 1)
    {
        op[0] = '\0';
        return;
    }

    if (strcmp(op, "ADD") == 0) op_add();
    else if (strcmp(op, "SUB") == 0) op_sub();
    else if (strcmp(op, "MUL") == 0) op_mul();
    else if (strcmp(op, "DIV") == 0) op_div();
    else if (strcmp(op, "MOD") == 0) op_mod();
    else if (strcmp(op, "AND") == 0) op_and();
    else if (strcmp(op, "OR") == 0) op_or();
    else if (strcmp(op, "XOR") == 0) op_xor();
    else if (strcmp(op, "MOV") == 0) op_mov();
    else if (strcmp(op, "LOAD") == 0) op_load();
    else if (strcmp(op, "LOOP") == 0) op_loop();
    else if (strcmp(op, "STORE") == 0) op_store();
    else if (strcmp(op, "SET") == 0) op_set();
    else if (strcmp(op, "END") == 0) bin[0] = '1';
    else op[0] = '\0';
}

static bool findArgs(const char *asm_str, const char *op)
{
    if (strcmp(op, "MOV") != 0 && strcmp(op, "SET") != 0 && strcmp(op, "LOOP") !=0)
        return true;

    char args[64];
    snprintf(args, sizeof(args), "%s", asm_str);

    strtok(args, " \t\r\n");
    char *val = strtok(NULL, " \t\r\n");
    char *loc = strtok(NULL, " \t\r\n");

    if (strcmp(op, "LOOP") == 0)
    {
        if (val == NULL || loc == NULL)
            return false;

        char *end_c, *end_s;
        long cloop = strtol(val, &end_c, 10);
        long sloop = strtol(loc, &end_s, 10);

        if (*end_c != '\0' || *end_s != '\0')
            return false;

        if (cloop < 0 || cloop > 7 || sloop < 0 || sloop > 6)
            return false;

        int cl = (int)cloop, sl = (int)sloop + 1;

        char *bin_c = ntob(cl);
        char *bin_s = ntob(sl);
        if (bin_c == NULL || bin_s == NULL)
        {
            free(bin_c);
            free(bin_s);
            return false;
        }

        bin[0] = bin_c[sizeof(int) * 8 - 3];
        bin[1] = bin_c[sizeof(int) * 8 - 2];
        bin[2] = bin_c[sizeof(int) * 8 - 1];

        bin[5] = bin_s[sizeof(int) * 8 - 3];
        bin[6] = bin_s[sizeof(int) * 8 - 2];
        bin[7] = bin_s[sizeof(int) * 8 - 1];

        free(bin_c);
        free(bin_s);

        return true;
    }

    if (strcmp(op, "SET") == 0)
    {

        if (strcmp(val, "REGA") == 0) rega('d');
        else if (strcmp(val, "REGB") == 0) regb('d');
        else if (strcmp(val, "MAR") == 0) mar('d');
        else if (strcmp(val, "ACC") == 0) acc('d');

        bin[0] = ((loc[0] - '0') & 2) ? '1' : '0';
        bin[1] = ((loc[0] - '0') & 1) ? '1' : '0';
        return true;
    }
    if (strcmp(op, "LOOP") != 0)
    {
        if (strcmp(val, "REGA") == 0) rega('u');
        else if (strcmp(val, "REGB") == 0) regb('u');
        else if (strcmp(val, "MAR") == 0) mar('u');
        else if (strcmp(val, "ACC") == 0) acc('u');

        if (strcmp(loc, "REGA") == 0) rega('d');
        else if (strcmp(loc, "REGB") == 0) regb('d');
        else if (strcmp(loc, "MAR") == 0) mar('d');
        else if (strcmp(loc, "ACC") == 0) acc('d');
    }
    return true;
}

char *ntob(int n) 
{
    int bits = sizeof(n) * 8;
    
    char *str = (char*)malloc(bits + 1);
    if (str == NULL)
        return NULL;

    str[bits] = '\0';
    for (int i = bits - 1; i >= 0; i--) {
        str[i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }

    return str;
}
