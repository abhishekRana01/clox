#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"


int main(int argc, char const *argv[]) {
    initVM();
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 12);
    writeChunk(&chunk, constant, 12);

    writeChunk(&chunk, OP_RETURN, 11);

    // disassembleChunk(&chunk, "test chunk");
    // freeChunk(&chunk);
    interpret(&chunk);
    freeVM();
}
