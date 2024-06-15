#ifndef MEMINFO_H
#define MEMINFO_H

#include <stdbool.h>
#include <stddef.h>

struct meminfo {
	void* addr;
	size_t size;
};

struct meminfo_f {
	struct meminfo (*init) (void* addr, size_t size);
	bool (*isValid) (struct meminfo meminfo);
};

extern const struct meminfo_f Meminfo;

#endif
