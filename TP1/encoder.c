#include <string.h>
#include "encoder.h"

uint32_t codar_instrucao(Instrucao instr) {
    uint32_t codado = 0;

    if (strcmp(instr.opcode, "add") == 0) 
    {
        codado = (0x00 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x0 << 12) | (instr.rd << 7) | 0x33;
    }
    else if (strcmp(instr.opcode, "sub") == 0) 
    {
        codado = (0x20 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x0 << 12) | (instr.rd << 7) | 0x33;
    }
    else if (strcmp(instr.opcode, "and") == 0) 
    {
        codado = (0x00 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x7 << 12) | (instr.rd << 7) | 0x33;
    }
    else if (strcmp(instr.opcode, "or") == 0) 
    {
        codado = (0x00 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x6 << 12) | (instr.rd << 7) | 0x33;
    }
    else if (strcmp(instr.opcode, "sll") == 0) 
    {
        codado = (0x00 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x1 << 12) | (instr.rd << 7) | 0x33;
    }
    else if (strcmp(instr.opcode, "srl") == 0) 
    {
        codado = (0x00 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x5 << 12) | (instr.rd << 7) | 0x33;
    }
    else if (strcmp(instr.opcode, "ori") == 0) 
    {
        codado = ((instr.imm & 0xFFF) << 20) | (instr.rs1 << 15) |
                  (0x6 << 12) | (instr.rd << 7) | 0x13;
    }
    else if (strcmp(instr.opcode, "addi") == 0) 
    {
        codado = ((instr.imm & 0xFFF) << 20) | (instr.rs1 << 15) |
                  (0x0 << 12) | (instr.rd << 7) | 0x13;
    }
    else if (strcmp(instr.opcode, "andi") == 0) 
    {
        codado = ((instr.imm & 0xFFF) << 20) | (instr.rs1 << 15) |
                  (0x7 << 12) | (instr.rd << 7) | 0x13;
    }  
    else if (strcmp(instr.opcode, "lb") == 0) 
    {
        codado = ((instr.imm & 0xFFF) << 20) | (instr.rs1 << 15) |
                  (0x0 << 12) | (instr.rd << 7) | 0x03;
    }    
    else if (strcmp(instr.opcode, "sb") == 0) 
    {
        uint32_t imm11_5 = (instr.imm >> 5) & 0x7F;
        uint32_t imm4_0 = instr.imm & 0x1F;
        codado = (imm11_5 << 25) | (instr.rs2 << 20) | (instr.rs1 << 15) |
                  (0x0 << 12) | (imm4_0 << 7) | 0x23;
    }
    else if (strcmp(instr.opcode, "beq") == 0) 
    {
        uint32_t imm = instr.imm;
        uint32_t imm12 = (imm >> 12) & 0x1;
        uint32_t imm10_5 = (imm >> 5) & 0x3F;
        uint32_t imm4_1 = (imm >> 1) & 0xF;
        uint32_t imm11 = (imm >> 11) & 0x1;
        codado = (imm12 << 31) | (imm10_5 << 25) | (instr.rs2 << 20) |
                  (instr.rs1 << 15) | (0x0 << 12) | (imm4_1 << 8) | (imm11 << 7) | 0x63;
    }

    return codado;
}