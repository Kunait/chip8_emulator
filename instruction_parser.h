#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define RED "\e[0;31m"
#define NC "\e[0m"

#define VRAM_SIZE 32
#define STACK_SIZE 16
#define RAM_SIZE 4096
#define REGISTER_COUNT 16

#define PROGRAM_START_ADDRESS 512


typedef struct {



uint8_t ram[RAM_SIZE];
uint8_t V[REGISTER_COUNT];
uint16_t I;
uint16_t PC;
uint8_t stack_pointer;
uint8_t delay_timer;
uint8_t sound_timer;
uint8_t pressedKey;

uint16_t stack[STACK_SIZE];
uint64_t vram[VRAM_SIZE];
    
} CHIP;


typedef enum{

    CLS = 0x00E0, //Clear Display
    RET = 0x00EE, //Return from Subroutine, PC = Address at top of stack, decrement stackpointer
    JMP = 0x1000, //Jump to address in last 3 bytes
    CALL = 0x2000, //Call Subroutine, increment SP, push PC on stack, PC = address in last 3 bytes
    SKIP_R_V_EQUAL = 0x3000, //3xkk, skip if Reg Vx = kk, increment PC by 2
    SKIP_R_V_NOT_EQUAL = 0x4000, //4xkk skip if Reg Vx != kk, increment PC by 2
    SKIP_R_R_EQUAL = 0x5000, //5xy0, skip if Vx == Vy, PC+2
    LD_V_TO_R = 0x6000, //6xkk, Vx = kk
    ADD_V_TO_R = 0x7000, //7xkk, Vx = Vx+kk
    LD_R_TO_R = 0x8000, //8xy0, Vx = Vy
    OR_R_R = 0x8001, //8xy1, Vx = Vx OR Vy
    AND_R_R = 0x8002, //8xy2, Vx = Vx AND Vy
    XOR_R_R = 0x8003, //8xy3, Vx = Vx XOR Vy
    ADD_R_TO_R = 0x8004, //8xy4, Vx = Vx + Vy, VF = carry (if result > 8bits -> VF =1), Vx only has lowest 8 bits of result
    SUB_R_TO_R = 0x8005, //8xy5, Vx = Vx - Vy, VF = NOT borrow, if Vx > Vy -> VF = 1, else 0
    SHR_R = 0x8006, //8xy6, Vx = Vx >> 1, maybe 1 is replaced by Vy if y exists. If least-significant bit of Vx = 1 -> VF = 1, then    Vx = Vx / 2
    SUBN_R_TO_R = 0x8007, //8xy7, Vx = Vy - Vx, VF = not borrow, if Vy > Vx -> VF = 1, else 0
    SHL_R = 0x800E, //8xyE, Vx = Vx << 1, maybe 1 is replaced by Vy if y exists. If least-significant bit of Vx = 1 -> VF = 1, then   Vx = Vx * 2
    SKIP_R_R_NOT_EQUAL = 0x9000, //9xy0, skip next instr if Vx != Vy, increment PC by 2
    LD_TO_I = 0xA000, // Annn, set I = nnn
    JMP_ADDR_PLUS_R = 0xB000, // Bnnn, PC = nnn + V0
    RND_AND_INTO_R = 0xC000, //Cxkk, Vx = random byte AND kkk, rnd(0,255) | kkk -> Vx
    DISPLAY_SPRITE = 0xD000, //Dxyn, display n-byte sprite starting at mem loc. stored in I at (Vx,Vy),Sprite XOR'ed on screen, if pixel erased through this VF = 1, wraps if outside of screen
    SKIP_PRESSED = 0xE09E, //Ex9E, PC = PC + 2 if Key in Vx pressed
    SKIP_NOT_PRESSED = 0xE0A1, //ExA1, PC = PC + 2 if Key in Vx NOT pressed
    LD_DT_INTO_R = 0xF007, //Fx07, Vx = DT
    LD_KEY_INTO_R = 0xF00A, //Fx0A, Wait for keypress stop program, store keypress in Vx
    LD_R_INTO_DT = 0xF015, //Fx15, DT = Vx
    LD_R_INTO_ST = 0xF018, //Fx18, ST = Vx
    ADD_R_TO_I = 0xF01E, //Fx1E, I = I + Vx
    LD_SPRITE_ADDR_INTO_R = 0xF029, //Fx29, I = location of sprite for digit Vx
    REG_TO_H_T_O_IN_I = 0xF033, //Fx33, value in Vx, hundreds stored in I, tens in I+1, ones in I+2
    LD_REGS_INTO_I = 0xF055, //Fx55, store V0 to Vx in memory starting at location I 
    LD_FROM_I_INTO_REGS = 0xF065 //Fx65, read V0 to Vx from memory starting at location I


} opcode;


typedef struct{

    opcode instruction;
    uint16_t data;
    uint16_t all_bytes;


} full_instr;

void bytes_to_full_instr(uint16_t data, full_instr *instr);

const char* string_opcode(opcode code);


void execute_instruction(CHIP *c, full_instr *instruction);

uint16_t popStack(CHIP *c);
void pushStack(CHIP *c, uint16_t value);
void clearScreen(CHIP *c);
uint16_t getX(uint16_t data);
uint16_t getY(uint16_t data);
uint16_t getN(uint16_t data);
uint16_t getKK(uint16_t data);
void drawSprite(CHIP *c, uint8_t x, uint8_t y, uint8_t n);
