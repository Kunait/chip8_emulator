# CHIP-8 Emulator

A CHIP-8 interpreter/emulator written in C, designed to execute CHIP-8 ROMs and provide instruction-level debugging capabilities.

## Overview

CHIP-8 is an interpreted programming language developed in the 1970s for vintage computers. This emulator implements the complete CHIP-8 instruction set, allowing you to run classic CHIP-8 programs and games.

## Features

- **Complete instruction set implementation**: All 35 CHIP-8 opcodes fully supported
- **Instruction parsing and decoding**: Converts raw bytecode into executable instructions
- **Debug output**: Prints decoded instructions with addresses and data for debugging
- **Stack operations**: 16-level stack for subroutine calls
- **Memory management**: 4KB RAM with program start at address 0x200
- **Register system**: 16 general-purpose 8-bit registers (V0-VF)
- **Timers**: Delay and sound timer support

## Architecture

### Memory Layout
- **RAM**: 4096 bytes (0x000 - 0xFFF)
- **Program start**: 0x200 (512 bytes)
- **Stack**: 16 levels
- **Registers**: 16 x 8-bit (V0-VF)
- **Index register**: 16-bit (I)
- **Program counter**: 16-bit (PC)
- **VRAM**: 64x32 pixel display buffer

### Implemented Instructions

The emulator supports all CHIP-8 opcodes including:
- Display operations (CLS, DISPLAY_SPRITE)
- Flow control (JMP, CALL, RET, conditional skips)
- Arithmetic and logic (ADD, SUB, AND, OR, XOR)
- Bitwise operations (SHR, SHL)
- Memory operations (load/store registers)
- Timers and random number generation
- Keyboard input handling

## Building

```bash
gcc -o chip chip.c instruction_parser.c -std=c11
