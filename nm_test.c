#include <stdio.h>


void test_1()
{
    printf("%s\n",__func__);
}
void test_2()
{
    printf("%s\n",__func__);
}
void test_3()
{
        printf("%s\n",__func__);
}

void main()
{
    test_1();
    printf("hello world!\n");    
}
