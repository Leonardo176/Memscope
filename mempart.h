#ifndef MEMPART_H
#define MEMPART_H

#include "meminfo.h"

struct mempart {
	struct mempart* parent;
	struct meminfo current;
};

struct mempart_f {
	struct mempart (*init) (struct mempart parent, size_t offset, size_t size);
	struct mempart (*initRoot) (struct meminfo root);

	struct meminfo (*getRoot) (struct mempart mempart);

	bool(*isValid) (struct mempart mempart);
	bool (*isRoot) (struct mempart mempart);
};

extern const struct mempart_f Mempart;

#endif
