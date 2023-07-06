#include <stdlib.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

void* reallocate(
    void* pointer, __attribute__((unused)) size_t oldSize, size_t newSize
) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL) {
        exit(1);
    }
    return result;
}

static void freeObject(Obj* object) {
    switch (object->type) {
    case OBJ_STRING: {
        ObjString* string = (ObjString*)object;
        if (string->owned) {
            // Discard const qualifier because object is owned
            FREE_ARRAY(char, (char*)string->chars, string->length + 1);
        }
        FREE(ObjString, object);
        break;
    }
    }
}

void freeObjects(void) {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }
}
