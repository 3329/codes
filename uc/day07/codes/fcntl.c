#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	/*
	int fd;
	fd=fcntl(1,F_DUPFD,5);
	if(fd==-1) printf("%m\n"),exit(-1);
	write(fd,"Hello\n",6);
	printf("%d\n",getpid());
	while(1);*/
	int fd;
	fd=open("a.txt",O_WRONLY);
	if(fd==-1) printf("%m\n"),exit(-1);
	
	int status=fcntl(fd,F_GETFL);
	printf("%d\n",status);
	if(status == O_RDONLY)
	{
		printf("ֻ��!\n");
	}
	if(status & O_WRONLY)
	{
		printf("ֻд!\n");
	}
	if(status & O_RDWR)
	{
		printf("��д!\n");
	}
	
	return 0;			
}
