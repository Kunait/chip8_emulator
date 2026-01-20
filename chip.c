#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include "instruction_parser.h"
#include "chip.h"


#define RED "\e[0;31m"
#define NC "\e[0m"

#define VRAM_SIZE 32
#define STACK_SIZE 16
#define RAM_SIZE 4096
#define REGISTER_COUNT 16

#define PROGRAM_START_ADDRESS 512





CHIP c = {0};



bool run_instruction(){
    full_instr *instr = malloc(sizeof(full_instr));
    uint16_t opcode = ((uint16_t)c.ram[PROGRAM_START_ADDRESS+c.PC]) << 8;
    opcode |= c.ram[PROGRAM_START_ADDRESS+c.PC+1];
    bytes_to_full_instr(opcode, instr);
    execute_instruction(&c,instr);
    free(instr);
    c.PC+=2;
}

void print_instruction(uint16_t instruction, uint16_t address){

    full_instr full_instruction = {0};
    bytes_to_full_instr(instruction, &full_instruction);

    if(full_instruction.instruction != 0){
    printf("%x:%s, Data: %x \n", address, string_opcode(full_instruction.instruction), full_instruction.data);
    }
}
void read_rom_into_memory(char *path){

    FILE *f = fopen(path,"rb");
    if(f == NULL) {
        fprintf(stderr, RED "ERROR: COULD NOT OPEN FILE, CHECK PATH");
        exit(EXIT_FAILURE);
    }
    int size = RAM_SIZE - PROGRAM_START_ADDRESS;
    char buffer[size];
    memset(buffer, 0, size);
    int result = fread(buffer,sizeof(buffer[0]), size, f);
    if(result <= 0){
        fprintf(stderr, RED "ERROR: COULD NOT READ FILE INTO MEMORY, MOST LIKELY FILE > MEMORY");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < size; i=i+2){
        
            //printf("%d ",buffer[i] );
            
            uint8_t byte_one = buffer[i];
            uint8_t byte_two = buffer[i+1];
            uint16_t instruction = (byte_one << 8 ) | byte_two;
        
            c.ram[PROGRAM_START_ADDRESS + (i)] = byte_one;
            c.ram[PROGRAM_START_ADDRESS + i + 1] = byte_two;
            print_instruction(instruction, PROGRAM_START_ADDRESS + i);
    }
    

}


void initialize_sprites(){
    //ZERO - 0
    c.ram[0] = 0xF0;
    c.ram[1] = 0x90;
    c.ram[2] = 0x90;
    c.ram[3] = 0x90;
    c.ram[4] = 0xF0;

    //ONE - 1
    c.ram[5] = 0x20;
    c.ram[6] = 0x60;
    c.ram[7] = 0x20;
    c.ram[8] = 0x20;
    c.ram[9] = 0x70;

    //TWO - 2
    c.ram[10] = 0xF0;
    c.ram[11] = 0x10;
    c.ram[12] = 0xF0;
    c.ram[13] = 0x80;
    c.ram[14] = 0xF0;

    //THREE - 3
    c.ram[15] = 0xF0;
    c.ram[16] = 0x10;
    c.ram[17] = 0xF0;
    c.ram[18] = 0x10;
    c.ram[19] = 0xF0;

    //FOUR - 4
    c.ram[20] = 0x90;
    c.ram[21] = 0x90;
    c.ram[22] = 0xF0;
    c.ram[23] = 0x10;
    c.ram[24] = 0x10;

    //FIVE - 5
    c.ram[25] = 0xF0;
    c.ram[26] = 0x80;
    c.ram[27] = 0xF0;
    c.ram[28] = 0x10;
    c.ram[29] = 0xF0;

    //SIX - 6
    c.ram[30] = 0xF0;
    c.ram[31] = 0x80;
    c.ram[32] = 0xF0;
    c.ram[33] = 0x90;
    c.ram[34] = 0xF0;

    //SEVEN - 7
    c.ram[35] = 0xF0;
    c.ram[36] = 0x10;
    c.ram[37] = 0x20;
    c.ram[38] = 0x40;
    c.ram[39] = 0x40;

    //EIGHT - 8
    c.ram[40] = 0xF0;
    c.ram[41] = 0x90;
    c.ram[42] = 0xF0;
    c.ram[43] = 0x90;
    c.ram[44] = 0xF0;

    //NINE - 9
    c.ram[45] = 0xF0;
    c.ram[46] = 0x90;
    c.ram[47] = 0xF0;
    c.ram[48] = 0x10;
    c.ram[49] = 0xF0;

    //A - A
    c.ram[50] = 0xF0;
    c.ram[51] = 0x90;
    c.ram[52] = 0xF0;
    c.ram[53] = 0x90;
    c.ram[54] = 0x90;

    //B - B
    c.ram[55] = 0xE0;
    c.ram[56] = 0x90;
    c.ram[57] = 0xE0;
    c.ram[58] = 0x90;
    c.ram[59] = 0xE0;

    //C - C
    c.ram[60] = 0xF0;
    c.ram[61] = 0x80;
    c.ram[62] = 0x80;
    c.ram[63] = 0x80;
    c.ram[64] = 0xF0;

    //D - D
    c.ram[65] = 0xE0;
    c.ram[66] = 0x90;
    c.ram[67] = 0x90;
    c.ram[68] = 0x90;
    c.ram[69] = 0xE0;

    //E - E
    c.ram[70] = 0xF0;
    c.ram[71] = 0x80;
    c.ram[72] = 0xF0;
    c.ram[73] = 0x80;
    c.ram[74] = 0xF0;

    //F - F
    c.ram[75] = 0xF0;
    c.ram[76] = 0x80;
    c.ram[77] = 0xF0;
    c.ram[78] = 0x80;
    c.ram[79] = 0x80;

}


CHIP *init(char *path) {
    
    read_rom_into_memory(path);
    initialize_sprites();
    
    return &c;
}  


