#ifndef MEMSCOPE_H
#define MEMSCOPE_H

#include <sys/types.h>

#include "meminfo.h"

struct memscope_f {
	void (*alloc)(size_t, void (*)(struct meminfo memory));
};

extern const struct memscope_f Memscope;

#endif
