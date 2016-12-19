#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd;
	fd=open("/dev/tty",O_RDWR);
	
	write(fd,"永远不会被重定向!\n",18);
	
	int fd2=100;
	/*
	int fd2=dup(fd);
	printf("fd:%d,fd2:%d\n",fd,fd2);
	*/
	dup2(fd,fd2);
	printf("fd:%d,fd2:%d\n",fd,fd2);
	write(fd2,"永远不会被重定向!\n",18);
	
	if(isatty(1)){
		printf("Hello重定向!\n");
		write(1,"Killer\n",7);
	}
	else{
		printf("被重定向!\n");
	}
	
	close(fd);
	close(fd2);
	return 0;
}
