#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/un.h>

int main()
{
	int serverfd;

	serverfd = socket(AF_FILE, SOCK_STREAM, 0);
	if (serverfd == -1) printf("socket: %m\n"), exit(-1);
	printf("socket ok!\n");

	struct sockaddr_un addr;
	addr.sun_family = AF_FILE;
	memcpy(addr.sun_path, "sock.data", strlen("sock.data") + 1);
	
	int r = bind(serverfd, (struct sockaddr*)&ddr, sizeof(addr));
	if (r == -1)
	{
		printf("bind: %m\n"), close(serverfd), exit(-1);
	}
	printf("bind ok!\n");

	r = listen(serverfd, 10);
}

