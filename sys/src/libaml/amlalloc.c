#include <u.h>
#include <libc.h>
#include <aml.h>

void*
amlalloc(usize n)
{
	return mallocz(n, 1);
}

void
amlfree(void *p)
{
	free(p);
}
