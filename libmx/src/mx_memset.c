#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
	unsigned char	*temp;
	temp = (unsigned char *)b;
	while (len--)
	{
		*temp = (unsigned char)c;
		temp++;
	}
	return b;
}
