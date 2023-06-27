#include <assert.h>
#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

VM vm;

static void resetStack(void) {
    vm.stackTop = vm.stack;
}

void initVM(void) {
    resetStack();
}

void freeVM(void) {}

void push(Value value) {
    // Check for a stack overflow
    assert(vm.stackTop != vm.stack + STACK_MAX);
    *vm.stackTop = value;
    ++vm.stackTop;
}

Value pop(void) {
    --vm.stackTop;
    return *vm.stackTop;
}

static Value READ_CONSTANT_LONG(void) {
#define READ_BYTE() (*vm.ip++)
    int b0 = READ_BYTE();
    int b1 = READ_BYTE();
    int b2 = READ_BYTE();
    return vm.chunk->constants.values[(b2 << 16) + (b1 << 8) + b0];

#undef READ_BYTE
}

static InterpretResult run(void) {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
    do {                                                                       \
        Value b = pop();                                                       \
        Value a = pop();                                                       \
        push(a op b);                                                          \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, vm.ip - vm.chunk->code);
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(constant);
            break;
        }
        case OP_CONSTANT_LONG: {
            Value constant = READ_CONSTANT_LONG();
            push(constant);
            break;
        }
        case OP_NEGATE:
            *(vm.stackTop - 1) = -*(vm.stackTop - 1);
            break;
        case OP_ADD:
            BINARY_OP(+);
            break;
        case OP_SUBTRACT:
            BINARY_OP(-);
            break;
        case OP_MULTIPLY:
            BINARY_OP(*);
            break;
        case OP_DIVIDE:
            BINARY_OP(/);
            break;
        case OP_RETURN:
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}
