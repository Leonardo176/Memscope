#include "mempart.h"

static bool memoryIsInside(struct meminfo parent, size_t offset, size_t size)
{
	return (offset > 0) && (size > 0) && ((offset + size) < parent.size);
}

struct mempart initRoot(struct meminfo meminfo)
{
	struct mempart root = {};

	if(Meminfo.isValid(meminfo)) {
		root.parent = NULL;
		root.current = meminfo;
	}

	return root;
}

struct mempart init(struct mempart parent, size_t offset, size_t size)
{
	struct mempart mempart = {};

	if(Mempart.isValid(parent) && memoryIsInside(parent.current, offset, size))
	{
		mempart.parent = &parent;

		mempart.current.addr = parent.current.addr + offset;
		mempart.current.size = size;
	}

	return mempart;
}

struct meminfo getRoot(struct mempart mempart)
{
	struct mempart* parent = mempart.parent;
	struct meminfo root = mempart.current;

	while(parent != NULL) {
		root = parent->current;
		parent = parent->parent;
	}

	return root;
}

bool isValid(struct mempart mempart)
{
	return Meminfo.isValid(mempart.current);
}

bool isRoot(struct mempart mempart)
{
	return Mempart.isValid(mempart) && mempart.parent == NULL;
}

const struct mempart_f Mempart = {
	.init = init,
	.initRoot = initRoot,

	.getRoot = getRoot,

	.isValid = isValid,
	.isRoot = isRoot
};
