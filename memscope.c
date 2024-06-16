#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

#include "memscope.h"

static void* low_alloc(size_t size)
{
	void* addr = NULL;

	if(size > 0) {
		addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	}

	return addr;
}

static void low_free(struct meminfo memory)
{
	if(Meminfo.isValid(memory)) {
		munmap(memory.addr, memory.size);
	}
}

void alloc(size_t size, memfunc run)
{
	if(run != NULL && size > 0) {
		void* addr = low_alloc(size);
		
		struct meminfo memory = Meminfo.init(addr, size);

		run(&memory);

		low_free(memory);
	}
}

void memscope_realloc(struct meminfo* memory, size_t newSize)
{
	if(memory != NULL) {
		low_free(*memory);

		memory->addr = low_alloc(newSize);
		memory->size = newSize;
	}
}

void borrow(struct meminfo* memory, size_t offset, size_t size, memfunc run)
{
	if(memory != NULL) {
		struct mempart allMem = Mempart.initRoot(*memory);

		struct mempart partialMem = Mempart.init(allMem, offset, size);

		if(Mempart.isValid(partialMem)) {
			run(&partialMem.current);
		}
	}
}

const struct memscope_f Memscope = {
	.alloc = alloc,
	.realloc = memscope_realloc,
	.borrow = borrow
};
