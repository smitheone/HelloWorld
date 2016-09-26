#include <stdio.h>

typedef unsigned int u32;

u32 btol(u32 var)
{
       union res{
               char byte[4];
               u32 val;
       };
       union res big,little;
       unsigned int i = 0;

       big.val = var;
       for(i = 0; i<4; i++){
               little.byte[i] = big.byte[3-i];
       }
       return little.val;
}

void main()
{
	unsigned int val = 0x12345678;
	printf("%08x\n",btol(val));
}
