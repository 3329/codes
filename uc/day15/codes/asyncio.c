#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
void handle(int s)
{
	char buf[256];
	int r;
	if(s==34){
		r=read(0,buf,sizeof(buf)-1);
		if(r>0){
			buf[r]=0;
			printf("::%s",buf);
		}
	}
}

main()
{
	/*处理SIGIO信号，并且在信号处理中读取数据*/
	signal(34,handle);
	/*把0设置异步IO*/
	fcntl(0,F_SETFL,O_ASYNC);
	/*设置信号发送目标进程*/
	fcntl(0,F_SETOWN,getpid());
	/*设置发送的信号*/
	/*-D_GNU_SOURCE*/
	fcntl(0,F_SETSIG,34);
	while(1);
}
