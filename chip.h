#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "instruction_parser.h"

bool run_instruction();
void print_instruction(uint16_t instruction, uint16_t address);
void read_rom_into_memory(char *path);
void initialize_sprites();
CHIP *init(char *path);