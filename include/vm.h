#ifndef HG_8608b79b_2cda_4875_a505_f4c3758b9d72
#define HG_8608b79b_2cda_4875_a505_f4c3758b9d72

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256


typedef struct {
  Chunk* chunk;
  uint8_t* ip;
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM(void);
void freeVM(void);
InterpretResult interpret(const char* source);
void push(Value value);
Value pop(void);

#endif  // HG_8608b79b_2cda_4875_a505_f4c3758b9d72
