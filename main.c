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

#define testfile "test/task4/t8"


// static program test
static int progr[] = {
        // As minimal RISC-V assembler example used for testing
        0xfec00513, // addi x10 x0 -20
        0xffd50593, // addi x11 x10 3
        0x00b50633, // add x12 x10 x11
};

// in
int temp (int instr, uint32_t reg[32], uint32_t *memory);
void readBinFile(uint32_t *memory);
void readResFile(uint32_t reg[32]);


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


//        temp(progr[0], reg, memory);
//        temp(progr[1], reg, memory);
//        temp(progr[2], reg, memory);
//        i = 0;
        if (i == 0){
            break;
        }


    }

    for (int j = 0; j < 8; ++j) {

        printf("x%02d = 0x%08x, x%02d = 0x%08x, x%02d = 0x%08x, x%02d = 0x%08x \n",0+(j*4),reg[0+(j*4)],1+(j*4),reg[1+(j*4)],2+(j*4),reg[2+(j*4)],3+(j*4),reg[3+(j*4)]);
    }


    printf("END of RISC-V Simiulator\n");
    readResFile(reg);

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
    int regR1;
    int regR2;
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
            regR1 = reg[rs1]; //USED FOR SIGNED OPERATIONS
            switch (funct3) {
                case 0b000: //ADDI = add immediate
                    reg[rd] = reg[rs1] + imm;
                    break;
                case 0b010: //SLTI = set less than immediate
                    reg[rd] = regR1  < imm;
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
            regR1 = reg[rs1];
            regR2 = reg[rs2];
            if (instr < 0){imm = ~(0x1fff ^ imm);}
            switch (funct3) {
                case 0b000: //BEQ = branch equal
                    if(regR1 == regR2){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b001: //BNE = branch not equal
                    if(regR1 != regR2){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b100: //BLT = branch less than
                    if(regR1 < (int) regR2){
                        pc = pc + imm;
                    } else {
                        pc += 4;
                    }
                    break;
                case 0b101: //BGE = branch greater than or equal
                    if(regR1 >= regR2){
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
    char str[] = testfile".bin";
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

void readResFile(uint32_t reg[32]){
    char str[] = testfile".res";
    FILE *file = fopen(str, "rb");  // Open the file in binary mode
    int count = 0;

    if (file == NULL) {
        perror("Error opening file");
    }
    printf("File found %s printing result \n",str);
    for (int j = 0; j < 8; ++j){
        // Read the first 16 bytes so first 4 registers
        uint8_t bytes[16];
        fread(bytes, sizeof(uint8_t), 16, file);
        // Assuming little-endian, convert bytes to a 32-bit integer
        uint32_t val1 = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
        uint32_t val2 = bytes[4] | (bytes[5] << 8) | (bytes[6] << 16) | (bytes[7] << 24);
        uint32_t val3 = bytes[8] | (bytes[9] << 8) | (bytes[10] << 16) | (bytes[11] << 24);
        uint32_t val4 = bytes[12] | (bytes[13] << 8) | (bytes[14] << 16) | (bytes[15] << 24);

        // Print the value using printf
        printf("x%02d = 0x%08x, x%02d = 0x%08x, x%02d = 0x%08x, x%02d = 0x%08x \n",0+(j*4),val1,1+(j*4),val2,2+(j*4),val3,3+(j*4),val4);


        //CHECKS IF THE REGISTERS ARE EQUAL TO THE RESULT FILE
        if (reg[0+(j*4)]==val1){
            count++;
        }if (reg[1+(j*4)]==val2){
            count++;
        }if (reg[2+(j*4)]==val3){
            count++;
        }if (reg[3+(j*4)]==val4){
            count++;
        }




    }
    if (count == 32){
        printf("All 32 registers are equal to the result file\n");
    } else{
        printf("there is %d registers wrong\n",(32-count));
    }
    fclose(file);

}