#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int fd;
	int r;
	fd=open("a.txt",O_RDWR);
	if(fd==-1) printf("%m\n"),exit(-1);
	
	r=lseek(fd,100,SEEK_END);
	printf("%d\n",r);
	
	//r=write(fd,"hello",5);
	//printf("д������ݳ���:%d\n",r);
	close(fd);
	return 0;
}
