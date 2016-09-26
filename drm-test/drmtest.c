#include <stddef.h>
#include <assert.h>
#include <drm/drm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/** Open the first DRM device we can find, searching up to 16 device nodes */
int drm_open_any(void)
{
	char name[20];
	int i, fd;

	for (i = 0; i < 16; i++) {
		sprintf(name, "/dev/dri/card%d", i);
		fd = open(name, O_RDWR);
		if (fd != -1)
			return fd;
	}
	abort();
}

#if 1
/**
 * Open the first DRM device we can find where we end up being the master.
 */
int drm_open_any_master(void)
{
	char name[20];
	int i, fd;

	for (i = 0; i < 16; i++) {
		drm_client_t client;
		drm_version_t version;
		int ret;

		printf("%d\n",i);
		sprintf(name, "/dev/dri/card%d", i);
		fd = open(name, O_RDWR);
		if (fd < 0)
			continue;

		/* Check that we're the only opener and authed. */
		client.idx = 0;
		ret = ioctl(fd, DRM_IOCTL_GET_CLIENT, &client);
		assert (ret == 0);
		if (!client.auth) {
			close(fd);
			continue;
		}
		printf("idx:%d,auth:%d,pid:%d,uid:%d,magic:%d,iocs:%d\n",
						client.idx,client.auth,client.pid,client.uid,client.magic,client.iocs);
//		ret = drmGetVersion(fd);
//		if(ret == 0)
//		{
//			printf("can't get version\n");
//		}
//		ret = ioctl(fd, DRM_IOCTL_VERSION, &version);
//		assert (ret == 0);
//		printf("%s\n",version.name);

		client.idx = 1;
		ret = ioctl(fd, DRM_IOCTL_GET_CLIENT, &client);
		if (ret != -1 || errno != EINVAL) {
			close(fd);
			continue;
		}
		printf("idx:%d,auth:%d,pid:%d,uid:%d,magic:%d,iocs:%d\n",
						client.idx,client.auth,client.pid,client.uid,client.magic,client.iocs);
//		ret = ioctl(fd, DRM_IOCTL_VERSION, &version);
//		assert (ret == 0);
//		printf("%s\n",version.name);
		return fd;
	}
	printf("Couldn't find an un-controlled DRM device\n");
	abort();
}
#endif

void main()
{
	drm_open_any_master();
}
