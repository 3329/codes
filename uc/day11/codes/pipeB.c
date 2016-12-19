#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
main()
{
	int r;
	int fd;
	int data;
	/*打开管道*/
	fd=open("a.pipe",O_RDWR);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*循环数据到管道*/
	data=0;
	while(1)
	{
		
		r=write(fd,&data,sizeof(data));
		if(r==-1) break;
		data++;
		sleep(1);
	}
	/*关闭管道*/
	close(fd);
}
