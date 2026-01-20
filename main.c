#include <SDL2/SDL.h>
#include <stdlib.h>
#include "chip.h"
#include "chip.c"
#include "instruction_parser.c"


CHIP *chip;

void write_vram_to_file(uint64_t vram[32], const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) return;
    
    for (int row = 0; row < 32; row++) {
        uint64_t value = vram[row];
        
        // Write each bit from MSB to LSB
        for (int bit = 63; bit >= 0; bit--) {
            if (value & (1ULL << bit)) {
                fputc('1', fp);
            } else {
                fputc('0', fp);
            }
        }
        fputc('\n', fp);  // Newline after each row
    }
    
    fclose(fp);
}
int main(){

    printf("Enter ROM path: \n");
    char *path = (char*) calloc(100,1);
    scanf("%99s", path);
    chip = init(path);
    free(path);
    while(true){
        run_instruction();
        write_vram_to_file(chip->vram, "vram.txt");
    }

    return 0;
}

