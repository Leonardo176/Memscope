#ifndef MEMSCOPE_H
#define MEMSCOPE_H

#include <sys/types.h>

#include "meminfo.h"
#include "mempart.h"

// Define a type called 'memfunc' that is the samething as: void (*) (struct meminfo*)
typedef void (*memfunc)(struct meminfo*);

/** Main header of the memscope library!
 * This library allows you to get memory from the heap without worring to remember to use free because it will free it automatically for you!
 * Calling the function Memscope.alloc() you can get n bytes of memory that you can use inside the passed function!
**/
struct memscope_f {
	void (*alloc)(size_t n, memfunc func);
	void (*realloc)(struct meminfo* memory, size_t newSize);
};

extern const struct memscope_f Memscope;

#endif
