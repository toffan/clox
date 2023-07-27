#ifndef HG_7bb1201c_d4bd_47e9_a661_6018dc876702
#define HG_7bb1201c_d4bd_47e9_a661_6018dc876702

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef struct {
    ObjString* key;
    Value value;
} Entry;

typedef struct {
    int count;
    int capacity;
    Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableSet(Table* table, ObjString* key, Value value);
bool tableDelete(Table* table, ObjString* key);
void tableAddAll(Table* from, Table* to);
ObjString* tableFindString(
    Table* table, const char* chars, int length, uint32_t hash
);

#endif // HG_7bb1201c_d4bd_47e9_a661_6018dc876702
