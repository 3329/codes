#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd;
	fd=open("/dev/tty",O_RDWR);
	
	write(fd,"��Զ���ᱻ�ض���!\n",18);
	
	int fd2=100;
	/*
	int fd2=dup(fd);
	printf("fd:%d,fd2:%d\n",fd,fd2);
	*/
	dup2(fd,fd2);
	printf("fd:%d,fd2:%d\n",fd,fd2);
	write(fd2,"��Զ���ᱻ�ض���!\n",18);
	
	if(isatty(1)){
		printf("Hello�ض���!\n");
		write(1,"Killer\n",7);
	}
	else{
		printf("���ض���!\n");
	}
	
	close(fd);
	close(fd2);
	return 0;
}
