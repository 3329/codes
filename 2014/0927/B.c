#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>

main()
{
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (-1 == fd) 
	{
		printf("socket error.\n");
		exit(-1);
	}

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_path, "my.sock", strlen("my.sock") + 1);

	int r = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (-1 == r)
	{
		close(fd);
		printf("connect error.\n");
		exit(-1);
	}
	printf("connrct sucessful.\n");

	
	int count = 0;
	while (1)
	{
		char *data = "2东, 你妈叫你吃饭了...";
		write(fd, data, strlen(data));
		printf("%d\t%s\n", count++, data);
		sleep(1);
	}


	close(fd);
}

