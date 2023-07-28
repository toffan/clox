#ifndef HG_06fc2a35_e2f6_4481_a312_c299d866dcbb
#define HG_06fc2a35_e2f6_4481_a312_c299d866dcbb

#include "object.h"
#include "vm.h"

ObjFunction* compile(const char* source);
void markCompilerRoots(void);

#endif // HG_06fc2a35_e2f6_4481_a312_c299d866dcbb
