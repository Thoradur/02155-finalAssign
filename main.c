//
// Created by pouls on 13/11/2023.
// test from AB 13-11 this is heini
//
#include "stdio.h"
int main() {

    int a = 1;
    int b = 2;

    return a+b;
}

void temp (int opcode){
    switch (opcode) {
        case 0000011:
            printf("1");
            break;
        /*case 0001111: fence og fence.i skal ikke bruges
            printf("2");
            break;*/
        case 0010011:
            printf("3");
            break;
        case 0010111:
            printf("4");
            break;
        case 0100011:
            printf("5");
            break;
        case 0110011:
            printf("6");
            break;
        case 0110111:
            printf("7");
            break;
        case 1100011:
            printf("8");
            break;
        case 1100111:
            printf("9");
            break;
        case 1101111:
            printf("10");
            break;
        case 1110011:// det er kun ecall som skal bruges
            printf("11");
            break;
        default:
            printf("error in the opcode value");
    }
}