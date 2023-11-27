//
// Created by pouls on 13/11/2023.
// test from AB 13-11 this is heini
//
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__

#include "stdint-gcc.h"
#elif _WIN32

#include <stdint.h>
#endif

#define testfile "test/task2/branchmany.bin"


// static program test
static int progr[] = {
        // As minimal RISC-V assembler example
        0x00200093, // addi x1 x0 2
        0x00300113, // addi x2 x0 3
        0x002081b3, // add x3 x1 x2
};

// in
int temp (int instr, uint32_t reg[32], uint32_t *memory);
void readBinFile(uint32_t *memory);


//GLOBAL VAL

int pc;
/*

*/
int main() {
    //size_t size_in_bytes = 1024 * 1024;

    //memory = malloc(size_in_bytes);
    uint32_t *memory = malloc(0xFFFFF * sizeof(uint32_t));
    uint32_t reg[32] ={0};

    //temp(0000011, reg);

    readBinFile(memory);

    printf("Start of RISC-V Simiulator\n");

    pc = 0;
    int i = 1;
    while(1){

        i = temp(memory[pc], reg, memory);
        if (i == 0){
            break;
        }

//        temp(progr[0], reg);
//        temp(progr[1], reg);
//        temp(progr[2], reg);


    }

    printf("x0  = 0x%08x,  x1 = 0x%08x,  x2 = 0x%08x,  x3 = 0x%08x \n",reg[0],reg[1],reg[2],reg[3]);
    printf("x4  = 0x%08x,  x5 = 0x%08x,  x6 = 0x%08x,  x7 = 0x%08x \n",reg[4],reg[5],reg[6],reg[7]);
    printf("x8  = 0x%08x,  x9 = 0x%08x, x10 = 0x%08x, x11 = 0x%08x \n",reg[8],reg[9],reg[10],reg[11]);
    printf("x12 = 0x%08x, x13 = 0x%08x, x14 = 0x%08x, x15 = 0x%08x \n",reg[12],reg[13],reg[14],reg[15]);
    printf("x16 = 0x%08x, x17 = 0x%08x, x18 = 0x%08x, x19 = 0x%08x \n",reg[16],reg[17],reg[18],reg[19]);
    printf("x20 = 0x%08x, x21 = 0x%08x, x22 = 0x%08x, x23 = 0x%08x \n",reg[20],reg[21],reg[22],reg[23]);
    printf("x24 = 0x%08x, x25 = 0x%08x, x26 = 0x%08x, x27 = 0x%08x \n",reg[24],reg[25],reg[26],reg[27]);
    printf("x28 = 0x%08x, x29 = 0x%08x, x30 = 0x%08x, x31 = 0x%08x \n",reg[28],reg[29],reg[30],reg[31]);




    printf("END of RISC-V Simiulator\n");
    return 0;
}

//Operatsions




//instructions
int temp (int instr, uint32_t reg[32], uint32_t *memory){
    int opcode = instr & 0x7F;
    int rd;
    int imm;
    int funct3;
    int rs1;
    int rs2;
    int funct7;
    switch (opcode) {




        case 0b0000011: //FMT = I   (LB,LH,LW,LBU,LHU might be wrong)
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 0b000: //LB = load byte
                    reg[rd] = memory[reg[rs1]+imm];
                    break;
                case 0b001: //LH = load halfword
                    reg[rd] = memory[reg[rs1]+imm] & 0x0ff;
                    reg[rd] += (memory[(reg[rs1] + imm) + 1]) << 8;
                    break;
                case 0b010: //LW = load word
                    reg[rd] = memory[reg[rs1]+imm] & 0x0ff;
                    reg[rd] += (memory[(reg[rs1] + imm) + 1]) << 8;
                    reg[rd] += (memory[(reg[rs1] + imm) + 2]) << 16;
                    reg[rd] += (memory[(reg[rs1] + imm) + 3]) << 24;
                    break;
                case 0b100: //LBU = load byte unsigned
                    reg[rd] = memory[reg[rs1] + imm] & 0xff;
                    break;
                case 0b101: //LHU = load halfword unsigned
                    reg[rd] = memory[reg[rs1]+imm] & 0x0ff;
                    reg[rd] += (memory[(reg[rs1] + imm) + 1]) << 8;
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            pc +=4;
            break;




            /*case 0001111: fence og fence.i skal ikke bruges
                printf("2");
                break;*/
        case 0b0010011: //FMT = I
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 0b000: //ADDI = add immediate
                    reg[rd] = reg[rs1] + imm;
                    break;
                case 0b010: //SLTI = set less than immediate
                    reg[rd] = reg[rs1] < imm;
                    break;
                case 0b011: //SLTIU = set less than immediate unsigned
                    reg[rd] = reg[rs1] < imm;
                    break;
                case 0b100: //XORI = exclusive or immediate
                    reg[rd] = reg[rs1] ^ imm;
                    break;
                case 0b110: //ORI = or immediate
                    reg[rd] = reg[rs1] | imm;
                    break;
                case 0b111: //ANDI = and immediate
                    reg[rd] = reg[rs1] & imm;
                    break;
                case 0b001: //SLLI = shift left logical immediate
                    reg[rd] = reg[rs1] << imm;
                    break;
                case 0b101: //SRLI = shift right logical immediate and SRAI = shift right arithmetic immediate
                    imm = (instr >> 20) & 0x01f;
                    funct7 = (instr >> 25);
                    if (funct7 == 0b0000000) { //SRLI
                        reg[rd] = reg[rs1] >> imm;
                    } else if (funct7 == 0b0100000) { //SRAI
                        int s = -(reg[rs1] >> 31);
                        reg[rd] = (reg[rs1] >> imm) | (s << (32 - imm));
                    } else {
                        printf("Funct7 %d not yet implemented", funct7);
                    }
                    break;
                    /*case 101 && ((instr >> 30) & 0x01)==1: //
                        printf("4");
                        break;*/
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            pc += 4;
            break;




        case 0b0010111: //FMT = U AUIPC
            rd = (instr >> 7) & 0x01f;
            imm = (instr >> 12);
            reg[rd] = pc + imm;
            pc +=4;
            break;




        case 0b0100011: //FMT = S
            imm = (((instr >> 25) & 0x07f) << 5)+((instr >> 7) & 0x01f);
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            rs2 = (instr >> 20) & 0x01f;
            switch (funct3) {
                case 0b000: //SB = store byte
                        memory[rs1 + imm] = rs2 & 0x7f;
                    break;
                case 0b001: //SH = store halfword
                        memory[rs1 + imm] = rs2 & 0x7f;
                        memory[rs1 + imm + 1] = rs2 & 0x7f00;
                    break;
                case 0b010: //SW = store word
                    memory[rs1 + imm] = rs2 & 0x7f;
                    memory[rs1 + imm + 1] = rs2 & 0x7f00;
                    memory[rs1 + imm + 2] = rs2 & 0x7f0000;
                    memory[rs1 + imm + 3] = rs2 & 0x7f000000;
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            pc +=4;
            break;




        case 0b0110011: //FMT = R
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            rs2 = (instr >> 20) & 0x01f;
            funct7 = (instr >> 25);
            switch (funct3) {
                case 0b000: //ADD = add and SUB = subtract
                    if (funct7 == 0b0000000) { //ADD
                        reg[rd] = reg[rs1] + reg[rs2];
                    } else if (funct7 == 0b0100000) { // SUB
                        reg[rd] = reg[rs1] - reg[rs2];
                    } else {
                        printf("Funct7 %d not yet implemented", funct7);
                    }
                    break;
                case 0b001: //SLL = shift left logical
                    reg[rd] = reg[rs1] << reg[rs2];
                    break;
                case 0b010: //SLT = set less than
                    reg[rd] = reg[rs1] < reg[rs2];
                    break;
                case 0b011: //SLTU = set less than unsigned
                    reg[rd] = reg[rs1] < reg[rs2];
                    break;
                case 0b100: //XOR = exclusive or
                    reg[rd] = reg[rs1] ^ reg[rs2];
                    break;
                case 0b101: //SRL = shift right logical miising slra
                    reg[rd] = reg[rs1] >> reg[rs2];
                    break;
                case 0b110: //OR = or
                    reg[rd] = reg[rs1] | reg[rs2];
                    break;
                case 0b111: //AND = and
                    reg[rd] = reg[rs1] & reg[rs2];
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            pc +=4;
            break;




        case 0b0110111: //FMT = U //LUI
            rd = (instr >> 7) & 0x01f;
            imm = (instr >> 12);
            reg[rd] = imm<<12;
            pc = pc + 4;
            break;




        case 0b1100011: //FMT = SB
            imm = (((instr >> 31) & 0x01) <<12 )| (((instr >> 7) & 0x01) << 11)|(((instr >> 25) & 0x03f)<<5)|(((instr >> 8) & 0x0f)<<1);
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            rs2 = (instr >> 20) & 0x01f;
            if (instr < 0){imm = ~(0x1fff ^ imm);}
            switch (funct3) {
                case 0b000: //BEQ = branch equal
                    if(reg[rs1] == reg[rs2]){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b001: //BNE = branch not equal
                    if(reg[rs1] != reg[rs2]){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b100: //BLT = branch less than
                    if(reg[rs1] < reg[rs2]){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b101: //BGE = branch greater than or equal
                    if(reg[rs1] >= reg[rs2]){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b110: //BLTU = branch less than unsigned
                    if(reg[rs1] < reg[rs2]){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b111: //BGEU = branch greater than or equal unsigned
                    if(reg[rs1] >= reg[rs2]){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }

            break;




        case 0b1100111: //FMT = I
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 0b000: //JALR = jump and link register
                    reg[rd] = pc+4;
                    pc = reg[rs1] +imm;
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);
            }
            break;




        case 0b1101111: //FMT = UJ //JAL
            rd = (instr >> 7) & 0x01f;
            imm = (((instr >> 31) & 0x01) <<20 )| (((instr >> 12) & 0xff) << 12)|(((instr >> 20) & 0x01) << 11)|(((instr >> 21) & 0x03ff)<<1);
            reg[rd] = pc+4;
            pc = pc + imm;
            break;




        case 0b1110011://FMT = I  det er kun ecall som skal bruges
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (reg[17]){
                case 10: //exit
                    //printf("exit");
                    return 0;
                default:
                    printf("Funct3 %d not yet implemented", funct3);
            }
            break;




        default:
            printf("Opcode %d not yet implemented", opcode);
    }
    return 1;
}


void readBinFile(uint32_t *memory){
    char str[] = testfile;
    FILE *fp = fopen(str,"r");
    if (fp == NULL){
        perror("Unable to find file");
        exit(1);
    }
    printf("File found %s\n",str);

    fseek(fp,0,SEEK_END);
    int size = ftell(fp);
    fseek(fp,0,SEEK_SET);

    uint32_t word = getw(fp);
    int i = 0;
    while (word != EOF){
        //printf("%d\n",word);
        memory[i] = word;
        i += 4;
        word = getw(fp);
    }
    fclose(fp);

}