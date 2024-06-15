#ifndef MEMINFO_H
#define MEMINFO_H

#include <stdbool.h>
#include <stddef.h>

// The structure for holding memory info
struct meminfo {
	void* addr;
	size_t size;
};

// Functions that can be used on the meminfo structure
struct meminfo_f {
	// Init: initialize the structure given the address and the size of memory
	struct meminfo (*init) (void* addr, size_t size);

	// isValid: checks if the info of the memory are valid (addr != NULL && size > 0)
	bool (*isValid) (struct meminfo meminfo);
};

extern const struct meminfo_f Meminfo;

#endif
