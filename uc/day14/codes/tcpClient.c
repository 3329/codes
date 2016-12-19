#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

main()
{
	int fd;
	struct sockaddr_in addr;
	int r;
	/*1.建立socket*/
	fd=socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("建立socket成功!\n");
	
	/*2.连接到服务器*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(8888);
	inet_aton("192.168.99.85",&addr.sin_addr);
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("已经连接到服务器!\n");
	/*3.发送数据*/
	r=send(fd,"maomaoyu!",strlen("maomaoyu!"),0);
	if(r==-1) {
		printf("发送失败!\n");
	}
	else{
		printf("发送成功!\n");
	}	
	/*4.关闭socket*/
	close(fd);
}
