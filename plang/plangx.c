//
//  plangx.c
//  plang
//
//  Created by Patrick Crowne on 11/25/21.
//

#include "plangx.h"
#include "plang.h"

int main(int argc, char* argv[]) {
    
    // Open the file
    FILE* file = fopen(argv[argc - 1], "r");
    if (!file) {
        printf("plangx: file not found!\n");
        return 0;
    }
    
    FILE* file_binary = fopen(argv[argc - 2], "wb");
    if (!file_binary) {
        printf("plangx: file not found!\n");
        return 0;
    }
    
    plang_assemble(file, file_binary);
    fclose(file);
    fclose(file_binary);
    
    file = fopen(argv[argc - 2], "r");
    if (!file) {
        printf("plangx: file not found!\n");
        return 0;
    }
    rewind(file);
    
    // Create application thread
    plangthread_t *app_thread = plang_create_thread(file);
    if (!app_thread) {
        printf("plangx: execution failed!\n");
        return 0;
    }
    
    printf("%s\n", app_thread->instr);
    
    // Execution loop
    while (1) {
        
        // Execution loop
        char arg0 = *((app_thread->instr) + *(app_thread->instr_ptr));
        char arg1 = *((app_thread->instr) + *(app_thread->instr_ptr) + 1);
        char arg2 = *((app_thread->instr) + *(app_thread->instr_ptr) + 2);
        char arg3 = *((app_thread->instr) + *(app_thread->instr_ptr) + 3);
        
        switch (arg0) {
                
            case CMD_EXIT:
                printf("EXIT\n");
                return 1;
            case CMD_CMP:
                printf("CMP\n");
                *(app_thread->reg0) = *((app_thread->mem) + arg1) - *((app_thread->mem) + arg2);
                *(app_thread->instr_ptr) += 3;
                break;
            case CMD_JUMP:
                printf("JUMP\n");
                *(app_thread->instr_ptr) = arg1;
                break;
            case CMD_ADD:
                printf("ADD\n");
                *((app_thread->mem) + arg3) = *((app_thread->mem) + arg1) + *((app_thread->mem) + arg2);
                *(app_thread->instr_ptr) += 4;
                break;
            case CMD_JEQ:
                printf("JEQ\n");
                if (*(app_thread->reg0) == 0) {
                    *(app_thread->instr_ptr) = arg1;
                }
                else {
                    *(app_thread->instr_ptr) += 2;
                }
                break;
            case CMD_JNE:
                printf("JNE %d\n", *(app_thread->reg0));
                if (*(app_thread->reg0) != 0) {
                    *(app_thread->instr_ptr) = arg1;
                }
                else {
                    *(app_thread->instr_ptr) += 2;
                }
                break;
            case CMD_TEST:
                printf("TEST\n");
                *(app_thread->instr_ptr) += 1;
                break;
            case CMD_MOV:
                printf("MOV\n");
                *((app_thread->mem) + arg1) = arg2;
                *(app_thread->instr_ptr) += 3;
                break;
            default: // UNKNOWN OPERATION
                *(app_thread->instr_ptr) += 1;
                
        }
        
        if (*(app_thread->instr_ptr) >= app_thread->instr_size) {
            return 2;
        }
        
    }
    
}
