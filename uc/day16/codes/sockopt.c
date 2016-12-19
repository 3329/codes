#include <stdio.h>
#include <sys/socket.h>
main()
{
	int fd;
	int optval=16*4096;/*缓冲大小*/
	socklen_t optlen=sizeof(int);
	
	fd=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&optval,sizeof(int));
	
	getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&optval,&optlen);
	
	printf("缓冲长度:%d\n",optval);
	
	close(fd);
	
	
}
