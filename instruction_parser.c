#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "instruction_parser.h"

#define SKIP_INSTRUCTION c->PC = c->PC+2

void bytes_to_full_instr(uint16_t input, full_instr *instr){


    instr->all_bytes = input;

    switch(input & 0x00EE){

        case 0x00E0:
            instr->instruction = CLS;
            break;

        case 0x00EE:
            instr->instruction = RET;
            break;
    }

    switch (input & 0xF0FF){

        case 0xF065:
            instr->instruction = LD_FROM_I_INTO_REGS;
            instr->data = input & 0x0F00;
            break;
        case 0xF055:
            instr->instruction = LD_REGS_INTO_I;
            instr->data = input & 0x0F00;
            break;
        case 0xF033:
            instr->instruction = REG_TO_H_T_O_IN_I;
            instr->data = input & 0x0F00;
            break;
        case 0xF029:
            instr->instruction = LD_SPRITE_ADDR_INTO_R;
            instr->data = input & 0x0F00;
            break;
        case 0xF01E:
            instr->instruction = ADD_R_TO_I;
            instr->data = input & 0x0F00;
            break;
        case 0xF018:
            instr->instruction = LD_R_INTO_ST;
            instr->data = input & 0x0F00;
            break;
        case 0xF015:
            instr->instruction = LD_R_INTO_DT;
            instr->data = input & 0x0F00;
            break;

    }

    switch(input & 0xF00F){
        case 0xF00A:
            instr->instruction = LD_KEY_INTO_R;
            instr->data = input & 0x0FF0;
            break;

        case 0xF007:
            instr->instruction = LD_DT_INTO_R;
            instr->data = input & 0x0FF0;
            break;
    }

    switch (input & 0xF000)
    {
        case 0x1000:
            instr->instruction = JMP;
            instr->data = input & 0x0FFF;
            break;
        case 0x2000:
            instr->instruction = CALL;
            instr->data = input & 0x0FFF;
            break;
        case 0x3000:
            instr->instruction = SKIP_R_V_EQUAL;
            instr->data = input & 0x0FFF;
            break;
        case 0x4000:
            instr->instruction = SKIP_R_V_NOT_EQUAL;
            instr->data = input & 0x0FFF;
            break;
        case 0x5000:
            instr->instruction = SKIP_R_R_EQUAL;
            instr->data = input & 0x0FFF;
            break;
        case 0x6000:
            instr->instruction = LD_V_TO_R;
            instr->data = input & 0x0FFF;
            break;
        case 0x7000:
            instr->instruction = ADD_V_TO_R;
            instr->data = input & 0x0FFF;
            break;
        case 0x8000:
            instr->instruction = LD_R_TO_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x9000:
            instr->instruction = SKIP_R_R_NOT_EQUAL;
            instr->data = input & 0x0FF0;
            break;
        case 0xA000:
            instr->instruction = LD_TO_I;
            instr->data = input & 0x0FFF;
            break;
        case 0xB000:
            instr->instruction = JMP_ADDR_PLUS_R;
            instr->data = input & 0x0FFF;
            break;
        case 0xC000:
            instr->instruction = RND_AND_INTO_R;
            instr->data = input & 0x0FFF;
            break;
        case 0xD000:
            instr->instruction = DISPLAY_SPRITE;
            instr->data = input & 0x0FFF;
            break;
    }

    switch(input & 0xF00F){
        case 0x8001:
            instr->instruction = OR_R_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x8002:
            instr->instruction = AND_R_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x8003:
            instr->instruction = XOR_R_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x8004:
            instr->instruction = ADD_R_TO_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x8005:
            instr->instruction = SUB_R_TO_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x8006:
            instr->instruction = SHR_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x8007:
            instr->instruction = SUBN_R_TO_R;
            instr->data = input & 0x0FF0;
            break;
        case 0x800E:
            instr->instruction = SHL_R;
            instr->data = input & 0x0FF0;
            break;
        
    }

    switch(input & 0xF0FF){
        case 0xE09E:
            instr->instruction = SKIP_PRESSED;
            instr->data = input & 0x0F00;
            break;

        case 0xE0A1:
            instr->instruction = SKIP_NOT_PRESSED;
            instr->data = input & 0x0F00;
            break;
    }

    


}



const char* string_opcode(opcode code){
    switch(code) {
        case CLS: return "CLS";
        case RET: return "RET";
        case JMP: return "JMP";
        case CALL: return "CALL";
        case SKIP_R_V_EQUAL: return "SKIP_R_V_EQUAL";
        case SKIP_R_V_NOT_EQUAL: return "SKIP_R_V_NOT_EQUAL";
        case SKIP_R_R_EQUAL: return "SKIP_R_R_EQUAL";
        case LD_V_TO_R: return "LD_V_TO_R";
        case ADD_V_TO_R: return "ADD_V_TO_R";
        case LD_R_TO_R: return "LD_R_TO_R";
        case OR_R_R: return "OR_R_R";
        case AND_R_R: return "AND_R_R";
        case XOR_R_R: return "XOR_R_R";
        case ADD_R_TO_R: return "ADD_R_TO_R";
        case SUB_R_TO_R: return "SUB_R_TO_R";
        case SHR_R: return "SHR_R";
        case SUBN_R_TO_R: return "SUBN_R_TO_R";
        case SHL_R: return "SHL_R";
        case SKIP_R_R_NOT_EQUAL: return "SKIP_R_R_NOT_EQUAL";
        case LD_TO_I: return "LD_TO_I";
        case JMP_ADDR_PLUS_R: return "JMP_ADDR_PLUS_R";
        case RND_AND_INTO_R: return "RND_AND_INTO_R";
        case DISPLAY_SPRITE: return "DISPLAY_SPRITE";
        case SKIP_PRESSED: return "SKIP_PRESSED";
        case SKIP_NOT_PRESSED: return "SKIP_NOT_PRESSED";
        case LD_DT_INTO_R: return "LD_DT_INTO_R";
        case LD_KEY_INTO_R: return "LD_KEY_INTO_R";
        case LD_R_INTO_DT: return "LD_R_INTO_DT";
        case LD_R_INTO_ST: return "LD_R_INTO_ST";
        case ADD_R_TO_I: return "ADD_R_TO_I";
        case LD_SPRITE_ADDR_INTO_R: return "LD_SPRITE_ADDR_INTO_R";
        case REG_TO_H_T_O_IN_I: return "REG_TO_H_T_O_IN_I";
        case LD_REGS_INTO_I: return "LD_REGS_INTO_I";
        case LD_FROM_I_INTO_REGS: return "LD_FROM_I_INTO_REGS";
        default: return "UNKNOWN";
    }
}

uint16_t popStack(CHIP *c){

    if(c->stack_pointer>0){
        c->stack_pointer--;
        return c->stack[c->stack_pointer-1];
    }
    fprintf(stderr, RED "ERROR: STACK EMPTY, COULD NOT POP");
    exit(EXIT_FAILURE);

}

void pushStack(CHIP *c, uint16_t value){

    if(c->stack_pointer > STACK_SIZE-1){
        c->stack[c->stack_pointer] = value;
        c->stack_pointer++;
    }

    fprintf(stderr, RED "ERROR: STACK FULL, COULD NOT PUSH");
    exit(EXIT_FAILURE);

}

void clearScreen(CHIP *c){
    memset(c->vram, 0, VRAM_SIZE);
}


//X is always second 4 bits of 16 bit instruction
uint16_t getX(uint16_t data){

    uint8_t result = data & 0x0F00;
    result = result >> 8;  
    return result;  
}

//Y is always third 4 bits of 16 bit instruction
uint16_t getY(uint16_t data){
    uint8_t result = data & 0x00F0;
    result = result >> 4;  
    return result;  
}

//N alone is always lowest 4 bits of 16 bit instruction
uint16_t getN(uint16_t data){
    uint8_t result = data & 0x000F; 
    return result;  
}

//KK is last 8 bits of 16 bit instruction
uint16_t getKK(uint16_t data){
    uint8_t result = data & 0x00FF; 
    return result;
}

uint8_t rndInt8Bit(){

    srand(time(NULL));  // Seed with current time
    


    return (uint8_t) rand();
}

void drawSprite(CHIP *c, uint8_t x, uint8_t y, uint8_t n){

    uint8_t lines[n];
    for(int j = 0; j < n; j++){
        lines[j] = c->ram[c->I+j]; 
    }
    y = y % 32;
    x = x % 64;
    
    c->V[0xF] = 0;

    for (int j = 0; j < n; j++) {
        uint8_t currentLine8 = lines[j];
        uint8_t currentY = (y + j) % 32;
        
        uint8_t bitsInFirstLine = 64 - x;

        if(bitsInFirstLine >= 8){

            uint64_t old = c->vram[currentY];
            uint64_t spriteBits = ((uint64_t) currentLine8 << (56-x));
            c->vram[currentY] ^= spriteBits;
            if((spriteBits & old)  !=0 ) c->V[0xF] = 1;

        } else{

            uint8_t bitsInSecondLine = 8 - bitsInFirstLine;
            
            uint64_t old1 = c->vram[currentY];
            uint64_t spriteBits1 = (uint64_t) (currentLine8 >> bitsInSecondLine);
            c->vram[currentY] ^= spriteBits1;
            if((spriteBits1 & old1)  !=0 ) c->V[0xF] = 1;

            uint64_t old2 = c->vram[currentY];
            uint64_t spriteBits2 = ((uint64_t) (currentLine8 << bitsInFirstLine) << 56);
            c->vram[currentY] ^= spriteBits2;
            if((spriteBits2 & old1)  !=0 ) c->V[0xF] = 1;

        }

}
}

void execute_instruction(CHIP *c, full_instr *instruction){
    
    uint8_t x=0, y=0, kk = 0, n = 0;
    uint8_t regVal, hundreds, tens, ones;
    uint8_t digit;
    uint16_t result;

    switch (instruction->instruction)
    {
    case CLS:
        clearScreen(c);
        break;
    case RET:
        c->PC = popStack(c);
        break;
    case JMP:
        c->PC = instruction->data;
        break;
    case CALL:
        pushStack(c, instruction->data);
        c->PC = instruction->data;
        break;
    case SKIP_R_V_EQUAL:
        x = getX(instruction->data);
        kk = getKK(instruction->data);
        if(c->V[x] == kk) {
           SKIP_INSTRUCTION;
        }
        break;
    case SKIP_R_V_NOT_EQUAL:
        x = getX(instruction->data);
        kk = getKK(instruction->data);
        if(c->V[x] != kk) {
            SKIP_INSTRUCTION;
        }
        break;
    case SKIP_R_R_EQUAL:
        x = getX(instruction->data);
        y = getY(instruction->data);
        if(c->V[x] == c->V[y]) {
            SKIP_INSTRUCTION;
        }
        break;
    case LD_V_TO_R:
        x = getX(instruction->data);
        kk = getKK(instruction->data);
        c->V[x] = kk;
        break;
    case ADD_V_TO_R:
        x = getX(instruction->data);
        kk = getKK(instruction->data);
        c->V[x] = c->V[x] + kk;
        break;
    case LD_R_TO_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        c->V[x] = c->V[y];
        break;
    case OR_R_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        c->V[x] = c->V[x] | c->V[y];
        break; 
    case AND_R_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        c->V[x] = c->V[x] & c->V[y];
        break;  
    case XOR_R_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        c->V[x] = c->V[x] ^ c->V[y];
        break;   
    case ADD_R_TO_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        result = c->V[x] + c->V[y];
        c->V[0xF] = (result > 0xFF) ? 1 : 0;
        c->V[x] = result & 0x00FF;
        break;   
    case SUB_R_TO_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        result = c->V[x] - c->V[y];
        c->V[0xF] = (c->V[x] > c->V[y]) ? 1 : 0;
        c->V[x] = result;
        break;  
    case SHR_R:
        x = getX(instruction->data);
        //y = getY(instruction->data);
        if(x & 0b00000001 == 1) c->V[0xF] = 1; else c->V[0xF] = 0;
        c->V[x] = c->V[x] >> 1;
        break; 
    case SUBN_R_TO_R:
        x = getX(instruction->data);
        y = getY(instruction->data);
        result = c->V[y] - c->V[x];
        c->V[0xF] = (c->V[y] > c->V[x]) ? 1 : 0;
        c->V[x] = result;
        break;
    case SHL_R:
        x = getX(instruction->data);
        //y = getY(instruction->data);
        if(x & 0b00000001 == 1) c->V[0xF] = 1; else c->V[0xF] = 0;
        c->V[x] = c->V[x] << 1;
        break; 
    case SKIP_R_R_NOT_EQUAL:
        x = getX(instruction->data);
        y = getY(instruction->data);
        if(c->V[x] != c->V[y]) SKIP_INSTRUCTION;
        break; 
    case LD_TO_I:
        c->I = instruction->data;
        break;
    case JMP_ADDR_PLUS_R:
        c->PC = instruction->data + c->V[0];
        break;
    case RND_AND_INTO_R:
        x = getX(instruction->data);
        kk = getKK(instruction->data);
        c->V[x] = rndInt8Bit() & kk;
        break;
    case SKIP_PRESSED:
        x = getX(instruction->data);
        if(c->V[x] ==  c->pressedKey) SKIP_INSTRUCTION;
        break;
    case SKIP_NOT_PRESSED:
        x = getX(instruction->data);
        if(c->V[x] !=  c->pressedKey) SKIP_INSTRUCTION;
        break;
    case LD_DT_INTO_R:
        x = getX(instruction->data);
        c->V[x] = c->delay_timer;
        break;
    //TODO: implement key press and wait for keypress!
    //! DOES NOT WORK YET
    case LD_KEY_INTO_R:
        x = getX(instruction->data);
        c->V[x] = c->delay_timer;
        break;
    case LD_R_INTO_DT:
        x = getX(instruction->data);
        c->delay_timer = c->V[x];
        break;   
    case LD_R_INTO_ST:
        x = getX(instruction->data);
        c->sound_timer = c->V[x];
        break; 
    case ADD_R_TO_I:
        x = getX(instruction->data);
        c->I = c->I + c->V[x];
        break;
    case LD_SPRITE_ADDR_INTO_R:
        x = getX(instruction->data);
        digit = c->V[x];
        c->I = c->ram[5*digit];
        break;
    case REG_TO_H_T_O_IN_I:
        x = getX(instruction->data);
        regVal = c->V[x];
        hundreds = regVal / 100;
        regVal = regVal - hundreds*100;
        tens = regVal/10;
        regVal = regVal - tens*10;
        ones = regVal;
        c->ram[c->I] = hundreds;
        c->ram[c->I+1] = tens;
        c->ram[c->I+2] = ones;
        break;
    case LD_REGS_INTO_I:
        x = getX(instruction->data);
        for(int j = 0; j <= x ; j ++){
            c->ram[c->I+j] = c->V[j];
        }
        break;
    case LD_FROM_I_INTO_REGS:
        x = getX(instruction->data);
        for(int j = 0; j<= x; j++){
            c->V[j] = c->ram[c->I+j];
        }
        break;
    case DISPLAY_SPRITE:
        x = getX(instruction->data);
        y  = getY(instruction->data);
        n = getN(instruction->data);
        drawSprite(c,x,y,n);
        break;
    default:
        break;
    }



}









