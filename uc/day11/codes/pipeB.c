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
	/*�򿪹ܵ�*/
	fd=open("a.pipe",O_RDWR);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*ѭ�����ݵ��ܵ�*/
	data=0;
	while(1)
	{
		
		r=write(fd,&data,sizeof(data));
		if(r==-1) break;
		data++;
		sleep(1);
	}
	/*�رչܵ�*/
	close(fd);
}
