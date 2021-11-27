//
//  plang.h
//  plang
//
//  Created by Patrick Crowne on 11/25/21.
//

#ifndef plang_h
#define plang_h

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_START        512
#define INSTRUCTION_START   0x1000
#define INSTRUCTION_SIZE    0x04

// Commands
#define CMD_NOP     0x00
#define CMD_TEST    0x11
#define CMD_EXIT    0x1f
#define CMD_MOV     0x01
#define CMD_READ    0x02

#define CMD_ADD     0x20

#define CMD_JUMP    0x03
#define CMD_JEQ     0x04
#define CMD_JNE     0x05
#define CMD_JGTE    0x06
#define CMD_JLTE    0x07
#define CMD_JGT     0x08
#define CMD_JLT     0x09

#define CMD_CMP     0x09

#define CMD_RETURN  0x50


#define uint unsigned int

// data types

// A thread in the plang virtual machine
typedef struct plangthread {
    
    uint* instr_ptr;
    uint* mem_ptr;
    uint* stack;
    uint* base;
    uint* ret;
    uint* reg0;
    uint* reg1;
    uint* reg2;
    uint* reg3;
    uint* reg4;
    uint* reg5;
    uint* reg6;
    uint* reg7;
    uint instr_size;
    uint mem_size;
    char *instr;
    char *mem;
    
} plangthread_t;

// A command in the plang virtual machine
typedef struct plangcmd {
    
    char instruction;
    char arg0;
    char arg1;
    char arg2;
    
} plangcmd_t;

// functions
plangthread_t* plang_create_thread(FILE*);

#endif /* plang_h */
