#include <stdio.h>
#include <stdbool.h>


void main()
{
	struct test123 {
		int var1;
		bool var2 : 1;
	};

	struct test123 var = {
		.var1 = 123,
	};

	printf("var.var2: %d \n", var.var2);
}
