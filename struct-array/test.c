#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	struct test {
		unsigned int var8;
		unsigned char var6;
		unsigned char var5;
		unsigned int var1;
		unsigned int var3;
		unsigned int var4;
		unsigned char var2[];
	};
	unsigned char *p = "hello world!\n";

	struct test *var = malloc(sizeof(*var) + 128 * sizeof(var->var2[0]));
	
	var->var2[0] = 1;

	printf("sizeof(struct test): %d \n", sizeof(struct test));
	printf("sizeof(var): %d \n", sizeof(var));
	printf("sizeof(p): %d \n", sizeof(p));
	printf("strlen(p): %d \n", strlen(p));
}
