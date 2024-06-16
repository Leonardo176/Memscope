#include "meminfo.h"

struct meminfo meminfo_init(void* addr, size_t size)
{
	struct meminfo meminfo;
	
	meminfo.addr = addr;
	meminfo.size = size;

	return meminfo;
}

bool meminfo_isValid(struct meminfo meminfo)
{
	return meminfo.addr != NULL && meminfo.size > 0;
}

const struct meminfo_f Meminfo = {
	.init = meminfo_init,
	.isValid = meminfo_isValid,
};

