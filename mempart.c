#include "mempart.h"

#include <stdint.h>

static size_t safe_sum(size_t s1, size_t s2)
{
	bool overflow = (s1 + s2) < s1 || (s1 + s2) < s2;

	if(overflow) {
		return SIZE_MAX;
	}else return s1 + s2;
}

// This function checks if the given offset (bytes after the address of the parent) with the given size is inside the parent memory
static bool isMemoryInside(struct meminfo parent, size_t offset, size_t size)
{
	return (offset >= 0) && (size > 0) && (safe_sum(offset,  size) <= parent.size);
}

struct mempart mempart_initRoot(struct meminfo meminfo)
{
	struct mempart root = {};

	if(Meminfo.isValid(meminfo)) {
		root.parent = NULL;
		root.current = meminfo;
	}

	return root;
}

struct mempart mempart_init(struct mempart parent, size_t offset, size_t size)
{
	struct mempart mempart = {};

	if(Mempart.isValid(parent) && isMemoryInside(parent.current, offset, size))
	{
		mempart.parent = &parent;

		mempart.current.addr = parent.current.addr + offset;
		mempart.current.size = size;
	}

	return mempart;
}

struct meminfo mempart_getRoot(struct mempart mempart)
{
	struct mempart* parent = mempart.parent;
	struct meminfo root = mempart.current;

	while(parent != NULL) {
		root = parent->current;
		parent = parent->parent;
	}

	return root;
}

bool mempart_isValid(struct mempart mempart)
{
	return Meminfo.isValid(mempart.current);
}

bool mempart_isRoot(struct mempart mempart)
{
	return Mempart.isValid(mempart) && mempart.parent == NULL;
}

const struct mempart_f Mempart = {
	.init = mempart_init,
	.initRoot = mempart_initRoot,

	.getRoot = mempart_getRoot,

	.isValid = mempart_isValid,
	.isRoot = mempart_isRoot
};
