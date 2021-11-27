//
//  plangmem.c
//  plang
//
//  Created by Patrick Crowne on 11/26/21.
//

#include "plangmem.h"

// Allocates size_bytes number of bytes to a new memory chunk
plangmemchunk_t* plangmem_allocate(plangthread_t* thread, uint size_bytes) {
    
    // Allocate this chunk of memory at the end of the memory heap
    plangmemchunk_t* new_mem = (plangmemchunk_t*) thread->mem_ptr;
    new_mem->status = PLANG_MEM_USED;
    // move the end of memory pointer up
    thread->mem_ptr += (PLANG_MEM_CHUNK_HEADER_SIZE + size_bytes);
    new_mem->data = (char*) (new_mem + PLANG_MEM_CHUNK_HEADER_SIZE);
    // Return memory address
    return new_mem;
    
}

// Deallocates a memory chunk
void plangmem_free(plangthread_t* thread, plangmemchunk_t* memory_chunk) {
    
    if (memory_chunk->status == PLANG_MEM_USED) {
        memory_chunk->status = PLANG_MEM_FREE;
    }
    else {
        
    }
    
}
