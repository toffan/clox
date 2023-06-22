#ifndef HG_1531cb0b_7826_4cbf_bb70_ffe43d200d3f
#define HG_1531cb0b_7826_4cbf_bb70_ffe43d200d3f

#include "common.h"

typedef double Value;

typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif  // HG_1531cb0b_7826_4cbf_bb70_ffe43d200d3f
