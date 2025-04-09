#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#define MAX_INSTRUCOES 1000

typedef struct {
    char opcode[10];
    int rd;
    int rs1;
    int rs2;
    int imm;
    char label[50];
} Instrucao;

void parse_file(char *filename, Instrucao *programa, int *pc);

void print_binary(uint32_t value);


#endif