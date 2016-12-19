#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
main()
{
	int fd;
	
	printf("ruid:%d\teuid:%d\n",getuid(),geteuid());
	
	fd=open("a.txt",O_RDWR);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	
	close(fd);
}
