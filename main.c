//
// Created by pouls on 13/11/2023.
// test from AB 13-11 this is heini
//
#include <stdio.h>

void temp (int instr, int pc);



int main() {

    static int *pc;
    static int reg[32];

    temp(0000011, *pc);
    return 0;
}

//Operatsions




//instructions
void temp (int instr, int pc){
    int opcode = instr & 0x7F;
    int rd;
    int imm;
    int funct3;
    int rs1;
    int rs2;
    int funct7;
    switch (opcode) {




        case 0000011: //FMT = I
            printf("1");
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 000: //LB = load byte
                    reg[rd] = memory[reg[rs1]+imm]; //might be wrong
                    break;
                case 001: //LH = load halfword
                    printf("load halfword not implemented missing memory");
                    break;
                case 010: //LW = load word
                    printf("load halfword not implemented missing memory");
                    break;
                case 100: //LBU = load byte unsigned
                    printf("load byte unsigned not implemented missing memory");
                    break;
                case 101: //LHU = load halfword unsigned
                    printf("load halfword not implemented missing memory");
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            break;




            /*case 0001111: fence og fence.i skal ikke bruges
                printf("2");
                break;*/
        case 0010011: //FMT = I
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 000: //ADDI = add immediate
                    reg[rd] = reg[rs1] + imm;
                    break;
                case 010: //SLTI = set less than immediate
                    reg[rd] = reg[rs1] < imm;
                    break;
                case 011: //SLTIU = set less than immediate unsigned
                    reg[rd] = reg[rs1] < imm;
                    break;
                case 100: //XORI = exclusive or immediate
                    reg[rd] = reg[rs1] ^ imm;
                    break;
                case 110: //ORI = or immediate
                    reg[rd] = reg[rs1] | imm;
                    break;
                case 111: //ANDI = and immediate
                    reg[rd] = reg[rs1] & imm;
                    break;
                case 001: //SLLI = shift left logical immediate
                    reg[rd] = reg[rs1] << imm;
                    break;
                case 101: //SRLI = shift right logical immediate and SRAI = shift right arithmetic immediate
                    imm = (instr >> 20) & 0x01f;
                    funct7 = (instr >> 25);
                    if (funct7 == 0000000) { //SRLI
                        reg[rd] = reg[rs1] >> imm;
                    } else if (funct7 == 0100000) { //SRAI
                        printf("spunk not imlemented");
                    } else {
                        printf("Funct7 %d not yet implemented", funct7);
                    }
                    printf("4");
                    break;
                    /*case 101 && ((instr >> 30) & 0x01)==1: //
                        printf("4");
                        break;*/
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            printf("3");
            break;




        case 0010111: //FMT = U AUIPC
            rd = (instr >> 7) & 0x01f;
            imm = (instr >> 12);
            rd = pc + imm;
            break;




        case 0100011: //FMT = S
            imm = (((instr >> 25) & 0x07f) << 5)+((instr >> 7) & 0x01f);
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            rs2 = (instr >> 20) & 0x01f;
            switch (funct3) {
                case 000: //SB = store byte
                    printf("store byte not implemented missing memory");
                    break;
                case 001: //SH = store halfword
                    printf("store halfword not implemented missing memory");
                    break;
                case 010: //SW = store word
                    printf("store word not implemented missing memory");
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            printf("5");
            break;




        case 0110011: //FMT = R
            printf("6");
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            rs2 = (instr >> 20) & 0x01f;
            funct7 = (instr >> 25);
            switch (funct3) {
                case 000: //ADD = add and SUB = subtract
                    if (funct7 == 0000000) {
                        rd = rs1 + rs2;
                    } else if (funct7 == 0100000) { // SUB
                        rd = rs1 - rs2;
                    } else {
                        printf("Funct7 %d not yet implemented", funct7);
                    }
                    break;
                case 001: //SLL = shift left logical
                    rd = rs1 << rs2;
                    break;
                case 010: //SLT = set less than
                    rd = rs1 < rs2;
                    break;
                case 011: //SLTU = set less than unsigned
                    rd = rs1 < rs2;
                    break;
                case 100: //XOR = exclusive or
                    rd = rs1 ^ rs2;
                    break;
                case 101: //SRL = shift right logical miising slra
                    rd = rs1 >> rs2;
                    break;
                case 110: //OR = or
                    rd = rs1 | rs2;
                    break;
                case 111: //AND = and
                    rd = rs1 & rs2;
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            break;




        case 0110111: //FMT = U //LUI
            rd = (instr >> 7) & 0x01f;
            imm = (instr >> 12);
            rd = imm;
            break;




        case 1100011: //FMT = SB
            imm = (((instr >> 31) & 0x01) <<12 )| (((instr >> 7) & 0x01) << 11)|(((instr >> 25) & 0x03f)<<5)|(((instr >> 8) & 0x0f)<<1);
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            rs2 = (instr >> 20) & 0x01f;
            switch (funct3) {
                case 000: //BEQ = branch equal
                    if(reg[rs1] == reg[rs2]){
                        pc = pc + imm;
                    }
                    break;
                case 001: //BNE = branch not equal
                    if(reg[rs1] != reg[rs2]){
                        pc = pc + imm;
                    }
                    break;
                case 100: //BLT = branch less than
                    if(reg[rs1] < reg[rs2]){
                        pc = pc + imm;
                    }
                    break;
                case 101: //BGE = branch greater than or equal
                    if(reg[rs1] >= reg[rs2]){
                        pc = pc + imm;
                    }
                    break;
                case 110: //BLTU = branch less than unsigned
                    if(reg[rs1] < reg[rs2]){
                        pc = pc + imm;
                    }
                    break;
                case 111: //BGEU = branch greater than or equal unsigned
                    if(reg[rs1] >= reg[rs2]){
                        pc = pc + imm;
                    }
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            printf("8");
            break;




        case 1100111: //FMT = I
            printf("9");
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 000: //JALR = jump and link register
                    reg[rd] = pc+4;
                    pc = reg[rs1] +imm;
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);
            }
            break;




        case 1101111: //FMT = UJ //JAL
            rd = (instr >> 7) & 0x01f;
            imm = (((instr >> 31) & 0x01) <<20 )| (((instr >> 12) & 0xff) << 12)|(((instr >> 20) & 0x01) << 11)|(((instr >> 21) & 0x03ff)<<1);
            reg[rd] = pc+4;
            pc = pc + imm;
            break;




        case 1110011://FMT = I  det er kun ecall som skal bruges
            printf("11");
            rd = (instr >> 7) & 0x01f;
            funct3 = (instr >> 12) & 0x07;
            rs1 = (instr >> 15) & 0x01f;
            imm = (instr >> 20);
            switch (funct3) {
                case 000: //ECALL = environment call
                    printf("4");
                    break;
                default:
                    printf("Funct3 %d not yet implemented", funct3);

            }
            break;




        default:
            printf("Opcode %d not yet implemented", opcode);
    }
}