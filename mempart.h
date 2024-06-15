#ifndef MEMPART_H
#define MEMPART_H

#include "meminfo.h"

// The structure for a memory partition: a part of the allocated memory obtained with Memscope.alloc() or a part of another memory partition
struct mempart {
	//The parent where the memory was divided: this must be NULL if the memory partition is the whole allocated memory
	struct mempart* parent;

	// The current information of the memory partition
	struct meminfo current;
};

//The functions that we can use with this structure
struct mempart_f {
	// initialize the memory partition given its parent, an offset (bytes after the address of the parent) and the size of the memory partition to initialize
	struct mempart (*init) (struct mempart parent, size_t offset, size_t size);

	// initialize the memory partition as the whole memory (root memory partition)
	struct mempart (*initRoot) (struct meminfo root);

	// get the root of memory partition
	struct meminfo (*getRoot) (struct mempart mempart);

	bool(*isValid) (struct mempart mempart);
	bool (*isRoot) (struct mempart mempart);
};

extern const struct mempart_f Mempart;

#endif
