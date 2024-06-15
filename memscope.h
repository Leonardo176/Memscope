#ifndef MEMSCOPE_H
#define MEMSCOPE_H

#include <sys/types.h>

#include "meminfo.h"

/** Main header of the memscope library!
 * This library allows you to get memory from the heap without worring to remember to use free because it will free it automatically for you!
 * Calling the function Memscope.alloc() you can get n bytes of memory that you can use inside the passed function!
**/
struct memscope_f {
	void (*alloc)(size_t n, void (*func)(struct meminfo memory));
};

extern const struct memscope_f Memscope;

#endif
