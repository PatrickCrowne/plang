//
//  plangc.c
//  plang
//
//  Created by Patrick Crowne on 11/25/21.
//

#include "plangc.h"
#include <string.h>

void plang_assemble(FILE* object, FILE* binary) {
    
    char* buffer = malloc(4);
    char* line = malloc(64);
    
    // Read each line of assembly code
    while (fscanf(object, "%[^\n]\n", line) != EOF) {
        char* instruction = malloc(16);
        sscanf(line, "%[^ ]", instruction);
        
        if (strncmp(instruction, "TEST", 4) == 0) {
            fputc((char) CMD_TEST, binary);
        }
        if (strncmp(instruction, "EXIT", 4) == 0) {
            fputc((char) CMD_EXIT, binary);
        }
        if (strncmp(instruction, "JUMP", 4) == 0) {
            fputc((char) CMD_JUMP, binary);
            int value = 0;
            sscanf(line, "JUMP %d", &value);
            fputc((char) value, binary);
        }
        if (strncmp(instruction, "JNE", 4) == 0) {
            fputc((char) CMD_JNE, binary);
            int value = 0;
            sscanf(line, "JNE %d", &value);
            fputc((char) value, binary);
        }
        if (strncmp(instruction, "CMP", 4) == 0) {
            fputc((char) CMD_CMP, binary);
            int value_a = 0;
            int value_b = 0;
            sscanf(line, "CMP %d %d", &value_a, &value_b);
            fputc((char) value_a, binary);
            fputc((char) value_b, binary);
        }
        if (strncmp(instruction, "ADD", 4) == 0) {
            fputc((char) CMD_ADD, binary);
            int value_a = 0;
            int value_b = 0;
            int value_c = 0;
            sscanf(line, "ADD %d %d %d", &value_a, &value_b, &value_c);
            fputc((char) value_a, binary);
            fputc((char) value_b, binary);
            fputc((char) value_c, binary);
        }
        if (strncmp(instruction, "MOV", 4) == 0) {
            fputc((char) CMD_MOV, binary);
            int value_a = 0;
            int value_b = 0;
            sscanf(line, "MOV %d %d", &value_a, &value_b);
            fputc((char) value_a, binary); // Reg0 hardcoded temp
            fputc((char) value_b, binary);
        }
        
        free(instruction);
    }
    
    printf("end of compile\n");
    
    // Free memory
    free(buffer);
    free(line);
    buffer = NULL;
    line = NULL;
    
}
