#include <stdio.h>

void filename(int a,int *b)
{
		a = 3*a;
//		*b *= 3;
		b = b * 3;
}

int main()
{
		int x=4;int *y = &x;
		filename(x,y);
		printf("%d,%d\n",x,*y);
		return 0;
}
