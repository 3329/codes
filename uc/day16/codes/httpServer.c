#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
main()
{
	int fd;
	struct sockaddr_in addr;
	char buf[4096];
	int r;
	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9999);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	
	fd=socket(AF_INET,SOCK_STREAM,0);
	bind(fd,(struct sockaddr*)&addr,sizeof addr);
	listen(fd,10);
	
	int cfd;
	cfd=accept(fd,0,0);
	
	while(1){
		r=recv(cfd,buf,sizeof(buf)-1,0);
		if(r<=0) break;
		buf[r]=0;
		printf("%s\n",buf);
	}
	
	
	
	close(cfd);
	close(fd);
}

