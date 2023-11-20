//
// Created by pouls on 13/11/2023.
// test from AB 13-11 this is heini
//
#include "stdio.h"
int main() {

    static int pc;
    static int reg[32];

    return 0;
}

void temp (int instr){
    int opcode = instr & 0x7F;
    int rd;
    int imm;
    int funct3;
    switch (opcode) {
        case 0000011: //FMT = I
            printf("1");
            rd = (instr >> 7) & 0x01f;
            int funct = (instr >> 12) & 0x07;
            int rs1 = (instr >> 15) & 0x01f;
            int imm = (instr >> 20);
            switch (funct) {

            }
            break;
            /*case 0001111: fence og fence.i skal ikke bruges
                printf("2");
                break;*/
        case 0010011: //FMT = I
            rd = (instr >> 7) & 0x01f;
            printf("3");
            break;
        case 0010111: //FMT = U
            rd = (instr >> 7) & 0x01f;
            imm = (instr >> 12);
            printf("4");
            break;
        case 0100011: //FMT = S NOTDONE
            funct3 ;
            printf("5");
            break;
        case 0110011: //FMT = R
            printf("6");
            break;
        case 0110111: //FMT = U
            rd = (instr >> 7) & 0x01f;
            imm = (instr >> 12);
            printf("7");
            break;
        case 1100011: //FMT = SB
            printf("8");
            break;
        case 1100111: //FMT = I
            printf("9");
            break;
        case 1101111: //FMT = UJ
            printf("10");
            break;
        case 1110011://FMT = I  det er kun ecall som skal bruges
            printf("11");
            break;
        default:
            printf("Opcode %s not yet implemented", opcode);
    }
}