#ifndef HG_1749e240_f0cb_4d30_a919_742294a16ada
#define HG_1749e240_f0cb_4d30_a919_742294a16ada

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(type, pointer, oldCount, newCount) (type*)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))
#define FREE_ARRAY(type, pointer, oldCount) reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif  // HG_1749e240_f0cb_4d30_a919_742294a16ada
