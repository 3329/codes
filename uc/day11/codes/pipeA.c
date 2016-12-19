#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

main()
{
	int r;
	int fd;
	
	int  data;
	/*建立管道文件*/
	r=mkfifo("a.pipe",0666);
	if(r==-1) printf("mkfifo:%m\n"),exit(-1);
	/*打开管道*/
	fd=open("a.pipe",O_RDWR);
	if(fd==-1) printf("open:%m\n"),exit(-1);
	/*循环从管道读取数据*/
	while(1){
		r=read(fd,&data,sizeof(data));
		if(r<=0) break;
		printf("::%d\n",data);
	}
	/*关闭管道*/
	close(fd);
	/*删除管道文件*/
	unlink("a.pipe");
}

