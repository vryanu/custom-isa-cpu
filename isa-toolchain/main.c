#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/bintoasm.h"
#include "headers/asmtobin.h"
/*
Usage ./translator type, input.txt, output.txt

Type 'bta' bin to asm
Type 'atb' asm to bin
Type 'ath' asm to hex

Commands in a .txt must be seperated by newline
Proper syntax found in headers
*/
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("./main <type> <input.txt> <output.txt>\n");
        return 1;
    }
    char *type = argv[1];

    FILE *input = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");

    char line[256];

    while (fgets(line, sizeof(line), input) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';

        char *comment = strchr(line, '*');
        if (comment != NULL)
            *comment = '\0';

        if (line[0] == '\0')
            continue;

        if (strcmp(type, "bta") == 0)
            bintoasm(line, output);
        else if (strcmp(type, "atb") == 0)
            asmtobin(line, output, 'b');
        else if (strcmp(type, "ath") == 0)
            asmtobin(line, output, 'h');
        else
        {
            fclose(input);
            fclose(output);
            return 1;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}