#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "encoder.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo.asm>\n", argv[0]);
        return 1;
    }

    Instrucao programa[MAX_INSTRUCOES];
    int pc = 0;
    parse_file(argv[1], programa, &pc);

    for (int i = 0; i < pc / 4; i++) {
        uint32_t codado = codar_instrucao(programa[i]);
        print_binary(codado);
    }

    return 0;
}