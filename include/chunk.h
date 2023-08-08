#ifndef HG_ebdcf7ae_1bc9_4405_ae2c_e5d0535e63f8
#define HG_ebdcf7ae_1bc9_4405_ae2c_e5d0535e63f8

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
    OP_CONSTANT,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_POP,
    OP_GET_LOCAL,
    OP_SET_LOCAL,
    OP_GET_GLOBAL,
    OP_DEFINE_GLOBAL,
    OP_SET_GLOBAL,
    OP_GET_UPVALUE,
    OP_SET_UPVALUE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_NEGATE,
    OP_PRINT,
    OP_JUMP,
    OP_JUMP_IF_FALSE,
    OP_LOOP,
    OP_CALL,
    OP_CLOSURE,
    OP_CLOSE_UPVALUE,
    OP_RETURN,
} OpCode;

typedef struct {
    int number;
    int length;
} Line;

typedef struct {
    int count;
    int capacity;
    Line* lines;
} LinesInfo;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    LinesInfo lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void writeConstant(Chunk* chunk, Value value, int line);
int addConstant(Chunk* chunk, Value value);

int getLine(Chunk* chunk, int offset);

#endif // HG_ebdcf7ae_1bc9_4405_ae2c_e5d0535e63f8
