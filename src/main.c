#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"


void repl() {
    char line[1024];
    while(true) {
        printf("> ");
        if(!fgets(line, sizeof(line), stdin)) {
            printf("End of input\n");
            break;
        }

        interpret(line);
    }
}

char* readFile(char* path) {
    FILE* file = fopen(path, "rb");

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(fileSize + 1);
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = "\0";

    fclose(file);
    return buffer;
}


void runFile(char *path) {
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if(result == INTERPRET_COMPILE_ERROR) exit(65);
    if(result == INTERPRET_RUNTIME_ERROR) exit(70);
}




int main(int argc, char const *argv[]) {
    initVM();
    if(argc == 1) {
        repl();
    } else if(argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage : clox [path]\n");
        exit(64);
    }
    // Chunk chunk;
    // initChunk(&chunk);
    //
    // int constant = addConstant(&chunk, 1.2);
    // writeChunk(&chunk, OP_CONSTANT, 12);
    // writeChunk(&chunk, constant, 12);
    //
    // constant = addConstant(&chunk, 2.4);
    // writeChunk(&chunk, OP_CONSTANT, 12);
    // writeChunk(&chunk, constant, 12);
    //
    // writeChunk(&chunk, OP_DIVIDE, 12);
    //
    // writeChunk(&chunk, OP_NEGATE, 13);
    //
    // writeChunk(&chunk, OP_RETURN, 11);
    // // disassembleChunk(&chunk, "test chunk");
    // // freeChunk(&chunk);
    // interpret(&chunk);
    freeVM();

}
