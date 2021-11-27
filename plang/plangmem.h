//
//  plangmem.h
//  plang
//
//  Created by Patrick Crowne on 11/26/21.
//

#ifndef plangmem_h
#define plangmem_h

#include <stdio.h>
#include "plang.h"

#define PLANG_MEM_FREE 0x0000
#define PLANG_MEM_USED 0x0001

typedef struct plangmemchunk {
    
    struct plangmemchunk* left;
    struct plangmemchunk* right;
    uint size;
    char status;
    char* data;
    
} plangmemchunk_t;

plangmemchunk_t* plangmem_allocate(plangthread_t*, uint);
void plangmem_free(plangthread_t*, plangmemchunk_t*);

#define PLANG_MEM_CHUNK_HEADER_SIZE ((sizeof(plangmemchunk_t*) * 2) + sizeof(uint) + sizeof(char))

#endif /* plangmem_h */
