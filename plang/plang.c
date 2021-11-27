//
//  plang.c
//  plang
//
//  Created by Patrick Crowne on 11/25/21.
//
#include "plang.h"

// Sets up the thread registers
void plang_setup_thread_registers(plangthread_t* thread) {
    
    thread->reg0 =      (uint*) (thread->mem + 0x0000);
    thread->reg1 =      (uint*) (thread->mem + 0x0004);
    thread->reg2 =      (uint*) (thread->mem + 0x0008);
    thread->reg3 =      (uint*) (thread->mem + 0x000c);
    thread->reg4 =      (uint*) (thread->mem + 0x0010);
    thread->reg5 =      (uint*) (thread->mem + 0x0014);
    thread->reg6 =      (uint*) (thread->mem + 0x0018);
    thread->reg7 =      (uint*) (thread->mem + 0x001c);
    thread->stack =     (uint*) (thread->mem + 0x0020);
    thread->base =      (uint*) (thread->mem + 0x0024);
    thread->instr_ptr = (uint*) (thread->mem + 0x0028);
    thread->ret =       (uint*) (thread->mem + 0x002c);
    
    // Point to the top of the stack
    *(thread->stack) =  0x0030;
    *(thread->base) = 0x0030;
    // Address is different since it's different memory
    *(thread->instr_ptr) = 0x0000;
    
}

// Creates a new plang process and thread from the file
plangthread_t* plang_create_thread(FILE* file) {
    
    plangthread_t* thread = (plangthread_t*) malloc(sizeof(plangthread_t));
    // Find the file length
    fseek(file, 0L, SEEK_END);
    thread->instr_size = (uint) ftell(file);
    rewind(file);
    // load it into app instruction pointer
    thread->instr = malloc((size_t) (thread->instr_size));
    for (unsigned long i = 0; i < thread->instr_size; i++) {
        thread->instr[i] = fgetc(file);
    }
    // Initialize app memory
    thread->mem_size = MEMORY_START;
    thread->mem = malloc((size_t) (thread->mem_size));
    thread->mem_ptr = (uint*) thread->mem;
    
    // Initialze registers
    plang_setup_thread_registers(thread);
    
    // Return thread
    return thread;
    
}
