#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/un.h>

main()
{
	int fd;
	struct sockaddr_un addr;
	int r;	
	/*1.建立socket:socket*/
	fd=socket(AF_FILE,SOCK_DGRAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("socket OK!\n");
	
	/*2.构造通信地址:struct sockaddr_un*/
	addr.sun_family=AF_FILE;
	memcpy(addr.sun_path,"my.sock",strlen("my.sock")+1);
	
	/*3.连接到通信地址:connect*/
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("成功连接到socket文件!\n");
	
	/*4.发送数据到目标:write*/
	while(1){
		write(fd,"靓崽!",strlen("靓崽!"));
		sleep(1);
	}
	
	/*5.关闭socket:close*/
	close(fd);
}
