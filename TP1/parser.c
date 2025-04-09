#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

void print_binary(uint32_t value) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

//pra ler e mandar pro encoder que está na pasta homônima (isso signfica "de mesmo nome, Pedro")

void parse_file(char *filename, Instrucao *programa, int *pc) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *ptr = line;
        while (isspace(*ptr)) ptr++;
        if (*ptr == '\0' || *ptr == '#') continue;

        Instrucao instr = {0};
        char *token = strtok(ptr, " \t,\n");
        if (!token) continue;
        strcpy(instr.opcode, token);

        if (strcmp(instr.opcode, "add") == 0 || strcmp(instr.opcode, "sub") == 0 ||
            strcmp(instr.opcode, "and") == 0 || strcmp(instr.opcode, "or") == 0 ||
            strcmp(instr.opcode, "sll") == 0 || strcmp(instr.opcode, "srl") == 0) {
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rd);
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rs1);
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rs2);
        } else if (strcmp(instr.opcode, "ori") == 0 || strcmp(instr.opcode, "andi") == 0 ||
                   strcmp(instr.opcode, "addi") == 0 || strcmp(instr.opcode, "lb") == 0) {
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rd);
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rs1);
            token = strtok(NULL, " \t,\n"); instr.imm = atoi(token);
        } else if (strcmp(instr.opcode, "sb") == 0) {
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rs2);
            token = strtok(NULL, " \t,\n"); sscanf(token, "%d(x%d)", &instr.imm, &instr.rs1);
        } else if (strcmp(instr.opcode, "beq") == 0) {
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rs1);
            token = strtok(NULL, " \t,\n"); sscanf(token, "x%d", &instr.rs2);
            token = strtok(NULL, " \t,\n"); instr.imm = atoi(token);
        }

        programa[*pc / 4] = instr;
        *pc += 4;
    }

    fclose(file);
}
