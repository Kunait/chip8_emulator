
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include "instruction_parser.h"


#define RED "\e[0;31m"
#define NC "\e[0m"

#define VRAM_SIZE 32
#define STACK_SIZE 16
#define RAM_SIZE 4096
#define REGISTER_COUNT 16

#define PROGRAM_START_ADDRESS 512





CHIP c = {0};



bool run_instruction(uint16_t instruction){

    printf("%04x \n", instruction);

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


int main(int argc, char *argv) {
    printf("Enter ROM path: \n");
    char path[100];
    scanf("%s", path);
    read_rom_into_memory(path);

    
    //printf("%llu", sizeof(chip));
    
    


    return 0;
}
