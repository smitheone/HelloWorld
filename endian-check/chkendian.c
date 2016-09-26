#include <stdio.h>

int chkCPUendian()
{
	union{
		unsigned int a;
		unsigned char b;
	}c;
	c.a = 1;
	return (c.b == 1);
}

void main()
{
	unsigned int val = chkCPUendian();
	printf("return val = %d\n", val);
}
