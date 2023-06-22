#ifndef HG_ebdcf7ae_1bc9_4405_ae2c_e5d0535e63f8
#define HG_ebdcf7ae_1bc9_4405_ae2c_e5d0535e63f8

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

#endif  // HG_ebdcf7ae_1bc9_4405_ae2c_e5d0535e63f8
