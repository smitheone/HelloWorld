#include <stdio.h>
#include <fcntl.h>

#define fbdev "/dev/fb0"

void main()
{
	int fd;
	fd = open(fbdev, O_RDWR);
	if (fd < 0)
		printf("failed to open fbdev\n");
	else
		printf("succeed to open fbdev\n");
}
