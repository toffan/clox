#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

static void initLinesInfo(LinesInfo* linesinfo) {
    linesinfo->count = 0;
    linesinfo->capacity = 0;
    linesinfo->lines = NULL;
}

static void freeLinesInfo(LinesInfo* linesinfo) {
    FREE_ARRAY(Line, linesinfo->lines, linesinfo->capacity);
    initLinesInfo(linesinfo);
}

static void addLine(LinesInfo* linesinfo, int line_number) {
    if (linesinfo->count > 0 &&
        linesinfo->lines[linesinfo->count - 1].number == line_number) {
        linesinfo->lines[linesinfo->count - 1].length++;

    } else {
        if (linesinfo->capacity < linesinfo->count + 1) {
            int oldCapacity = linesinfo->capacity;
            linesinfo->capacity = GROW_CAPACITY(oldCapacity);
            linesinfo->lines = GROW_ARRAY(
                Line, linesinfo->lines, oldCapacity, linesinfo->capacity
            );
        }
        linesinfo->lines[linesinfo->count].length = 1;
        linesinfo->lines[linesinfo->count].number = line_number;
        linesinfo->count++;
    }
}

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initLinesInfo(&chunk->lines);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLinesInfo(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    addLine(&chunk->lines, line);
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int offset) {
    LinesInfo* linesinfo = &chunk->lines;
    int i = 0;
    while (1) {
        if (linesinfo->lines[i].length >= offset) {
            return linesinfo->lines[i].number;
        } else {
            offset -= linesinfo->lines[i].length;
        }
    }
}
