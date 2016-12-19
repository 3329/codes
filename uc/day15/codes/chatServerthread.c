#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
int sfd;
int fds[4096];
int id=0;
struct sockaddr_in addr={0};

void *clienth(void *d){
	/*2.1.循环接受客户数据*/
	/*2.2.广播客户数据*/
}

main()
{	
	int i;
	for(i=0;i<4096;i++){
		fds[i]=-1;
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10000);
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	/*1.1.建立服务器socket*/
	/*1.2.绑定通信地址*/
	/*1.3.监听*/
	/*1.4.循环接受客户连接*/
	/*1.5.创建子线程*/
}

