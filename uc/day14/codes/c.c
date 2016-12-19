#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
main()
{
	char buf[256];
	int r;
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1) exit(-1);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.85");
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) exit(-1);
	
	while (1)
	{
		r=recv(fd,buf,sizeof(buf)-1,0);
		if(r<=0) exit(-1);
		buf[r]=0;
		printf("%s\n", buf);
	}

	// close
	close(fd);
}

