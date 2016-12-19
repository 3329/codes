#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <linux/un.h>
#include <stdlib.h>


int main()
{
	// 1. create socket fd
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (-1 == fd)
	{
		printf("socket error\n");
		exit(-1);
	}

	// 2. construct communicaty Addr
	struct sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX; 
	memcpy(addr.sun_path, "my.sock", strlen("my.sock") + 1);

	// 3. bind
	int r = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (-1 == r) 
	{
		printf("bind error.\n");
		exit(-1);
	}


	// 4. read/write
	char buf[256];
	while (1) 
	{
		bzero(buf, sizeof(buf));
		read(fd, buf, sizeof(buf));
		printf("read> %s\n", buf);
	}

	// 5. close socket fd
	close(fd);
	unlink("my.sock");

	return 0;
}
