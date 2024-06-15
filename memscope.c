#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

#include "memscope.h"

void alloc(size_t size, void (*run)(struct meminfo memory))
{
	if(run != NULL && size > 0) {
		void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		run(Meminfo.init(addr, size));

		munmap(addr, size);
	}
}

const struct memscope_f Memscope = {
	.alloc = alloc
};
