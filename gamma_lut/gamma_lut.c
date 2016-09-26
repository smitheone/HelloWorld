#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
  
typedef unsigned char UNIT8; //用 8 位无符号数表示 0～255 之间的整数  
UNIT8 g_GammaLUT[256];//全局数组：包含256个元素的gamma校正查找表  
//Buildtable()函数对0-255执行如下操作：  
//①归一化、预补偿、反归一化;  
//②将结果存入 gamma 查找表。  
//从公式得fPrecompensation=1/gamma  
void BuildTable(float fPrecompensation )  
{  
    int i;  
    float f;  
    for( i=0;i<256;i++)  
    {  
        f=(i+0.5F)/256;//归一化  
        f=(float)pow(f,fPrecompensation);  
        g_GammaLUT[i]=(UNIT8)(f*256-0.5F);//反归一化  
    }  
}  
  
void GammaCorrectiom(UNIT8 src[],int iWidth,int iHeight,float fGamma,UNIT8 Dst[])  
{  
    int iCols,iRows;  
    BuildTable(1/fGamma);//gamma校正查找表初始化  
    //对图像的每个像素进行查找表矫正  
    for(iRows=0;iRows<iHeight;iRows++)  
    {  
        for(iCols=0;iCols<iWidth;iCols++)  
        {  
            Dst[iRows*iWidth+iCols]=g_GammaLUT[src[iRows*iWidth+iCols]];  
        }  
    }  
} 

void main(int argc, char **argv)
{
	unsigned int i;
	float gamma = strtof(argv[1], NULL);

	printf("gamma: %f\n", gamma);
	BuildTable(gamma);
	for (i = 0; i <256; i++) {
		if ((i !=0) && ((i + 1) % 16 == 0))
			printf("0x%02X,\n",g_GammaLUT[i]);
		else
			printf("0x%02X, ",g_GammaLUT[i]);
	}
	printf("\n");
}
