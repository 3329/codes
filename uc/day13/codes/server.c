#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/un.h>
main()
{
	int serverfd;
	/*1.建立服务器socket*/
	serverfd=socket(AF_FILE,SOCK_STREAM,0);
	if(serverfd==-1) printf("socket:%m\n"),exit(-1);
	printf("socket ok!\n");
	/*2.构建一个通信地址*/
	struct sockaddr_un addr;
	addr.sun_family=AF_FILE;
	memcpy(addr.sun_path,"sock.dat",strlen("sock.dat")+1);
	/*3.绑定一个通信地址*/
	int r;
	r=bind(serverfd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("bind:%m\n"),close(serverfd),exit(-1);
	printf("bind ok!\n");
	/*4.监听服务器socket*/	
	r=listen(serverfd,10);
	if(r==-1) printf("listen:%m\n"),close(serverfd),exit(-1);
	printf("listen ok!\n");
	/*5.从监听列表得到新的连接者*/
	int fd;
	fd=accept(serverfd,NULL,NULL);
	if(fd==-1) printf("accept:%m\n"),close(serverfd),exit(-1);
	printf("有客户连接!\n");
	/*6.获取数据*/
	char buf[256];
	while(1){
		bzero(buf,sizeof(buf));
		read(fd,buf,sizeof(buf)-1);
		printf("::%s\n",buf);
	}
	/*7.关闭连接*/
	close(fd);
	/*8.关闭服务器socket*/
	close(serverfd);
}
