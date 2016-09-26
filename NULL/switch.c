#include <stdio.h>
struct demo{
	char 	*str;
	int		num;
};
void main()
{
	char *str = "hello world!\n";
	struct demo *test = (struct demo*)malloc(sizeof(struct demo));
	test->num = 1;
	test = NULL;
	switch(test->num)
	{
		case 1:
			printf("str isn't null\n");
			break;
	}
}
